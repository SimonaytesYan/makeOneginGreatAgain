#include <stdlib.h>
#include <stdio.h>

#include "QSORT.h"
#include "Strings\_Strings.h"
#include "Console\ConsoleSettings.h"

int comp(void * a, void* b)
{
    int A = *((int*)a);
    int B = *((int*)b);

    return A - B;
}

void normal_swap(void *a, void *b, size_t ElementSize)
{
    char* c = (char*)malloc(ElementSize);

    for(int i = 0; i < ElementSize; i++)
        c[i] =  ((char*)a)[i];

    for(int i = 0; i < ElementSize; i++)
        ((char*)a)[i] = ((char*)b)[i];
    
    for(int i = 0; i < ElementSize; i++)
        ((char*)b)[i] = ((char*)c)[i];

    free(c);
}

void QSORT(void * first, int number, int ElementSize, int (*comparator)(void *, void *))
{
    if (number <= 1)
        return;
    
    char *l   = (char *)first;
    char *r   = (char *)first + (number - 1) * ElementSize;
    char *piv = (char *)first + (number / 2) * ElementSize;

    while (l <= r)
    {
        while (comparator(l, piv) < 0)
            l += ElementSize;
        while (comparator(r, piv) > 0)
            r -= ElementSize;
        
        if (l <= r)
        {
            if (piv == l)
                piv = r;
            else if (piv == r)
                piv = l;
            
            normal_swap(l, r, ElementSize);

            l += ElementSize;
            r -= ElementSize;
        }
    }

    int left_length  = (r - (char*)first)/ElementSize + 1;
    int right_length = ((char*)first + ElementSize*number - l)/ElementSize; 
    
    QSORT(first, left_length,  ElementSize, comparator);
    QSORT(l,     right_length, ElementSize, comparator);
}

void test_qsort()
{
    int arr[10] = {7, 4, 2, 17, 17, 19, 3, 1, 9, 18 };
    for(int t = 0; t < 1000; t++)
    {
        printf("TEST %d\n", t + 1);

        for(int i = 0; i < 10; i++)
        {
            arr[i] = rand()%15;
            printf("%d ", arr[i]);
        }
        printf("\n");

        QSORT(arr, 10, sizeof(int), comp);

        bool sorted = true;
        for(int i = 1; i < 10; i++)
            if (arr[i - 1] > arr[i])
            {
                sorted = false;
            }
        if (sorted)
        {
            set_console_color(GREEN);
            printf("PASSED!!!\n");
            set_console_color(DEFAULT);
        }
        else
        {
            set_console_color(RED);
            printf("FAILED!!!\n");
            set_console_color(DEFAULT);

            for(int i = 0; i < 10; i++)
                printf("%d ", arr[i]);
            printf("\n\n");
        }
    }
}

void test_swap()
{
    printf("TEST 1: ");
    int a = 0;
    int b = 10;
    
    normal_swap(&a, &b, sizeof(int));
    if (a == 10 && b == 0)
    {
        set_console_color(GREEN);
        printf("PASSED!!!\n");
        set_console_color(DEFAULT);
    }
    else 
    {
        set_console_color(RED);
        printf("FAILED!!!\n");
        set_console_color(DEFAULT);
        
        printf("a_start = %d\n", 0);
        printf("b_start = %d\n", 10);
        printf("a       = %d\n", a);
        printf("b       = %d\n", b);
    }

    printf("TEST 2: ");
    char c = 0;
    char d = 10;

    normal_swap(&c, &d, sizeof(char));
    if (c == 10 && d == 0)
    {
        set_console_color(GREEN);
        printf("PASSED!!!\n");
        set_console_color(DEFAULT);
    }
    else 
    {
        set_console_color(RED);
        printf("FAILED!!!\n");
        set_console_color(DEFAULT);

        printf("c_start = %d\n", 0);
        printf("d_start = %d\n", 10);
        printf("c       = %d\n", c);
        printf("d       = %d\n", d);
    }

    printf("TEST 3: ");
    int *a_p = &a;
    int *b_p = &b;

    normal_swap(&a_p, &b_p, sizeof(int*));
    if (a_p == &b && b_p == &a)
    {
        set_console_color(GREEN);
        printf("PASSED!!!\n");
        set_console_color(DEFAULT);
    }
    else 
    {
        set_console_color(RED);
        printf("FAILED!!!\n");
        set_console_color(DEFAULT);
        
        printf("a_p_start = %d\n", &a);
        printf("b_p_start = %d\n", &b);
        printf("a_p       = %d\n", a_p);
        printf("b_p       = %d\n", b_p);
    }

    printf("TEST 4: ");
    char *c_p = &c;
    char *d_p = &d;

    normal_swap(&c_p, &d_p, sizeof(char*));
    if (c_p == &d && d_p == &c)
    {
        set_console_color(GREEN);
        printf("PASSED!!!\n");
        set_console_color(DEFAULT);
    }
    else 
    {
        set_console_color(RED);
        printf("FAILED!!!\n");
        set_console_color(DEFAULT);

        printf("c_p_start = %d\n", &c);
        printf("d_p_start = %d\n", &d);
        printf("c_p       = %d\n", c_p);
        printf("d_p       = %d\n", d_p);
    }
}