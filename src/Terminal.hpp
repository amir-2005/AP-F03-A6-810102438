#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "Utaste.hpp"
#include "libraries.hpp"
#include "constants.hpp"
#include "Exceptions.hpp"

using namespace std;

class Terminal
{
public:
    Terminal(UTaste _utaste);

private:
    UTaste& utaste;
    string command;
    string command_type;
    map<string, string> args;
    void extractCommandArgs(string input);
    void handleSignUp();
    void handleLogin();
    void handleLogout();
    void handleMyDistrict();
    void handleShowDistricts();
    void handleShowRestaurants();
    void handleRestaurantDetail();
    void handleShowReserves();
    void handleReserve();
    void handleDeleteReserve();
    void handleShowBudget();
    void handleIncreaseBudget();

};

#endif