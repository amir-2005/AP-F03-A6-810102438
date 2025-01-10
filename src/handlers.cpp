#include "handlers.hpp"

using namespace std;

Response* LoginHandler::callback(Request* req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");

    utaste.login(username, password);

    Response* res = Response::redirect("/rand");
    res->setSessionId(SESSION_LOGGED_IN);
    return res;
}

Response* SignUpHandler::callback(Request* req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");

    utaste.signUp(username, password);

    Response* res = Response::redirect("/rand");
    res->setSessionId(SESSION_LOGGED_IN);
    return res;
}

Response* UploadHandler::callback(Request* req) {
    std::string name = req->getBodyParam("file_name");
    std::string file = req->getBodyParam("file");
    utils::writeToFile(file, name);
    Response* res = Response::redirect("/");
    return res;
}

ColorHandler::ColorHandler(const std::string& filePath)
    : TemplateHandler(filePath) {}

std::map<std::string, std::string> ColorHandler::handle(Request* req) {
    std::string newName = "I am " + req->getQueryParam("name");
    std::map<std::string, std::string> context;
    context["name"] = newName;
    context["color"] = req->getQueryParam("color");
    return context;
}
