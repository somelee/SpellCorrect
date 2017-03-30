 ///
 /// @file    Mylog.cc
 /// @author  lee(847394837@qq.com)
 /// @date    2017-02-27 17:10:46
 ///
 
#include "Mylog.h"

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <iostream>
using std::cout;
using std::endl;

Mylog * Mylog::_pInstance = NULL;

Mylog * Mylog::setLogPath(const char* path)
{
	if(NULL == _pInstance)
	{
		_pInstance = new Mylog(path);
	}else{
		LogWarn("setLogPath error.");
		cout << "setLogPath error." << endl 
			 << "Path = ./Mylog.log" << endl;
	}
	return _pInstance;
}

Mylog * Mylog::getInstance()
{
	if(NULL == _pInstance)
	{
		_pInstance = new Mylog;
	}
	return _pInstance;
}

void Mylog::destroy()
{
	if(_pInstance)
	{
		Category::shutdown();
		delete _pInstance;
	}
}

Mylog::Mylog()
:_cat(Category::getRoot().getInstance("Mylog.log"))
{
	PatternLayout * ptn1 = new PatternLayout();
	ptn1->setConversionPattern("%d:%c %p %x:%m%n");
	PatternLayout * ptn2 = new PatternLayout();
	ptn2->setConversionPattern("%d:%c %p %x:%m%n");

	OstreamAppender * osApp = new OstreamAppender("osApp",&cout);
	osApp->setLayout(ptn1);

	FileAppender * fileApp = new FileAppender("fileApp","Mylog.log");
	fileApp->setLayout(ptn2);

	_cat.addAppender(osApp);
	_cat.addAppender(fileApp);

	_cat.setPriority(Priority::DEBUG);
}


Mylog::Mylog(const char * path)
:_cat(Category::getRoot().getInstance(path))
{
	PatternLayout * ptn1 = new PatternLayout();
	ptn1->setConversionPattern("%d:%c %p %x:%m%n");
	PatternLayout * ptn2 = new PatternLayout();
	ptn2->setConversionPattern("%d:%c %p %x:%m%n");

	OstreamAppender * osApp = new OstreamAppender("osApp",&cout);
	osApp->setLayout(ptn1);

	FileAppender * fileApp = new FileAppender("fileApp",path);
	fileApp->setLayout(ptn2);

	_cat.addAppender(osApp);
	_cat.addAppender(fileApp);

	_cat.setPriority(Priority::DEBUG);
}

Mylog::~Mylog()
{}

void Mylog::warn(const string & msg)
{
	_cat.warn(msg.c_str());
}

void Mylog::debug(const string & msg)
{
	_cat.debug(msg.c_str());
}

void Mylog::error(const string & msg)
{
	_cat.error(msg.c_str());
}

void Mylog::info(const string & msg)
{
	_cat.info(msg.c_str());
}
