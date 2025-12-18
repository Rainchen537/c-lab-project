This sample document showcase the output log for each function in the system. Record from program startup. Cases may uses different pre-filled data, please see the description in each case block.
此示例文档展示了系统中每个功能的输出日志。从程序启动开始记录。案例可能使用不同的预填充数据，请参阅每个案例块中的说明。

**Table of Contents**:
**目录**：

[[_TOC_]]
[[_目录_]]

# "Login" Menu
# “登录”菜单

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

## If invalid option number is given, give a warning and continue.
## 如果给出的选项编号无效，则发出警告并继续。

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 4
Invalid choice! Please enter a number between 1 and 3.
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

## Exit
## 退出

Exit the program.
退出程序。

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 3
Byebye!
Press any key to continue...
```

## Login - When there is no account in this program
## 登录 - 当该程序中没有帐户时

When there is no account in this program, if a user try to login:
当该程序中没有帐户时，如果用户尝试登录：

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Tom
and password: 123
No user in this system, please register one.
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

## Register
## 注册

If account name not used but two passwords different, give a warning.
如果未使用帐户名但两个密码不同，则发出警告。

account: Cindy  
帐号： 辛迪  
password: 123456  
密码：123456  
confirm password: 654321
确认密码：654321

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 2
Enter account name: Cindy
Enter password: 123456
Confirm password: 654321
Passwords do not match. Registration failed.
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

### If account name not used and two passwords are the same, register successfully.
### 如果未使用账户名且两个密码相同，则注册成功。

account: Cindy  
帐号： 辛迪  
password: 4567A8  
密码：4567A8  
confirm password: 4567A8
确认密码：4567A8

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 2
Enter account name: Cindy
Enter password: 4567A8
Confirm password: 4567A8
Registration successful! You can now login.
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

### If account name used, give a warning.
### 如果使用帐户名，请发出警告。

Account "Cindy" already exists.
帐户“Cindy”已存在。

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 2
Enter account name: Cindy
Account name already exists.
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

### Register more accounts
### 注册更多账户

account info:  
帐户信息：  
|  name  | password |
|  姓名      | 密码         |
| ------ | ------   |
| Emily  | e9M2xQ   |
| 艾米丽      | e9M2xQ       |
| James  | j8#Kp3   |
| 詹姆斯      | j8#Kp3   |
| Sophia | s5Rf@v   |
| 索菲亚       | s5Rf@v       |

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 2
Enter account name: Emily
Enter password: e9M2xQ
Confirm password: e9M2xQ
Registration successful! You can now login.
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 2
Enter account name: James
Enter password: j8#Kp3
Confirm password: j8#Kp3
Registration successful! You can now login.
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 2
Enter account name: Sophia
Enter password: s5Rf@v
Confirm password: s5Rf@v
Registration successful! You can now login.
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

## Manually combine all the .txt files generated until this stage into stage1.zip file.
## 手动将在此阶段之前生成的所有 .txt 文件合并到 stage1.zip 文件中。

** Manually combine all the .txt files generated until this stage into stage1.zip file. ** 
** 手动将在此阶段之前生成的所有 .txt 文件合并到 stage1.zip 文件中。** 

## Login - When there are accounts in this program
## 登录 - 当该程序中有帐户时

### If the input account not registered, give a warning.
### 如果输入的账号未注册，则给予警告。

account: Tom  
帐户： 汤姆  
password: 123
密码：123

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Tom
and password: 123
Warning! Account name not found.
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

### If the input account exists but password incorrect, give a warning.
### 如果输入的账号存在但密码不正确，则给出警告。

account: Cindy  
帐号： 辛迪  
password: 123456
密码：123456

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Cindy
and password: 123456
Warning! Incorrect password.
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

### If the input account exists and password correct, login successfully and "Main Service" menu shown.
### 如果输入的账号存在且密码正确，则登录成功，并显示“主要服务”菜单。

account: Cindy  
帐号： 辛迪  
password: 4567A8
密码：4567A8

In "Main Service" menu, user is able to go back to "Login" menu.
在“主要服务”菜单中，用户可以返回“登录”菜单。

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Cindy
and password: 4567A8
Login successful. Welcome Cindy!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

# Main Service - Manage Friends
# 主要服务-管理好友

## Add friends (Login as "Cindy")
## 添加好友（以“Cindy”身份登录）

### Add Cindy herself, give a warning.
### 添加辛迪本人，发出警告。

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Cindy
and password: 4567A8
Login successful. Welcome Cindy!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 1
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 1
Enter usernames to add (in one line separated by space): Cindy
You cannot send a friend request to yourself.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 
```

### Add an account that not exists, give a warning
### 添加不存在的账户，给出警告

```
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 1
Enter usernames to add (in one line separated by space): Apple
Account Apple does not exist.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 
```

### Add an existant account for the first time
### 首次添加现有帐户

```
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 1
Enter usernames to add (in one line separated by space): Emily
Friend request sent to Emily.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 
```

### Add an existant account for the second time
### 第二次添加现有帐户

```
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 1
Enter usernames to add (in one line separated by space): Emily
Friend request to Emily is already pending.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 
```

### Add more than one accounts (self, not exists, requested) at the same time
### 同时添加多个帐户（自己、不存在、请求）

```
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 1
Enter usernames to add (in one line separated by space): Cindy Apple Emily
You cannot send a friend request to yourself.
Account Apple does not exist.
Friend request to Emily is already pending.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 
```

### Add more than one accounts (all kinds) at the same time
### 同时添加多个账户（各种）

```
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 1
Enter usernames to add (in one line separated by space): Cindy James Apple Emily Sophia
You cannot send a friend request to yourself.
Friend request sent to James.
Account Apple does not exist.
Friend request to Emily is already pending.
Friend request sent to Sophia.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 
```

## Add friends (Switch user from "Cindy" to "Emily")
## 添加好友（将用户从“Cindy”切换为“Emily”）

```
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 5
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Emily
and password: e9M2xQ
Login successful. Welcome Emily!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 
```

### Add an account that has sent request to the current user
### 添加已向当前用户发送请求的帐户

Current user Emily try to add Cindy, but Cindy has requested to add Emily before
当前用户 Emily 尝试添加 Cindy，但 Cindy 之前已请求添加 Emily

```
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 1
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 1
Enter usernames to add (in one line separated by space): Cindy
Cindy has sent friend request to you.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 
```

### Switch to different accounts and add friends
### 切换不同账号并添加好友

Current user: Emily  
当前用户：艾米丽  
1. Enter "Accept friends", there will be "Cindy" in the pending friend requests list
1. 输入“接受好友”，待处理的好友请求列表中将会有“Cindy”
2. Go back to "Add friends" to add "James" and "Sophia"
2. 返回“添加好友”添加“James”和“Sophia”
3. Go back to "Login"
3. 返回“登录”

```
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 2
Pending friend requests for Emily:
1. Cindy
2. All
3. Back
Enter indices (space separated), press Enter to finish: 3
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 1
Enter usernames to add (in one line separated by space): James Sophia
Friend request sent to James.
Friend request sent to Sophia.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 5
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

Login as "James", add "Sophia":
以“James”身份登录，添加“Sophia”：

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: James
and password: j8#Kp3
Login successful. Welcome James!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 1
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 1
Enter usernames to add (in one line separated by space): Sophia
Friend request sent to Sophia.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 5
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 
```

## Delete/Show current friends - when the user have no friends
## 删除/显示当前好友 - 当用户没有好友时

```
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 3
You have no friends.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 4
You have no friends.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 
```

## Accept friends & Show current friends
## 接受好友并显示当前好友

Current account: James
经常账户：詹姆斯

```
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 2
Pending friend requests for James:
1. Cindy
2. Emily
3. All
4. Back
Enter indices (space separated), press Enter to finish: 2
Friend requests updated for Emily.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 4
Your friends:
1. Emily
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5):2
Pending friend requests for James:
1. Cindy
2. All
3. Back
Enter indices (space separated), press Enter to finish: 1
Friend requests updated for Cindy.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 4
Your friends:
1. Cindy
2. Emily
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5):2
No pending friend requests for James.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 5
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

Login as "Sophia", accept all friends and show current friends:
以“Sophia”身份登录，接受所有好友并显示当前好友：

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Sophia
and password: s5Rf@v
Login successful. Welcome Sophia!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 1
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 2
Pending friend requests for Sophia:
1. Cindy
2. Emily
3. James
4. All
5. Back
Enter indices (space separated), press Enter to finish: 1 2
Friend requests updated for Cindy.
Friend requests updated for Emily.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 4
Your friends:
1. Cindy
2. Emily
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 2
Pending friend requests for Sophia:
1. James
2. All
3. Back
Enter indices (space separated), press Enter to finish: 2
Friend requests updated for all.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 5
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

Login as "Emily", show current friends, accept all friends and show current friends again:
以“Emily”身份登录，显示当前好友，接受所有好友并再次显示当前好友：

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Emily
and password: e9M2xQ
Login successful. Welcome Emily!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 1
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 4
Your friends:
1. James
2. Sophia
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 2
Pending friend requests for Emily:
1. Cindy
2. All
3. Back
Enter indices (space separated), press Enter to finish: 2
Friend requests updated for all.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 4
Your friends:
1. Cindy
2. James
3. Sophia
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 5
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

Login as "Cindy", accept friends and show current friends:
以“Cindy”身份登录，接受好友并显示当前好友：

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Cindy
and password: 4567A8
Login successful. Welcome Cindy!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 1
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 2
No pending friend requests for Cindy.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 4
Your friends:
1. Emily
2. James
3. Sophia
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 
```

## Manually combine all the .txt files generated until this stage into stage2.zip file.
## 手动将在此阶段之前生成的所有 .txt 文件合并到 stage2.zip 文件中。

** Manually combine all the .txt files generated until this stage into stage2.zip file. **
** 手动将在此阶段之前生成的所有 .txt 文件合并到 stage2.zip 文件中。**

## Delete friends - When current friend list not empty
## 删除好友 - 当前好友列表不为空时

Current account: Cindy
往来账户： 辛迪

Delete one friend:
删除一位好友：

```
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 4
Your friends:
1. Emily
2. James
3. Sophia
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 3
Your friends:
1. Emily
2. James
3. Sophia
4. All
5. Back
Enter friend numbers (separated by space), press Enter to finish: 3
Deleting Sophia...
Friend list updated.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 5
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

Login as "Sophia", check the current friends of Sophia:
以“Sophia”登录，查看Sophia当前好友：

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Sophia
and password: s5Rf@v
Login successful. Welcome Sophia!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 1
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 4
Your friends:
1. Emily
2. James
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 
```

Delete multiple friends:
删除多个好友：

```
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 3
Your friends:
1. Emily
2. James
3. All
4. Back
Enter friend numbers (separated by space), press Enter to finish: 2 1
Deleting James...
Deleting Emily...
Friend list updated.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 4
You have no friends.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 5
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

Login as "James" and delete all friends:
以“James”身份登录并删除所有好友：

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: James
and password: j8#Kp3
Login successful. Welcome James!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 1
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 3
Your friends:
1. Cindy
2. Emily
3. All
4. Back
Enter friend numbers (separated by space), press Enter to finish: 3
Deleting all...
Friend list updated.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 4
You have no friends.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 5
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

Login as "Emily" and delete all friends:
以“Emily”身份登录并删除所有好友：

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Emily
and password: e9M2xQ
Login successful. Welcome Emily!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 1
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 3
Your friends:
1. Cindy
2. All
3. Back
Enter friend numbers (separated by space), press Enter to finish: 2
Deleting all...
Friend list updated.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 4
You have no friends.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 5
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

Login as "Cindy", delete all friends:
以“Cindy”登录，删除所有好友：

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Cindy
and password: 4567A8
Login successful. Welcome Cindy!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 1
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 3
You have no friends.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 4
You have no friends.
==================== Manage Friends ====================
1. Add friends
2. Accept friends
3. Delete friends
4. Show current friends
5. Back
========================================================
Choose an option (1-5): 5
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 3
Byebye!
Press any key to continue...
```

# Main Service - Manage Messages
# 主要服务 - 管理消息
Before testing "Manage Messages", we need to repeat the previous operations before ["Delete friends - When current friend list not empty"](#delete-friends-when-current-friend-list-not-empty). That is, Cindy, Emily, James and Sophia are friends of each other.
在测试“管理消息”之前，我们需要重复前面的操作[“删除好友-当当前好友列表不为空时”](#delete-friends-when-current-friend-list-not-empty)。也就是说，Cindy、Emily、James 和 Sophia 是彼此的朋友。

## Read/Delete messages - when the user have no messages
## 读取/删除消息 - 当用户没有消息时

Login as "James":
以“詹姆斯”身份登录：

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: James
and password: j8#Kp3
Login successful. Welcome James!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
No messages found.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 3
No messages found.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 
```

## Send/Read messages
## 发送/读取消息

### Message sending between two friends (James and Cindy)
### 两个朋友（詹姆斯和辛迪）之间发送消息

1. James send a message to Cindy:
1. 詹姆斯给辛迪发消息：

```
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 1
Enter message (max 255 chars), press Enter to finish: Hi Cindy, are we still meeting for lunch tomorrow?
Your friends:
1. Cindy
2. Emily
3. Sophia
4. All
5. Back
Enter friend numbers (separated by space), press Enter to finish: 1
Message sent to Cindy
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 3
No messages found.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
No messages found.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

2. Cindy read messages from James
2. 辛迪读了詹姆斯发来的信息

Login as "Cindy":
以“Cindy”身份登录：

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Cindy
and password: 4567A8
Login successful. Welcome Cindy!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 2
[2025-11-21 10:54:31] From: James
Hi Cindy, are we still meeting for lunch tomorrow?
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 2
Found no messages.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 1
[2025-11-21 10:54:31] From: James
Hi Cindy, are we still meeting for lunch tomorrow?
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 
```

3. Cindy send a message to James
3. 辛迪给詹姆斯留言

```
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 1
Enter message (max 255 chars), press Enter to finish: Yes, 12:30 at the usual place?
Your friends:
1. Emily
2. James
3. Sophia
4. All
5. Back
Enter friend numbers (separated by space), press Enter to finish: 2
Message sent to James
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

4. James read messages from Cindy
4. 詹姆斯读了辛迪发来的消息

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: James
and password: j8#Kp3
Login successful. Welcome James!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 2
[2025-11-21 11:16:11] From: Cindy
Yes, 12:30 at the usual place?
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3):
```

### Send a message to selected friends
### 向选定的朋友发送消息

1. Emily send a message to Cindy and Sophia
1. 艾米丽向辛迪和索菲亚发送消息

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Emily
and password: e9M2xQ
Login successful. Welcome Emily!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
No messages found.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 3
No messages found.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 1
Enter message (max 255 chars), press Enter to finish: Emergency meeting in 10 minutes!
Your friends:
1. Cindy
2. James
3. Sophia
4. All
5. Back
Enter friend numbers (separated by space), press Enter to finish: 1 3
Message sent to Cindy
Message sent to Sophia
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3):
```

2. Cindy reads messages
2. 辛迪读消息

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Cindy
and password: 4567A8
Login successful. Welcome Cindy!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 2
[2025-11-21 12:05:38] From: Emily
Emergency meeting in 10 minutes!
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 2
Found no messages.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 1
[2025-11-21 10:54:31] From: James
Hi Cindy, are we still meeting for lunch tomorrow?
[2025-11-21 12:05:38] From: Emily
Emergency meeting in 10 minutes!
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

3. Sophia reads messages
3. 索菲亚阅读消息

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Sophia
and password: s5Rf@v
Login successful. Welcome Sophia!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 1
[2025-11-21 12:05:38] From: Emily
Emergency meeting in 10 minutes!
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 2
Found no messages.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

### Send a message to all friends
### 给所有朋友发消息

1. Emily send a message to all friends
1. 艾米丽向所有朋友发送消息

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Emily
and password: e9M2xQ
Login successful. Welcome Emily!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 1
Enter message (max 255 chars), press Enter to finish: Emergency meeting in 5 minutes!
Your friends:
1. Cindy
2. James
3. Sophia
4. All
5. Back
Enter friend numbers (separated by space), press Enter to finish: 4
Message sent to All==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
No messages found.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 3
No messages found.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

2. Cindy reads messages
2. 辛迪读消息

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Cindy
and password: 4567A8
Login successful. Welcome Cindy!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 2
[2025-11-21 12:41:56] From: Emily
Emergency meeting in 5 minutes!
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 1
[2025-11-21 10:54:31] From: James
Hi Cindy, are we still meeting for lunch tomorrow?
[2025-11-21 12:05:38] From: Emily
Emergency meeting in 10 minutes!
[2025-11-21 12:41:56] From: Emily
Emergency meeting in 5 minutes!
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

3. James reads messages
3. 詹姆斯读消息

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: James
and password: j8#Kp3
Login successful. Welcome James!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 2
[2025-11-21 12:41:56] From: Emily
Emergency meeting in 5 minutes!
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 1
[2025-11-21 11:16:11] From: Cindy
Yes, 12:30 at the usual place?
[2025-11-21 12:41:56] From: Emily
Emergency meeting in 5 minutes!
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3):
```

4. Sophia reads messages
4. 索菲亚阅读消息

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Sophia
and password: s5Rf@v
Login successful. Welcome Sophia!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 2
[2025-11-21 12:41:56] From: Emily
Emergency meeting in 5 minutes!
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 1
[2025-11-21 12:05:38] From: Emily
Emergency meeting in 10 minutes!
[2025-11-21 12:41:56] From: Emily
Emergency meeting in 5 minutes!
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 
```

### Send a message from different users to their friends
### 将不同用户的消息发送给他们的朋友

1. Sophia continue to send a message to Emily
1. 索菲亚继续给艾米丽发消息

```
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 1
Enter message (max 255 chars), press Enter to finish: Running late, save me a seat
Your friends:
1. Cindy
2. Emily
3. James
4. All
5. Back
Enter friend numbers (separated by space), press Enter to finish: 2
Message sent to Emily
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

2. James sends a message to Sophia
2. 詹姆斯向索菲亚发送消息

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: James
and password: j8#Kp3
Login successful. Welcome James!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 1
Enter message (max 255 chars), press Enter to finish: Can you review my presentation?
Your friends:
1. Cindy
2. Emily
3. Sophia
4. All
5. Back
Enter friend numbers (separated by space), press Enter to finish: 3
Message sent to Sophia
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

3. Emily reads messages
3. 艾米丽读消息

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Emily
and password: e9M2xQ
Login successful. Welcome Emily!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 2
[2025-11-21 12:51:38] From: Sophia
Running late, save me a seat
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 1
[2025-11-21 12:51:38] From: Sophia
Running late, save me a seat
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

4. Sophia reads messages
4. 索菲亚阅读消息

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: Sophia
and password: s5Rf@v
Login successful. Welcome Sophia!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 2
[2025-11-21 12:55:12] From: James
Can you review my presentation?
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 1
[2025-11-21 12:05:38] From: Emily
Emergency meeting in 10 minutes!
[2025-11-21 12:41:56] From: Emily
Emergency meeting in 5 minutes!
[2025-11-21 12:55:12] From: James
Can you review my presentation?
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 
```

## Manually combine all the .txt files generated until this stage into stage3.zip file.
## 手动将在此阶段之前生成的所有 .txt 文件合并到 stage3.zip 文件中。

** Manually combine all the .txt files generated until this stage into stage3.zip file. **
** 手动将在此阶段之前生成的所有 .txt 文件合并到 stage3.zip 文件中。**

## Delete messages
## 删除消息

### Delete messages during a no message period
### 在无消息期间删除消息

```
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 3
Enter start date (dd/mm/yyyy): 20/11/2025
Enter end date (dd/mm/yyyy): 20/11/2025
Enter account name (or 'all'): Emily
Removed 0 message(s) from Emily in period 20/11/2025 - 20/11/2025.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 3
Enter start date (dd/mm/yyyy): 20/11/2024
Enter end date (dd/mm/yyyy): 20/12/2024
Enter account name (or 'all'): all
Removed 0 message(s) from all in period 20/11/2024 - 20/12/2024.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 
```

### Delete messages from a not existant friend
### 删除不存在的好友的消息

```
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 3
Enter start date (dd/mm/yyyy): 21/11/2025
Enter end date (dd/mm/yyyy): 21/11/2025
Enter account name (or 'all'): Apple
Removed 0 message(s) from Apple in period 21/11/2025 - 21/11/2025.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4):  
```

### Delete messages of a valid friend during a valid period
### 删除有效好友在有效期内的消息

```
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 3
Enter start date (dd/mm/yyyy): 21/11/2025
Enter end date (dd/mm/yyyy): 21/11/2025
Enter account name (or 'all'): Emily
Removed 2 message(s) from Emily in period 21/11/2025 - 21/11/2025.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 1
[2025-11-21 12:55:12] From: James
Can you review my presentation?
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 
```

### Delete all messages
### 删除所有消息

Login as "James":
以“詹姆斯”身份登录：

```
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 1
Please input your account name: James
and password: j8#Kp3
Login successful. Welcome James!
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 2
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
1. Read all messages
2. Read unread messages only
3. Back
Choose an option: 1
[2025-11-21 11:16:11] From: Cindy
Yes, 12:30 at the usual place?
[2025-11-21 12:41:56] From: Emily
Emergency meeting in 5 minutes!
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 3
Enter start date (dd/mm/yyyy): 21/11/2025
Enter end date (dd/mm/yyyy): 21/11/2025
Enter account name (or 'all'): all
Removed 2 message(s) from all in period 21/11/2025 - 21/11/2025.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 2
No messages found.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 3
No messages found.
==================== Manage Messages ====================
1. Send a message
2. Read messages
3. Delete messages
4. Back
=========================================================
Choose an option (1-4): 4
==================== Main Service ====================
1. Manage friends
2. Manage messages
3. Back
======================================================
Choose an option (1-3): 3
==================== Login ====================
1. Login
2. Register (If you do not have an account)
3. Exit
===============================================
Choose an option (1-3): 3
Byebye!
Press any key to continue...
```
