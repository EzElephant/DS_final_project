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

    for (int i = 0; i < max_user_id; i++)
    {
        User &request = user[i];
        int distance = edge[request.start][request.end];
        if (request.end_time - request.start_time < distance)
            continue;
        int mx = -1, mx_idx;
        for (int j = 0; j < request.size(); j++)
        {
            int type = request[j];
            for (int k = type_idx[type]; k < type_idx[type + 1]; k++)
            {
                Bike &cur = bike[k];
                if (cur.station == request.start && cur.aviable <= request.start_time && cur.count < count_limit)
                {
                    if (mx = -1)
                    {
                        mx = distance * cur.price;
                        mx_idx = k;
                    }
                    else if (distance * cur.price > mx)
                    {
                        mx = distance * cur.price;
                        mx_idx = k;
                    }
                }
            }
        }
        if (mx != -1)
        {
            Bike &cur = bike[mx_idx];
            cur.price -= discount;
            cur.count++;
            cur.station = request.end;
            cur.aviable = request.start_time + distance;
            while (mx_idx <= max_bike_id && bike[mx_idx] < bike[mx_idx + 1])
            {
                swap(bike[mx_idx], bike[mx_idx + 1]);
                mx_idx++;
            }
        }
    }
}