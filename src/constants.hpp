#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "libraries.hpp"

using namespace std;

typedef string food;
typedef pair<unsigned, unsigned> time_period;

const char DELIM = ',';
const char INNER_DELIM = ';';
const char PRICE_DELIM = ':';
const string ARGS_START_DELIM = "?";

const string PUT_COMMAND_TYPE = "PUT";
const string GET_COMMAND_TYPE = "GET";
const string POST_COMMAND_TYPE = "POST";
const string DELETE_COMMAND_TYPE = "DELETE";
const vector<string> COMMAND_TYPES = {PUT_COMMAND_TYPE, GET_COMMAND_TYPE, POST_COMMAND_TYPE, DELETE_COMMAND_TYPE};
const string SIGNUP_COMMAND = "signup";
const string LOGIN_COMMAND = "login";
const string LOGOUT_COMMAND = "logout";
const string DISTRICTS_COMMAND = "districts";
const string MY_DISTRICT_COMMAND = "my_district";
const string RESTAURANTS_COMMAND = "restaurants";
const string RESTAURANT_DETAIL_COMMAND = "restaurant_detail";
const string RESERVE_COMMAND = "reserve";
const string SHOW_RESERVES_COMMAND = "reserves";
const vector<string> COMMANDS = {SIGNUP_COMMAND, LOGIN_COMMAND, LOGOUT_COMMAND,
                                 DISTRICTS_COMMAND, MY_DISTRICT_COMMAND, RESTAURANTS_COMMAND,
                                 RESTAURANT_DETAIL_COMMAND, RESERVE_COMMAND, SHOW_RESERVES_COMMAND};

const string BAD_REQUEST_MSG = "Bad Request";
const string NOT_FOUND_MSG = "Not Found";
const string PERMISSION_DENIED_MSG = "Permission Denied";
const string EMPTY_MSG = "EMPTY";

const string ARG_KEY_USERNAME = "username";
const string ARG_KEY_PASSWORD = "password";
const string ARG_KEY_DISTRICT = "dsitrict";
const string ARG_KEY_FOOD_NAME = "food_name";
const string ARG_KEY_RESTAURANT_NAME = "restaurant_name";
const string ARG_KEY_TABLE_ID =  "table_id";
const string ARG_KEY_START_TIME =  "start_time";
const string ARG_KEY_END_TIME =  "end_time";
const string ARG_KEY_FOODS =  "foods";
const string ARG_KEY_RESERVE_ID =  "reserve_id";


#endif