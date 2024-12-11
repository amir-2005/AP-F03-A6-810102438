#include "Terminal.hpp"

Terminal::Terminal()
{
    string input;
    while (getline(cin, input))
    {
        storeCommandArgs(input);
    }
}

void Terminal::storeCommandArgs(string input)
{
    string token, temp;

    stringstream ss(input);
    ss >> command_type;
    if (find(MAIN_COMMANDS.begin(), MAIN_COMMANDS.end(), command_type) == MAIN_COMMANDS.end())
        throw(BadRequest("invalid main command"));

    ss >> command;

    ss >> temp;
    if (find(MAIN_COMMANDS.begin(), MAIN_COMMANDS.end(), ARGS_START) == MAIN_COMMANDS.end())
        throw(BadRequest("invalid input format"));

    while (ss >> token)
    {
        string key = token;

        ss >> token;
        token.erase(0, 1);
        string argument;

        while (token.back() != '\"')
        {
            argument += token + " ";
            ss >> token;
        }

        argument += token;

        argument.erase(argument.end() - 1);
        args[key] = argument;
    }
}