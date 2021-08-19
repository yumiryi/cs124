//
//  randmst.c
//  Yumi Yi
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

// variables
int N;
int size = 0;

// prototypes
void createGraph(float Matrix[N][N], int dimension);
int parent(int i);
int left(int i);
int right(int i);
void swap(int *x, int *y);
void min_heapify(int H[], int i, float a[]);
void build_min_heap(int a[], int length, float b[]);
int peek (int H[]);
int extract_min (int H[], float a[]);
bool in_heap(int H[], int k);
void insert(int H[], int k, float a[]);
float prim(float Matrix[N][N], int s);

// // main
// args: ./randmst 0 numpoints numtrials dimension
int main(int argc, const char * argv[])
{
    // seed random number generator
    srand(time(0));

    // check for invalid usage
    if (argc != 5)
    {
        printf("Invalid command line form\n");
        return 1;
    }

    // read inputs
    N = atoi(argv[2]);
    int trials = atoi(argv[3]);
    int dim = atoi(argv[4]);

    // initialize total of mst weights
    float total = 0.;

    // initialize adjacency matrix of graph
    float (*Matrix)[N] = malloc(sizeof(float[N][N]));

    // calculate average and print output
    for (int i = 0; i < trials; i++)
    {
        createGraph(Matrix, dim);
        float result = prim(Matrix, 1);
        total = total + result;
    }
    float average = total / trials;
    printf("%f %d %d %d\n", average, N, trials, dim);

    // free
    free(Matrix);
    return 0;
}

// // generate graph
void createGraph(float Matrix[N][N], int dimension)
{
    // initialize coordinate arrays
    float *x = malloc (N * sizeof *x);
    float *y = malloc (N * sizeof *y);
    float *z = malloc (N * sizeof *z);
    float *w = malloc (N * sizeof *w);

    if (dimension == 2 || dimension == 3 || dimension == 4)
    {
        for (int i = 0; i < N; i++)
        {
            x[i] = ((float)rand()/RAND_MAX);
            y[i] = ((float)rand()/RAND_MAX);
        }

        if (dimension == 3 || dimension == 4)
        {
            for (int i = 0; i < N; i++)
            {
                z[i] = ((float)rand()/RAND_MAX);
            }

            if (dimension == 4)
            {
                for (int i = 0; i < N; i++)
                {
                    w[i] = ((float)rand()/RAND_MAX);
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // no vertex has an edge to itself
            if (i == j)
            {
                Matrix[i][j] = 0.;
            }
            else
            {
                if (dimension == 0)
                {
                    Matrix[i][j] = ((float)rand()/RAND_MAX);
                }
                if (dimension == 2)
                {
                    Matrix[i][j] = sqrt(pow(x[j]-x[i], 2.) + pow(y[j]-y[i], 2.));
                }
                if (dimension == 3)
                {
                    Matrix[i][j] = sqrt(pow(x[j]-x[i], 2.) + pow(y[j]-y[i], 2.) + pow(z[j]-z[i], 2.));
                }
                if (dimension == 4)
                {
                    Matrix[i][j] = sqrt(pow(x[j]-x[i], 2.) + pow(y[j]-y[i], 2.) + pow(z[j]-z[i], 2.) + pow(w[j]-w[i], 2.));
                }
                Matrix[j][i] = Matrix[i][j];
            }
        }
    }
}

// // Binary min heap
// parent, left child, right child indeces
int parent(int i)
{
    return floor(i / 2);
}

int left(int i)
{
    return 2*i;
}

int right(int i)
{
    return 2*i + 1;
}

// swap
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// min_heapify
void min_heapify(int H[], int i, float a[])
{
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l <= size && a[H[l]] < a[H[i]])
    {
        smallest = l;
    }

    if (r <= size && a[H[r]] < a[H[smallest]])
    {
        smallest = r;
    }

    if (smallest != i)
    {
        swap(&H[i], &H[smallest]);
        min_heapify(H, smallest, a);
    }
}

// build_min_heap
void build_min_heap(int a[], int length, float b[])
{
    for (int i = floor(length/2); i >= 1; i--)
    {
        min_heapify(a, i, b);
    }
}

// peek
int peek (int H[])
{
    return H[1];
}

// extract_min
int extract_min (int H[], float a[])
{
    int min = H[1];
    H[1] = H[size];
    size--;
    min_heapify(H, 1, a);
    return min;
}

// check if k is in heap H
bool in_heap(int H[], int k)
{
    for (int i = 1; i <= size; i++)
    {
        if (H[i] == k)
        {
            return true;
        }
    }
    return false;
}

// insert k into H if not already present
void insert(int H[], int k, float a[])
{
    if (!(in_heap(H, k)))
    {
        size++;
        H[size] = k;
        int i = size;
        while (i != 1 && a[H[parent(i)]] > a[H[i]])
        {
            swap(&H[parent(i)], &H[i]);
            i = parent(i);
        }
    }
}

// // Prim's algorithm
float prim(float Matrix[N][N], int s)
{
    // initialize arrays and variables
    float *dist = malloc ((N + 1) * sizeof *dist);
    int *prev = malloc ((N + 1) * sizeof *prev);
    int *inS = malloc ((N + 1) * sizeof *inS);
    size = 0;
    int *H = malloc ((size + 1) * sizeof *H);
    insert(H, 1, dist);
    for (int i = 0; i <= N; i++)
    {
        dist[i] = INFINITY;
        prev[i] = 0;
        inS[i] = 0;
    }
    dist[s] = 0;

    // do until heap is empty
    while (size != 0)
    {
        // set v to vertex with smallest distance
        int v = extract_min(H, dist);
        inS[v] = 1;
        // for every w such that (v,w) is an existing edge
        for (int w = 1; w <= N; w++)
        {
            // if w is not in the set S
            if (v != w && inS[w] == 0)
            {
                if (dist[w] > Matrix[v - 1][w - 1])
                {
                    dist[w] = Matrix[v - 1][w - 1];
                    prev[w] = v;
                    insert(H, w, dist);
                }
            }
        }
    }
    
    // initialize mst variable
    float mst = 0.;
    // follow prev pointers and add up the weights of the edges
    for (int i = N; i >= 1; i--)
    {
        if (prev[i] != 0)
        {
            mst = mst + Matrix[i-1][prev[i]-1];
        }
    }

    free(dist);
    free(prev);
    free(inS);
    free(H);
    return mst;
}