#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "libraries.hpp"

using namespace std;

typedef string food;
typedef pair<unsigned,unsigned> time_period; 

const char DELIM = ',';
const char INNER_DELIM = ';';
const char PRICE_DELIM = ':';
const string ARGS_START = "?";
const vector<string> MAIN_COMMANDS = {"PUT", "GET", "POST", "DELETE"}; 
const string SIGNUP_COMMAND = "signup";
const string LOGIN_COMMAND = "login";

#endif