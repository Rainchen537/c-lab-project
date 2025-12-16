# 课程项目：电子消息系统

*课程：COMP1023 Foundations of C Programming - 2025 Fall*

**截止时间：2025 年 12 月 24 日晚 11 点**

-------
**目录**：

[[_TOC_]]

-------
## 背景
本项目以小组形式完成。每位成员的贡献量需记录在随文件发布的 Excel 表中。你必须独立完成代码，不得与组外同学讨论或抄袭网络/他人代码（下面时间获取代码除外）。如发现小组之间互相抄袭，双方都记 0 分，与被抄袭者是否知情无关。请自行防止代码被抄袭。请先完整阅读本文档；项目需要“文件”相关知识，听完对应课程后再开始编程。

## 系统需求
> 1. 你将开发一个供好友通过电子消息互通的系统。  
> 2. 系统用户需先注册再登录。程序启动时显示“Login”菜单：  
```
    ==================== Login ====================
    1. Login
    2. Register (If you do not have an account)
    3. Exit
    ===============================================
    Choose an option (1-3): 
```
>> 用户输入 1–3 选择操作。首次使用需先注册；输入 3 退出系统。  
>> 选择 2 注册，系统依次要求输入：  
>> 1) 账号  
>>> 若账号未被占用，则可继续设置密码；否则提示账号已存在。账号不含空格。  
>> 2) 密码  
>>> 需输入两次密码并校验一致性。  
>>> a) 若一致，注册成功；  
>>> b) 若不一致，给出警告。  
>> 无论结果如何，都会回到“Login”菜单。  
> 3. 选择 1 登录后进入“Main Service”菜单：  
```
    ==================== Main Service ====================
    1. Manage friends
    2. Manage messages
    3. Back
    ======================================================
    Choose an option (1-3): 
```
>> 输入对应序号继续。

### 1) 管理好友
> 选择后出现“Manage Friends”菜单：  
```
    ==================== Manage Friends ====================
    1. Add friends
    2. Accept friends
    3. Delete friends
    4. Show current friends
    5. Back
    ========================================================
    Choose an option (1-5): 
```
> 输入序号操作；完成后返回当前菜单。  

#### 添加好友
> 输入欲添加账号名，空格分隔，例如 `Andy Bob Tony`。  
>> a) 不存在的账号给出警告；  
>> b) 不可添加自己，否则警告；  
>> c) 已存在情况处理：  
>>> i. 若对方已在好友列表或“待确认”列表，提示对应信息并忽略；  
>>> ii. 否则将本账号加入对方的“待确认”列表（若尚未在其中），并提示结果；  
>>> iii. 操作结束返回“Manage Friends”菜单。  

#### 接受好友
> 显示当前“待确认”列表供选择：  
```
        1. Account 1
        2. Account 2
        3. Account 3
        ...
        ...
        n-1. All
        n. Back
```
> n 取决于待确认人数。可输入多个索引一次接受。错误索引忽略，无需警告。显示已接受账号后返回上一层。接受后双方互为好友并可互发消息。  

#### 删除好友
> 展示好友列表，支持多选或全部删除，删除后双方好友关系同时移除，并需删除相关消息。  
```
        1. Account 1
        2. Account 2
        3. Account 3
        ...
        ...
        n-1. All
        n. Back
```
> 错误索引忽略，无需警告。  

#### 查看当前好友
> 显示所有好友。  

#### 返回
> 回到上级菜单。  

### 2) 管理消息
> 选择后显示“Manage Messages”菜单；完成 1–3 后返回当前菜单。  
```
    ==================== Manage Messages ====================
    1. Send a message
    2. Read messages
    3. Delete messages
    4. Back
    =========================================================
    Choose an option (1-4): 
```
> 输入对应序号继续。  

#### 发送消息
> 列出好友供选择：  
```
        1. Friend 1
        2. Friend 2
        3. Friend 3
        ...
        ...
        n-1. All
        n. Back
```
> 可同时向多个或全部好友发送。系统提示输入消息内容；假设消息长度不超过 255 字符，无需额外校验。  
> 每个账号对应一个 `<账号>.txt` 文件存储收到的消息，例如 Andy 的文件为 `Andy.txt`。  
> 消息写入时需包含接收时间。  

#### 阅读消息
> 支持读取全部或未读消息；已读消息需在文件中标记。每条显示日期时间、发送者、内容。  

#### 删除消息
> 可按时间段删除消息，需要输入开始日期、结束日期（含）、账号名。日期格式 `dd/mm/year`。  
> 若账号名为 `all`，则删除该期间来自所有好友的消息。  

#### 返回
> 回到上级菜单。  

### 3) 返回
> 回到上级菜单。  

## 非系统需求
> 1. 消息文件应便于阅读。  
> 2. 界面需友好。  
> 3. 程序结构清晰：一个主函数 + 若干子函数。  

## 提示
> 1. 可用 `time.h` 的 `tm` 结构和 `time` 系列函数获取当前日期时间，示例：  
```
    #include <stdio.h>
    #include <time.h>
    int main(void)
    {
        struct tm *tblock;
        time_t current_time;
        
        time(&current_time);
        tblock = localtime(&current_time);
        printf("%d %d %d\n", tblock->tm_year, tblock->tm_mon, tblock->tm_mday);
        return 0;
    }
```
>   `struct tm` 成员如下：  
```
    struct tm {
        int tm_sec;   /* second: [0,59] */
        int tm_min;   /* minute: [0,59] */
        int tm_hour;  /* hour: [0,23] */
        int tm_mday;  /* day in month: [1,31] */
        int tm_mon;   /* month: [0,11] */
        int tm_year;  /* year - 1900 */
        int tm_wday;  /* weekday: [0,6] */
        int tm_yday;  /* day in year: [0,365] */
        int tm_isdst; /* Daylight Saving Time Identifier */
        long int tm_gmtoff; /* Dateline */
        const char *tm_zone; /* Timezone */
    };
```
> 2. 分工时先约定各自函数原型，便于后续集成。建议绘制函数调用关系图。  

## 提交
> 1. 提交名为 `Group##.zip` 的压缩包（`##` 替换为组名），包含：  
>> a) 代码：`.c` 与 `.h`（若有）；  
>> b) 按 [project25F_sample.md](project25F_sample.md) 生成的三个 `.zip` 文件；  
>> c) Excel 文件 [Group_XX.xlsx](Group_XX.xlsx)（`XX` 替换为组名），记录组员贡献：2=正常，1=较少，0=无。  
> 2. 截止时间：2025 年 12 月 24 日晚 11 点。  

