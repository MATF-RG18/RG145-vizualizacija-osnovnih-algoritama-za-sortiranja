#ifndef __SORTING_HPP__
#define __SORTING_HPP__ 1

extern int i, j;
extern int l, r;
extern int flag1, flag2;
extern int piv, piv1;
extern int beg[MAX_ARR_LENGHT];
extern int ending[MAX_ARR_LENGHT];
extern void glutTimer(int value);

int notsorted();
void selectionSort();
void insertionSort();
void bubbleSort();
void quickSort();

#endif