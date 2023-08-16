#include <string>
#include <cstring>
#pragma once

inline char* StringToChar(std::string Text) {
	return &Text[0];
}

inline const char* StringToConstChar(std::string Text)
{
	return Text.c_str();
}