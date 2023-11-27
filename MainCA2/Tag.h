#pragma once

#include <string>


enum TagType
{
    OPENING,
    CLOSING,
    SELFCLOSING
};

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
    bool closes(Tag& t) const;
    static std::string TagTypeToString(TagType tagType);
    friend bool operator==(const Tag& t1, const Tag& t2);
    friend bool operator!=(const Tag& t1, const Tag& t2);
};



