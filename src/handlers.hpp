#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include <map>
#include <string>
#include "Utaste.hpp"

#include "../server/server.hpp"

class ShowLogin : public TemplateHandler
{
public:
    ShowLogin(string file_path) : TemplateHandler(file_path) {};
    map<string, string> handle(Request *req) override;
};

class LoginHandler : public RequestHandler
{
public:
    LoginHandler(UTaste &_utaste) : utaste(_utaste) {};
    Response *callback(Request *) override;

private:
    UTaste &utaste;
};

class SignUpHandler : public RequestHandler
{
public:
    SignUpHandler(UTaste &_utaste) : utaste(_utaste) {};
    Response *callback(Request *) override;

private:
    UTaste &utaste;
};

class DashboardHandler : public TemplateHandler
{
public:
    DashboardHandler(string file_path, UTaste &_utaste) : TemplateHandler(file_path), utaste(_utaste) {};
    map<string, string> handle(Request *req) override;
    Response *callback(Request *) override;

private:
    UTaste &utaste;
};

class LogoutHandler : public RequestHandler
{
public:
    LogoutHandler(UTaste &_utaste) : utaste(_utaste) {};
    Response *callback(Request *) override;

private:
    UTaste &utaste;
};

class ReservationForm : public TemplateHandler
{
public:
    ReservationForm(string path, UTaste &_utaste) : TemplateHandler(path), utaste(_utaste) {};
    Response *callback(Request *) override;
    map<string, string> handle(Request *req) override;

private:
    UTaste &utaste;
};

class ReservationHandler : public RequestHandler
{
public:
    ReservationHandler(UTaste &_utaste) : utaste(_utaste) {};
    Response *callback(Request *) override;

private:
    UTaste &utaste;
};

class ReserveListHandler : public TemplateHandler
{
public:
    ReserveListHandler(string path, UTaste &_utaste) : TemplateHandler(path), utaste(_utaste) {}
    Response *callback(Request *) override;
    map<string, string> handle(Request *req) override;

private:
    UTaste &utaste;
};

class BudgetPage : public TemplateHandler
{
public:
    BudgetPage(string path, UTaste &_utaste) : TemplateHandler(path), utaste(_utaste) {}
    Response *callback(Request *) override;
    map<string, string> handle(Request *req) override;

private:
    UTaste &utaste;
};

class BudgetHandler : public RequestHandler
{
public:
    BudgetHandler(UTaste &_utaste) : utaste(_utaste) {};
    Response *callback(Request *) override;

private:
    UTaste &utaste;
};

#endif
