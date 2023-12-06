#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <fstream>
#include <optional>
#include <filesystem>
#include <chrono>
#include <thread>
#include "XMLValidator.h"
#include "Tree.h"
#include "Tag.h"

using namespace std;

static string getInput();
static void displayHelp();
static void exitProgram();

chrono::seconds exitDelay(1);

int main() {
    cout << "Type help to see all commands" << "\n";
    bool exit = false;

    while (!exit)
    {
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