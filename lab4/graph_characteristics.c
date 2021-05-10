#include <stdio.h>
#include "graph_characteristics.h"

int* countDegreesNotOrient(int** adjMatrix, int n)
{
    int* degrees = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
    {
        degrees[i] = 0;
        for(int j = 0; j < n; j++)
        {
            if(adjMatrix[i][j])
            {
                degrees[i]++;
                if(i == j)
                    degrees[i]++;
            }
        }
    }
    return degrees;
}

int* countOutdegrees(int** adjMatrix, int n)
{
    int* outdegrees = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
    {
        outdegrees[i] = 0;
        for(int j = 0; j < n; j++)
        {
            if(adjMatrix[j][i])
            {
                outdegrees[i]++;
            }
        }
    }
    return outdegrees;
}

int* countIndegrees(int** adjMatrix, int n)
{
    int* indegrees = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
    {
        indegrees[i] = 0;
        for(int j = 0; j < n; j++)
        {
            if(adjMatrix[i][j])
            {
                indegrees[i]++;
            }
        }
    }
    return indegrees;
}

void printDegrees(int* degrees, int n, char sign)
{
    for(int i  = 0; i < n; i++)
    {
        printf("deg%c(V%d): %d \n", sign, i+1, degrees[i]);
    }
}

int homogeneousNotOrientGr(int* degrees, int n)
{
    int r = degrees[0];
    for(int i = 0; i < n; i++)
    {
        if(r != degrees[i])
        {
            r = -1;
            break;
        }
    }
    return r;
}

int homogeneousOrientGr(int* indegrees, int* outdegrees, int n)
{
    int r = indegrees[0];
    for(int i = 0; i < n; i++)
    {
        if(r != indegrees[i] || r != outdegrees[i])
        {
            r = -1;
            break;
        }
    }
    return r;
}

void printIsolatedAndExternalVert(int* degrees, int* indegrees, int* outdegrees, int n)
{
    int foundIsolV = 0;
    int foundExtV = 0;
    for (int i = 0; i < n; i++)
    {
        if(indegrees[i] == 0 && outdegrees == 0)
        {
            printf("V%d is isolated vertex in oriented graph\n", i+1);
            foundIsolV = 1;
        }
        if(indegrees[i] == 1 && outdegrees[i] == 0 ||
           indegrees[i] == 0 && outdegrees[i] == 1)
        {
            printf("V%d is external vertex in  oriented graph\n", i+1);
            foundExtV = 1;
        }
        if(degrees[i] == 0)
        {
            printf("V%d is isolated vertex in not oriented graph\n", i+1);
            foundIsolV = 1;
        }
        if(degrees[i] == 1)
        {
            printf("V%d is external vertex in not oriented graph\n", i+1);
             foundExtV = 1;
        }
    }
    if(foundIsolV == 0)
       printf("No isolated vertices found\n");
    if(foundExtV == 0)
       printf("No external vertices found\n\n");
}

void printWays(int** matrix, int n)
{
    int count = 0;
    printf("Ways of length 2\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                for (int k = 0; k < n; k++) {
                    if (matrix[j][k] == 1)
                    {
                        if(i == 9 && k == 9)
                            printf(" %d->%d->%d ", i + 1, j + 1, k + 1);
                        else if(i == 9 || j == 9 || k == 9)
                            printf(" %d->%d->%d  ", i + 1, j + 1, k + 1);
                        else
                            printf(" %d->%d->%d   ", i + 1, j + 1, k + 1);
                        count++;
                        if(count == 10)
                        {
                            printf("\n");
                            count = 0;
                        }
                    }
                }
            }
        }
    }
    count = 0;
    printf("\n\n");
    printf("Ways of length 3\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                for (int k = 0; k < n; k++) {
                    if (matrix[j][k] == 1) {
                        for (int m = 0; m < n; m++) {
                            if (matrix[k][m] == 1) {
                                if(i != 9 && j != 9 && k != 9 && m != 9)
                                    printf(" %d->%d->%d->%d   ", i + 1, j + 1, k + 1, m + 1);
                                else
                                    printf(" %d->%d->%d->%d  ", i + 1, j + 1, k + 1, m + 1);
                                count++;
                                if(count == 8)
                                {
                                    printf("\n");
                                    count = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
   }
   printf("\n\n");
}

int** createReachMatrix(int** adjMatrix, int n)
{
    int** reachMatrix = createAdjacencyMatrix_2(n);
    for (int k = 0; k < n; k++)
    {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    reachMatrix[i][j] = reachMatrix[i][j] ||
                                       (reachMatrix[i][k] && reachMatrix[k][j]) ||
                                       (i == j);
                        }
                    }
                }
    return reachMatrix;
}

int** createConnectionMatrix(int** reachMatrix, int n)
{
    int** connectionMatrix = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
        connectionMatrix[i] = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            connectionMatrix[i][j] = 1;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            if(reachMatrix[i][j] == 0)
            {
                connectionMatrix[i][j] = 0;
                connectionMatrix[j][i] = 0;
            }
        }
    return connectionMatrix;
}

int** components(int** connMatrix, int n)
{
    int** components = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
        components[i] = (int*)malloc(n * sizeof(int));
    int usedVert[n];
    for(int i = 0; i < n; i++)
     {
         usedVert[i] = 0;
         for(int j = 0; j < n; j++)
            components[i][j] = 0;
     }
      int countery = 0;
    for (int count = 0; count < n; count++) {
        for (int i = 0; i < n; i++) {
            if (usedVert[i] == 1)
                continue;
            for (int j = 0; j < n; j++) {
                if (connMatrix[count][j] != connMatrix[i][j])
                    break;
                if (j == n - 1) {
                    usedVert[i] = 1;
                    components[countery][i] = 1;
                    }
                }
            }
        for (int i = 0; i < n; i++) {
                if (components[countery][i]) countery++;
        }
    }
    return components;
}

void printComponents(int** components, int n)
{
    int count = 0;
    for(int i = 0; i < n; i++)
    {
        if(count <= n-1)
            printf("| Comp %d:", i + 1);
        for(int j = 0; j < n; j++)
        {
            if(components[i][j])
            {
                printf(" %d ", j + 1);
                count++;
            }
        }
    }
}
