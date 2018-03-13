#include "Configs.h"



Configs::Configs()
{
}

bool Configs::readFile(const char* cfgpath) {
	std::ifstream ifs(cfgpath);

	std::string errs;

	bool parsingSuccessful = Json::parseFromStream(reader, ifs, &root, &errs);
	if (!parsingSuccessful)
	{
		std::cout << "Failed to parse configuration file\n"
			<< errs;
		return false;
	}
	//Close file after parsing
	ifs.close();

	return true;
}

Json::Value Configs::getValue(const char* key, const char* repl) {
	return root.get(key, repl);
}

Configs::~Configs()
{
}
