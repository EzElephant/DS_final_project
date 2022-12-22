#include "./nthu_bike.h"

void floyd_warshall()
{
    // undirected graph we can just compute half matrix
    for (int k = 0; k <= max_station_id; k++)
        for (int i = 0; i <= max_station_id; i++)
            for (int j = i + 1; j <= max_station_id; j++)
                if (edge[i][k] + edge[k][j] < edge[i][j])
                    edge[i][j] = edge[i][k] + edge[k][j];
    for (int i = 0; i <= max_station_id; i++)
        for (int j = i - 1; j >= 0; j--)
            edge[i][j] = edge[j][i];
}

