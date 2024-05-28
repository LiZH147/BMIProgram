#include <stdio.h>
#include "../include/record.h"

void drawRecords(char *username)
{
    struct BMIRecord *recordList = NULL;
    int len = 0, i;
    loadFromFile(username, &recordList, &len);
    printf("您共记录了%d次BMI，按时间由近及远依次为：\n", len);

    double maxBMI = 0.0;
    for (i = 0; i < len; i++)
    {
        if (recordList[i].BMI > maxBMI)
        {
            maxBMI = recordList[i].BMI;
        }
    }
    for (i = 10; i >= 0; i--)
    {
        if ((maxBMI * i / 10) < 10)
        {
            printf(" ");
        }
        printf("%.1lf |\t", maxBMI * i / 10);
        int j;
        for (j = 0; j < len; j++)
        {
            if (recordList[j].BMI >= maxBMI * i / 10)
            {
                printf("█\t");
            }
            else
            {
                printf("\t");
            }
        }
        printf("\n");
    }

    printf("\n     	");
    for (i = 0; i < len; i++)
    {
        printf("%.1lf\t", recordList[i].BMI);
    }
    printf("\n");
}
