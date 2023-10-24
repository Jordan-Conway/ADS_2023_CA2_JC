#pragma once
#include "XMLTagParser.h"
#include <iostream>

XMLTagParser::XMLTagParser() {}

std::list<Tag> XMLTagParser::getTagsFromString(std::string string) 
{
    std::list<Tag> foundTags;

    while (containsTag(string))
    {
        int first = string.find("<");
        int second = string.find(">");
        std::string stringWithTag = string.substr(first+1, second - first -1);
        if (stringWithTag.find("/") == 0)
        {
            stringWithTag = stringWithTag.substr(1);
            foundTags.push_back(Tag(stringWithTag, TagType::CLOSING));
        }
        else if (stringWithTag.back() == '/')
        {
            stringWithTag = stringWithTag.substr(0, stringWithTag.size() -1);
            foundTags.push_back(Tag(stringWithTag, TagType::SELFCLOSING));
        }
        else
        {
            foundTags.push_back(Tag(stringWithTag, TagType::OPENING));
        }
        string = string.substr(second+1);
    }

    return foundTags;
}

bool XMLTagParser::containsTag(std::string string)
{
    if (string.find('<') == std::string::npos)
    {
        return false;
    }

    if (string.find('>') == std::string::npos)
    {
        return false;
    }

    if (string.find('<') > string.find('>'))
    {
        return false;
    }

    return true;
}

bool XMLTagParser::hasAttributes(std::string string)
{
    if (!containsTag(string))
    {
        return false;
    }
    int space = string.find(" ");

    if (space == std::string::npos)
    {
        return false;
    }

    int first = string.find("<");
    int second = string.find(">");
    std::string stringWithTag = string.substr(first + 1, second - first - 1);
    std::string attributes;
    if (stringWithTag.find('/') == stringWithTag.size() - 1)
    {
        attributes = stringWithTag.substr(space, stringWithTag.size() - space - 1);
    }
    else
    {
        attributes = stringWithTag.substr(space, stringWithTag.size() - space);
    }

    //Taken from https://stackoverflow.com/a/6444999
    return attributes.find_first_not_of(' ') != std::string::npos;
}