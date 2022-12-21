#include "./nthu_bike.h"
stringstream ss;
double discount;
int count_limit;
int max_user_id;
double ori_price[MAX_BIKE];
Bike bike[MAX_BIKE];
ll edge[MAX_STATION][MAX_STATION];
User user[MAX_USER];

void readcase(string selectedCase)
{
    read_bikeinfo(selectedCase);
    read_bike(selectedCase);
    read_map(selectedCase);
    read_user(selectedCase);
}

void read_bikeinfo(string selectedCase)
{
    string path = "./testcases/" + selectedCase + "/bike_info.txt";
    ifstream file(path);
    if (!file.is_open())
        cerr << '\t' << "could not open file " << path;
    ss.str("");
    ss.clear();
    ss << file.rdbuf();
    ss >> discount >> count_limit;
    char ch;
    int idx;
    while (ss >> ch >> idx)
        ss >> ori_price[idx];
}

void read_bike(string selectedCase)
{
    string path = "./testcases/" + selectedCase + "/bike.txt";
    ifstream file(path);
    if (!file.is_open())
        cerr << '\t' << "could not open file " << path;
    ss.str("");
    ss.clear();
    ss << file.rdbuf();
    char ch;
    while (ss >> ch)
    {
        int type, id;
        ss >> type >> id;
        bike[id].type = type;
        bike[id].id = id;
        ss >> ch >> bike[id].station >> bike[id].price >> bike[id].count;
    }
}

void read_map(string selectedCase)
{
    // init map
    for (int i = 0; i < MAX_STATION; i++)
        for (int j = 0; j < MAX_STATION; j++)
        {
            if (i == j)
                edge[i][j] = 0;
            else
                edge[i][j] = 1e18 + 87;
        }

    string path = "./testcases/" + selectedCase + "/map.txt";
    ifstream file(path);
    if (!file.is_open())
        cerr << '\t' << "could not open file " << path;
    ss.str("");
    ss.clear();
    ss << file.rdbuf();
    char ch;
    while (ss >> ch)
    {
        int u, v, w;
        ss >> u >> ch >> v >> w;
        edge[u][v] = w;
        edge[v][u] = w;
    }
}

void read_user(string selectedCase)
{
    string path = "./testcases/" + selectedCase + "/user.txt";
    ifstream file(path);
    if (!file.is_open())
        cerr << '\t' << "could not open file " << path;
    ss.str("");
    ss.clear();
    ss << file.rdbuf();
    char ch;
    while (ss >> ch)
    {
        int id;
        string buffer;
        ss >> id;
        user[id].id = id;
        max_user_id = max(max_user_id, id);
        ss >> ch;
        ss >> buffer;
        int accept_n = 0;
        for (auto tmp : buffer)
        {
            if (tmp == 'B')
            {
                continue;
            }
            else if (tmp == ',')
            {
                user[id].accept_bike.push_back(accept_n);
                accept_n = 0;
            }
            else
            {
                accept_n *= 10;
                accept_n += (tmp - '0');
            }
        }
        user[id].accept_bike.push_back(accept_n);
        ss >> user[id].start_time >> user[id].end_time >> ch >> user[id].start >> ch >> user[id].end;
    }
}