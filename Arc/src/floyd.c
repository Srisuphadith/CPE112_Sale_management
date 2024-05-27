#include <stdio.h>
#define V 4
#define INF 99999
void printSolution(int dist[][V]);
void floydWarshall(int dist[][V])
{
    int i, j, k;
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distance matrix
    printSolution(dist);
}

/* A utility function to print solution */
void printSolution(int dist[][V])
{
    printf(
        "The following matrix shows the shortest distances"
        " between every pair of vertices \n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// driver's code
// int main()
// {
//     /* Let us create the following weighted graph
//             10
//        (0)------->(3)
//         |         /|\
//       5 |          |
//         |          | 1
//        \|/         |
//        (1)------->(2)
//             3           */
//     int graph[V][V] = { { 0, 5, INF, 10 },
//                         { INF, 0, 3, INF },
//                         { INF, INF, 0, 1 },
//                         { INF, INF, INF, 0 } };

//     // Function call
//     floydWarshall(graph);
//     return 0;
// }

void bubbleSort(int *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int* suggestionCat(int category, const char *cateFile, char *floyd) {
    int col[4];
    FILE* fp = fopen(cateFile, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    int *arr = (int *)malloc(4 * sizeof(int));
    if (arr == NULL) {
        perror("Failed to allocate memory");
        fclose(fp);
        return NULL;
    }

    char floyd_category_buffer[255];
    int i = 0;
    while (fgets(floyd_category_buffer, sizeof(floyd_category_buffer), fp) != NULL && i <= category) {
        if (sscanf(floyd_category_buffer, "%d,%d,%d,%d", &col[0], &col[1], &col[2], &col[3]) == 4) {
            // Assuming we are collecting data from the specified category
            if (i == category) {
                for (int j = 0; j < 4; j++) {
                    arr[j] = col[j];
                }
                break;
            }
        }
        i++;
    }

    fclose(fp);

    // Sort the array using bubbleSort
    bubbleSort(arr, 4);

    return arr;
}