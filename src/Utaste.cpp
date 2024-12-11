#include "Utaste.hpp"

UTaste::UTaste()
{
}

void UTaste::loadDistrictsData(string path_to_districts)
{
    // ifstream rests_file(path_to_restaurants);
    // if (!rests_file)
    //     throw(invalid_argument("Cant open " + path_to_restaurants));
    ifstream districts_file(path_to_districts);
    if (!districts_file)
        throw(invalid_argument("Cant open " + path_to_districts));

    vector<vector<string>> neighbors;
    string line, district_name, neighbor_name;
    int i = 0;

    getline(districts_file, line);
    while (getline(districts_file, line))
    {
        neighbors.push_back({});
        stringstream ss(line);
        getline(ss, district_name, DELIM);

        districts.push_back(make_shared<District>(district_name));

        while (getline(ss, neighbor_name, INNER_DELIM))
        {
            neighbors[i].push_back(neighbor_name);
        }

        i++;
    }
}