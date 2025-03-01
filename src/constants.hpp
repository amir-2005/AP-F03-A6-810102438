#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "libraries.hpp"

using namespace std;

typedef string food;
typedef pair<unsigned, unsigned> time_period;

const char DELIM = ',';
const char INNER_DELIM = ';';
const char PRICE_DELIM = ':';
const char DISCOUNT_DELIM = '|';

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
const string SHOW_BUDGET_COMMAND = "show_budget";
const string INCREASE_BUDGET_COMMAND = "increase_budget";
const vector<string> COMMANDS = {SIGNUP_COMMAND, LOGIN_COMMAND, LOGOUT_COMMAND, INCREASE_BUDGET_COMMAND,
                                 DISTRICTS_COMMAND, MY_DISTRICT_COMMAND, RESTAURANTS_COMMAND, SHOW_BUDGET_COMMAND,
                                 RESTAURANT_DETAIL_COMMAND, RESERVE_COMMAND, SHOW_RESERVES_COMMAND};

const string BAD_REQUEST_MSG = "Bad Request";
const string NOT_FOUND_MSG = "Not Found";
const string PERMISSION_DENIED_MSG = "Permission Denied";
const string EMPTY_MSG = "Empty";
const string SUCCESS_MSG = "OK";

const string ARG_KEY_USERNAME = "username";
const string ARG_KEY_PASSWORD = "password";
const string ARG_KEY_DISTRICT = "district";
const string ARG_KEY_FOOD_NAME = "food_name";
const string ARG_KEY_RESTAURANT_NAME = "restaurant_name";
const string ARG_KEY_TABLE_ID = "table_id";
const string ARG_KEY_START_TIME = "start_time";
const string ARG_KEY_END_TIME = "end_time";
const string ARG_KEY_FOODS = "foods";
const string ARG_KEY_RESERVE_ID = "reserve_id";
const string ARG_KEY_AMOUNT = "amount";

const string UNEXPECTED_ERROR_FILE_OPEN = "Unexpected error: unable to open file ";
const string UNEXPECTED_ERROR_FILE_FORMAT = "Unexpected error: file format is incorrect";

const string MSG_NOT_FOUND = " not found";
const string MSG_NOT_FOUND_FOOD = "food is not availble";
const string MSG_NOT_FOUND_TABLE_ID = "table id is out of range";
const string MSG_NOT_FOUND_DISTRICT_SET = "user district is not set";

const string MSG_BAD_REQUEST_COMMAND_TYPE = "invalid command type";
const string MSG_BAD_REQUEST_COMMAND = "invalid command";
const string MSG_BAD_REQUEST_FORMAT = "invalid input format";
const string MSG_BAD_REQUEST_ARGUMENTS = "invalid arguments for ";
const string MSG_BAD_REQUEST_RESTAURNT = "restaurant should be specified";
const string MSG_BAD_REQUEST_RESERVE_ID = "reserve id and restaurant name should be specified";
const string MSG_BAD_REQUEST_NEGATIVE = "can't be negative";
const string MSG_BAD_REQUEST_LOW_BUDGET = "not enough catch";

const string MSG_PERMISSION_DENIED_SIGN_UP = "can't sign up while logged in";
const string MSG_PERMISSION_DENIED_DUPLICATED = "The user is already signed up";
const string MSG_PERMISSION_DENIED_LOGIN = "can't login twice";
const string MSG_PERMISSION_DENIED_LOGOUT = "can't logout before login";
const string MSG_PERMISSION_DENIED_NO_USER = "no user has logged in";
const string MSG_PERMISSION_DENIED_PASSWORD = "wrong password";
const string MSG_PERMISSION_DENIED_RESERVATION = "the reservation belongs to someone else";
const string MSG_PERMISSION_DENIED_RESERVE_TIME = "invalid reservation time";
const string MSG_PERMISSION_DENIED_TABLE = "table is reserved";

const string MSG_EMPTY_NO_DISTRICT = "there is no district";
const string MSG_EMPTY_NO_RESTAURANT = "no restaurant with this food: ";
const string MSG_EMPTY_NO_RESERVATION = "no reservation found";

const string RESERVATION_INFO_ID = "Reserve ID";
const string RESERVATION_INFO_TABLE = "Table";
const string RESERVATION_INFO_ORIGINAL_PRICE = "Original Price";
const string RESERVATION_INFO_ORDER_DISCOUNT = "Order Amount Discount"; 
const string RESERVATION_INFO_FOOD_DISCOUNT = "Total ItemSpecific Discount";
const string RESERVATION_INFO_FIRST_DISCOUNT = "First Order Discount";
const string RESERVATION_INFO_TOTAL_DISCOUNT = "Total Discount";
const string RESERVATION_INFO_TOTAL_PRICE = "Total Price";

const string RESTAURANT_INFO_NAME = "Name";
const string RESTAURANT_INFO_DISTRICT = "District";
const string RESTAURANT_INFO_TIME = "Time";
const string RESTAURANT_INFO_MENU_ITEM = "Menu Item";
const string RESTAURANT_INFO_MENU_PRICE = "Menu Price";
const string RESTAURANT_INFO_TABLE = "Table";
const string RESTAURANT_INFO_ORDER_DISCOUNT = "Order Amount Discount";
const string RESTAURANT_INFO_ITEM_DISCOUNT = "Item Specific Discount";
const string RESTAURANT_INFO_FIRST_DISCOUNT = "First Order Discount";

const string TYPE_AMOUNT = "amount";
const string TYPE_PERCENTAGE = "percent";
const string TYPE_PERCENTAGE_NAME = "percentage";
const string NO_DISCOUNT = "none";

const int FULL_DAY_TIME = 24;
const float REFUND_PERCENT = 0.6;

const string SESSION_LOGGED_IN = "LOGGED_IN";

const string STYLE_FOR_RESTAURANTS_PAGE = R"(
    <style>
        :root {
            --primary-color: #B08850;
            --secondary-color: #8A4A2C;
            --background-color: #fceccc;
            --text-color: #4B352A;
            --button-text-color: #FFFFFF;
            --error-color: #FF5252;
            --border-color: #B08850;
        }

        body {
            margin: 0;
            font-family: 'Roboto', sans-serif;
            background-color: var(--background-color);
            color: var(--text-color);
            padding: 20px;
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        h2, h3, h4 {
            color: var(--primary-color);
            margin: 10px 0;
            padding: 10px 10px 10px 0;
            border-bottom: 2px solid var(--primary-color);
            width: calc(100% - 20px);
            text-align: left;
        }

        fieldset {
            border: 1px solid var(--border-color);
            border-radius: 10px;
            padding: 20px;
            width: 90%;
            max-width: 600px;
            background-color: white;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }

        table {
            width: 100%;
            border-collapse: collapse;
            margin: 10px 0;
        }

        th, td {
            border: 1px solid var(--border-color);
            padding: 8px;
            text-align: left;
        }

        th {
            background-color: var(--primary-color);
            color: white;
        }

        .top-links {
            width: 100%;
            display: flex;
            justify-content: space-between;
            margin-bottom: 20px;
        }

        .link-button {
            display: inline-block;
            padding: 10px 15px;
            background-color: var(--primary-color);
            color: white;
            text-decoration: none;
            border-radius: 5px;
            text-align: center;
        }

        .link-button:hover {
            background-color: var(--secondary-color);
        }

        .logout {
            color: var(--error-color);
            text-decoration: none;
            padding: 10px 15px;
            background-color: var(--background-color);
            border: 1px solid var(--error-color);
            border-radius: 5px;
        }

        .logout:hover {
            background-color: var(--error-color);
            color: white;
        }

        .content-container {
            display: flex;
            justify-content: space-between;
            flex-wrap: wrap;
            gap: 20px;
            padding: 10px 10px;
            width: 100%;
        }

        .content-box {
            flex: 1;
            min-width: 45%;
            background-color: white;
            padding: 15px;
            border: 1px solid var(--border-color);
            border-radius: 10px;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }

        .submit {
            margin-top: 7px;
        }
    </style>
)";

#endif