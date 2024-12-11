#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include "libraries.hpp"
using namespace std;

class BadRequest : public exception
{
public:
    BadRequest(const string &msg)
    {
        message = msg;
    }

    const char *what() const throw()
    {
        return message.c_str();
    }

private:
    string message;
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
        return message.c_str();
    }

private:
    string message;
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
        return message.c_str();
    }

private:
    string message;
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
        return message.c_str();
    }

private:
    string message;
};

#endif