#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include "../include/userInterface.h"

void mainInterface()
{
    printf("\n┌─────────── 主　界　面 ──────────┐\n");
    printf("│           1. 用户注册           │\n");
    printf("│           2. 用户登录           │\n");
    printf("│           3. 退出程序           │\n");
    printf("│                                 │\n");
    printf("请输入选项:");
}
void secondInterface()
{
   printf("\n┌─────────── 功　能　界　面 ──────────┐\n");
    printf("│           1. 计算BMI值              │\n");
    printf("│           2. 显示历史BMI记录        │\n");
    printf("│           3. 保存BMI记录            │\n");
    printf("│           4. 显示BMI记录柱状图      │\n");
    printf("│           5. 删除BMI记录            │\n");
    printf("│           6. 更改身高               │\n");
    printf("│           7. 账号注销               │\n");
    printf("│           8. 返回主界面             │\n");
    printf("│                                     │\n");
    printf("│ 注意，请保存BMI记录后再使用其他功能 │\n");
}

void deleteInterface()
{
    printf("│           1. 删除某条记录           │\n");
    printf("│           2. 删除所有记录           │\n");
    printf("│           3. 返回上一级             │\n");
}
