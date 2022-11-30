#include "Object.h"

Object::Object(std::string& name, long long id) : id(id), name(name)
{}

Object::Object(const char* name, long long id) : id(id), name(name)
{}

Object::~Object()
{}
