#pragma once
#include "Tree.h"
#include "Tag.h"
#include <iostream>
#include <fstream>
#include <optional>

class XMLValidator
{
private:
    /*TODO*/
    //Add stack here
public:
    std::optional<Tree<Tag>> validate(std::ifstream& stream);
};

