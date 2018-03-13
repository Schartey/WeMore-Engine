#pragma once
#include <iostream>
#include <fstream>

#include <json/json.h>

class Configs
{
public:
	Configs();

	bool readFile(const char* cfgpath);
	Json::Value getValue(const char* key, const char* repl);

	~Configs();

private:
	Json::CharReaderBuilder reader;
	Json::Value root;
};

