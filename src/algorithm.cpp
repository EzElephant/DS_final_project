#include "./nthu_bike.h"

void floyd_warshall()
{
    // undirected graph we can just compute half matrix
    for (int k = 0; k <= max_station_id; k++)
        for (int i = 0; i <= max_station_id; i++)
        {
            int dist_ki = (k < i) ? edge[k][i] : edge[i][k];
            if (k == i || dist_ki == 9487)
                continue;
            for (int j = i + 1; j <= max_station_id; j++)
            {
                int dist_kj = (k < j) ? edge[k][j] : edge[j][k];
                if (k == j || dist_kj == 9487)
                    continue;
                if (dist_ki + dist_kj < edge[i][j])
                    edge[i][j] = dist_ki + dist_kj;
            }
        }

    for (int i = 0; i <= max_station_id; i++)
        for (int j = i - 1; j >= 0; j--)
            edge[i][j] = edge[j][i];
}

