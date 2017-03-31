 ///
 /// @file    DictProducer.cc
 /// @author  lee(847394837@qq.com)
 /// @date    2017-03-30 17:17:31
 ///
 
#include "DictProducer.h"
#include "Mylog.h"
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::vector;
using std::map;
using std::pair;

DictProducer::DictProducer(const string & dir)//构造函数，初始化语料路径
:_dir(dir)
{}

void DictProducer::build_dir()//建立词频库
{
	get_files();//把语料文件夹内的文件名都写入到_files里
	string str;//临时存储每行的内容
	for(auto & f : _files )
	{
		str.assign(f).append(" is reading...");
		LogInfo(str.c_str());
		//把语料全部一行一行的读入到内存中
		vector<string> vecStr;//把语料的每行写入vector
		ifstream ifs(f);//打开一个语料文件
		if(!ifs.good())
		{
			string error = f + "open error";
			LogWarn(error.c_str());
		}
		while(getline(ifs,str))
		{
			vecStr.push_back(str);
		}
		ifs.close();

		//处理此次读入的一篇语料
		for(auto & elem : vecStr)//把每行内容取出来
		{
			for(auto & c : elem)//取出每个字符
			{
				if(c < 97)//若为大写改为小写
				{
					c += 32;
				}
				if(97 > c || c > 122)//除小写字母外，都改为空格
				{
					c = 32;
				}
				istringstream iss(elem);//分单词
				while(iss >> str)//建立词频词库
				{
					map<string,int>::iterator mit;
					mit = _dict.find(str);
					if(mit == _dict.end())
					{
						_dict[str] = 1;
					}else{
						++mit->second;
					}
				}
			}
		}
	}
}

void DictProducer::store_dict(const char * filePath)//将词频库写入到磁盘
{
	//build_dir();
	ofstream ofs(filePath);//打开要把词频写入的文件
	if(!ofs.good())//打开失败处理
	{
		string error;
		error.assign(filePath).append(" open error.");
		LogWarn(error.c_str());
		ofs.close();
	}
	for(auto & wdct : _dict)//写入文件
	{
		ofs << wdct.first << " " << wdct.second << endl;
	}
	ofs.close();
}

void DictProducer::show_files() const
{
	for(auto & path : _files)
	{
		cout << path << endl;
	}
}

void DictProducer::get_files()
{
//	if(-1 == chdir(_dir.c_str()))
//	{
//		LogWarn("FilePath error");
//		exit(-1);
//	}
//	struct stat buf;
	DIR *dir;
	dir = opendir(_dir.c_str());
	if(NULL == dir)
	{
		LogWarn("opendir open error.");
		exit(-1);
	}
	struct dirent *p;
	off_t pos;
	string path;
	while(NULL!= (p = readdir(dir)))
	{
//		memset(&buf,0,sizeof(buf));
//		int ret;
//		ret = stat(p->d_name,&buf);
//		if(-1 == ret)
//		{
//			LogWarn("stat error");
//			perror("stat");
//			exit(-1);
//		}
		if(strcmp(p->d_name,".") && strcmp(p->d_name,".."))
		{
			path.assign(_dir).append(p->d_name);
			_files.push_back(path);
		}
	}
}


