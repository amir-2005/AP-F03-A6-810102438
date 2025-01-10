#include "Terminal.hpp"

int main(int argc, char*argv[])
{
    if (argc!=4)
        return 1;
        
    UTaste program(argv[1],argv[2], argv[3]);
    Terminal terminal(program);

    return 0;
}