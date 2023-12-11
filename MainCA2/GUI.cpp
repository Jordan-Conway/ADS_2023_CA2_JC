#include "GUI.h"

GUI::GUI()
{
    this->window = new sf::Window(sf::VideoMode(800, 600), "Tree");
    tree = nullptr;
}

GUI::~GUI()
{
    delete this->window;
}

void GUI::loadTree(Tree<Tag>* root)
{
    this->tree = root;
}
