#pragma once
#include <string>

class Object
{
public:
	std::string name;
	const long long id;

	Object(std::string& name, long long id);
	Object(const char* name, long long id);
	virtual ~Object();
};

