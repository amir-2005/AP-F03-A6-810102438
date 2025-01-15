#include "handlers.hpp"

using namespace std;

map<string, string> ShowLoginSignUp::handle(Request *req)
{
    map<string, string> contex;
    contex["msg"] = utaste.last_error_msg.login_signup;
    utaste.last_error_msg.login_signup = "";
    return contex;
}

Response *LoginHandler::callback(Request *req)
{
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");

    Response *res = Response::redirect("/dashboard");

    try
    {
        utaste.login(username, password);
        res->setSessionId(username);
    }
    catch (const PermissionDenied &e)
    {
        res = Response::redirect("/login");
        utaste.last_error_msg.login_signup = e.message;
    }
    catch (const NotFound &e)
    {
        res = Response::redirect("/login");
        utaste.last_error_msg.login_signup = e.message;
    }

    return res;
}

Response *SignUpHandler::callback(Request *req)
{
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    Response *res = Response::redirect("/dashboard");

    try
    {
        utaste.signUp(username, password);
        res->setSessionId(username);
    }
    catch (const PermissionDenied &e)
    {
        res = Response::redirect("/signup");
        utaste.last_error_msg.login_signup = e.message;
    }
    catch (const BadRequest &e)
    {
        res = Response::redirect("/signup");
        utaste.last_error_msg.login_signup = e.message;
    }

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

map<string, string> ReservationForm::handle(Request *req)
{
    map<string, string> contex;
    for (auto r : utaste.rests)
        contex[r->name] = "REST";

    for (auto r : utaste.rests)
        for (auto item : r->menu)
            contex[item.first] = "FOOD";

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

Response *RestaurantHandler::callback(Request *req)
{
    Response *res = new Response;

    if (utaste.current_user == nullptr || req->getSessionId() != utaste.current_user->getName())
    {
        res = Response::redirect("/");
        res->setSessionId("");
        return res;
    }

    current_rest = req->getBodyParam(ARG_KEY_RESTAURANT_NAME);

    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body << R"(  
        <!DOCTYPE html>  
        <html lang="en">  
        <head>  
        <meta charset="UTF-8">  
        <meta name="viewport" content="width=device-width, initial-scale=1.0">  
        <title>UTaste - Restaurants</title> )";
    body << STYLE_FOR_RESTAURANTS_PAGE;
    body << "</head>";

    body << R"(
    <body>
    <div class="top-links">
        <a class="link-button" href="/dashboard">Back to Dashboard</a>
        <a class="logout" href="/logout">Logout</a>
    </div>
    <fieldset>
    <h4>Reserve a Table</h4>
    <form action="/restaurants" method="POST">
        <label for="restaurant_name">Restaurant:</label>
        <select id="restaurant_name" name="restaurant_name" required>
    )";
    for (auto r : utaste.rests)
        body << "<option value=\"" << r->name << "\">" << r->name << "</option>";
    body << "</select><br>";
    body << R"(<input type="submit" class="submit" value="Show Details">)";
    body << R"(</form></fieldset><br>)";

    if (!current_rest.empty())
    {
        map<string, vector<string>> info = utaste.getRestaurantInfo(current_rest);
        body << "<h2>" << info[RESTAURANT_INFO_NAME].back() << "</h2>";
        body << "<h3>District: " << info[RESTAURANT_INFO_DISTRICT].back() << "</h3>";
        body << "<h3>Time: " << info[RESTAURANT_INFO_TIME].back() << "</h3>";

        body << R"(<div class="content-container">
            <div class="content-box">
            <h2>Menu</h2>
            <table>
                <tr><th>Item</th> <th>Price</th> </tr>)";
        for (int i = 0; i < info[RESTAURANT_INFO_MENU_ITEM].size(); i++)
        {
            body << "<tr> <td>" << info[RESTAURANT_INFO_MENU_ITEM][i] << "</td>";
            body << "<td>" << info[RESTAURANT_INFO_MENU_PRICE][i] << "</td> </tr>";
        }
        body << "</table> </div>";

        body << R"(<div class="content-box">
            <h2>Discounts</h2>
            <table>
                <tr>
                    <th>Type</th>
                    <th>Details</th>
                </tr>)";
        if (!info[RESTAURANT_INFO_ORDER_DISCOUNT].empty())
        {
            body << "<tr> <td>Order Amount Discount</td> <td>";
            body << info[RESTAURANT_INFO_ORDER_DISCOUNT].back();
            body << "</td> </tr>";
        }
        if (!info[RESTAURANT_INFO_ITEM_DISCOUNT].empty())
        {
            body << "<tr> <td>Item Specific Discount</td> <td>";
            for (auto discount : info[RESTAURANT_INFO_ITEM_DISCOUNT])
                body << discount << "<br>";
            body << "</td></tr>";
        }
        if (!info[RESTAURANT_INFO_FIRST_DISCOUNT].empty())
        {
            body << "<tr> <td>First Order Discount</td> <td>";
            body << info[RESTAURANT_INFO_FIRST_DISCOUNT].back();
            body << "</td></tr>";
        }
        body << "</table> </div> </div>";

        body << R"(<div class="content-box"> <h2>Tables</h2>
            <table id="3">
            <tr>
                <th>Id</th>
                <th>Reservation Times</th>
            </tr>)";
        for (int i = 0; i < info[RESTAURANT_INFO_TABLE].size(); i++)
        {
            body << "<tr><td>" << to_string(i + 1) << "</td>";
            body << "<td>" << info[RESTAURANT_INFO_TABLE][i] << "<td></tr>";
        }
        body << "</table> </div>";
    }
    body << "</body> </html>";
    res->setBody(body.str());
    return res;
}