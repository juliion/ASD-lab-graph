#pragma once

typedef struct vertex
{
    char name[17];
    int x;
    int y;
}vertex;

typedef struct graph
{
    int x0;
    int y0;
    int endX;
    int endY;
    int n;
    struct vertex** vertices;
    int** adjacencyMatrix;
}graph;


graph* createGraph(int n, int oriented);
void setCoordinatesVertices(int n, int x0, int y0, int distance, graph* gr);
int** createAdjacencyMatrix(int n);
void makeSymmetricMatrix(int** matrix, int n);

