#include<windows.h>
#include<math.h>
#include <unistd.h>
#include <stdio.h>
#include "graph.h"
#include "draw_graph.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char ProgName[]="Лабораторна робота 6";
const int  N = 10;

typedef struct stack {
    int items[10];
    int top;
} stack;

stack* createStack()
{
    stack* st = malloc(sizeof(stack));
    st->top = 0;
    return st;
}

int stackIsEmpty(stack *st) {
  if(st->top == 0)
    return 1;
  else
    return 0;
}

void push_stack(stack* st, int value)
{
    if (st->top < N) {
        st->items[st->top] = value;
        st->top++;
    }
}

int pop_stack(stack* st)
{
     st->top--;
}

int getTop(stack* st) {
    if (st->top > 0)
        return st->items[st->top - 1];
    else
        return -1;
}

int dfs(struct graph* gr, int startVertex, int end)
{
    int** adjacencyMatrix = createAdjacencyMatrix(N);
    int* visited = malloc(N * sizeof(int));
    int currVertex;
    stack* st = createStack();
    push_stack(st, startVertex);
    visited[startVertex] = 1;
    while(!stackIsEmpty(st))
    {
        currVertex = getTop(st);
        for (int i = 0; i < N; i++) {
            if (adjacencyMatrix[currVertex][i]) {
                if(i == end)
                    return 1;
                if(!visited[i])
                {
                    visited[i] = 1;
                    push_stack(st, i);
                    break;
                }
            }
            if (i == N - 1)
            {
                pop_stack(st);
            }
        }
    }
    return 0;
}

int loop(int start, int end, int** visited) {
    if (start == end)
        return 1;
    if (visited[start] && visited[end])
        return 1;
    return 0;
}

void prim(HDC hdc, struct graph* gr, int cur)
{
    int visitedEdges = 0, totalWeight = 0, start, end;
    int** weight = gr->weightMatrix;
    int* visited = malloc(N * sizeof(int));
    visited[cur] = 1;
    while (visitedEdges < N - 1) {
        int num = 200;
        for (int i = 0; i < N; i++) {
            if (!visited[i])
                continue;
            for (int j = i; j < N; j++) {
                if (weight[i][j] && weight[i][j] < num) {
                    num = weight[i][j];
                    start = i;
                    end = j;
                }
            }
        }
        if (loop(start, end, visited) && dfs(gr, start, end)) {
            weight[start][end] = 0;
        }
        else
        {
            HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 200, 0));
            drawVertix(hdc, pen, gr->vertices, start);
            drawEdgeNotOrient(hdc, pen, gr, start, end, 1);
            drawVertix(hdc, pen, gr->vertices, start);
            drawVertix(hdc, pen, gr->vertices, end);
            totalWeight += num;
            weight[start][end] = 0;
            visited[start] = 1;
            visited[end] = 1;
            visitedEdges++;
            sleep(2);
        }
    }
    printf("\nTotal weight: %d", totalWeight);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w;

    w.lpszClassName=ProgName;
    w.hInstance=hInstance;
    w.lpfnWndProc=WndProc;
    w.hCursor=LoadCursor(NULL, IDC_ARROW);
    w.hIcon=0;
    w.lpszMenuName=0;
    w.hbrBackground = LTGRAY_BRUSH;
    w.style=CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;

    hWnd=CreateWindow(ProgName,
        "Лабораторна робота 6. Виконала Іонова Ю.",
        WS_OVERLAPPEDWINDOW,
        900,
        100,
        600,
        800,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);

    printMatrix();
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    while(GetMessage(&lpMsg, hWnd, 0, 0)) {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
    return(lpMsg.wParam);
    }


LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
    {
    HDC hdc;
    PAINTSTRUCT ps;

    switch(messg){
        case WM_PAINT :
            hdc = BeginPaint(hWnd, &ps);
            int x0 = 100;
            int y0 = 100;
            int dist = 100;
            graph* graph = createGraph(N, 0);
            setCoordinatesVertices(N, x0, y0, dist, graph);
            HPEN pen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
            drawEdges(hdc, graph, N, 0);
            drawVertices(hdc, graph->vertices, N);
            prim(hdc, graph, 0);
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}

void printMatrix()
{
    AllocConsole();
    FILE* pf;
    freopen_s(&pf, "CONOUT$", "w", stdout);
    int** matrix = createAdjacencyMatrix(N);
    makeSymmetricMatrix(matrix, N);
    int** wMatrix = createWeightMatrix(N, matrix);
    printf("Adjacency matrix:\n");
    printf("    ");
    for (int k = 0; k < N; k++)
        printf("%d  ", k + 1);
    printf("\n    -----------------------------\n");
	for (int i = 0; i < N; i++)
	{
	    if(i >= 9)
            printf("%d| ", i + 1);
        else
	        printf("%d | ", i + 1);
		for (int j = 0; j < N; j++)
		{
			printf("%d  ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("Weight matrix:\n");
	printf("    ");
    for (int k = 0; k < N; k++)
        printf("%d    ", k + 1);
    printf("\n    ------------------------------------------------\n");
	for (int i = 0; i < N; i++)
	{
	    if(i >= 9)
            printf("%d| ", i + 1);
        else
	        printf("%d | ", i + 1);
		for (int j = 0; j < N; j++)
		{
		    if(wMatrix[i][j] <= 9)
                printf("%d    ", wMatrix[i][j]);
            else if(wMatrix[i][j] <= 99)
                printf("%d   ", wMatrix[i][j]);
            else if(wMatrix[i][j] <= 999)
                printf("%d  ", wMatrix[i][j]);

		}
		printf("\n");
	}
}
