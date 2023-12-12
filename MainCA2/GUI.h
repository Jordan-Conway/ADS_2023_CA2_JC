#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Tree.h"
#include "Tag.h"

class GUI
{
    sf::RenderWindow* window;
    Tree<Tag>* tree;
    int drawTree(Tree<Tag>* tree, int indent = 0, int layer = 0);
public:
    GUI();
    ~GUI();
    void display();
    void loadTree(Tree<Tag>* root);
};

