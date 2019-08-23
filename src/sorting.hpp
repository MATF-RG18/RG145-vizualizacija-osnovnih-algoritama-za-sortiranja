#ifndef __SORTING_HPP__
#define __SORTING_HPP__ 1

extern float init_x1, init_x2;
extern int i, j;
extern int minimum;
// cuva indekse promenljivih koje trenutno menjaju mesta da bi im promenili boje
extern int p, q;

//sortovi za kule
void selectionSort();
void insertionSort();
void bubbleSort();

//sortovi za sfere
void insertionSortSphere();
void bubbleSortSphere();
void selectionSortSphere();

//pomocne: da li je soritran i zamena
int notsorted();
void swap(Sphere &s1, Sphere &s2);

#endif