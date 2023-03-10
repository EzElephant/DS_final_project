#include "./nthu_bike.h"
#include <chrono>
#include <ctime>
const int GAP = 5;

void advanced(string selectedCase)
{
    // insert your code here
    auto T_start = std::chrono::system_clock::now();
    cerr << "Advanced Verson for " << selectedCase << endl;

    adv = true;
    readcase(selectedCase);
    floyd_warshall();
    for (int i = 0; i <= max_user_id; i++)
        user[i].distance = edge[user[i].start][user[i].end];
    PriorityQueue pq;
    for (int i = 0; i <= max_user_id; i++)
        pq.push(i);
    quick_sort(bike, 0, max_bike_id);
    type_idx = new int[max_bike_type + 2];
    type_idx[max_bike_type + 1] = max_bike_id + 1;
    for (int i = max_bike_id; i >= 0; i--)
        type_idx[bike[i].type] = i;
    max_record_id = 0;

    while (pq.size())
    {
        auto T_cur = std::chrono::system_clock::now();
        std::chrono::duration<double> T_elapsed = T_cur - T_start;
        if (T_elapsed.count() > 54.87)
            break;
        int cur = pq.top();
        pq.pop();
        User &request = user[cur];
        int distance = request.distance;
        if (request.end_time - request.start_time <= distance)
        {
            continue;
        }
        double mx = 0;
        int mx_idx = -1;
        for (int j = 0; j < request.size(); j++)
        {
            int type = request[j];
            for (int k = type_idx[type]; k < type_idx[type + 1]; k++)
            {
                Bike &cur = bike[k];
                if (cur.count >= count_limit || cur.price <= 0.0)
                    continue;
                if ((cur.station == request.start) && (cur.aviable <= request.start_time)) // 同站
                {
                    if (cur.price > mx)
                    {
                        mx = cur.price;
                        mx_idx = k;
                    }
                    break;
                }
                else if (cur.aviable + edge[cur.station][request.start] <= request.start_time) // 不同站
                {
                    if (cur.price > mx)
                    {
                        mx = cur.price;
                        mx_idx = k;
                    }
                    break;
                }
            }
        }
        if (mx != 0)
        {
            Bike &cur = bike[mx_idx];
            if (cur.station != request.start)
            {
                record[max_record_id].rider = -1;
                record[max_record_id].start = cur.station;
                record[max_record_id].end = request.start;
                record[max_record_id].bike_id = cur.id;
                record[max_record_id].start_time = cur.aviable;
                record[max_record_id].end_time = cur.aviable + edge[cur.station][request.start];
                max_record_id++;
            }

            request.accept = true;
            record[max_record_id].rider = request.id;
            record[max_record_id].start = request.start;
            record[max_record_id].end = request.end;

            request.bike_id = cur.id;
            record[max_record_id].bike_id = cur.id;

            request.used_start = request.start_time;
            record[max_record_id].start_time = request.start_time;

            request.used_end = request.start_time + distance;
            record[max_record_id].end_time = request.start_time + distance;

            request.revenue = distance * (cur.price + 0.000001);
            cur.price -= discount;
            cur.count++;
            cur.station = request.end;
            cur.aviable = request.start_time + distance;
            max_record_id++;
            // update position of bike
            while (mx_idx < max_bike_id && bike[mx_idx] > bike[mx_idx + 1])
            {
                swap(bike[mx_idx], bike[mx_idx + 1]);
                mx_idx++;
            }
        }
        else
        {
            if (T_elapsed.count() > 44.87)
            {
                continue;
            }
            request.start_time += GAP;
            pq.push(cur);
        }
    }

    over = true;
    quick_sort(user, 0, max_user_id);
    quick_sort(bike, 0, max_bike_id);
    max_record_id--;
    quick_sort(record, 0, max_record_id);
    writecase(selectedCase);
}