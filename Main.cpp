#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys\stat.h>

#include "Strings\_Strings.h"
#include "Console\ConsoleSettings.h"

const char READ_FROM[] = "EOnegin.txt";

const char WRITE_TO[] = "OUTPUT.txt";

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

void QSORT(void * first, size_t number, int ElementSize, int (*comparator)(void *, void *))
{
    printf("\nStart\n");
    if (number <= 1)
        return;
    
    char *l = (char *)first;
    char *piv = ((char*)first + (number / 2) * ElementSize);

    normal_swap(l, piv, ElementSize);
    
    for(int i = 0; i < number; i++)
    {
        printf("%d ", ((int *)first)[i]);
    }
    printf("\n");

    int left_len = 0;
    char *last = (char*)first+ number*ElementSize;

    for(char *r = (char*)first + ElementSize; r < last; r += ElementSize)
    {
        if (comparator(first, r) >= 0)
        {
            left_len++;
            l += ElementSize;
            normal_swap(l, r, ElementSize);
        }
    }
    normal_swap(l, piv, ElementSize);

    for(int i = 0; i < number; i++)
    {
        printf("%d ", ((int *)first)[i]);
    }
    printf("\n");
    int k = 0;
    scanf("%d", &k);

    QSORT(first, left_len,          ElementSize, comparator);
    QSORT(l,     number - left_len, ElementSize, comparator);
}

void test_qsort()
{
    int arr[10] = {7, 4, 2, 17, 17, 19, 3, 1, 9, 18 };
    for(int t = 0; t < 10; t++)
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

int main()
{   
    init_console();

    test_qsort();

    abort();
    
    struct stat buff = {};
    stat(READ_FROM, &buff);

    char* work_text              = (char*)calloc(buff.st_size, 1);
    char* correct_text_to_output = (char*)calloc(buff.st_size, 1);

    assert(work_text != NULL);
    assert(correct_text_to_output != NULL);

    FILE *fp = fopen(READ_FROM, "r");
    assert(fp != NULL);

    int numberLines = _gettext(work_text, buff.st_size, fp);
    _strcpy(correct_text_to_output, work_text);

    fclose(fp);

    const char** arrayLines = (const char**)calloc(numberLines, sizeof(char*));
    assert(arrayLines != NULL);

    _getlines_from_text(arrayLines, work_text); 

    FILE *ofp = fopen(WRITE_TO, "w");
    assert(ofp);

    printf("Array was got\n");
    QSORT(arrayLines, numberLines, sizeof(char *) , _strcmp);
    printf("Array sorted\n");

    for(int i = 0; i < numberLines; i++)
    {
        _puts(arrayLines[i], ofp);
    }
    _puts("\n\n", ofp);
    printf("Array printed\n");

    _puts(correct_text_to_output, ofp);
    printf("Original array printed\n");

    fclose(ofp);

    free(arrayLines);
    free(correct_text_to_output);
    free(work_text);
}