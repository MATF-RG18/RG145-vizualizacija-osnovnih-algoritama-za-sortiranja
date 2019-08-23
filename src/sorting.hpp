#ifndef __SORTING_HPP__
#define __SORTING_HPP__ 1

extern float init_x1, init_x2;
extern int i, j;
extern int minimum;
extern int p, q;
extern int flag;
extern int speed;
extern int speed_for_bars[5];
extern int speed_for_spheres[5];


void barTimer(int value);
void sphereTimer(int value);


void selectionSort();
void insertionSort();
void bubbleSort();

void insertionSortSphere();
void bubbleSortSphere();
void selectionSortSphere();

int notsorted();
void swap(Sphere &s1, Sphere &s2);

#endif