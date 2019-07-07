#pragma once

#include <boost/format.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include "Singleton.h"

class LogMessageManager : public Singleton<LogMessageManager>
{
	friend class Singleton<LogMessageManager>;
	~LogMessageManager();

public:
	enum class Type
	{
		PLAIN,
		WARNING,
		ERROR,
		FATAL_ERROR
	};

	using Callback = std::function<void(const string &)>;

	void PrepareMessage(Type messageType, size_t line, const string & file);
	
	void SetCallback(const Callback & callback) { m_output = callback; }
	Callback GetCallback() const { return m_output; }

	template <typename... Args>
	void WriteMessage(const string & format, Args && ...args);

	void WriteMessage(const string & message);

private:
	LogMessageManager();

	template <typename T, typename... Args>
	void WriteMessage(boost::format & format, T && arg, Args && ...args);

	template <typename T>
	void WriteMessage(boost::format & fmt, T && arg);

	string GetMessagePrefix() const;

	Callback		m_output;
	Type			m_messageType {Type::PLAIN};
	size_t			m_line {0};
	string			m_file;

	bool			m_isFirstMessage {true};
	string			m_logFilename;
};

template <typename ... Args>
void LogMessageManager::WriteMessage(const string & format, Args&&... args)
{
	boost::format fmt;
	try
	{
		fmt = boost::format(format);
	} catch (const boost::exception & e)
	{
		WriteMessage(boost::diagnostic_information(e));
		return;
	}
	WriteMessage(fmt, std::forward<Args>(args)...);
}

template <typename T, typename ... Args>
void LogMessageManager::WriteMessage(boost::format& format, T && arg, Args&&... args)
{
	WriteMessage(format.operator%(std::forward<T>(arg)), std::forward<Args>(args)...);
}

template <typename T>
void LogMessageManager::WriteMessage(boost::format& fmt, T&& arg)
{
	WriteMessage(fmt.operator%(std::forward<T>(arg)).str());	
}

#define LOG_MESSAGE \
	LogMessageManager::Instance()->PrepareMessage(LogMessageManager::Type::PLAIN, __LINE__, __FILE__), \
	LogMessageManager::Instance()->WriteMessage

#define LOG_WARNING \
	LogMessageManager::Instance()->PrepareMessage(LogMessageManager::Type::WARNING, __LINE__, __FILE__), \
	LogMessageManager::Instance()->WriteMessage

#define LOG_ERROR \
	LogMessageManager::Instance()->PrepareMessage(LogMessageManager::Type::ERROR, __LINE__, __FILE__), \
	LogMessageManager::Instance()->WriteMessage

#define LOG_FATAL_ERROR \
	LogMessageManager::Instance()->PrepareMessage(LogMessageManager::Type::FATAL_ERROR, __LINE__, __FILE__), \
	LogMessageManager::Instance()->WriteMessage