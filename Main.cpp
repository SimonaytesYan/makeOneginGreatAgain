#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys\stat.h>

#include "Strings\_Strings.h"
#include "Console\ConsoleSettings.h"

const char READ_FROM[] = "EOnegin.txt";

//const char READ_FROM[] = "TEST.txt";
const char WRITE_TO[] = "OUTPUT.txt";

//void _qsort(char * first, int number, int ElementSize, int (*comparator)(const char *, const char *));

int pivot(int l, int r)
{
    return (l + r) / 2;
}

void swap(char **a, char **b)   //size_t
{
    char* c = *a;   //
    *a = *b;
    *b = c;
}

void swap1(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int comp(void* a, void* b)
{
    int a1 = *((int *)a);
    int b1 = *((int *)b);
    return a1 - b1;
}

void QSORT(void * first, size_t number, int ElementSize, int (*comparator)(void *, void *))
{
    //printf("Start sort\n");
    if (number <= 1)
        return;
    
    char *l = (char *)first;
    //printf("number = %d", number);
    //printf("l   = %s\n", *(char**)(l));
    char *r = ((char*)first + (number - 1)*ElementSize);
    //printf("r = %d", r);
    //printf("%s\n", *(char**)(r));
    //for(char *i =l; i <= r; i+=ElementSize)
       // printf("%s\n", *(char**)(i));
    
    char *piv = ((char*)first + (number / 2) * ElementSize);
    //printf("\npiv   = %d\n", *(int *)(piv));
    //printf("number = %d\n", number);
    //printf("piv   = %s\n", *(char**)(piv));

    while (l <= r)
    {
        //printf("piv   = %s\n", *(char**)(piv));
        // && l < ((char *)first + number*ElementSize)
        while(comparator(l, piv) < 0)
        {
            l = l + ElementSize;
        }
        // && r > (char*)first
        while (comparator(r, piv) > 0)
        {
            r = r - ElementSize;
        }
        // && comparator(l, piv) >= 0 && comparator(r, piv) <= 0
        if (l <= r)
        {   
            /*printf("l = %d\n", *l);
            printf("r = %d\n", *r);
            for(int i = 0; i < number; i++)
                printf("%d ", *(int*)(((char*)first + i*ElementSize)));
            printf("\n");*/
            
            if (l == piv)
                piv = r;
            else if (r == piv)
                piv = l;
            //swap(&l, &r);
            swap1((int *)l, (int*)r);

            l = l + ElementSize;
            r = r - ElementSize;
        }
    }

    //for(int i = 0; i < number; i++)
    //    printf("%d ", *(int*)(((char*)first + i*ElementSize)));
    //printf("\n");
    
    int left_len  = (r - (char*)first)/ElementSize + 1;
    int right_len = (l - (char*)first)/ElementSize + 1;

    
    /*printf("first = %d\n", first);
    printf("l     = %d\n", l);
    printf("r     = %d\n", r);*/
    //printf("left_len  = %d\n", left_len);
    //printf("reght_len = %d\n", right_len);
    QSORT(first, left_len , ElementSize, comparator);
    QSORT(l    , right_len, ElementSize, comparator);
}

int main()
{   
    init_console();

    int arr[10] = {7, 4, 2, 17, 17, 19, 3, 1, 9, 18 };
    for(int t = 0; t < 10; t++)
    {
        for(int i = 0; i < 10; i++)
        {
            arr[i] = rand()%15;
            printf("%d ", arr[i]);
        }
        printf("\n");
        QSORT(arr, 10, 4, comp);
        for(int i = 0; i < 10; i++)
            printf("%d ", arr[i]);
        printf("\n\n");
    }
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





//void _qsort(char * first, int number, int ElementSize, int (*comparator)(const char *, const char *))