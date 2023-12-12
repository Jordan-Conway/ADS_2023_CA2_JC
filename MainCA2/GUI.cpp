#include "GUI.h"
#include <iostream>

GUI::GUI()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Tree");
    window->setFramerateLimit(24);
    tree = nullptr;
}

GUI::~GUI()
{
    delete this->window;
}

void GUI::display()
{
    if (this->tree == nullptr)
    {
        return;
    }

    while (window->isOpen())
    {
        window->clear();
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }
        this->drawTree(this->tree);

        window->display();
    }
}

void GUI::loadTree(Tree<Tag>* root)
{
    this->tree = root;
}

int GUI::drawTree(Tree<Tag>* tree, int indent, int layer)
{
    int numDrawn = 1;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) 
    {
        std::cout << "Failed to load font" << "\n";
        return 0;
    }
    sf::Text text;
    text.setString(tree->data.getName());
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::White);
    text.setPosition(20 + (indent * 20), 20 + (layer * 20));
    text.setFont(font);
    window->draw(text);

    DListIterator<Tree<Tag>*> iter = tree->children->getIterator();
    while (iter.isValid())
    {
        numDrawn += drawTree(iter.currentNode->data, indent + 1, layer + numDrawn);
        iter.advance();
    }

    return numDrawn;
}
