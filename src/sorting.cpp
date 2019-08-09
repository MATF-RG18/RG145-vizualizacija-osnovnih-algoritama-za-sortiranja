#include <iostream>
#include <GL/glut.h>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include "callbackfunc.hpp"
#include "sorting.hpp"

using namespace std;

float init_x1 = 0, init_x2 = 0;
int flag = 0; 
int p = -1, q = -1;
int i = 0, j = 0;
int minimum = -1;

void barTimer(int value){
    if(value != 1)
        return;
    if(sorting){
        switch(type_of_sort){
            case 0: selectionSort(); break;
            case 1: insertionSort();break;
            case 2: bubbleSort();break;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1000, barTimer, 1);
}
void sphereTimer(int value){
    if(value != 2)
        return;
    
    if(sorting){
        switch(type_of_sort){
            case 0: selectionSortSphere(); break;
            case 1: insertionSortSphere();break;
            case 2: bubbleSortSphere();break;
        }
    }
    
    glutPostRedisplay();
    glutTimerFunc(30, sphereTimer, 2);
}
int notsorted(){
    for(int k=0;k<array_lenght-1;k++){
        if(array[k]>array[k+1])
            return 1;
    }
    return 0;
}

void selectionSort(){
    if(notsorted()){
        while(i < MAX_ARR_BARS-1){
            int minimum = i;
            for (j = i+1; j < MAX_ARR_BARS; j++){
                if (array[j] < array[minimum])
                    minimum = j;
            }
            
            if(array[minimum] < array[i]){
                p = minimum;
                q = i;
                int temp = array[minimum];
                array[minimum] = array[i];
                array[i] = temp;
                
                //ideja je da prekinem petlju posle svakog koraka da bi se iscrtalo
                return;
            }
            i++;
        }   
    }
    sorting = 0;
    i = j = 0;
}

void insertionSort(){
    if(notsorted()){
        while(i<MAX_ARR_BARS){
                j = i;
            while(j<MAX_ARR_BARS-1){
                if(array[j]>array[j+1]){
                    p = j;
                    q = j - 1;
                    int temp=array[j];
                    array[j]=array[j+1];
                    array[j+1]=temp;
                    i = 0;
                    j = 0;
                    return;
                }
                j++;
            }
            i++;
        }
    }else{
        sorting = 0;
        i = j = 0;
    }
}


void bubbleSort(){
    if(notsorted()){
        while(i < MAX_ARR_BARS - 1){
            if(array[i] > array[i+1]){
                int temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                p = i;
                q = i + 1;
                return;
            }
            i++;
            if(i == MAX_ARR_BARS - 1){
                i = 0;
            }
        }
    }
    sorting = 0;
    i = 0;
}

void insertionSortSphere(){
    // samo ako se trenutno ne smenjuju loptice mozemo da udjemo 
    // u sledeci korak
     if(!swapping_ongonig){
         while(global_i < MAX_ARR_SPHERES){
                global_j = global_i;
            while(global_j < MAX_ARR_SPHERES - 1){
                if(array[global_j] > array[global_j+1]){
                    swap(array_of_spheres[global_j], array_of_spheres[global_j+1]);
                    
                    int temp = array[global_j];
                    array[global_j] = array[global_j+1];
                    array[global_j+1] = temp;
                    return;
                }
                global_j++;
            }
        }
        global_i++;
    }else{
        swap(array_of_spheres[global_j], array_of_spheres[global_j+1]);
    }
    if(!notsorted() && swapping_ongonig  == 0){
        sorting = 0;
        global_i = global_j = 0;
    }
}

void bubbleSortSphere(){
    if(!swapping_ongonig){
        std::cout << global_i << "\n";
        while(global_i < MAX_ARR_SPHERES - 1){
            if(array[global_i] > array[global_i+1]){
                swap(array_of_spheres[global_i], array_of_spheres[global_i+1]);
                
                int temp = array[global_i];
                array[global_i] = array[global_i+1];
                array[global_i+1] = temp;
                return;
            }
            global_i++;
            if(global_i == MAX_ARR_SPHERES - 1){
                global_i = 0;
            }
        }
    }else{
        swap(array_of_spheres[global_i], array_of_spheres[global_i+1]);
    }
    if(swapping_ongonig == 0 && !notsorted()){
        sorting = 0;
        global_i = 0;
    }
}

void selectionSortSphere(){
    if(!swapping_ongonig){
        while(global_i < MAX_ARR_SPHERES-1){
            minimum = global_i;
            for (global_j = global_i+1; global_j < MAX_ARR_SPHERES; global_j++){
                if (array[global_j] < array[minimum])
                    minimum = global_j; 
            }
            
            if(array[minimum] < array[global_i]){
                swap(array_of_spheres[global_i], array_of_spheres[minimum]);
                
                int temp = array[minimum];
                array[minimum] = array[global_i];
                array[global_i] = temp;
                
                //ideja je da prekinem petlju posle svakog koraka da bi se iscrtalo
                return;
            }
            global_i++;
        }   
    }else{
        swap(array_of_spheres[global_i], array_of_spheres[minimum]);
    }
    if(swapping_ongonig == 0 && !notsorted()){
        sorting = 0;
        i = j = 0;
    }
}

void swap(Sphere &s1, Sphere &s2){
    if(swapping_ongonig  == 0){
        init_x1 = s1.x_axis;
        init_x2 = s2.x_axis;
        swapping_ongonig  = 1;
    }
    
    if(init_x1 <= s2.x_axis)
        s2.x_axis -= 0.1;
    
    if(init_x2 >= s1.x_axis)
        s1.x_axis += 0.1;
    
    if(fabs(init_x1 - s2.x_axis) < 0.005  && fabs(init_x2 - s1.x_axis) < 0.005){
        swapping_ongonig  = 0;
        
        std::cout << s1.x_axis << " " << s2.x_axis << "\n"; 
        float temp = s1.x_axis;
        s1.x_axis = s2.x_axis;
        s2.x_axis = temp;
        std::cout << s1.x_axis << " " << s2.x_axis << "\n"; 
        
        temp = s1.y_axis;
        s1.y_axis = s2.y_axis;
        s2.y_axis = temp;
        
        temp = s1.radius;
        s1.radius = s2.radius;
        s2.radius = temp;
    }
}