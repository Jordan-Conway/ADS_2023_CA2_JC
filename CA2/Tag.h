#pragma once

#include <string>
#include "TagType.h"

class Tag
{
	std::string tagName;
	TagType tagType;

public:
	Tag(std::string tagName, TagType tagType);
	std::string getTagName() const;
	TagType getTagType() const;
	void setTagName(std::string tagName);
	void setTagType(TagType tagType);
	std::string toString() const;
};

