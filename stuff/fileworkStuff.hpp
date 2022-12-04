#pragma once
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
#include <codecvt>
#include <fstream>
#include <vector>

using namespace std;

void wreadFile(wstring filepath, vector<wstring>& content);

wstring readFile(string filepath) {
	wifstream file(filepath);
	file.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	wstringstream wbuff;
	wbuff << file.rdbuf();
	if (wbuff.str().empty()) throw runtime_error("failed to read file: " + filepath);
	file.close();
	return wbuff.str();
}

void wreadFile(wstring filepath, vector<wstring>& content) {
	if (filepath.empty()) throw runtime_error("function wreadFile(wstring, vector´<wstring>&): filepath can't be empty");
	wifstream file(filepath);
	file.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	wstring line;
	while (getline(file, line)) {
		content.push_back(line);
	}
	file.close();
}
void readFile(string filepath, vector<string>& content) {
	if (filepath.empty()) throw runtime_error("function readFile(string, vector<string>&): filepath can't be empty");
	ifstream file(filepath);
	file.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	string line;
	while (getline(file, line)) {
		content.push_back(line);
	}
	file.close();
}

wstring wreadFile(wstring filepath, bool throwEmptyError) {
	if (filepath.empty()) throw runtime_error("function wreadFile(wstring, bool): filepath can't be empty");
	wifstream file(filepath);
	file.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	wstringstream wbuff;
	wbuff << file.rdbuf();
	if (wbuff.str().empty() && throwEmptyError) throw runtime_error("function wreadFile(wstring, bool): failed to wread file");
	file.close();
	return wbuff.str();
}
wstring wreadFile(wstring filepath) {
	wstring buff = wreadFile(filepath, true);
	return buff;
}