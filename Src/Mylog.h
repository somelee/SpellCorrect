 ///
 /// @file    Mylog.h
 /// @author  lee(847394837@qq.com)
 /// @date    2017-02-27 17:00:33
 ///
 
#ifndef __MYLOG_H__
#define __MYLOG_H__

#include <iostream>
#include <string>
#include <log4cpp/Category.hh>

using std::cout;
using std::endl;
using std::string;
using namespace log4cpp;

class Mylog
{
public:
	static Mylog * setLogPath(const char*);
	static Mylog * getInstance();
	static void destroy();

	void warn(const string & msg);
	void error(const string & msg);
	void info(const string & msg);
	void debug(const string & msg);

private:
	Mylog();
	Mylog(const char*);
	~Mylog();
private:
	static Mylog * _pInstance;
	Category & _cat;
};

inline string int2str(int num)
{
	std::ostringstream oss;
	oss << num;
	return oss.str();
}

#define postfix(msg) \
	string(string("\n").append(msg)).append("\n[").append(__FILE__)\
			   .append(":").append(__FUNCTION__)\
			   .append(":").append(int2str(__LINE__)).append("]")

inline void logPath(const char* msg)
{
	Mylog * plog = Mylog::setLogPath(msg);
}

inline void logWarn(const string & msg)
{
	Mylog * plog = Mylog::getInstance();
	plog->warn(msg);
}

inline void logError(const string & msg)
{
	Mylog * plog = Mylog::getInstance();
	plog->error(msg);
}

inline void logInfo(const string & msg)
{
	Mylog * plog = Mylog::getInstance();
	plog->info(msg);
}

inline void logDebug(const string & msg)
{
	Mylog * plog = Mylog::getInstance();
	plog->debug(msg);
}

#define LogPath(msg) logPath(msg)
#define LogWarn(msg) logWarn(postfix(msg))
#define LogError(msg) logError(postfix(msg))
#define LogInfo(msg) logInfo(postfix(msg))
#define LogDebug(msg) logDebug(postfix(msg))


#endif
