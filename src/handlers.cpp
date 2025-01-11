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
    return res;
}

map<string, string> DashboardHandler::handle(Request *req)
{
    map<string, string> contex;
    // if (utaste.current_user->getName() != req->getSessionId())
    //     throw(PermissionDenied(MSG_PERMISSION_DENIED_NO_USER));

    contex["username"] = req->getSessionId();
    return contex;
}

map<string, string> ShowLogin::handle(Request *req)
{
    map<string, string> contex;
    contex["situation"] = req->getSessionId();
    return contex;
}
