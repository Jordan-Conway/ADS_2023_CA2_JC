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
    std::string name;
    int lengthInBytes;
    std::string type;
    std::string content;

public:
    Tag(std::string tagName, TagType tagType);
    Tag(const Tag& t);
    std::string getTagName() const;
    TagType getTagType() const;
    void setTagName(std::string tagName);
    void setTagType(TagType tagType);
    std::string toString() const;
    bool closes(Tag& t) const;
    void setName(std::string name);
    std::string getName();
    void setLength(std::string length);
    int getLength();
    void setType(std::string type);
    void setContent(std::string content);
    std::string getContent();
    static std::string TagTypeToString(TagType tagType);
    friend bool operator==(const Tag& t1, const Tag& t2);
    friend bool operator!=(const Tag& t1, const Tag& t2);
    friend std::ostream& operator<< (std::ostream& stream, const Tag& t);
};



