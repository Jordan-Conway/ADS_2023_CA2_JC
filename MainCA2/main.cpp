#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <thread>
#include "XMLValidator.h"
#include "Tree.h"
#include "Tag.h"

using namespace std;

const string fileName = "vs_sample.xml";

static string getInput();
static void displayHelp();
static void exitProgram();
static void loadFile();
static int getItemCount();

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

        cout << "Currently at " << tree.value().getData() << "\n";
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
    }
    
    return 0;
}

static string getInput()
{
    string input = "";

    cin >> input;

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