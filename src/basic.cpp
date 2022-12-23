#include "./nthu_bike.h"
int *type_idx;

void basic(string selectedCase)
{
    // insert your code here
    cerr << "Basic Verson for " << selectedCase << endl;

    readcase(selectedCase);
    floyd_warshall();
    quick_sort(user, 0, max_user_id);
    quick_sort(bike, 0, max_bike_id);
    type_idx = new int[max_bike_type + 2];
    type_idx[max_bike_type + 1] = max_bike_id + 1;
    for (int i = max_bike_id; i >= 0; i--)
        type_idx[bike[i].type] = i;
    max_record_id = 0;

    for (int i = 0; i < max_user_id; i++)
    {
        User &request = user[i];
        int distance = edge[request.start][request.end];
        if (request.end_time - request.start_time < distance)
            continue;
        double mx = -1;
        int mx_idx;
        for (int j = 0; j < request.size(); j++)
        {
            int type = request[j];
            for (int k = type_idx[type]; k < type_idx[type + 1]; k++)
            {
                Bike &cur = bike[k];
                if (cur.station == request.start && cur.aviable <= request.start_time && cur.count < count_limit)
                {
                    if (mx == -1)
                    {
                        mx = cur.price;
                        mx_idx = k;
                        break;
                    }
                    else if (cur.price == mx)
                    {
                        if (cur.id < bike[mx_idx].id)
                        {
                            mx_idx = k;
                            break;
                        }
                    }
                    else if (cur.price > mx)
                    {
                        mx = cur.price;
                        mx_idx = k;
                        break;
                    }
                }
            }
        }
        if (mx != -1)
        {
            request.accept = true;
            record[max_record_id].rider = request.id;
            record[max_record_id].start = request.start;
            record[max_record_id].end = request.end;

            Bike &cur = bike[mx_idx];
            request.bike_id = cur.id;
            record[max_record_id].bike_id = cur.id;

            request.used_start = request.start_time;
            record[max_record_id].start_time = request.start_time;

            request.used_end = request.start_time + distance;
            record[max_record_id].end_time = request.start_time + distance;

            request.revenue = distance * cur.price;
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
    }

    over = true;
    quick_sort(user, 0, max_user_id);
    quick_sort(bike, 0, max_bike_id);
    max_record_id--;
    quick_sort(record, 0, max_record_id);
    writecase(selectedCase);
}