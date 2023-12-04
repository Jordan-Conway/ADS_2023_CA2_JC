#pragma once
#include "XMLTagParser.h"
#include <iostream>

XMLTagParser::XMLTagParser() {}

std::list<Tag> XMLTagParser::getTagsFromString(std::string string) 
{
    std::list<Tag> foundTags;
    std::list<std::string> propertyTags = {
        "name",
        "length",
        "type"
    };

    while (containsTag(string))
    {
        int first = static_cast<int>(string.find("<"));
        int second = static_cast<int>(string.find(">"));
        std::string stringWithTag = string.substr(first+1, second - first -1);
        if (stringWithTag.find("/") == 0)
        {
            stringWithTag = stringWithTag.substr(1);
            foundTags.push_back(Tag(stringWithTag, TagType::CLOSING));
        }
        else if (stringWithTag.back() == '/')
        {
            if (hasAttributes(stringWithTag))
            {
                stringWithTag = stringWithTag.substr(0, stringWithTag.find(' '));
            }
            else
            {
                stringWithTag = stringWithTag.substr(0, stringWithTag.size() - 1);
            }
            foundTags.push_back(Tag(stringWithTag, TagType::SELFCLOSING));
        }
        else
        {
            if (hasAttributes(stringWithTag))
            {
                stringWithTag = stringWithTag.substr(0, stringWithTag.find(' '));
            }
            Tag tag(stringWithTag, TagType::OPENING);
            foundTags.push_back(tag);
        }

        //If the tag contains text
        if (string[second + 1] != '<')
        {
            std::string content = string.substr(second + 1);
            content = content.substr(0, content.find('<'));
            foundTags.back().setContent(content);
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
    int space = static_cast<int>(string.find(" "));

    if (space == std::string::npos)
    {
        return false;
    }

    int first = static_cast<int>(string.find("<"));
    int second = static_cast<int>(string.find(">"));
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