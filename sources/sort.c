#include "../include/sort.h"
#include "../include/record.h"
#include <stdio.h>

void bubbleSort(double *arr, int len){
    printf("222\n");
}

void sortByBMI(struct BMIRecord *recordList, int len){
    int i;
    for (i = 0; i < len - 1; i++){
        int j;
        for (j = i + 1; j < len; j++){
            if (recordList[j].BMI > recordList[i].BMI){
                struct BMIRecord temp = recordList[i];
                recordList[i] = recordList[j];
                recordList[j] = temp;
            }
        }
    }
}