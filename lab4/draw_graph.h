#pragma once
#include<windows.h>
#include <math.h>
#include "graph.h"

void drawVertices(HDC hdc, vertex** vertices, int n);
void drawEdge(HDC hdc, int** adjacencyMatrix, vertex** vertices, int n, int oriented);
int lieOnDiagonal(int x1, int y1, int x2, int y2, int x3, int y3);
void drawLoop(HDC hdc, int x0, int y0, int endX, int x, int y);
void arrow(HDC hdc, float fi, int px, int py);
void drawLoopWithArrow(HDC hdc, int x0, int y0, int endX, int x, int y);
void drawDoubleArc(HDC hdc, int x1, int y1, int x2, int y2, int midX, int midY);
void drawCondGraph(HDC hdc, int** adjMatrix, int** compon, int n);
