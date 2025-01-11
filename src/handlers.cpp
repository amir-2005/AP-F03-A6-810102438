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

    contex["msg"] = utaste.last_error_msg;
    cout<<req->getSessionId();
    return contex;
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
        utaste.last_error_msg = e.message;
    }
    catch (const NotFound &e)
    {
        res = Response::redirect("/reservation");
        utaste.last_error_msg = e.message;
    }
    catch (const Empty &e)
    {
        res = Response::redirect("/reservation");
        utaste.last_error_msg = e.message;
    }

    return res;
}