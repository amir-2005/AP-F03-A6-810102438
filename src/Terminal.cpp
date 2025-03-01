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
                handleSignUp();
            }
            else if (command_type == POST_COMMAND_TYPE && command == LOGIN_COMMAND)
            {
                handleLogin();
            }
            else if (command_type == POST_COMMAND_TYPE && command == LOGOUT_COMMAND)
            {
                handleLogout();
            }
            else if (command_type == PUT_COMMAND_TYPE && command == MY_DISTRICT_COMMAND)
            {
                handleMyDistrict();
            }
            else if (command_type == POST_COMMAND_TYPE && command == RESERVE_COMMAND)
            {
                handleReserve();
            }
            else if (command_type == GET_COMMAND_TYPE && command == DISTRICTS_COMMAND)
            {
                handleShowDistricts();
            }
            else if (command_type == GET_COMMAND_TYPE && command == RESTAURANTS_COMMAND)
            {
                handleShowRestaurants();
            }
            else if (command_type == GET_COMMAND_TYPE && command == RESTAURANT_DETAIL_COMMAND)
            {
                handleRestaurantDetail();
            }
            else if (command_type == GET_COMMAND_TYPE && command == SHOW_RESERVES_COMMAND)
            {
                handleShowReserves();
            }
            else if (command_type == DELETE_COMMAND_TYPE && command == RESERVE_COMMAND)
            {
                handleDeleteReserve();
            }
            else if (command_type == GET_COMMAND_TYPE && command == SHOW_BUDGET_COMMAND)
            {
                handleShowBudget();
            }
            else if (command_type == POST_COMMAND_TYPE && command == INCREASE_BUDGET_COMMAND)
            {
                handleIncreaseBudget();
            }
            else
            {
                throw(NotFound(MSG_NOT_FOUND + command));
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
        throw(BadRequest(MSG_BAD_REQUEST_COMMAND_TYPE));

    ss >> command;
    if (find(COMMANDS.begin(), COMMANDS.end(), command) == COMMANDS.end())
        throw(NotFound(MSG_NOT_FOUND + command));

    ss >> temp;
    if (ARGS_START_DELIM != temp)
        throw(BadRequest(MSG_BAD_REQUEST_FORMAT));

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
                throw(BadRequest(MSG_BAD_REQUEST_FORMAT));
        }

        argument += token;
        argument.erase(argument.end() - 1);
        args[key] = argument;
    }
}

void Terminal::handleSignUp()
{
    if (args.find(ARG_KEY_USERNAME) == args.end() || args.find(ARG_KEY_PASSWORD) == args.end())
        throw(BadRequest(MSG_BAD_REQUEST_ARGUMENTS + SIGNUP_COMMAND));

    utaste.signUp(args[ARG_KEY_USERNAME], args[ARG_KEY_PASSWORD]);
    cout << SUCCESS_MSG << endl;
}

void Terminal::handleLogin()
{
    if (args.find(ARG_KEY_USERNAME) == args.end() || args.find(ARG_KEY_PASSWORD) == args.end())
        throw(BadRequest(MSG_BAD_REQUEST_ARGUMENTS + LOGIN_COMMAND));

    utaste.login(args[ARG_KEY_USERNAME], args[ARG_KEY_PASSWORD]);
    cout << SUCCESS_MSG << endl;
}

void Terminal::handleLogout()
{
    if (!args.empty())
        throw(BadRequest(MSG_BAD_REQUEST_ARGUMENTS + LOGOUT_COMMAND));

    utaste.logout();
    cout << SUCCESS_MSG << endl;
}

void Terminal::handleMyDistrict()
{
    if (args.find(ARG_KEY_DISTRICT) == args.end())
        throw(BadRequest(MSG_BAD_REQUEST_ARGUMENTS + MY_DISTRICT_COMMAND));

    utaste.setUserDistrict(args[ARG_KEY_DISTRICT]);
    cout << SUCCESS_MSG << endl;
}

void Terminal::handleReserve()
{
    if (args.find(ARG_KEY_RESTAURANT_NAME) == args.end() ||
        args.find(ARG_KEY_TABLE_ID) == args.end() ||
        args.find(ARG_KEY_START_TIME) == args.end() ||
        args.find(ARG_KEY_END_TIME) == args.end())
        throw(BadRequest(MSG_BAD_REQUEST_ARGUMENTS + RESERVE_COMMAND));

    time_period reserve_time = make_pair(stoi(args[ARG_KEY_START_TIME]), stoi(args[ARG_KEY_END_TIME]));
    stringstream ss(args[ARG_KEY_FOODS]);
    map<food, int> reserve_foods;
    string token;

    while (getline(ss, token, DELIM))
        reserve_foods[token]++;

    cout << utaste.setReservation(args[ARG_KEY_RESTAURANT_NAME], stoi(args[ARG_KEY_TABLE_ID]), reserve_time, reserve_foods);
}

void Terminal::handleShowDistricts()
{
    cout << utaste.getDistrictsInfo(args[ARG_KEY_DISTRICT]);
}

void Terminal::handleShowRestaurants()
{
    cout << utaste.getRestaurantsList(args[ARG_KEY_FOOD_NAME]);
}

void Terminal::handleRestaurantDetail()
{
    if (args.find(ARG_KEY_RESTAURANT_NAME) == args.end())
        throw(BadRequest(""));
    cout << utaste.getRestaurantInfo(args[ARG_KEY_RESTAURANT_NAME]);
}

void Terminal::handleShowReserves()
{
    if (args.find(ARG_KEY_RESERVE_ID) != args.end() && args.find(ARG_KEY_RESTAURANT_NAME) == args.end())
        throw(BadRequest(MSG_BAD_REQUEST_RESTAURNT));

    int reserve_id = 0;
    if (!args[ARG_KEY_RESERVE_ID].empty())
        reserve_id = stoi(args[ARG_KEY_RESERVE_ID]);

    cout << utaste.showReservations(args[ARG_KEY_RESTAURANT_NAME], reserve_id);
}

void Terminal::handleDeleteReserve()
{
    if (args.find(ARG_KEY_RESERVE_ID) == args.end() || args.find(ARG_KEY_RESTAURANT_NAME) == args.end())
        throw(BadRequest(MSG_BAD_REQUEST_RESERVE_ID));

    utaste.deleteReservation(args[ARG_KEY_RESTAURANT_NAME], stoi(args[ARG_KEY_RESERVE_ID]));
    cout << SUCCESS_MSG << endl;
}

void Terminal::handleShowBudget()
{
    cout << utaste.showBudget() << endl;
}

void Terminal::handleIncreaseBudget()
{
    if (args.find(ARG_KEY_AMOUNT) == args.end())
        throw(BadRequest(MSG_BAD_REQUEST_ARGUMENTS + INCREASE_BUDGET_COMMAND));

    string amount = args[ARG_KEY_AMOUNT];

    if (!all_of(amount.begin(), amount.end(), ::isdigit) || amount.empty())
        throw(BadRequest(MSG_BAD_REQUEST_ARGUMENTS + INCREASE_BUDGET_COMMAND));
    utaste.increaseBudget(stoi(amount));
    cout << SUCCESS_MSG << endl;
}