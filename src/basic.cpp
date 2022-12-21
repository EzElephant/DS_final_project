#include "./nthu_bike.h"

void basic(string selectedCase)
{
    // insert your code here
    cerr << "Basic Verson for " << selectedCase << endl;

    readcase(selectedCase);
    floyd_warshall();
    quick_sort(user, 0, max_user_id);
}