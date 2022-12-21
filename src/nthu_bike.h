#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <random>
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

    bool operator<(const User &rhs)
    {
        if (start_time != rhs.start_time)
            return start_time < rhs.start_time;
        else
            return id < rhs.id;
    }

    bool operator>(const User &rhs)
    {
        if (start_time != rhs.start_time)
            return start_time > rhs.start_time;
        else
            return id > rhs.id;
    }
};

const int MAX_USER = 100087;
const int MAX_BIKE = 10087;
const int MAX_STATION = 1001;
const int CUT = 50;

static mt19937 rng(random_device{}());

extern stringstream ss; // 共用節省資源

extern double discount;
extern int count_limit;
extern int max_user_id;
extern double ori_price[MAX_BIKE];
extern Bike bike[MAX_BIKE];
extern ll edge[MAX_STATION][MAX_STATION];
extern User user[MAX_USER];

// basic.cpp
void basic(string selectedCase);

// advanced.cpp
void advanced(string selectedCase);

// read.cpp
void readcase(string selectedCase);
void read_bikeinfo(string selectedCase);
void read_bike(string selectedCase);
void read_map(string selectedCase);
void read_user(string selectedCase);

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

template <typename T> void 
quick_sort(T *arr, int left, int right)
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
