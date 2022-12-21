#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
typedef long long ll;

template <typename T>
class myvector
{
public:
    myvector() : v_size(0), v_capacity(0), data(nullptr) {}
    myvector(int n, const T &val = T())
        : v_size(n), v_capacity(n), data(new T[n])
    {
        for (int i = 0; i < n; i++)
            data[i] = val;
    }
    ~myvector() { delete[] data; }

    int size() const { return v_size; }

    T &operator[](int idx)
    {
        if (idx < 0)
            return data[v_size + idx];
        return data[idx];
    }

    void push_back(const T &val)
    {
        if (v_size == v_capacity)
        {
            v_capacity = (v_capacity == 0) ? 1 : v_capacity * 2;
            T *new_data = new T[v_capacity];
            for (int i = 0; i < v_size; i++)
                new_data[i] = data[i];
            delete[] data;
            data = new_data;
        }
        data[v_size++] = val;
    }

private:
    T *data;
    int v_size, v_capacity;
};

class Bike
{
public:
    int type, id, station, count;
    double price;
};

class User
{
public:
    int id, start_time, end_time, start, end;
    myvector<int> accept_bike;
};

const int MAX_USER = 100087;
const int MAX_BIKE = 10087;
const int MAX_STATION = 1087;

extern stringstream ss; // 共用節省資源

extern double discount;
extern int count_limit;
extern double ori_price[MAX_BIKE];
extern Bike bike[MAX_BIKE];
extern ll edge[MAX_STATION][MAX_STATION];
extern User user[MAX_USER];

void basic(string selectedCase);
void advanced(string selectedCase);

void readcase(string selectedCase);
void read_bikeinfo(string selectedCase);
void read_bike(string selectedCase);
void read_map(string selectedCase);
void read_user(string selectedCase);
