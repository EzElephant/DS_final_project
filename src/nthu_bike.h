#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <random>
using namespace std;

class Bike
{
public:
    int type, id, station, count, aviable;
    double price;
    Bike() {}
    Bike(int id, int station, double price, int count)
        : id(id), station(station), price(price), count(count), aviable(0) {}
    Bike &operator=(const Bike &);
    bool operator<(const Bike &);
    bool operator>(const Bike &);
};

class User
{
public:
    int id, start_time, end_time, start, end, bike_id, used_start, used_end, revenue;
    bool accept;
    int *accept_bike;
    User();
    bool operator<(const User &);
    bool operator>(const User &);
    int &operator[](int);
    void push(int);
    int size();

private:
    int _capacity, _size;
};

class Record
{
public:
    int bike_id, start, end, start_time, end_time, rider;
    bool operator<(const Record &);
    bool operator>(const Record &);
};

const int MAX_USER = 100087;
const int MAX_BIKE = 10087;
const int MAX_STATION = 1001;
const int CUT = 50;

static mt19937 rng(random_device{}());

extern stringstream ss; // 共用節省資源

extern double discount;
extern int count_limit;
extern int max_bike_id, max_user_id, max_station_id, max_bike_type, max_record_id;
extern bool over;
extern double ori_price[MAX_BIKE];
extern Bike bike[MAX_BIKE];
extern int edge[MAX_STATION][MAX_STATION];
extern User user[MAX_USER];
extern int *type_idx;
extern Record record[2 * MAX_USER];

// basic.cpp
void basic(string);

// advanced.cpp
void advanced(string);

// read.cpp
void readcase(string);
void read_bikeinfo(string);
void read_bike(string);
void read_map(string);
void read_user(string);

// write.cpp
void writecase(string);
void write_station(string);
void write_user(string);
void write_record(string);

// algorithm.cpp
void floyd_warshall(void);
template <typename T>
void insertion_sort(T *arr, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        T key = arr[i];
        int j = i - 1;
        while (key < arr[j] && j >= left)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
void quick_sort(T *arr, int left, int right)
{
    if (left >= right)
        return;
    else if (right - left < CUT)
    {
        insertion_sort(arr, left, right);
        return;
    }
    int rand = left + rng() % (right - left + 1);
    if (rand != left)
        swap(arr[left], arr[rand]);
    T pivot = arr[left];
    int l = left;
    int r = right + 1;
    while (true)
    {
        while (l < right && arr[++l] < pivot)
            ;
        while (r > 0 && arr[--r] > pivot)
            ;
        if (l >= r)
            break;
        swap(arr[l], arr[r]);
    }
    swap(arr[left], arr[r]);
    quick_sort(arr, left, r - 1);
    quick_sort(arr, r + 1, right);
}
