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
	return "{tagName:" + this->tagName + ",tagType:" + this->tagType + "}";
}
