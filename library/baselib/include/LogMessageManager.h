#pragma once

#include <boost/format.hpp>
#include <boost/exception/diagnostic_information.hpp>

class LogMessageManager
{
public:
	enum class Type
	{
		PLAIN,
		WARNING,
		ERROR,
		FATAL_ERROR
	};

	using Callback = std::function<void(const string &)>;

	LogMessageManager();
	~LogMessageManager();

	void PrepareMessage(Type messageType, size_t line, const string & file);
	
	void SetCallback(const Callback & callback) { m_output = callback; }
	Callback GetCallback() const { return m_output; }

	template <typename... Args>
	void WriteMessage(const string & format, Args && ...args);

	void WriteMessage(const string & message);

private:
	template <typename T, typename... Args>
	void WriteMessage(boost::format & format, T && arg, Args && ...args);

	template <typename T>
	void WriteMessage(boost::format & fmt, T && arg);

	Callback		m_output;
	Type		m_messageType;
	size_t			m_line;
	string			m_file;
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