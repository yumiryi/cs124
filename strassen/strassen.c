//
//  strassen.c
//  Yumi Yi
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

// variables
FILE *file;
int N;
int CROSS = 16; // crosover point

// prototypes
void create_matrix(int **A, int **B);
int triangles(int **A, int dim, float p);
int **add(int **A, int op, int **B, int dim);
int **standard(int **A, int **B, int dim);
int **strassen(int **A, int **B, int dim);
int **submatrix(int **A, int flag, int dim);

// // main
// args: ./strassen 0 dimension inputfile
int main(int argc, const char * argv[])
{
    // seed random number generator
    srand(time(0));

    // read inputs
    file = fopen(argv[3], "r");
    N = atoi(argv[2]);

    if (file == NULL)
    {
        printf("Input file cannot be opened.\n");
        return 1;
    }

    // allocate memory for input matrices
    int **A = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        A[i] = (int *)malloc(N * sizeof(int));
    }
    int **B = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        B[i] = (int *)malloc(N * sizeof(int));
    }

    // convert input file to matrices
    create_matrix(A, B);

    // compute using strassen's algorithm
    int **output = strassen(A, B, N);

    // print diagonal
    for (int i = 0; i < N; i++)
    {
        printf("%d\n", output[i][i]);
    }
    printf("\n");

    // free memory
	for(int i = 0; i < N; i++){free(A[i]);}
	free(A);
	for(int i = 0; i < N; i++){free(B[i]);}
	free(B);
	for(int i = 0; i < N; i++){free(output[i]);}
	free(output);

    fclose(file);
}

// convert input file to matrices
void create_matrix(int **A, int **B)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fscanf(file, "%d", &A[i][j]);
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fscanf(file, "%d", &B[i][j]);
        }
    }
}

// compute numer of triangles in matrix
int triangles(int **A, int dim, float p)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            A[i][j] = 0;
            if (i < j)
            {
                if ((rand() % 100) < (p*100))
                {
                    A[i][j] = 1;
                }
            }
            else
            {
                A[i][j] = A[j][i];
            }
        }
    }

    int **output = strassen(A, strassen(A, A, N), N);
    int sum = 0;

    for (int i = 0; i < N; i++)
    {
        sum += output[i][i];
    }

	for(int i = 0; i < N; i++){free(output[i]);}
	free(output);

    return sum / 6;
}

// add or subtract matrices
int **add(int **A, int op, int **B, int dim)
{
    // memory allocation
    int **final = (int **)malloc(dim * sizeof(int *));
    for (int i = 0; i < dim; i++)
    {
        final[i] = (int *)malloc(dim * sizeof(int));
    }

    // body
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (op == 1)
            {
                final[i][j] = A[i][j] + B[i][j];
            }
            else if (op == -1)
            {
                final[i][j] = A[i][j] - B[i][j];
            }
            else
            {
                printf("Invalid operator\n");
            }
        }
    }

    return final;
}

// standard matrix multiplication algorithm
int **standard(int **A, int **B, int dim)
{
    // memory allocation
    int *prods = malloc(dim * sizeof(int));
    int **final = (int **)malloc(dim * sizeof(int *));
    for (int i = 0; i < dim; i++)
    {
        final[i] = (int *)malloc(dim * sizeof(int));
    }

    // body
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            for (int k = 0; k < dim; k++)
            {
                // compute products
                prods[k] = A[i][k] * B[k][j];
            }
            // store sum of products
            int sum = prods[0];
            for (int k = 1; k < dim; k++)
            {
                sum += prods[k];
            }
            final[i][j] = sum;
        }
    }

    free(prods);
    return final;
}

// strassen's algorithm
int **strassen(int **A, int **B, int dim)
{
    // if below threshold, use standard algorithm
    if (dim <= CROSS)
    {
        return standard(A, B, dim);
    }

    // initialize submatrices
    int **a;
    int **b;
    int **c;
    int **d;
    int **e;
    int **f;
    int **g;
    int **h;

    // if dimension is odd, pad with one more row and column of 0s
    if (dim % 2)
    {
        dim += 1;

        int **newA = (int **)malloc(dim * sizeof(int *));
        for (int i = 0; i < dim; i++)
        {
            newA[i] = (int *)malloc(dim * sizeof(int));
        }
        int **newB = (int **)malloc(dim * sizeof(int *));
        for (int i = 0; i < dim; i++)
        {
            newB[i] = (int *)malloc(dim * sizeof(int));
        }

        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                if (i == (dim-1) || j == (dim-1))
                {
                    newA[i][j] = 0;
                }
                else
                {
                    newA[i][j] = A[i][j];
                }
            }
        }

        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                if (i == (dim-1) || j == (dim-1))
                {
                    newB[i][j] = 0;
                }
                else
                {
                    newB[i][j] = B[i][j];
                }
            }
        }

        a = submatrix(newA, 0, dim);
        b = submatrix(newA, 1, dim);
        c = submatrix(newA, 2, dim);
        d = submatrix(newA, 3, dim);
        e = submatrix(newB, 0, dim);
        f = submatrix(newB, 1, dim);
        g = submatrix(newB, 2, dim);
        h = submatrix(newB, 3, dim);

        for(int i = 0; i < dim; i++){free(newA[i]);}
        free(newA);
        for(int i = 0; i < dim; i++){free(newB[i]);}
        free(newB);
    }
    // if dimension is even, use matrices as is
    else
    {
        a = submatrix(A, 0, dim);
        b = submatrix(A, 1, dim);
        c = submatrix(A, 2, dim);
        d = submatrix(A, 3, dim);
        e = submatrix(B, 0, dim);
        f = submatrix(B, 1, dim);
        g = submatrix(B, 2, dim);
        h = submatrix(B, 3, dim);
    }

    // compute strassen products
    int **p1 = strassen(a, add(f, -1, h, dim/2), dim/2);
    int **p2 = strassen(add(a, 1, b, dim/2), h, dim/2);
    int **p3 = strassen(add(c, 1, d, dim/2), e, dim/2);
    int **p4 = strassen(d, add(g, -1, e, dim/2), dim/2);
    int **p5 = strassen(add(a, 1, d, dim/2), add(e, 1, h, dim/2), dim/2);
    int **p6 = strassen(add(b, -1, d, dim/2), add(g, 1, h, dim/2), dim/2);
    int **p7 = strassen(add(a, -1, c, dim/2), add(e, 1, f, dim/2), dim/2);

    // compute terms of final product
    a = add(add(add(p5, 1, p4, dim/2), -1, p2, dim/2), 1, p6, dim/2);
    b = add(p1, 1, p2, dim/2);
    c = add(p3, 1, p4, dim/2);
    d = add(add(add(p5, 1, p1, dim/2), -1, p3, dim/2), -1, p7, dim/2);

    // insert terms into final matrix
    int **final = (int **)malloc(dim * sizeof(int *));
    for (int i = 0; i < dim; i++)
    {
        final[i] = (int *)malloc(dim * sizeof(int));
    }

    for (int i = 0; i < dim/2; i++)
    {
        for (int j = 0; j < dim/2; j++)
        {
            final[i][j] = a[i][j];
        }
    }

    for (int i = 0; i < dim/2; i++)
    {
        for (int j = dim/2; j < dim; j++)
        {
            final[i][j] = b[i][j - (dim/2)];
        }
    }

    for (int i = dim/2; i < dim; i++)
    {
        for (int j = 0; j < dim/2; j++)
        {
            final[i][j] = c[i - (dim/2)][j];
        }
    }

    for (int i = dim/2; i < dim; i++)
    {
        for (int j = dim/2; j < dim; j++)
        {
            final[i][j] = d[i - (dim/2)][j - (dim/2)];
        }
    }

	for(int i = 0; i < dim/2; i++){free(a[i]);}
	free(a);
    for(int i = 0; i < dim/2; i++){free(b[i]);}
	free(b);
    for(int i = 0; i < dim/2; i++){free(c[i]);}
	free(c);
    for(int i = 0; i < dim/2; i++){free(d[i]);}
	free(d);
    for(int i = 0; i < dim/2; i++){free(e[i]);}
	free(e);
    for(int i = 0; i < dim/2; i++){free(f[i]);}
	free(f);
    for(int i = 0; i < dim/2; i++){free(g[i]);}
	free(g);
    for(int i = 0; i < dim/2; i++){free(h[i]);}
	free(h);
    for(int i = 0; i < dim/2; i++){free(p1[i]);}
	free(p1);
    for(int i = 0; i < dim/2; i++){free(p2[i]);}
	free(p2);
    for(int i = 0; i < dim/2; i++){free(p3[i]);}
	free(p3);
    for(int i = 0; i < dim/2; i++){free(p4[i]);}
	free(p4);
    for(int i = 0; i < dim/2; i++){free(p5[i]);}
	free(p5);
    for(int i = 0; i < dim/2; i++){free(p6[i]);}
	free(p6);
    for(int i = 0; i < dim/2; i++){free(p7[i]);}
	free(p7);

    return final;
}

// compute the four submatrices of a matrix
int **submatrix(int **A, int flag, int dim)
{
    // memory allocation
    int **final = (int **)malloc((dim/2) * sizeof(int *));
    for (int i = 0; i < dim/2; i++)
    {
        final[i] = (int *)malloc((dim/2) * sizeof(int));
    }

    // flag 0 -> upper left submatrix; flag 1 -> upper right submatrix
    if (flag == 0 || flag == 1)
    {
        for (int i = 0; i < (dim/2); i++)
        {
            if (flag == 0)
            {
                for (int j = 0; j < (dim/2); j++)
                {
                    final[i][j] = A[i][j];
                }
            }
            else if (flag == 1)
            {
                for (int j = dim/2; j < dim; j++)
                {
                    final[i][j - (dim/2)] = A[i][j];
                }               
            }
        }
    }
    // flag 2 -> lower left submatrix; flag 3 -> lower right submatrix
    else if (flag == 2 || flag == 3)
    {
        for (int i = (dim/2); i < dim; i++)
        {
            if (flag == 2)
            {
                for (int j = 0; j < (dim/2); j++)
                {
                    final[i - (dim/2)][j] = A[i][j];
                }
            }
            else if (flag == 3)
            {
                for (int j = (dim/2); j < dim; j++)
                {
                    final[i - (dim/2)][j - (dim/2)] = A[i][j];
                }               
            }
        }
    }
    else
    {
        printf("Error finding submatrices\n");
    }

    return final;
}