#include "./nthu_bike.h"

void writecase(string selectedCase)
{
    write_station(selectedCase);
    write_user(selectedCase);
    write_record(selectedCase);
}

void write_station(string selectedCase)
{
    string path = "./result/" + selectedCase + "/station_status.txt";
    ofstream file(path);
    if (!file.is_open())
        cerr << '\t' << "could not open file " << path;
    for (int i = 0; i <= max_bike_id; i++)
        file << 'S' << bike[i].station << ' ' << bike[i].id << " B" << bike[i].type << ' ' << bike[i].price << ' ' << bike[i].count << '\n';
}

void write_user(string selectedCase)
{
    string path = "./result/" + selectedCase + "/user_result.txt";
    ofstream file(path);
    if (!file.is_open())
        cerr << '\t' << "could not open file " << path;
    for (int i = 0; i <= max_user_id; i++)
    {
        file << 'U' << user[i].id;
        if (user[i].accept)
        {
            file << " 1 " << user[i].bike_id << ' ' << user[i].used_start << ' ' << user[i].used_end << ' ' << user[i].revenue << '\n';
        }
        else
        {
            file << " 0 0 0 0 0\n";
        }
    }
}

void write_record(string selectedCase)
{
    string path = "./result/" + selectedCase + "/transfer_log.txt";
    ofstream file(path);
    if (!file.is_open())
        cerr << '\t' << "could not open file " << path;
    for (int i = 0; i <= max_record_id; i++)
    {
        file << record[i].bike_id << " S" << record[i].start << " S" << record[i].end << ' ' << record[i].start_time << ' ' << record[i].end_time << " U" << record[i].rider << '\n';
    }
}
