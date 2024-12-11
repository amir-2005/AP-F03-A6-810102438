#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include "libraries.hpp"
using namespace std;

class BadRequest : public exception
{
public:
    BadRequest(const string &msg)
    {
        message = BAD_REQUEST_MSG;
    }

    const char *what() const throw()
    {
        return default_message.c_str();
    }

private:
    string message;
    string default_message = BAD_REQUEST_MSG;
};

class Empty : public exception
{
public:
    Empty(const string &msg)
    {
        message = msg;
    }

    const char *what() const throw()
    {
        return default_message.c_str();
    }

private:
    string message;
    string default_message = EMPTY_MSG;
};

class PermissionDenied : public exception
{
public:
    PermissionDenied(const string &msg)
    {
        message = msg;
    }

    const char *what() const throw()
    {
        return default_message.c_str();
    }

private:
    string message;
    string default_message = PERMISSION_DENIED_MSG;
};

class NotFound : public exception
{
public:
    NotFound(const string &msg)
    {
        message = msg;
    }

    const char *what() const throw()
    {
        return default_message.c_str();
    }

private:
    string message;
    string default_message = NOT_FOUND_MSG;

};

#endif