// AutoUpdate.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <io.h>
#include <Windows.h>
using namespace std;

#include "RemovalUDisk.h"


int getExe(string path, vector<string>& files)
{
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	string p = path + "\\*.exe";
	printf("getExe : %s\n", p.c_str());

	int n = 0;
	struct _finddata_t fileinfo;
	if ((hFile = _findfirst(p.c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				printf("find : %s\n%s\n", p.c_str(), files.end());
				n++;
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return n;
}


int _tmain(int argc, _TCHAR* argv[])
{
	for (int i=0; i<argc; ++i)
	{
		printf("%s\n", argv[i]);
	}

	Sleep(5000);

	char cmd[256] = { 0 };
	sprintf(cmd, "copy \"%c:\\update\\*.*\" \"%s\"", argv[2][0], argv[1]);
	printf("copy : %s\n", cmd);
	system(cmd);


	SetCurrentDirectory(argv[1]);
	vector<string> f;
	if(getExe(argv[1], f) > 0)
	{
		printf("WinExec : %s\n", f.at(0));
		WinExec(f.at(0).c_str(), SW_SHOW);
	}

	RemovalUDisk(argv[2][0]);


	return 0;
}

