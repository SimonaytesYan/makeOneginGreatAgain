#ifndef _QSORT_SYM_
#define _QSORT_SYM_

void normal_swap(void *a, void *b, size_t ElementSize);

void QSORT(void * first, int number, int ElementSize, int (*comparator)(void *, void *));

#endif