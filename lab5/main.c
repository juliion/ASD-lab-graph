#include<windows.h>
#include<math.h>
#include <unistd.h>
#include <stdio.h>
#include "graph.h"
#include "draw_graph.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char ProgName[]="Лабораторна робота 5";
const int  N = 10;


typedef struct queue {
    int items[10];
    int front;
    int last;
}queue;

typedef struct stack {
    int items[10];
    int top;
} stack;

queue* createQueue() {
    queue* q = malloc(sizeof(queue));
    q->front = -1;
    q->last = -1;
    return q;
}

stack* createStack()
{
    stack* st = malloc(sizeof(queue));
    st->top = 0;
    return st;
}

int queueIsEmpty(queue* q) {
    if(q->last == -1)
        return 1;
    else
        return 0;
}

int stackIsEmpty(stack *st) {
  if(st->top == 0)
    return 1;
  else
    return 0;
}

void push(queue* q, int value)
{
    if (q->front == -1)
        q->front = 0;
    q->last++;
    q->items[q->last] = value;
}

void push_stack(stack* st, int value)
{
    if (st->top < N) {
        st->items[st->top] = value;
        st->top++;
    }
}

int pop(queue* q)
{
    int item;
    if (queueIsEmpty(q)) {
        item = -1;
    }
    else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->last) q->front = q->last = -1;
    }
    return item;
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


void bfs(HDC hdc, struct graph* gr, int startVertex)
{
    int treeMatrix[10][10] = {
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 }
    };
    int** adjacencyMatrix = createAdjacencyMatrix(N);
    int* visited = malloc(N * sizeof(int));
    int currVertex;
    struct queue* plan = createQueue();
    int counter = 1;
    visited[startVertex] = counter;
    push(plan, startVertex);
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 200, 0));
    drawVertix(hdc, pen, gr->vertices, startVertex);
    while(!queueIsEmpty(plan))
    {
        currVertex = pop(plan);
        for (int i = 0; i < N; i++) {
            if (adjacencyMatrix[currVertex][i] && !visited[i]) {
                counter++;
                visited[i] = counter;
                push(plan, i);
                drawEdgeOrient(hdc, pen, gr, currVertex, i);
                drawVertix(hdc, pen, gr->vertices, currVertex);
                drawVertix(hdc, pen, gr->vertices, i);
                treeMatrix[currVertex][i] = 1;
                sleep(1);
            }
        }
    }
    printf("Tree Matrix:\n");
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
			printf("%d  ", treeMatrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	counter = 1;
	for(int i = 0; i < N; i++)
    {
         printf("%d: ", counter);
        for(int j = 0; j < N; j++)
        {
            if(visited[j] == counter)
                printf("%d \n", j + 1);
        }
            counter++;
    }

}

void dfs(HDC hdc, struct graph* gr, int startVertex)
{
    int treeMatrix[10][10] = {
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 }
    };
    int** adjacencyMatrix = createAdjacencyMatrix(N);
    int* visited = malloc(N * sizeof(int));
    int currVertex;
    stack* st = createStack();
    push_stack(st, startVertex);
    int counter = 1;
    visited[startVertex] = counter;
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 200, 0));
    drawVertix(hdc, pen, gr->vertices, startVertex);
    while(!stackIsEmpty(st))
    {
        currVertex = getTop(st);
        pop_stack(st);
        for (int i = 0; i < N; i++) {
            if (adjacencyMatrix[currVertex][i] && !visited[i]) {
                counter++;
                visited[i] = counter;
                push_stack(st, i);
                drawEdgeOrient(hdc, pen, gr, currVertex, i);
                drawVertix(hdc, pen, gr->vertices, currVertex);
                drawVertix(hdc, pen, gr->vertices, i);
                treeMatrix[currVertex][i] = 1;
                sleep(1);
                break;
            }
        }
    }

    printf("Tree Matrix:\n");
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
			printf("%d  ", treeMatrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	counter = 1;
	for(int i = 0; i < N; i++)
    {
         printf("%d: ", counter);
        for(int j = 0; j < N; j++)
        {
            if(visited[j] == counter)
                printf("%d \n", j + 1);
        }
            counter++;
    }

}


// доробити щоб була одна арка
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
        "Лабораторна робота 5. Виконала Іонова Ю.",
        WS_OVERLAPPEDWINDOW,
        900,
        100,
        600,
        800,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);

    //printMatrix();
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
            graph* graphOrient = createGraph(N, 1);
            setCoordinatesVertices(N, x0, y0, dist, graphOrient);
            HPEN pen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
            drawEdges(hdc, graphOrient, N, 1);
            drawVertices(hdc, graphOrient->vertices, N);
            //bfs(hdc, graphOrient, 7);
            dfs(hdc, graphOrient, 7);
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
}

