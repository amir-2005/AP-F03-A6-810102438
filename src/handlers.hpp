#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include <map>
#include <string>
#include "Utaste.hpp"

#include "../server/server.hpp"

class LoginHandler : public RequestHandler {
public:
    LoginHandler(UTaste _utaste) : utaste(_utaste) {};
    Response* callback(Request*) override;

private:
    UTaste& utaste;
};

class SignUpHandler : public RequestHandler {
public:
    SignUpHandler(UTaste _utaste) : utaste(_utaste) {};
    Response* callback(Request*) override;

private:
    UTaste& utaste;
};

class UploadHandler : public RequestHandler {
public:
    Response* callback(Request*) override;
};

class ColorHandler : public TemplateHandler {
public:
    ColorHandler(const std::string& filePath);
    std::map<std::string, std::string> handle(Request* req) override;
};

#endif // HANDLERS_HPP_INCLUDE
