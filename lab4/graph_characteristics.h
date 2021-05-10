#pragma once

int* countDegreesNotOrient(int** adjMatrix, int n);
int* countOutdegrees(int** adjMatrix, int n);
int* countIndegrees(int** adjMatrix, int n);
void printDegrees(int* degrees, int n, char sign);
int homogeneousNotOrientGr(int* degrees, int n);
int homogeneousOrientGr(int* indegrees, int* outdegrees, int n);
void printIsolatedAndExternalVert(int* degrees, int* indegrees, int* outdegrees, int n);
void printWays(int** matrix, int n);
int** createReachMatrix(int** adjMatrix, int n);
int** createConnectionMatrix(int** reachMatrix, int n);
int** components(int** connMatrix, int n);
void printComponents(int** components, int n);


