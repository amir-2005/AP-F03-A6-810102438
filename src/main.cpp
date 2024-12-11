#include "Utaste.hpp"
#include "Terminal.hpp"

int main()
{
    string path1 = "./Restaurants.csv";
    string path2 = "./Districts.csv";
    UTaste program(path1,path2);
    Terminal terminal;

    return 0;
}