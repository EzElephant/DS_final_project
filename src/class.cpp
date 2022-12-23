#include "./nthu_bike.h"

// Bike
Bike &Bike::operator=(const Bike &other)
{
    type = other.type;
    id = other.id;
    station = other.station;
    count = other.count;
    price = other.price;
    aviable = other.aviable;
    return *this;
}

bool Bike::operator<(const Bike &rhs)
{
    if (!over)
    {
        if (type != rhs.type)
            return type < rhs.type;
        else if (count != rhs.count)
            return count < rhs.count;
        else
            return id < rhs.id;
    }
    else
    {
        if (station != rhs.station)
            return station < rhs.station;
        else
            return id < rhs.id;
    }
}

bool Bike::operator>(const Bike &rhs)
{
    if (!over)
    {
        if (type != rhs.type)
            return type > rhs.type;
        else if (count != rhs.count)
            return count > rhs.count;
        else
            return id > rhs.id;
    }
    else
    {
        if (station != rhs.station)
            return station > rhs.station;
        else
            return id > rhs.id;
    }
}

// User
User::User() : _size(0), _capacity(1), accept(false)
{
    accept_bike = new int[1];
}

bool User::operator<(const User &rhs)
{
    if (!over)
    {
        if (start_time != rhs.start_time)
            return start_time < rhs.start_time;
        else
            return id < rhs.id;
    }
    else
    {
        return id < rhs.id;
    }
}

bool User::operator>(const User &rhs)
{
    if (!over)
    {
        if (start_time != rhs.start_time)
            return start_time > rhs.start_time;
        else
            return id > rhs.id;
    }
    else
    {
        return id > rhs.id;
    }
}

int &User::operator[](int idx)
{
    if (idx < 0)
        return accept_bike[_size + idx];
    return accept_bike[idx];
}

void User::push(int val)
{
    if (_size == _capacity)
    {
        _capacity = (_capacity == 0) ? 1 : _capacity * 2;
        int *new_data = new int[_capacity];
        for (int i = 0; i < _size; i++)
            new_data[i] = accept_bike[i];
        delete[] accept_bike;
        accept_bike = new_data;
    }
    accept_bike[_size++] = val;
}

int User::size() { return _size; }

bool Record::operator<(const Record &rhs)
{
    return rider < rhs.rider;
}

bool Record::operator>(const Record &rhs)
{
    return rider > rhs.rider;
}