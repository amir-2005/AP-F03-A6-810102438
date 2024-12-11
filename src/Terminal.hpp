#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "libraries.hpp"
#include "constants.hpp"

using namespace std;

class Terminal
{
public:
    Terminal();

private:
    string input;
    vector<string> args;
};

#endif