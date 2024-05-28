#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/record.h"
#include "../include/user.h"

int addRecordToFIle(struct BMIRecord record){
    FILE *fp;
    char filename[128];
    sprintf(filename, "%srecords.txt", RECORD_PATH);
    //sprintf(filename, "../userlib/%s.txt", username);
    fp = fopen(filename, "a");
    if (fp == NULL){
        return 0;
    }
    fwrite(&record, sizeof(struct BMIRecord), 1, fp);
    fclose(fp);
    return 1;
}

int loadByUsername(char *username, struct BMIRecord **recordList, int *len){
    FILE *fp;
    fp = fopen("../userlib/records.txt", "r");
    if (fp == NULL){
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);
    *len = fileSize / sizeof(struct BMIRecord);
    *recordList = (struct BMIRecord *)malloc(*len * sizeof(struct BMIRecord));
    int i = 0;
    while (fread(&(*recordList)[i], sizeof(struct BMIRecord), 1, fp) == 1){
        if (strcmp((*recordList)[i].username, username) == 0){
            i++;
        }
    }
    fclose(fp);
    *len = i;
    return 1;
}

int saveToFile(char *username, struct BMIRecord *recordList, int len){
    //创建并打开对应文件
    FILE *fp;
    char filename[128];
    sprintf(filename, "../userlib/%s.txt", username);
    char cwd[1000];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error\n");
        return 0;
    }
    char* full_filename = strcat(cwd, "/");
    full_filename = strcat(full_filename, filename);
    printf("%s\n", full_filename);
    //以追加模式打开文件，在文件末尾添加内容
	fp = fopen(full_filename, "a");
    
    if (fp == NULL){
        return 0;
    }
    //差异化存储操作
    struct BMIRecord *oldRecordList = NULL;
	int oldlen = 0;
	loadFromFile(username, &oldRecordList, &oldlen);
    int i;
    for (i = 0; i < len; i++){
    	//printf("\n%s %.2lf %.2lf %.3lf %s", recordList[i].username, recordList[i].height, recordList[i].weight, recordList[i].BMI, recordList[i].date);
        if (strcmp(recordList[i].username, username) == 0){
        	int flag = 0, j;
        	for (j = 0; j < oldlen; j++){
        		if (strcmp(recordList[i].date, oldRecordList[j].date) == 0) {
        			flag = 1;
        			break;
        		}
        	}
        	if (flag == 1)
        		continue;
            fprintf(fp, "\n%s %.2lf %.2lf %.3lf %s", recordList[i].username, recordList[i].height, recordList[i].weight, recordList[i].BMI, recordList[i].date);
        }
    }
    fclose(fp);
    return 1;
}


int loadFromFile(char *username, struct BMIRecord **recordList, int *len){
    FILE *fp;
    char filename[128];
    sprintf(filename, "../userlib/%s.txt", username);
    fp = fopen(filename, "r");
    //fp = fopen("records.txt", "r");
    if(fp == NULL){
        return 0;
    }
    int recordCount = 0;
    char temp[50];
    while (fgets(temp, 50, fp) != NULL){
        char *pch;
        pch = strtok(temp, " ");
        if (strcmp(pch, username) == 0){
            recordCount++;
        }
    }
    rewind(fp);
    *len = recordCount;
    *recordList = (struct BMIRecord *)malloc(recordCount * sizeof(struct BMIRecord));
    int i = 0;
    char tempTime[100];
    while (fscanf(fp, "%s %lf %lf %lf %s %s\n", (*recordList)[i].username, &(*recordList)[i].height, &(*recordList)[i].weight, &(*recordList)[i].BMI, (*recordList)[i].date, tempTime) == 6){
        strcat((*recordList)[i].date, " ");
        strcat((*recordList)[i].date, tempTime);
        tempTime[0] = '\0';
        i++;
    }
    fclose(fp);
    return 1;
}

int deleteByIndex(char* username, int index) {
	index++;
    FILE *fp;
    char filename[128];
    sprintf(filename, "../userlib/%s.txt", username);
    fp = fopen(filename, "r");
    if(fp == NULL) {
        return 0;
    }

    int recordCount = 0;
    int deleteIndex = -1;
    char temp[50];
    char* tempFileName = "../userlib/temp.txt";
    FILE* tempfp = fopen(tempFileName, "w");

    while (fgets(temp, 50, fp) != NULL) {
    	//printf("temp:%s\n", temp);
        if (temp[0] == '-' && temp[1] == '1') {
            continue;
        }
        if (++recordCount == index) {
            deleteIndex = ftell(fp);
            printf("%s", temp);
            //fprintf(tempfp, "%s", "-1\n");
        }
        else {
            fprintf(tempfp, "%s", temp);
        }
    }
    fclose(fp);
    fclose(tempfp);

    if (deleteIndex == -1) {
        printf("deleteIndex == -1\n");
        remove(tempFileName);
        return 0;
    }
	remove(filename);
    rename(tempFileName, filename);

    return 1;
}

int delAllRecords(char *username){
	FILE *fp;
    char filename[128];
    sprintf(filename, "../userlib/%s.txt", username);
    fp = fopen(filename, "w");
    if(fp == NULL) {
        return 0;
    }
    return 1;
}
