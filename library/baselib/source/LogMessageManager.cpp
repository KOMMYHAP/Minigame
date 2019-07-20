#include "basic_defs.h"
#include "LogMessageManager.h"

#define _AMD64_
#include <processthreadsapi.h>
#include <debugapi.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include <ctime>

LogMessageManager::LogMessageManager()
{
	namespace fs = std::filesystem;
	auto path = fs::current_path() / fs::path("minigame_log.txt");
	if (fs::exists(path))
	{
		fs::path to;
		for (size_t i = 0; i < 999999; ++i)
		{
			auto && name = path.stem().string() + "_" + std::to_string(i) + ".txt";
			to = path.parent_path() / name;
			if (!fs::exists(to))
			{
				break;
			}
		}
		if (fs::copy_file(path, to))
		{
			fs::remove(path);
		}
	}

	auto filename = path.string();
	m_logFilename = filename;

	m_output = [filename](const string & message)
	{
		std::ofstream f(filename, std::ios_base::app | std::ios_base::out);
		assert(f.is_open());
		if (f.is_open())
		{
			f << message << std::endl;	
		}
	};
}

string LogMessageManager::GetMessagePrefix() const
{
	string prefix;

	auto _id = GetCurrentThreadId();
	auto id = std::to_string(static_cast<uint64_t>(_id)) + ": ";

	auto _time = std::time(nullptr);
	string time(50, 0);

	tm tm;
	auto err = localtime_s(&tm, &_time);
	if (!err)
	{
		auto bytes = std::strftime(time.data(), time.size() - 1, "[%T]: ", &tm);
		time.resize(bytes);
	}

	auto place = "[file: \"" + m_file + "\", line: " + std::to_string(m_line) + "] ";

	switch (m_messageType)
	{
	case Type::PLAIN:
		return time + "";
	case Type::WARNING:
		return time + "WARNING: ";
	case Type::ERROR:
		return time + place + "ERROR: ";
	case Type::FATAL_ERROR:
		return time + id + place + "FATAL ERROR: ";
	default:
		return "";
	}
}

LogMessageManager::~LogMessageManager()
{

}

void LogMessageManager::PrepareMessage(Type messageType, size_t line, const string& file)
{
	m_messageType = messageType;
	m_line = line;
	m_file = file;
}

void LogMessageManager::WriteMessage(const string& message)
{
	if (m_isFirstMessage)
	{
		string time(250, 0);
		auto _time = std::time(nullptr);
		std::tm tm;
		localtime_s(&tm, &_time);
		auto bytes = std::strftime(time.data(), time.size(), "%c", &tm);
		time.resize(bytes);

		string prefix(25, '=');
		string header = prefix + " " + time + " " + prefix + "\n";
		m_output(header);

		m_isFirstMessage = false;
	}

	auto && prefix = GetMessagePrefix();
	if (m_output)
	{
		m_output(prefix + message);
#ifdef _DEBUG
		auto t = prefix + message + "\n";
		OutputDebugStringA(t.c_str());
#endif
	}
}

