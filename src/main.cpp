#include "Terminal.hpp"

// int main(int argc, char*argv[])
int main()
{
    // if (argc!=4)
    //     return 1;

    string argv[4]={"", "./Restaurants.csv", "./Districts.csv", "./Discounts.csv"};

    UTaste program(argv[1],argv[2],argv[3]);
    Terminal terminal(program);

    return 0;
}