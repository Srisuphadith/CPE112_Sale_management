#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct floyd{
    int position;
    int floydValue;
}floyd;

int** readAllData(const char* cateFile, int* numRows, int* numCols) {
    FILE* fp = fopen(cateFile, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    char buffer[1024];
    *numRows = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        (*numRows)++;
    }

    fseek(fp, 0, SEEK_SET);

    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        fclose(fp);
        return NULL;
    }

    *numCols = 0;
    char *token = strtok(buffer, " ");
    while (token != NULL) {
        (*numCols)++;
        token = strtok(NULL, " ");
    }

    int** arr = (int**)malloc(*numRows * sizeof(int*));
    if (arr == NULL) {
        perror("Failed to allocate memory for rows");
        fclose(fp);
        return NULL;
    }
    for (int i = 0; i < *numRows; i++) {
        arr[i] = (int*)malloc(*numCols * sizeof(int));
        if (arr[i] == NULL) {
            perror("Failed to allocate memory for columns");
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            fclose(fp);
            return NULL;
        }
    }

    fseek(fp, 0, SEEK_SET);

    int i = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        int j = 0;
        token = strtok(buffer, " ");
        while (token != NULL) {
            arr[i][j] = atoi(token);
            j++;
            token = strtok(NULL, " ");
        }
        i++;
    }

    fclose(fp);
    return arr;
}

void floydWarshall(int** dist, int V) {
    int i, j, k;
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

int *printSortedRow(int** arr, int numRows, int numCols, int chosenRowIndex) {
    floyd *sortSuggest = (floyd *)malloc(numCols * sizeof(floyd));
    if (chosenRowIndex < 0 || chosenRowIndex >= numRows) {
        printf("Invalid row index\n");
    }
    int* row = (int*)malloc((numCols) * sizeof(int));
    if (row == NULL) {
        perror("Failed to allocate memory for row");
    }
    int k = 0;
    for (int j = 0; j <= numCols; j++) {
            sortSuggest[k++].floydValue = arr[chosenRowIndex][j];
            sortSuggest[k].position = j+1;
    }

for (int i = 0; i <= numCols - 2; i++) {
    for (int j = 0; j <= numCols - 2 - i; j++) {
        if (sortSuggest[j].floydValue < sortSuggest[j + 1].floydValue) {
            floyd temp = sortSuggest[j];
            sortSuggest[j] = sortSuggest[j + 1];
            sortSuggest[j + 1] = temp;
        }
    }
}

    for (int i = 0; i <= numCols - 1; i++) {
        printf("%d | %d\n", sortSuggest[i].position , sortSuggest[i].floydValue);
    }
    printf("\n");

    for(int i = 0; i <= numCols - 1; i++){
        row[i] = (sortSuggest[i].position + 1);
        printf("%d ", row[i]);
    }

    return row;
}

void dealWithFloyd(int *productChose) {
    char* cateFile = "csv/cateFile.csv";  // Path to the cateFile
    int numRows = 0;
    int numCols = 0;
    int** result = readAllData(cateFile, &numRows, &numCols);

    if (result != NULL) {
        // Assuming the number of columns determines the value of V
        int V = numCols;

        // Run the Floyd-Warshall algorithm
        floydWarshall(result, V);
        // printf("DB2");

        // Print the sorted row (e.g., row index 1)
        printSortedRow(result, numRows, numCols, *productChose);

        // Free allocated memory
        for (int i = 0; i < numRows; i++) {
            free(result[i]);
        }
        free(result);
    }
}

int main(){
    int product;
    scanf("%d", &product);
    product--;
    dealWithFloyd(&product);
    return 0;

}