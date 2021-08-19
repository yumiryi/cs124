//
//  kk.c
//  Yumi Yi
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

// variables
FILE *file;
int size;

// prototypes
void file_to_array(uint64_t *A);
uint64_t kk(uint64_t *A);
// ———————————————————————————————————————————————— // ———————————————————————————————————————————————— //
/*
void random_problem(uint64_t *A);
int *standard(void);
int *standard_n(int *S);
uint64_t standard_r(uint64_t *A, int *S);
int *prepart(void);
int *prepart_n(int *P);
uint64_t prepart_r(uint64_t *A, int *P);
int *rr_s(uint64_t *A);
int *rr_p(uint64_t *A);
int *hc_s(uint64_t *A);
int *hc_p(uint64_t *A);
double T(int i);
int *sa_s(uint64_t *A);
int *sa_p(uint64_t *A);
*/
// ———————————————————————————————————————————————— // ———————————————————————————————————————————————— //
int parent(int i);
int left(int i);
int right(int i);
void swap(uint64_t *x, uint64_t *y);
void max_heapify(uint64_t H[], int i);
void build_max_heap(uint64_t a[], int length);
uint64_t extract_max (uint64_t H[]);
void insert(uint64_t H[], uint64_t k);

// // main
// args: ./randmst 0 numpoints numtrials dimension
int main(int argc, const char * argv[])
{
    // seed random number generator
    srand(time(0));

    // check for invalid usage
    if (argc != 2)
    {
        printf("Invalid command line form\n");
        return 1;
    }

    // read input file
    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Input file cannot be opened\n");
        return 1;
    }

    // allocate array memory
    uint64_t *A = malloc(101 * sizeof(uint64_t));

    // read input file into array
    file_to_array(A);

    // compute KK residue
    uint64_t residue = kk(A);
    printf("%" PRIu64 "\n", residue);

    // ———————————————————————————————————————————————— // ———————————————————————————————————————————————— //
    /*

    uint64_t min_kk;
    uint64_t max_kk;
    double ave_kk;
    double time_kk;

    uint64_t min_rrs;
    uint64_t max_rrs;
    double ave_rrs;
    double time_rrs;

    uint64_t min_rrp;
    uint64_t max_rrp;
    double ave_rrp;
    double time_rrp;

    uint64_t min_hcs;
    uint64_t max_hcs;
    double ave_hcs;
    double time_hcs;

    uint64_t min_hcp;
    uint64_t max_hcp;
    double ave_hcp;
    double time_hcp;

    uint64_t min_sas;
    uint64_t max_sas;
    double ave_sas;
    double time_sas;

    uint64_t min_sap;
    uint64_t max_sap;
    double ave_sap;
    double time_sap;

    double ave_a;
    double ave_b;
    double time_a;
    double time_b;

    // 100 instances
    for (int i = 1; i <= 100; i++)
    {
        // generate random problem instance
        random_problem(A);

        // kk algorithm
        clock_t begin = clock();
        uint64_t res_kk = kk(A);
        clock_t end = clock();
        if (i == 1)
        {
            min_kk = res_kk;
            max_kk = res_kk;
            ave_kk = res_kk;
            time_kk = (double)(end - begin);
        }
        else
        {
            if (res_kk < min_kk)
            {
                min_kk = res_kk;
            }
            if (res_kk > max_kk)
            {
                max_kk = res_kk;
            }
            ave_a = ave_kk;
            ave_b = res_kk;
            ave_kk = (ave_a + ave_b) / 2.;
            time_a = time_kk;
            time_b = (double)(end - begin);
            time_kk = (time_a + time_b) / 2.;
        }

        // repeated random - standard
        begin = clock();
        uint64_t res_rrs = standard_r(A, rr_s(A));
        end = clock();
        if (i == 1)
        {
            min_rrs = res_rrs;
            max_rrs = res_rrs;
            ave_rrs = res_rrs;
            time_rrs = (double)(end - begin);
        }
        else
        {
            if (res_rrs < min_rrs)
            {
                min_rrs = res_rrs;
            }
            if (res_rrs > max_rrs)
            {
                max_rrs = res_rrs;
            }
            ave_a = ave_rrs;
            ave_b = res_rrs;
            ave_rrs = (ave_a + ave_b) / 2.;
            time_a = time_rrs;
            time_b = (double)(end - begin);
            time_rrs = (time_a + time_b) / 2.;
        }

        // repeated random - prepartition
        begin = clock();
        uint64_t res_rrp = prepart_r(A, rr_p(A));
        end = clock();
        if (i == 1)
        {
            min_rrp = res_rrp;
            max_rrp = res_rrp;
            ave_rrp = res_rrp;
            time_rrp = (double)(end - begin);
        }
        else
        {
            if (res_rrp < min_rrp)
            {
                min_rrp = res_rrp;
            }
            if (res_rrp > max_rrp)
            {
                max_rrp = res_rrp;
            }
            ave_a = ave_rrp;
            ave_b = res_rrp;
            ave_rrp = (ave_a + ave_b) / 2.;
            time_a = time_rrp;
            time_b = (double)(end - begin);
            time_rrp = (time_a + time_b) / 2.;
        }

        // hill climbing - standard
        begin = clock();
        uint64_t res_hcs = standard_r(A, hc_s(A));
        end = clock();
        if (i == 1)
        {
            min_hcs = res_hcs;
            max_hcs = res_hcs;
            ave_hcs = res_hcs;
            time_hcs = (double)(end - begin);
        }
        else
        {
            if (res_hcs < min_hcs)
            {
                min_hcs = res_hcs;
            }
            if (res_hcs > max_hcs)
            {
                max_hcs = res_hcs;
            }
            ave_a = ave_hcs;
            ave_b = res_hcs;
            ave_hcs = (ave_a + ave_b) / 2.;
            time_a = time_hcs;
            time_b = (double)(end - begin);
            time_hcs = (time_a + time_b) / 2.;
        }

        // hill climbing - prepartition
        begin = clock();
        uint64_t res_hcp = prepart_r(A, hc_p(A));
        end = clock();
        if (i == 1)
        {
            min_hcp = res_hcp;
            max_hcp = res_hcp;
            ave_hcp = res_hcp;
            time_hcp = (double)(end - begin);
        }
        else
        {
            if (res_hcp < min_hcp)
            {
                min_hcp = res_hcp;
            }
            if (res_hcp > max_hcp)
            {
                max_hcp = res_hcp;
            }
            ave_a = ave_hcp;
            ave_b = res_hcp;
            ave_hcp = (ave_a + ave_b) / 2.;
            time_a = time_hcp;
            time_b = (double)(end - begin);
            time_hcp = (time_a + time_b) / 2.;
        }

        // simulated annealing - standard
        begin = clock();
        uint64_t res_sas = standard_r(A, sa_s(A));
        end = clock();
        if (i == 1)
        {
            min_sas = res_sas;
            max_sas = res_sas;
            ave_sas = res_sas;
            time_sas = (double)(end - begin);
        }
        else
        {
            if (res_sas < min_sas)
            {
                min_sas = res_sas;
            }
            if (res_sas > max_sas)
            {
                max_sas = res_sas;
            }
            ave_a = ave_sas;
            ave_b = res_sas;
            ave_sas = (ave_a + ave_b) / 2.;
            time_a = time_sas;
            time_b = (double)(end - begin);
            time_sas = (time_a + time_b) / 2.;
        }

        // simulated annealing - prepartition
        begin = clock();
        uint64_t res_sap = prepart_r(A, sa_p(A));
        end = clock();
        if (i == 1)
        {
            min_sap = res_sap;
            max_sap = res_sap;
            ave_sap = res_sap;
            time_sap = (double)(end - begin);
        }
        else
        {
            if (res_sap < min_sap)
            {
                min_sap = res_sap;
            }
            if (res_sap > max_sap)
            {
                max_sap = res_sap;
            }
            ave_a = ave_sap;
            ave_b = res_sap;
            ave_sap = (ave_a + ave_b) / 2.;
            time_a = time_sap;
            time_b = (double)(end - begin);
            time_sap = (time_a + time_b) / 2.;
        }
    }

    printf("kk  (avg, min, max, time): %lf, %" PRIu64 ", %" PRIu64 ", %lf\n", ave_kk, min_kk, max_kk, time_kk);
    printf("rrs (avg, min, max, time): %lf, %" PRIu64 ", %" PRIu64 ", %lf\n", ave_rrs, min_rrs, max_rrs, time_rrs);
    printf("rrp (avg, min, max, time): %lf, %" PRIu64 ", %" PRIu64 ", %lf\n", ave_rrp, min_rrp, max_rrp, time_rrp);
    printf("hcs (avg, min, max, time): %lf, %" PRIu64 ", %" PRIu64 ", %lf\n", ave_hcs, min_hcs, max_hcs, time_hcs);
    printf("hcp (avg, min, max, time): %lf, %" PRIu64 ", %" PRIu64 ", %lf\n", ave_hcp, min_hcp, max_hcp, time_hcp);
    printf("sas (avg, min, max, time): %lf, %" PRIu64 ", %" PRIu64 ", %lf\n", ave_sas, min_sas, max_sas, time_sas);
    printf("sap (avg, min, max, time): %lf, %" PRIu64 ", %" PRIu64 ", %lf\n", ave_sap, min_sap, max_sap, time_sap);

    */
    // ———————————————————————————————————————————————— // ———————————————————————————————————————————————— //

    // cleanup
    free(A);
    fclose(file);
}

// read input file into array
void file_to_array(uint64_t *A)
{
    for (int i = 1; i <= 100; i++)
    {
        fscanf(file, "%" PRIu64, &A[i]);
    }
}

// KK algorithm
uint64_t kk(uint64_t *A)
{
    size = 100;
    uint64_t *temp = malloc(101 * sizeof(uint64_t));
    memcpy(temp, A, 101 * sizeof(uint64_t));
    build_max_heap(temp, size);
    uint64_t a = extract_max(temp);
    uint64_t b = extract_max(temp);
    while (b != 0)
    {
        uint64_t diff = a - b;
        insert(temp, diff);
        insert(temp, 0);
        a = extract_max(temp);
        b = extract_max(temp);
    }
    free(temp);
    return a;
}

// ———————————————————————————————————————————————— // ———————————————————————————————————————————————— //
/*

// generate random problem instance
void random_problem(uint64_t *A)
{
    uint64_t num;
    for (int i = 1; i <= 100; i++)
    {
        num = rand();
        num = (num << 32) | rand();
        num = (num % 1000000000000) + 1;
        A[i] = num;
    }
}

// generate random standard solution
int *standard(void)
{
    int *S = malloc(101 * sizeof(int));
    for (int i = 1; i <= 100; i++)
    {
        if ((rand() % 2) == 1)
        {
            S[i] = 1;
        }
        else
        {
            S[i] = -1;
        }
    }
    return S;
}

// generate random standard neighbor
int *standard_n(int *S)
{
    int *S_n = malloc(101 * sizeof(int));
    memcpy(S_n, S, 101 * sizeof(int));
    int i = (rand() % 100) + 1;
    int j = (rand() % 100) + 1;
    while (i == j)
    {
        j = (rand() % 100) + 1;
    }
    S_n[i] = -S_n[i];
    if ((rand() % 2) == 1)
    {
        S_n[j] = -S_n[j];
    }
    return S_n;
}

// compute standard residue
uint64_t standard_r(uint64_t *A, int *S)
{
    int64_t r = 0;
    for (int i = 1; i <= 100; i++)
    {
        r += A[i] * S[i];
    }
    return llabs(r);
}

// generate random prepartitioning solution
int *prepart(void)
{
    int *P = malloc(101 * sizeof(int));
    for (int i = 1; i <= 100; i++)
    {
        P[i] = (rand() % 100) + 1;
    }
    return P;
}

// generate random prepartitioning neighbor
int *prepart_n(int *P)
{
    int *P_n = malloc(101 * sizeof(int));
    memcpy(P_n, P, 101 * sizeof(int));
    int i = (rand() % 100) + 1;
    int j = (rand() % 100) + 1;
    while (P_n[i] == j)
    {
        j = (rand() % 100) + 1;
    }
    P_n[i] = j;
    return P_n;
}

// compute prepartitioning residue
uint64_t prepart_r(uint64_t *A, int *P)
{
    uint64_t *A_n = malloc(101 * sizeof(uint64_t));
    for (int i = 1; i <= 100; i++)
    {
        A_n[i] = 0;
    }
    for (int i = 1; i <= 100; i++)
    {
        A_n[P[i]] += A[i];
    }
    return kk(A_n);
}

// repeated random - standard
int *rr_s(uint64_t *A)
{
    int *S = standard();
    for (int i = 1; i <= 25000; i++)
    {
        int *Sp = standard();
        if (standard_r(A, Sp) < standard_r(A, S))
        {
            memcpy(S, Sp, 101 * sizeof(int));
        }
    }
    return S;
}

// repeated random - prepart
int *rr_p(uint64_t *A)
{
    int *P = prepart();
    for (int i = 1; i <= 25000; i++)
    {
        int *Pp = prepart();
        if (prepart_r(A, Pp) < prepart_r(A, P))
        {
            memcpy(P, Pp, 101 * sizeof(int));
        }
    }
    return P;
}

// hill climbing - standard
int *hc_s(uint64_t *A)
{
    int *S = standard();
    for (int i = 1; i <= 25000; i++)
    {
        int *Sp = standard_n(S);
        if (standard_r(A, Sp) < standard_r(A, S))
        {
            memcpy(S, Sp, 101 * sizeof(int));
        }
    }
    return S;
}

// hill climbing - prepart
int *hc_p(uint64_t *A)
{
    int *P = prepart();
    for (int i = 1; i <= 25000; i++)
    {
        int *Pp = prepart_n(P);
        if (prepart_r(A, Pp) < prepart_r(A, P))
        {
            memcpy(P, Pp, 101 * sizeof(int));
        }
    }
    return P;
}

// cooling schedule
double T(int i)
{
    return 10000000000 * pow(0.8, floor(i/300));
}

// simulated annealing - standard
int *sa_s(uint64_t *A)
{
    int *S = standard();
    int *Spp = malloc(101 * sizeof(int));
    memcpy(Spp, S, 101 * sizeof(int));
    for (int i = 1; i <= 25000; i++)
    {
        int *Sp = standard_n(S);
        if (standard_r(A, Sp) < standard_r(A, S))
        {
            memcpy(S, Sp, 101 * sizeof(int));
        }
        else
        {
            double p = exp(-(standard_r(A, Sp) - standard_r(A, S)) / T(i));
            if ((rand() % 100) < (p * 100.))
            {
                memcpy(S, Sp, 101 * sizeof(int));
            }
        }
        if (standard_r(A, S) < standard_r(A, Spp))
        {
            memcpy(Spp, S, 101 * sizeof(int));
        }
    }
    return Spp;
}

// simulated annealing - prepart
int *sa_p(uint64_t *A)
{
    int *P = prepart();
    int *Ppp = malloc(101 * sizeof(int));
    memcpy(Ppp, P, 101 * sizeof(int));
    for (int i = 1; i <= 25000; i++)
    {
        int *Pp = prepart_n(P);
        if (prepart_r(A, Pp) < prepart_r(A, P))
        {
            memcpy(P, Pp, 101 * sizeof(int));
        }
        else
        {
            double p = exp(-(prepart_r(A, Pp) - prepart_r(A, P)) / T(i));
            if ((rand() % 100) < (p * 100.))
            {
                memcpy(P, Pp, 101 * sizeof(int));
            }
        }
        if (prepart_r(A, P) < prepart_r(A, Ppp))
        {
            memcpy(Ppp, P, 101 * sizeof(int));
        }
    }
    return Ppp;
}

*/
// ———————————————————————————————————————————————— // ———————————————————————————————————————————————— //

// binary min heap
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
void swap(uint64_t *x, uint64_t *y)
{
    uint64_t temp = *x;
    *x = *y;
    *y = temp;
}

// max_heapify
void max_heapify(uint64_t H[], int i)
{
    int l = left(i);
    int r = right(i);
    int largest;

    if (l <= size && H[l] > H[i])
    {
        largest = l;
    }
    else
    {
        largest = i;
    }

    if (r <= size && H[r] > H[largest])
    {
        largest = r;
    }

    if (largest != i)
    {
        swap(&H[i], &H[largest]);
        max_heapify(H, largest);
    }
}

// build_max_heap
void build_max_heap(uint64_t a[], int length)
{
    for (int i = floor(length/2); i >= 1; i--)
    {
        max_heapify(a, i);
    }
}

// extract_max
uint64_t extract_max (uint64_t H[])
{
    uint64_t max = H[1];
    H[1] = H[size];
    size--;
    max_heapify(H, 1);
    return max;
}

// insert k into H
void insert(uint64_t H[], uint64_t k)
{
    size++;
    H[size] = k;
    int i = size;
    while (i != 1 && H[parent(i)] < H[i])
    {
        swap(&H[parent(i)], &H[i]);
        i = parent(i);
    }
}