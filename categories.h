#include <stdio.h>
#define Catagories 4

char catagories[Catagories][50] = {"A" , "B" , "C" , "D"};

// Initialize the matrix to zero
void init(int arr[][Catagories]) {
  int i, j;
  for (i = 0; i < Catagories; i++)
    for (j = 0; j < Catagories; j++)
      arr[i][j] = 0;
}
/*0 1 2 3 4 5
0   5 6
1 5
2 6
3
4
5
*/

// Add edges
void addEdge(int arr[][Catagories], int i, int j , int edgeValue) {
  arr[i][j] = edgeValue;
  arr[j][i] = edgeValue;
}