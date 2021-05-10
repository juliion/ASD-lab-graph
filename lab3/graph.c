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
    return gr;
}


void setCoordinatesVertices(int n, int x0, int y0, int distance, vertex** vertices)
{
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
}

int** createAdjacencyMatrix(int n)
{
    int seed = 309;
    double k = 1.0 - ((seed / 10) % 10) * 0.02 - (seed % 10) * 0.005 - 0.25;
    int** matrix = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
        matrix[i] = (int*)malloc(n * sizeof(int));

    srand(seed);
    for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = (double)k * ((double)rand() / (double)RAND_MAX * 2) > 1.0 ? 1 : 0;
	return matrix;
}

void makeSymmetricMatrix(int** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
             if(matrix[i][j] == 1)
                matrix[j][i] = 1;
             else if(matrix[j][i])
                matrix[i][j] = 1;
        }
    }
}
