#include "./nthu_bike.h"

void advanced(string selectedCase){
    // insert your code here
    cerr << "Advanced Verson for " << selectedCase << endl;

    readcase(selectedCase);
    floyd_warshall();
}