### 功能概述

1. 主界面

   主界面即登陆界面，包括三个功能：注册、登陆、退出程序

   + 用户在注册时需要输入用户名、密码、年龄、性别（1代表男性，2代表女性）、当前身高；身高可以在功能界面修改。

   + 登陆时只需输入账号密码即可

2. 功能界面

   功能界面左上角显示当前用户名，右上角显示此时该用户的身高，主体部分显示8个功能和对应的序号。

   + 计算BMI值：根据注册时的身高、性别、年龄和输入的体重计算BMI，计算后给出BMI值并给出体重过轻、体重过重、处于正常范围等提示。此处计算结果会保存到临时文件中。
   + 显示历史BMI记录：需要在保存BMI记录后使用，给出两种排序后的BMI记录，第一种是按照时间由远及近，第二种是按照BMI降序给出。
   + 保存BMI记录：在功能1中保存至临时文件中的数据中找出该用户的数据，并保存到以该用户名命名的文件中，以永久保存。
   + 显示BMI记录柱状图：读取功能3中保存到数据，并按时间顺序绘制柱状图。
   + 删除BMI记录：先给出所有的BMI记录，并标注其为第几条。分为两个功能：
     + 删除某条记录：用户输入要删除第几条，记录中就相应的删除该条。
     + 删除所有记录：删除该用户的所有BMI记录，直接清空文件。
   + 更改身高：考虑到用户的身高可能变化，设置这一功能，用于修改用户数据和计算BMI时的身高数据
   + 账号注销：直接删除该用户的账户数据和BMI记录文件，并返回到主页面
   + 返回主页面：返回上一级

### **注意事项：**

1. 退出系统前要选用功能3保存BMI记录；
2. 对于当次运行时的BMI记录，先使用功能3后才能使用功能2和功能4进行查看，也就是保存记录是必须的。