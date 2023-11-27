#pragma once
#include "Tree.h"
#include "Tag.h"
#include "TreeIterator.h"
#include <iostream>
#include <fstream>
#include <optional>
#include <stack>

class XMLValidator
{
public:
    std::optional<Tree<Tag>> validate(std::ifstream& stream);
};

