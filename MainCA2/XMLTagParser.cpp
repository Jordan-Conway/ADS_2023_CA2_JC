#pragma once
#include "XMLTagParser.h"

XMLTagParser::XMLTagParser() {}

std::list<Tag> XMLTagParser::getTagsFromString(std::string string) 
{
    if (string == "")
    {
        return {};
    }
}