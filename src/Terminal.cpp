#include "Terminal.hpp"

Terminal::Terminal(UTaste _utaste) : utaste(_utaste)
{
    string input;
    while (getline(cin, input))
    {
        args.clear();
        try
        {
            storeCommandArgs(input);

            if (command_type == POST_COMMAND_TYPE && command == SIGNUP_COMMAND)
            {   
                if (args.find(ARG_KEY_USERNAME) == args.end() || args.find(ARG_KEY_PASSWORD) == args.end())
                    throw(BadRequest("invalid arguments for sign up"));
                
                utaste.addUser(args[ARG_KEY_USERNAME], args[ARG_KEY_PASSWORD]);
                cout << SUCCESS_MSG << endl;
            }

            else if (command_type == POST_COMMAND_TYPE && command == LOGIN_COMMAND)
            {   
                if (args.find(ARG_KEY_USERNAME) == args.end() || args.find(ARG_KEY_PASSWORD) == args.end())
                    throw(BadRequest("invalid arguments for login"));
                
                utaste.login(args[ARG_KEY_USERNAME], args[ARG_KEY_PASSWORD]);
                cout << SUCCESS_MSG << endl;
            }

            else if (command_type == POST_COMMAND_TYPE && command == LOGOUT_COMMAND)
            {
                if (!args.empty())
                    throw(BadRequest("invalid arguments for logout"));
                
                utaste.logout();
                cout << SUCCESS_MSG << endl;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }

    }
}

void Terminal::storeCommandArgs(string input)
{
    string token, temp;

    stringstream ss(input);
    ss >> command_type;
    if (find(COMMAND_TYPES.begin(), COMMAND_TYPES.end(), command_type) == COMMAND_TYPES.end())
        throw(BadRequest("invalid main command"));

    ss >> command;
    if (find(COMMAND_TYPES.begin(), COMMAND_TYPES.end(), command) == COMMANDS.end())
        throw(BadRequest("invalid main command"));

    ss >> temp;
    if (ARGS_START_DELIM != temp)
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
            if(!(ss >> token))
                throw(BadRequest("invalid input format"));
        }

        argument += token;

        argument.erase(argument.end() - 1);
        args[key] = argument;
    }
}