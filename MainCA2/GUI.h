#pragma once
#include "SFML/Window.hpp"
#include "Tree.h"
#include "Tag.h"

class GUI
{
    sf::Window* window;
    Tree<Tag>* tree;

public:
    GUI();
    ~GUI();
    void loadTree(Tree<Tag>* root);
};

