#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <queue>
#include <thread>
#include "XMLValidator.h"
#include "Tree.h"
#include "Tag.h"

using namespace std;

const string fileName = "vs_sample_simple.xml";

static string getInput();
static void displayHelp();
static void exitProgram();
static void loadFile();
static int getItemCount();
static int getMemoryAmount();
static void move(string target);
static void list();
static int prune(Tree<Tag>* treeRoot);

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
            cout << "Moving to " << input.substr(input.find(' ')) << '\n';
            move(input.substr(input.find(' ') + 1));
            continue;
        }

        if (input == "list")
        {
            list();
        }

        if (input == "prune")
        {
            int numberDeleted = prune(&tree.value());
            cout << "Deleted " << numberDeleted << " empty directories" << "\n";
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
        }
        delete treeRoot;
        count++;
    }

    iter = TreeIterator(&tree.value());
    return count;
}

static void move(string target)
{
    if (!iter.has_value())
    {
        return;
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
        cout << iter.value().childIter.currentNode->data->getData() << "\n";
        iter.value().childIter.advance();
    }
}