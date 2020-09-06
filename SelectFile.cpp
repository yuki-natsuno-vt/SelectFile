// SelectFile.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include<iostream>
#include<fstream>

void writeFilePath(const char* workDir, const char* path) {
	std::string tempPathFile = workDir;
	tempPathFile += "/temp_path";

	std::ofstream outputfile(tempPathFile);
	outputfile << path;
	outputfile.close();
}

bool getOpenFileName(char* title, char* filter, char* defExt) {
	OPENFILENAME ofn = { 0 };
	constexpr int SIZE = MAX_PATH * 4;

	TCHAR workDir[SIZE] = { 0 };
	GetCurrentDirectory(SIZE, workDir);

	TCHAR filePath[SIZE] = { 0 };
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrTitle = title;
	ofn.lpstrDefExt = defExt;
	ofn.nMaxCustFilter = 256;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = SIZE;
	ofn.Flags = OFN_FILEMUSTEXIST;
	bool result = GetOpenFileName(&ofn);

	writeFilePath(workDir, filePath);
	return result;
}


bool getSaveFileName(char* title, char* filter, char* defExt) {
	OPENFILENAME ofn = { 0 };
	constexpr int SIZE = MAX_PATH * 4;

	TCHAR workDir[SIZE] = { 0 };
	GetCurrentDirectory(SIZE, workDir);

	TCHAR filePath[SIZE] = { 0 };
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrTitle = title;
	ofn.lpstrDefExt = defExt;
	ofn.nMaxCustFilter = 256;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = SIZE;
	ofn.Flags = OFN_EXPLORER;
	bool result = GetSaveFileName(&ofn);

	writeFilePath(workDir, filePath);
	return result;
}

int main(int argc, char* argv[])
{
	auto isSave = !strcmp(argv[1], "-s");
	auto isLoad = !strcmp(argv[1], "-l");
	auto title = argv[2];
	auto filter = argv[3];
	auto defExt = argv[4];

	char tmp[1000] = { 0 };
	int len = strlen(filter);
	int ti = 0;
	for (int fi = 0; fi < len; fi++) {
		printf("%c", tmp[ti]);
		auto c = filter[fi];
		if (c == '\\') {
			auto nc = filter[fi + 1];
			if (nc == '0') {
				fi++;
				tmp[ti] = '\0';
				ti++;
				continue;
			}
		}
		tmp[ti] = filter[fi];
		ti++;
	}
	filter = tmp;

	if (isSave) {
		getSaveFileName(title, filter, defExt);
	}
	else if (isLoad) {
		getOpenFileName(title, filter, defExt);
	}

    return 0;
}

