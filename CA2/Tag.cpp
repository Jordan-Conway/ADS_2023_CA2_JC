#include "Tag.h"

Tag::Tag(std::string tagName, TagType tagType)
{
	this->tagName = tagName;
	this->tagType = tagType;
}

std::string Tag::getTagName()
{
	return this->tagName;
}

TagType Tag::getTagType()
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

std::string Tag::toString()
{
	return "{tagName:" + this->tagName + ",tagType:" + this->tagType + "}";
}
