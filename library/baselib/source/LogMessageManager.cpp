#include "basic_defs.h"
#include "LogMessageManager.h"

#include <iostream>

LogMessageManager::LogMessageManager()
{
	m_output = [](const string & message)
	{
		std::cout << message << std::endl;
	};
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
	if (m_output)
	{
		m_output(message);	
	}
}

