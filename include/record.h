#ifndef RECORD_H
#define RECORD_H
#define RECORD_PATH "../userlib/"

struct BMIRecord{
    char username[50];
    double height;
    double weight;
    double BMI;
    char date[20];
};


int addRecordToFIle(struct BMIRecord record);

int loadByUsername(char *username, struct BMIRecord **recordList, int *len);

int saveToFile(char *username, struct BMIRecord *recordList, int len);

int loadFromFile(char *username, struct BMIRecord **recordList, int *len);

int deleteByIndex(char* username, int index);

int delAllRecords(char *username);

#endif
