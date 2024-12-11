#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "libraries.hpp"
#include "constants.hpp"
#include "Exceptions.hpp"

using namespace std;

class Terminal
{
public:
    Terminal();

private:
    string command;
    string command_type;
    map<string, string> args;
    void storeCommandArgs(string input);
};

#endif