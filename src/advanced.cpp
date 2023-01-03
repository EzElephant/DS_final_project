#include "./nthu_bike.h"
#include <chrono>
#include <ctime>
const int GAP = 10;

void advanced(string selectedCase)
{
    // insert your code here
    auto T_start = std::chrono::system_clock::now();
    cerr << "Advanced Verson for " << selectedCase << endl;

    adv = true;
    readcase(selectedCase);
    floyd_warshall();
}