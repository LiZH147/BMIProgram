#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/user.h"
#include <dirent.h>
#include <sys/stat.h>

int judgeDirectory(const char *path)
{
	struct stat statbuf;
	if (stat(path, &statbuf) != 0)
	{
		return 0; // 路径不存在，默认为非目录
	}
	return S_ISDIR(statbuf.st_mode);
}
void initUserDatabase(UserDatabase *db)
{
	db->count = 0;
}
int loadUserDatabase(UserDatabase *db)
{
	initUserDatabase(db);

	FILE *fp = fopen(USERLIB_PATH, "r");
	if (fp == NULL)
	{
		printf("用户数据文件不存在\n");
		return 0;
	}

	while (!feof(fp))
	{
		User user;
		if (fscanf(fp, "%s %s %lf %d %d\n", user.username, user.password, &user.height, &user.sex, &user.age) == 5)
		{
			db->users[db->count] = user;
			db->count++;
		}
	}

	fclose(fp);
	return 1;
}

int registerUser(UserDatabase *db, User user)
{
	// 账号数量检查

	// 检查用户名是否存在
	int i;
	for (i = 0; i < db->count; i++)
	{
		if (strcmp(db->users[i].username, user.username) == 0)
		{
			printf("用户名重复\n");
			return 0;
		}
	}

	// 将新用户添加到account文件中

	db->users[db->count] = user;
	db->count++;

	return saveUserDatabase(db);
}

int saveUserDatabase(UserDatabase *db)
{
	FILE *fp = fopen(USERLIB_PATH, "w");
	if (fp != NULL)
	{
		int i;
		for (i = 0; i < db->count; i++)
		{
			fprintf(fp, "%s %s %lf %d %d\n", db->users[i].username, db->users[i].password, db->users[i].height, db->users[i].age, db->users[i].sex);
		}
		fclose(fp);
	}
	else
	{
		perror("创建用户账户文件错误");
		return 0;
	}

	return 1;
}

int loginUser(UserDatabase *db, char *username, char *password, User *user, int *userNum)
{
	int i;
	for (i = 0; i < db->count; i++)
	{
		if (strcmp(db->users[i].username, username) == 0 &&
			strcmp(db->users[i].password, password) == 0)
		{
			user->age = db->users[i].age, user->height = db->users[i].height, user->sex = db->users[i].sex;
			*userNum = i;
			return 1; // 登录成功
		}
	}
	return 0; // 登录失败
}

int deleteUser(char *username)
{
	// 两步，第一是在account.txt中删除该用户，模仿record中的删除，将数据复制到新文件，再重命名该文件
	FILE *fp;
	fp = fopen(USERLIB_PATH, "r");
	if (fp == NULL)
	{
		printf("打开账户目录失败！\n");
		return 0;
	}

	char *newAccount = "../userlib/tempaccount.txt";
	FILE *newfp = fopen(newAccount, "w");

	int flag = -1;
	while (!feof(fp))
	{
		User user;
		if (fscanf(fp, "%s %s %lf %d %d\n", user.username, user.password, &user.height, &user.age, &user.sex) == 5)
		{
			if (!strcmp(user.username, username))
			{
				flag = 1;
				continue;
			}
			fprintf(newfp, "%s %s %lf %d %d\n", user.username, user.password, user.height, user.age, user.sex);
			// printf("%s %s\n", user.username, user.password);
		}
	}
	fclose(fp);
	fclose(newfp);
	if (flag == -1)
	{
		printf("未找到该用户，注销失败！\n");
		return 0;
	}
	remove(USERLIB_PATH);
	rename(newAccount, USERLIB_PATH);
	// 第二是删除用户数据
	// printf("userDataPath:%s\n", USERLIB_PATH);
	char userRecord[100];
	sprintf(userRecord, "../userlib/%s.txt", username);
	remove(userRecord);

	return 1;
}
