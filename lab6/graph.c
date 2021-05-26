#include <stdlib.h>
#include "graph.h"

graph* createGraph(int n, int oriented)
{
    graph* gr = malloc(sizeof(graph));
    gr->n = n;
    gr->vertices = (vertex*)malloc(n * sizeof(vertex));
    for (int i = 0; i < n; i++)
	{
	    vertex* vert = (vertex*)malloc(sizeof(vertex));
	    gr->vertices[i] = vert;
		itoa(i + 1, vert->name, 10);
	}
	gr->adjacencyMatrix = createAdjacencyMatrix(n);
	if(oriented == 0)
        makeSymmetricMatrix(gr->adjacencyMatrix, n);
    gr->weightMatrix = createWeightMatrix(n, gr->adjacencyMatrix);
    return gr;
}


void setCoordinatesVertices(int n, int x0, int y0, int distance, graph* gr)
{
    vertex** vertices = gr->vertices;
    int gaps[4] = {2, 2, 2, 1};
    int dx = 16, dy = 16;
    int size = n - 1;
    while(size - 4 >= 8)
    {
        for(int i = 0; i < 4; i++)
            gaps[i]++;
        size -= 4;
    }
    int dif = size - 8;
    for(int i = 0; i < dif; i++)
        gaps[i]++;

    vertices[0]->x = x0;
    vertices[0]->y = y0;
    int xPrev = x0;
    int yPrev = y0;
    int endX = 0;
    int endY = 0;
    int n1 = gaps[0] + 1;
    int n2 = gaps[1] + 1;
    int n3 = gaps[2] + 1;
    int n4 = gaps[3] + 2;
    int newDistance;
    for(int i = 1; i < n - 1; i++)
    {
        xPrev = vertices[i - 1]->x;
        yPrev = vertices[i - 1]->y;
        if (gaps[0] > 0)
        {
            vertices[i]->x = xPrev + distance;
            vertices[i]->y = yPrev;
            if(gaps[0] == 1)
                endX = vertices[i]->x;
            gaps[0]--;
        }
        else if (gaps[1] > 0)
        {
            vertices[i]->x = xPrev;
            vertices[i]->y = yPrev + distance;
            if(gaps[1] == 1)
                endY = vertices[i]->y;
            gaps[1]--;
        }
        else if (gaps[2] > 0)
        {
            if(n3 < n1)
            {
                newDistance = (x0 + endX - n3 * dx) / n3;
                vertices[i]->x = xPrev - newDistance;
            }
            else
                vertices[i]->x = xPrev - distance;
            vertices[i]->y = yPrev;
            gaps[2]--;
        }
        else if (gaps[3] > 0)
        {
             if(n4 < n2)
            {
                newDistance = (y0 + endY - n4 * dy) / n4;
                vertices[i]->y = yPrev - newDistance;
            }
            else
                vertices[i]->y = yPrev - distance;
            vertices[i]->x = xPrev;
            gaps[3]--;
        }
    }
    vertices[n - 1]->x = (x0 + endX) / 2;
    vertices[n - 1]->y = (y0 + endY) / 2;
    gr->x0 = x0;
    gr->y0 = y0;
    gr->endX = endX;
    gr->endY = endY;
}

int** initMatrix(int n)
{
    int** matrix =  (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        matrix[i] = (int*)malloc(n * sizeof(int));
    return matrix;
}

int** createAdjacencyMatrix(int n)
{
    int seed = 309;
    double k = 1.0 - ((seed / 10) % 10) * 0.01 - (seed % 10) * 0.005 - 0.05;
    int** matrix = initMatrix(n);

    srand(seed);
    for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = (double)k * ((double)rand() / (double)RAND_MAX * 2) > 1.0 ? 1 : 0;
	return matrix;
}

int** createWeightMatrix(int n, int** A)
{
    int num;
    int** Wt = initMatrix(n);
    int** B = initMatrix(n);
    int** C = initMatrix(n);
    int** D = initMatrix(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            num = roundf((rand() / (float)RAND_MAX * 2) * 100) * A[i][j];
            Wt[i][j] = num;
            if (num == 0)
                B[i][j] = 0;
            else if(num > 0)
                B[i][j] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (B[i][j] != B[j][i])
                C[i][j] = 1;
            else
                C[i][j] = 0;

            if (B[i][j] == B[j][i] && B[i][j] == 1 && j <= i)
                D[i][j] = 1;
            else
                D[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Wt[i][j] = (C[i][j] + D[i][j]) * Wt[i][j];
        }
    }
    makeSymmetricMatrix(Wt, n);
    return Wt;
}

void makeSymmetricMatrix(int** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
             if(matrix[i][j])
             {
                 matrix[j][i] = matrix[i][j];
             }

        }
    }
}


