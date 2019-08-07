#include <iostream>
#include <GL/glut.h>
#include <unistd.h>
#include "callbackfunc.hpp"
#include "sorting.hpp"

using namespace std;

int flag = 0; 
int p = -1, q = -1;
int i = 0, j = 0;
int l = 0, r = 0;
int flag1 = 0, flag2 = 0;
int beg[MAX_ARR_LENGHT];
int ending[MAX_ARR_LENGHT];
int piv = 0;

void glutTimer(int value){
    if(value != 1)
        return;
    if(sorting){
        switch(sort_count){
            case 0: selectionSort(); break;
            case 1: insertionSort();break;
            case 2: bubbleSort();break;
            case 3: quickSort();break;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1000, glutTimer, 1);
}
int notsorted(){
    for(int k=0;k<MAX_ARR_LENGHT-1;k++){
        if(array[k]>array[k+1])
            return 1;
    }
    return 0;
}

void selectionSort(){
    if(notsorted()){
        while(i < MAX_ARR_LENGHT-1){
            int min = i;
            for (j = i+1; j < MAX_ARR_LENGHT; j++){
                if (array[j] < array[min])
                    min = j;
            }
            
            if(array[min] < array[i]){
                p = min;
                q = i;
                int temp = array[min];
                array[min] = array[i];
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
    if(notsorted){
        while(i<MAX_ARR_LENGHT){
            if(flag == 0){
                j = i;
                flag = 1;
            }
            while(j<MAX_ARR_LENGHT-1){
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
                if(j == MAX_ARR_LENGHT - 1){
                    flag = 0;
                }
            }
            i++;
        }
    }
    sorting = 0;
    i = j = 0;
}


void bubbleSort(){
    if(notsorted()){
        while(i < MAX_ARR_LENGHT - 1){
            if(array[i] > array[i+1]){
                int temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                p = i;
                q = i + 1;
                return;
            }
            i++;
            if(i == MAX_ARR_LENGHT - 1){
                i = 0;
            }
        }
    }
    sorting = 0;
    i = 0;
}

void quickSort() {
    if(notsorted()){
     if(flag1 == 1){
         flag1 = 0;
         goto A1;
     }
     if(flag2 == 1){
         flag2 = 0;
         goto A2;
     }
    while (i>=0){
        l=beg[i];
        r=ending[i]-1;
        if (l<r){
            piv=array[l];
            while (l<r){
                while(array[r]>=piv && l<r) 
                    r--; 
                if (l<r){
                    array[l++]=array[r];
                     flag1 = 1;
                     goto A;
                     A1: ;
                }
                while (array[l]<=piv && l<r) 
                    l++;
                if (l<r){
                    array[r--]=array[l];
                      flag2 = 1;
                     goto A;
                     A2: ;
                }
            }
            array[l]=piv;
      
            beg[i+1]=l+1;
            ending[i+1]=ending[i];
            ending[i++]=l;
      
            if (ending[i]-beg[i]>ending[i-1]-beg[i-1]) {
                int temp=beg[i];
                beg[i]=beg[i-1];
                beg[i-1]=temp;
                temp=ending[i];
                ending[i]=ending[i-1];
                ending[i-1]=temp;
            }
            goto A;
        }else{
            i--; 
            goto A;
        }
    }
    }
    sorting = 0; i = j = 0;
    l = r = 0;
    flag1 = flag2 = 0;
    beg[0] = 0;
    ending[0] = MAX_ARR_LENGHT;
    A: ;
}
