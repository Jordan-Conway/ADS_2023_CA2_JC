#pragma once

enum class TagType {
    OPENING,
    CLOSING,
    SELFCLOSING
};

std::string TagTypeToString(TagType tagType) 
{
    switch (tagType)
    {
        case TagType::OPENING: return "OPENING";
        case TagType::CLOSING: return "CLOSING";
        case TagType::SELFCLOSING: return "SELFCLOSING";
    }
}