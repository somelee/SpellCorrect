 ///
 /// @file    DictProducer.h
 /// @author  lee(847394837@qq.com)
 /// @date    2017-03-30 16:25:18
 ///
 
#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::map;

class DictProducer
{
public:
	DictProducer(const string & dir);
	//DictProducer(const string & dir,SplitTool * SplitTool);//构造函数，中文处理
	
	void build_dir();//创建英文词典
	void build_cn_dir();//创建中文词典

	void store_dict(const char * filePath);//将词典写入文件
	void show_files() const;//测试，查看文件路径

private:
	void get_files();//获取语料文件夹下所有文件的绝对路径写入_files
private:
	string _dir;//语料库文件的存放文件夹
	vector<string> _files;//语料库文件的绝对路径
	map<string,int> _dict;//词频统计
	//SplitTool * _splitTool;//分词类

};

#endif
