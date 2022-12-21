#include "./nthu_bike.h"

void floyd_warshall()
{
    // undirected graph we can just compute half matrix
    for (int k = 0; k < MAX_STATION; k++)
        for (int i = 0; i < MAX_STATION; i++)
            for (int j = i + 1; j < MAX_STATION; j++)
                if (edge[i][k] + edge[k][j] < edge[i][j])
                    edge[i][j] = edge[i][k] + edge[k][j];
    for (int i = 0; i < MAX_STATION; i++)
        for (int j = i - 1; j >= 0; j--)
            edge[i][j] = edge[j][i];
}

