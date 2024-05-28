#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include "../include/bmi.h"
#include "../include/operation.h"
#include "../include/myTime.h"
#include "../include/record.h"
#include "../include/user.h"
#include "../include/sort.h"
#include "../include/barChart.h"
#include "../include/userInterface.h"

int start()
{
    // User login
    UserDatabase db; // 创建用户数据库
    mkdir("../userlib", 0777);
    initUserDatabase(&db);
    loadUserDatabase(&db); // 加载用户数据库

    int choice1;
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    int sex;
    double height;
    int age;
    User user;

    while (1)
    {
        // 开始界面
        mainInterface();
        scanf("%d", &choice1);
        getchar(); // 读取换行符

        switch (choice1)
        {
        case 1: // 用户注册
            printf("请按照提示完善用户信息\n");
            printf("请输入用户名: ");
            fgets(username, MAX_USERNAME_LENGTH + 1, stdin);
            username[strlen(username) - 1] = '\0'; // 删除末尾的换行符
            printf("请输入密码: ");
            fgets(password, MAX_PASSWORD_LENGTH + 1, stdin);
            password[strlen(password) - 1] = '\0'; // 删除末尾的换行符
            printf("请输入年龄：");
            scanf("%d", &age);
            printf("请输入性别：");
            scanf("%d", &sex);
            printf("请输入身高：");
            scanf("%lf", &height);
            User newUser;
            newUser.age = age, newUser.height = height, newUser.sex = sex;
            strcpy(newUser.username, username);
            strcpy(newUser.password, password);
            if (registerUser(&db, newUser))
            {
                printf("注册成功！\n");
            }
            else
            {
                printf("main注册失败！\n");
            }
            break;
        case 2: // 用户登录
            printf("请输入用户名: ");
            fgets(username, MAX_USERNAME_LENGTH + 1, stdin);
            username[strlen(username) - 1] = '\0'; // 删除末尾的换行符

            char c;
            int i = 0;
            struct termios old, new;

            /* 获取终端属性 */
            tcgetattr(STDIN_FILENO, &old);

            /* 复制终端属性 */
            new = old;

            /* 关闭 ECHO 标志，表示输入字符不回显 */
            new.c_lflag &= ~(ECHO);

            /* 设置终端属性 */
            tcsetattr(STDIN_FILENO, TCSANOW, &new);

            /* 提示用户输入密码 */
            printf("请输入密码: ");
            while ((c = getchar()) != '\n' && i < MAX_PASSWORD_LENGTH - 1)
            {
                putchar('*');
                password[i++] = c;
            }
            password[i] = '\0';
            putchar('\n');

            /* 恢复终端属性 */
            tcsetattr(STDIN_FILENO, TCSANOW, &old);

            int userNum; // 记录当前用户在数据库中的位置
            if (loginUser(&db, username, password, &user, &userNum))
            {
                printf("登录成功！\n");
                strcpy(user.username, username);
                int choice = 0;
                int deledUser = 0;
                while (1)
                {
                    if (deledUser == 1)
                    {
                        break;
                    }
                    // 二级界面
                    printf("\n");
                    printf("\033[32m"); // 设置绿色前景色
                    printf("\n%s，欢迎您！          当前身高为：%.2lf", username, db.users[userNum].height);

                    secondInterface();

                    printf("请输入选项:");
                    scanf("%d", &choice);
                    if (choice == 8)
                    {
                        break;
                    }
                    switch (choice)
                    {
                    case 1:
                    {
                        double height, weight;
                        height = db.users[userNum].height;
                        printf("请输入体重（千克）：");
                        scanf("%lf", &weight);
                        double BMI = calculateBMI(height, weight);
                        if (BMI < 0)
                        {
                            printf("身高和体重必须大于0！\n");
                        }
                        else
                        {
                            printMessage(BMI, db.users[userNum].age, height, weight, db.users[userNum].sex);
                            // 创建新的变量用于存储待记录的BMI数据
                            struct BMIRecord newRecord;
                            strcpy(newRecord.username, username);
                            newRecord.height = height;
                            newRecord.weight = weight;
                            newRecord.BMI = BMI;
                            char *now = getCurrentTime();
                            strcpy(newRecord.date, now);
                            free(now);
                            // 此处是将用户的所有计算作记录，用于选项3进行存储
                            addRecordToFIle(newRecord);
                        }

                        break;
                    }
                    case 2:
                    {
                        struct BMIRecord *recordList = NULL;
                        int len = 0;
                        loadFromFile(username, &recordList, &len);
                        printf("%s, 您共记录了%d次BMI。\n按时间由近及远依次为：\n", username, len);
                        printf("    \t时间\t\t身高\t体重\tBMI\n");
                        int i;
                        for (i = 0; i < len; i++)
                        {
                            printf("%s\t%.2lf\t%.2lf\t%.3lf\n", recordList[i].date, recordList[i].height, recordList[i].weight, recordList[i].BMI);
                        }
                        printf("按BMI指数降序排序为：\n");
                        sortByBMI(recordList, len);
                        printf("BMI\t\t时间\n");
                        for (i = 0; i < len; i++)
                        {
                            printf("%.3lf\t%s\n", recordList[i].BMI, recordList[i].date);
                        }
                        break;
                    }
                    case 3:
                    {
                        struct BMIRecord *recordList = NULL;
                        int len = 0;
                        loadByUsername(username, &recordList, &len);
                        if (len == 0)
                        {
                            printf("当前尚未记录BMI，无法保存记录！");
                        }
                        else
                        {
                            if (saveToFile(username, recordList, len))
                            {
                                printf("记录保存成功！\n");
                            }
                            else
                            {
                                printf("记录保存失败！\n");
                            }
                        }
                        break;
                    }
                    case 4:
                    {
                        drawRecords(username);
                        break;
                    }
                    case 5:
                    {
                        struct BMIRecord *recordList = NULL;
                        int len = 0;
                        loadFromFile(username, &recordList, &len);
                        int i;
                        for (i = 0; i < len; i++)
                        {
                            printf("第%d条\t%s\n", i + 1, recordList[i].date);
                        }
                        if (len == 0)
                        {
                            printf("当前尚未记录BMI，不能能进行删除！");
                        }
                        else
                        {
                            int choice5;
                            deleteInterface();
                            scanf("%d", &choice5);
                            if (choice5 == 3)
                            {
                                break;
                            }
                            switch (choice5)
                            {
                            case 1:
                            {
                                printf("输入要删除记录为第几条\n");
                                int delIndex;
                                scanf("%d", &delIndex);
                                if (deleteByIndex(username, delIndex) == 0)
                                {
                                    printf("删除记录失败，请重新选择操作\n");
                                    break;
                                }
                                else
                                {
                                    printf("记录删除成功！\n");
                                }
                                break;
                            }
                            case 2:
                            {
                                if (delAllRecords(username))
                                {
                                    printf("已清除全部记录！\n");
                                }
                                else
                                {
                                    printf("打开文件失败！\n");
                                }
                                break;
                            }
                            default:
                            {
                                printf("删除部分中无效的选择，请重新输入。\n");
                                break;
                            }
                            }
                        }
                        break;
                    }
                    case 6:
                    {
                        // 更新身高
                        printf("请输入最新身高：");
                        double newHeight;
                        scanf("%lf", &newHeight);
                        db.users[userNum].height = newHeight;
                        saveUserDatabase(&db);
                        break;
                    }
                    case 7:
                    {
                        printf("是否确定注销该账号:(y/n)");
                        char flag;
                        getchar();
                        scanf("%c", &flag);
                        if (flag == 'y')
                        {
                            if (!deleteUser(username))
                            {
                                printf("注销用户失败！\n");
                            }
                            else
                            {
                                printf("用户%s已经注销成功！\n", username);
                                deledUser = 1;
                                loadUserDatabase(&db);
                                // 此处应该到第一级页面，也就是注册登陆
                                break;
                            }
                        }
                        break;
                    }
                    default:
                    {
                        printf("%d是无效的选择，请重新输入。\n", choice);
                        break;
                    }
                    }
                }
                printf("\033[0m\n");
            }
            else
            {
                printf("登录失败！\n");
            }
            break;
        case 3:
            printf("程序已退出。\n");
            remove("../userlib/records.txt");
            exit(0); // 退出程序
        default:
            printf("输入不合法，请重新输入！\n");
            break;
        }
    }

    // return 0;
}
