#ifndef USER_H
#define USER_H

#define MAX_USER_COUNT 10
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define USERLIB_PATH "../userlib/account.txt"

typedef struct {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    int sex, age;
    double height;
} User;

typedef struct {
    User users[MAX_USER_COUNT];
    int count;
} UserDatabase;

int judgeDirectory(const char *path);

void initUserDatabase(UserDatabase *db);
int registerUser(UserDatabase *db, User user);
int loginUser(UserDatabase *db, char *username, char *password, User *user, int *userNum);
int saveUserDatabase(UserDatabase *db);
int loadUserDatabase(UserDatabase *db);
int deleteUser(char *username);

#endif
