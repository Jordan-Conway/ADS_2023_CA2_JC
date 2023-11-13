#pragma once
#include "Tag.h"

Tag::Tag(std::string tagName, TagType tagType)
{
	this->tagName = tagName;
	this->tagType = tagType;
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
	return false;
}

std::string Tag::TagTypeToString(TagType tagType)
{
	switch (tagType)
	{
		case TagType::OPENING: return "OPENING";
		case TagType::CLOSING: return "CLOSING";
		case TagType::SELFCLOSING: return "SELFCLOSING";
	}
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
