#pragma once
#include "Tag.h"
#include <list>

class XMLTagParser
{
public:
    XMLTagParser();
    std::list<Tag> getTagsFromString(std::string string);
    bool containsTag(std::string string);
    bool hasAttributes(std::string string);
};

