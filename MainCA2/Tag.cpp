#pragma once
#include <stdexcept>
#include <iostream>
#include "Tag.h"

Tag::Tag(std::string tagName, TagType tagType)
{
    this->tagName = tagName;
    this->tagType = tagType;
    this->name = "";
    this->lengthInBits = 0;
    this->type = "";
}

Tag::Tag(const Tag& t)
{
    this->tagName = t.getTagName();
    this->tagType = t.getTagType();
    this->name = t.name;
    this->lengthInBits = t.lengthInBits;
    this->type = t.type;
    this->content = t.content;
}

std::string Tag::getTagName() const
{
    return this->tagName;
}

TagType Tag::getTagType() const
{
    return this->tagType;
}

void Tag::setTagName(std::string tagName)
{
    this->tagName = tagName;
}

void Tag::setTagType(TagType tagType)
{
    this->tagType = tagType;
}

std::string Tag::toString() const
{
    return "{tagName:" + this->tagName + ",tagType:" + TagTypeToString(this->tagType) + "}";
}

bool Tag::closes(Tag& t) const
{
    if (this->getTagType() != CLOSING)
    {
        return false;
    }

    if (t.getTagType() != OPENING)
    {
        return false;
    }

    if (this->getTagName() != t.getTagName())
    {
        return false;
    }

    return true;
}

void Tag::setName(std::string name) 
{
    this->name = name;
}

std::string Tag::getName()
{
    return this->name;
}

void Tag::setLength(std::string length)
{
    length = length.substr(0, length.find(' '));
    int bytes = 0;
    try 
    {
        bytes = std::stoi(length);
    }
    catch(std::invalid_argument const& ex)
    {
        std::cout << ex.what() << " " << length << "\n";
    }
    this->lengthInBits = bytes;
}

int Tag::getLength()
{
    return this->lengthInBits;
}

void Tag::setType(std::string type) 
{
    this->type = type;
}

std::string Tag::getType()
{
    return this->type;
}

void Tag::setContent(std::string content) 
{
    this->content = content;
}

std::string Tag::getContent()
{
    return this->content;
}


std::string Tag::TagTypeToString(TagType tagType)
{
    switch (tagType)
    {
        case TagType::OPENING: return "OPENING";
        case TagType::CLOSING: return "CLOSING";
        case TagType::SELFCLOSING: return "SELFCLOSING";
    }

    return "";
}

bool operator==(const Tag& t1, const Tag& t2)
{
    if (t1.tagName != t2.tagName)
    {
        return false;
    }

    if (t1.tagType != t2.tagType) 
    {
        return false;
    }

    if (t1.name != t2.name)
    {
        return false;
    }

    if (t1.lengthInBits != t2.lengthInBits)
    {
        return false;
    }

    if (t1.type != t2.type)
    {
        return false;
    }

    if (t1.content != t2.content)
    {
        return false;
    }

    return true;
}

bool operator!=(const Tag& t1, const Tag& t2)
{
    if (t1 == t2)
    {
        return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& stream, const Tag& t)
{
    stream << "{Name: " << t.name;
    if (t.lengthInBits != NULL)
    {
        stream << ", Size: " << t.lengthInBits;
    }
    if (t.type != "")
    {
        stream << ", Type: " << t.type;
    }
    if (t.content != "")
    {
        stream << ", Content: " << t.content;
    }
    stream << "}";
    return stream;
}

