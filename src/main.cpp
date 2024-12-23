#include "Terminal.hpp"

int main(int argc, char*argv[])
{
    if (argc!=3)
        return 1;

    UTaste program(argv[1],argv[2]);
    Terminal terminal(program);

    return 0;
}