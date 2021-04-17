
#include <stdio.h>
#include <stdlib.h>

#define newline printf("\n")

void UNION (int, int);
int FIND (int);
void EQUIVALENCE (void);
int TEST(int, int);
void TEST_GROUP (void);
int* INIT_ARRAY (int);

int *FATHER; //the global FATHER array
int SIZE; //the global FATHER array size


int main()
{   
    EQUIVALENCE ();
    TEST_GROUP ();
    
    free (FATHER);
    return 0;
}

void EQUIVALENCE ()
{
    int i, j, n;
    
    scanf("%d\n", &n);
    
    FATHER = INIT_ARRAY(n);

    scanf("%d %d\n", &i, &j);
    while (i != 0 && j != 0)
    {
        i = FIND(i);
        j = FIND(j);

        if (i!=j){
            UNION(i,j);
        }

        scanf("%d %d\n", &i, &j);
    }
    
    return;
}

int *INIT_ARRAY (int size)
{
    int *p = malloc(size * sizeof(int));

    for(int i = 0; i < size; i++){
        p[i] = -1;
    }

    return p;
}

int FIND(int i)
{
    int r;
    int j; 
    int k;

    r = i;
    while (FATHER[r] > 0) {
        r = FATHER[r];
    }

    j = i;
    while (j!=r){
        k = FATHER[j];
        FATHER[j] = r;
        j = k;
    }

    return r;
}

int abs (int x)
{
    if (x < 0)
        return x;
    
    return x;
}

void UNION (int i, int j)
{
    int count;
    count = FATHER[i] + FATHER[j];

    if (abs(FATHER[i]) > abs(FATHER[j])){
        FATHER[j] = i;
        FATHER[i] = count;
    } else {
        FATHER[i] = j;
        FATHER[j] = count;
    }

}

void TEST_GROUP()
{
    int k, l, result;
    
    // read elements of test set T
    scanf("%d %d\n", &k, &l);
    while (k != 0 && l != 0)
    {
        result = TEST(k, l);
        if (result)
            printf("TRUE\n");
        else
            printf("FALSE\n");
        scanf("%d %d\n", &k, &l);
    }
    
    return;
}

/*
Returns True (non-0) if k \equiv l, False (0) otherwise
*/
int TEST (int k, int l)
{
    k = FIND(k);
    l = FIND(l);

    if (k==l){
        return 1;
    } else {
        return 0;
    }

}

