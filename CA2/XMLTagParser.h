#pragma once
#include "Tag.h"

class XMLTagParser
{
public:
	XMLTagParser();
	Tag getTagFromString(std::string string);
};

