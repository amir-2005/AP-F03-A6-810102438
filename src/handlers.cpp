#include "handlers.hpp"

using namespace std;

Response *LoginHandler::callback(Request *req)
{
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");

    Response *res = Response::redirect("/dashboard");
    res->setSessionId(username);

    try
    {
        utaste.login(username, password);
    }
    catch (const PermissionDenied &e)
    {
        res = Response::redirect("/login");
        res->setSessionId(PERMISSION_DENIED_MSG);
    }
    catch (const NotFound &e)
    {
        res = Response::redirect("/login");
        res->setSessionId(NOT_FOUND_MSG);
    }

    return res;
}

Response *SignUpHandler::callback(Request *req)
{
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");

    utaste.signUp(username, password);

    Response *res = Response::redirect("/dashboard");
    res->setSessionId(username);
    return res;
}

Response *LogoutHandler::callback(Request *req)
{
    try
    {
        utaste.logout();
    }
    catch (const PermissionDenied &e)
    {
        cout << "Repeated Request";
    }

    Response *res = Response::redirect("/");
    res->setSessionId("");
    return res;
}

map<string, string> DashboardHandler::handle(Request *req)
{
    map<string, string> contex;
    contex["username"] = req->getSessionId();
    return contex;
}

Response *DashboardHandler::callback(Request *req)
{
    map<string, string> context;
    context = this->handle(req);
    Response *res = new Response();

    if (utaste.current_user == nullptr || utaste.current_user->getName() != req->getSessionId())
    {
        res = Response::redirect("/");
        res->setSessionId("");
    }
    else
    {
        res->setHeader("Content-Type", "text/html");
        res->setBody(parser_->getHtml(context));
    }
    return res;
}

map<string, string> ShowLogin::handle(Request *req)
{
    map<string, string> contex;
    contex["situation"] = req->getSessionId();
    return contex;
}

map<string, string> ReservationForm::handle(Request *req)
{
    map<string, string> contex;
    for (auto r : utaste.rests)
        contex[r->name] = "REST";

    contex["msg"] = utaste.last_error_msg.reservation;
    utaste.last_error_msg.reservation = "";
    return contex;
}

Response *ReservationForm::callback(Request *req)
{
    map<string, string> context;
    context = this->handle(req);
    Response *res = new Response();

    if (utaste.current_user == nullptr || utaste.current_user->getName() != req->getSessionId())
    {
        res = Response::redirect("/");
        res->setSessionId("");
    }
    else
    {
        res->setHeader("Content-Type", "text/html");
        res->setBody(parser_->getHtml(context));
    }
    return res;
}

Response *ReservationHandler::callback(Request *req)
{
    Response *res;
    string restaurant_name = req->getBodyParam(ARG_KEY_RESTAURANT_NAME);
    int table_id = stoi(req->getBodyParam(ARG_KEY_TABLE_ID));
    string start_time = req->getBodyParam(ARG_KEY_START_TIME);
    string end_time = req->getBodyParam(ARG_KEY_END_TIME);
    string foods = req->getBodyParam("food_data");

    time_period reserve_time = make_pair(stoi(start_time), stoi(end_time));
    stringstream ss(foods);
    map<food, int> reserve_foods;
    string token;

    while (getline(ss, token, INNER_DELIM))
    {

        stringstream itemStream(token);
        string key;
        string value;

        getline(itemStream, key, DELIM);
        getline(itemStream, value);

        reserve_foods[key] = stoi(value);
    }

    try
    {
        utaste.setReservation(restaurant_name, table_id, reserve_time, reserve_foods);
        res = Response::redirect("/reserve_list");
        res->setSessionId(utaste.current_user->getName());
    }
    catch (const PermissionDenied &e)
    {
        res = Response::redirect("/reservation");
        utaste.last_error_msg.reservation = e.message;
    }
    catch (const NotFound &e)
    {
        res = Response::redirect("/reservation");
        utaste.last_error_msg.reservation = e.message;
    }
    catch (const Empty &e)
    {
        res = Response::redirect("/reservation");
        utaste.last_error_msg.reservation = e.message;
    }
    catch (const BadRequest &e)
    {
        res = Response::redirect("/reservation");
        utaste.last_error_msg.reservation = e.message;
    }

    return res;
}

map<string, string> ReserveListHandler::handle(Request *req)
{
    map<string, string> context;
    vector<vector<string>> reserve_list;
    int index = 0;
    try
    {
        reserve_list = utaste.current_user->getReservationsInfo("", 0);
    }
    catch (const Empty &e)
    {
        utaste.last_error_msg.reserve_list = e.message;
    }
    for (auto reserve : reserve_list)
        for (auto str : reserve)
        {
            context[to_string(index)] = str;
            index++;
        }

    context["msg"] = utaste.last_error_msg.reserve_list;
    utaste.last_error_msg.reserve_list = "";
    return context;
}

Response *ReserveListHandler::callback(Request *req)
{
    map<string, string> context;
    Response *res = new Response();

    if (utaste.current_user == nullptr || utaste.current_user->getName() != req->getSessionId())
    {
        res = Response::redirect("/");
        res->setSessionId("");
    }
    else
    {
        context = this->handle(req);
        res->setHeader("Content-Type", "text/html");
        res->setBody(parser_->getHtml(context));
    }
    return res;
}

map<string, string> BudgetPage::handle(Request *req)
{
    map<string, string> context;
    context["budget"] = utaste.showBudget();
    context["msg"] = utaste.last_error_msg.budget;
    utaste.last_error_msg.budget = "";
    return context;
}

Response *BudgetPage::callback(Request *req)
{
    map<string, string> context;
    Response *res = new Response();

    if (utaste.current_user == nullptr || utaste.current_user->getName() != req->getSessionId())
    {
        res = Response::redirect("/");
        res->setSessionId("");
    }
    else
    {
        context = this->handle(req);
        res->setHeader("Content-Type", "text/html");
        res->setBody(parser_->getHtml(context));
    }
    return res;
}

Response *BudgetHandler::callback(Request *req)
{
    Response *res;
    string charge_str = req->getBodyParam("budget");
    long long charge = stoi(charge_str);
    try
    {
        utaste.increaseBudget(charge);
        res = Response::redirect("/budget");
        res->setSessionId(utaste.current_user->getName());
    }
    catch (const BadRequest &e)
    {
        res = Response::redirect("/budget");
        utaste.last_error_msg.budget = e.message;
    }

    return res;
}