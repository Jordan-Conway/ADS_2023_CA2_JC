#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <queue>
#include <thread>
#include "XMLValidator.h"
#include "GUI.h"
#include "Tree.h"
#include "Tag.h"

using namespace std;

const string fileName = "vs_sample.xml";

static string getInput();
static void displayHelp();
static void exitProgram();
static void loadFile();
static int getItemCount();
static int getMemoryAmount();
static void move(string target);
static void list();
static int prune(Tree<Tag>* treeRoot);
static string getPath(string fileName);
static Tree<Tag>* findNode(Tree<Tag>* root, string name);
static void treeGUI();

chrono::seconds exitDelay(1);

optional<Tree<Tag>> tree = {};
optional<TreeIterator<Tag>> iter = {};
optional<Tree<Tag>> root = {};

int main() {
    loadFile();
    cout << "Type help to see all commands" << "\n";
    bool exit = false;

    while (!exit)
    {
        if (!tree.has_value())
        {
            cout << "No xml document was loaded" << "\n";
            cout << "Now exiting" << "\n";
            exitProgram();
        }

        cout << "Currently at " << iter.value().item().getName() << "\n";
        cout << "Enter a command: ";
        string input = getInput();
        cout << "\n";

        if (input == "help")
        {
            displayHelp();
            continue;
        }

        if (input == "exit")
        {
            exitProgram();
        }

        if (input == "1")
        {
            cout << "There are " << getItemCount() << " items in the current directory" << "\n";
            continue;
        }

        if (input == "2")
        {
            cout << "The current directory has a size of " << getMemoryAmount() << " bytes" << "\n";
            continue;
        }

        if (input.substr(0, input.find(' ')) == "move")
        {
            move(input.substr(input.find(' ') + 1));
            continue;
        }

        if (input == "list")
        {
            list();
            continue;
        }

        if (input == "prune")
        {
            int numberDeleted = prune(&tree.value());
            cout << "Deleted " << numberDeleted << " empty directories" << "\n";
            continue;
        }

        if (input.substr(0, input.find(' ')) == "find")
        {
            string path = getPath(input.substr(input.find(' ') + 1));
            if (path == "")
            {
                cout << "Not found" << "\n";
            }
            else
            {
                cout << "Path is " << path << "\n";
            }
            continue;
        }

        if (input == "gui")
        {
            treeGUI();
        }
    }
    
    return 0;
}

static string getInput()
{
    string input = "";

    getline(cin, input);

    //Convert input to lower case
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    return input;
}

static void displayHelp()
{
    cout << "help: show all commands" << "\n";
    cout << "exit: exit the program" << "\n";
}

static void exitProgram()
{
    cout << "Thank you for using this program" << "\n";
    this_thread::sleep_for(exitDelay);
    std::exit(0);
}

static void loadFile()
{
    XMLValidator validator;
    ifstream file(fileName);

    if (!file.good())
    {
        cout << "Could not open file" << "\n";
        return;
    }

    optional<Tree<Tag>> result = validator.validate(file);

    if (!result.has_value())
    {
        cout << "Error in file" << "\n";
        return;
    }

    tree = result.value();
    iter = TreeIterator(&tree.value());
    root = tree.value();
}

static int getItemCount()
{
    return tree.value().count();
}

static int getMemoryAmount()
{
    queue<Tree<Tag>> nodes;
    int size = 0;
    
    nodes.push(tree.value());

    while (!nodes.empty())
    {
        size += nodes.front().data.getLength();
        DListIterator<Tree<Tag>*> childIter = nodes.front().children->getIterator();
        while (childIter.isValid())
        {
            nodes.push(*childIter.currentNode->data);
            childIter.advance();
        }
        nodes.pop();
    }

    return size;
}

static int prune(Tree<Tag>* treeRoot)
{
    int count = 0;

    TreeIterator<Tag> pruneIter(treeRoot);
    while (pruneIter.childIter.isValid())
    {
        if (pruneIter.childIter.item()->getData().getTagName() == "dir")
        {
            int numbDeletedFromChild = prune(pruneIter.childIter.item());
            if (numbDeletedFromChild > 0)
            {
                pruneIter.childIter.start();
            }
            count += numbDeletedFromChild;
        }
        pruneIter.childIter.advance();
    }

    pruneIter.childIter.start();

    if (treeRoot->children->size() == 0)
    {
        if (treeRoot->parent != nullptr)
        {
            DListIterator<Tree<Tag>*> childIter = treeRoot->parent->children->getIterator();
            while (childIter.isValid())
            {
                if (childIter.item() == treeRoot)
                {
                    treeRoot->parent->children->remove(childIter);
                    break;
                }
                childIter.advance();
            }
            childIter.start();
        }
        delete treeRoot;
        count++;
    }

    return count;
}

static void move(string target)
{
    if (!iter.has_value())
    {
        return;
    }

    //Trim whitespace from input
    size_t first = target.find_first_not_of(' ');
    if (first != string::npos)
    {
        size_t second = target.find_last_not_of(' ');
        target = target.substr(first, (second - first +1));
    }

    if (target == "up")
    {
        iter.value().up();
        return;
    }

    while (iter.value().childIter.isValid())
    {
        string current = iter.value().childIter.item()->data.getName();
        transform(current.begin(), current.end(), current.begin(), ::tolower);
        if (current == target)
        {
            break;
        }
        iter.value().childIter.advance();
    }

    if (!iter.value().childIter.isValid())
    {
        cout << "Directory not found" << "\n";
        return;
    }

    if (iter.value().childIter.currentNode->data->getData().getTagName() != "dir")
    {
        return;
    }

    iter.value().down();

}

static void list()
{
    if (!iter.has_value())
    {
        cout << "No tree loaded" << "\n";
        return;
    }

    while (iter.value().childIter.isValid())
    {
        cout << iter.value().childIter.currentNode->data->getData().getName();
        if (iter.value().childIter.currentNode->data->getData().getTagName() == "file")
        {
            cout << ": " << iter.value().childIter.currentNode->data->getData().getLength() << " bytes";
        }
        cout << "\n";
        iter.value().childIter.advance();
    }

    iter.value().resetIterator();
}

static string getPath(string fileName)
{
    Tree<Tag>* destination = findNode(&tree.value(), fileName);
    if (destination == nullptr)
    {
        return "";
    }
    string path = destination->getData().getName();

    while (destination->parent != nullptr)
    {
        path = destination->parent->getData().getName() + "/" + path;
        destination = destination->parent;
    }

    return path;
}

static Tree<Tag>* findNode(Tree<Tag>* root, string name)
{
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    string currentName = root->getData().getName();
    transform(currentName.begin(), currentName.end(), currentName.begin(), ::tolower);
    //If starts with name provided
    if (currentName.rfind(name, 0) == 0)
    {
        return root;
    }

    Tree<Tag>* found = nullptr;

    DListIterator<Tree<Tag>*> childIter = root->children->getIterator();
    while (childIter.isValid())
    {
        found = findNode(childIter.item(), name);
        if (found != nullptr)
        {
            return found;
        }
        childIter.advance();
    }

    return nullptr;
}

static void treeGUI()
{
    GUI gui;
    gui.loadTree(iter.value().node);
    gui.display();
}