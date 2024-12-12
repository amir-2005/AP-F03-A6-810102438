#include "Terminal.hpp"

Terminal::Terminal(UTaste _utaste) : utaste(_utaste)
{
    string input;
    while (getline(cin, input))
    {
        args.clear();
        try
        {
            extractCommandArgs(input);

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

            else if (command_type == PUT_COMMAND_TYPE && command == MY_DISTRICT_COMMAND)
            {
                if (args.find(ARG_KEY_DISTRICT) == args.end())
                    throw(BadRequest("invalid arguments for my_district"));

                utaste.setUserDistrict(args[ARG_KEY_DISTRICT]);
                cout << SUCCESS_MSG << endl;
            }

            else if (command_type == POST_COMMAND_TYPE && command == RESERVE_COMMAND)
            {
                if (args.find(ARG_KEY_RESTAURANT_NAME) == args.end() ||
                    args.find(ARG_KEY_TABLE_ID) == args.end() ||
                    args.find(ARG_KEY_START_TIME) == args.end() ||
                    args.find(ARG_KEY_END_TIME) == args.end())
                    throw(BadRequest("invalid arguments for reserve"));

                time_period reserve_time = make_pair(stoi(args[ARG_KEY_START_TIME]), stoi(args[ARG_KEY_END_TIME]));
                stringstream ss(args[ARG_KEY_FOODS]);
                map<food, int> reserve_foods;
                string token;

                while (getline(ss, token, DELIM))
                    reserve_foods[token]++;

                utaste.setReservation(args[ARG_KEY_RESTAURANT_NAME], stoi(args[ARG_KEY_TABLE_ID]), reserve_time, reserve_foods);
                cout << SUCCESS_MSG << endl;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }
}

void Terminal::extractCommandArgs(string input)
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
            if (!(ss >> token))
                throw(BadRequest("invalid input format"));
        }

        argument += token;

        argument.erase(argument.end() - 1);
        args[key] = argument;
    }
}