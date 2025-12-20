#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

// 平台特定的头文件和函数
#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #define MKDIR(dir) _mkdir(dir)
    #define PATH_SEP "\\"
    // Windows控制台UTF-8支持
    void enable_utf8_windows(void) {
        SetConsoleOutputCP(65001); // UTF-8 code page
    }
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define MKDIR(dir) mkdir(dir, 0755)
    #define PATH_SEP "/"
    #define enable_utf8_windows() // 在Unix/Linux上不需要
#endif

// 文件与路径常量 - 使用平台特定的分隔符
#define DATA_DIR "data"
#define FRIEND_DIR "data" PATH_SEP "friends"
#define WAIT_DIR "data" PATH_SEP "waiting"
#define MSG_DIR "data" PATH_SEP "messages"
#define USER_DB "data" PATH_SEP "users.txt"

// 字符长度限制
#define MAX_NAME 32
#define MAX_PWD 32
#define MAX_LINE 512
#define MAX_MESSAGE 512

typedef struct {
    char status[8];   // UNREAD 或 READ
    char date[11];    // YYYY-MM-DD
    char time_str[9]; // HH:MM:SS
    char sender[MAX_NAME];
    char content[MAX_MESSAGE];
} Message;

// ---------- 基础工具 ----------

// 去除行末换行符
void trim_newline(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

// 简单字符串相等判断
int str_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}

// 清空输入缓冲区 - 跨平台版本
void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// 递归创建目录 - 跨平台版本
int create_directory_recursive(const char *path) {
    char temp[MAX_LINE];
    char *p = NULL;
    size_t len;
    
    snprintf(temp, sizeof(temp), "%s", path);
    len = strlen(temp);
    
    // 移除末尾的斜杠（如果有）
    if (len > 0 && (temp[len - 1] == '/' || temp[len - 1] == '\\')) {
        temp[len - 1] = '\0';
        len--;
    }
    
    // 逐级创建目录
    for (p = temp + 1; *p; p++) {
        if (*p == '/' || *p == '\\') {
            char old_char = *p;
            *p = '\0';
            
            // 尝试创建目录
            MKDIR(temp);
            
            *p = old_char;
        }
    }
    
    // 创建最终目录
    if (MKDIR(temp) != 0) {
        // 目录可能已经存在，这不是一个错误
        #ifdef _WIN32
            if (GetLastError() != ERROR_ALREADY_EXISTS) {
                return -1;
            }
        #endif
    }
    
    return 0;
}

// 确保目录存在
void ensure_dir(const char *path) {
    create_directory_recursive(path);
}

void ensure_base_dirs(void) {
    ensure_dir(DATA_DIR);
    ensure_dir(FRIEND_DIR);
    ensure_dir(WAIT_DIR);
    ensure_dir(MSG_DIR);
}

// 读取一行输入（包含空格）
void prompt_line(const char *tip, char *buf, size_t len) {
    printf("%s", tip);
    if (fgets(buf, (int)len, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    trim_newline(buf);
}

// ---------- 用户管理 ----------

// 检查账号是否存在
int user_exists(const char *name) {
    FILE *fp = fopen(USER_DB, "r");
    if (!fp) return 0;
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        char *sep = strchr(line, '|');
        if (!sep) continue;
        *sep = '\0';
        if (str_equal(line, name)) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// 新增账号
int add_user(const char *name, const char *pwd) {
    FILE *fp = fopen(USER_DB, "a");
    if (!fp) {
        // 保留诊断信息，便于调试
        printf("Cannot write to user database, check permissions.\n");
        return 0;
    }
    fprintf(fp, "%s|%s\n", name, pwd);
    fclose(fp);
    return 1;
}

// 验证登录
int verify_user(const char *name, const char *pwd) {
    FILE *fp = fopen(USER_DB, "r");
    if (!fp) return 0;
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        char *sep = strchr(line, '|');
        if (!sep) continue;
        *sep = '\0';
        const char *stored_pwd = sep + 1;
        if (str_equal(line, name) && str_equal(stored_pwd, pwd)) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// 注册流程
void register_flow(void) {
    char name[MAX_NAME];
    char pwd1[MAX_PWD];
    char pwd2[MAX_PWD];
    prompt_line("Enter account name: ", name, sizeof(name));
    if (strchr(name, ' ') || strlen(name) == 0) {
        printf("Invalid username: cannot contain spaces or be empty.\n");
        return;
    }
    if (user_exists(name)) {
        printf("Account name already exists.\n");
        return;
    }
    prompt_line("Enter password: ", pwd1, sizeof(pwd1));
    prompt_line("Confirm password: ", pwd2, sizeof(pwd2));
    if (!str_equal(pwd1, pwd2)) {
        printf("Passwords do not match. Registration failed.\n");
        return;
    }
    if (add_user(name, pwd1)) {
        printf("Registration successful! You can now login.\n");
    } else {
        printf("Registration failed.\n");
    }
}

// 登录流程
int login_flow(char *out_name) {
    char name[MAX_NAME];
    char pwd[MAX_PWD];
    prompt_line("Please input your account name: ", name, sizeof(name));
    prompt_line("and password: ", pwd, sizeof(pwd));
    
    // 检查是否有任何用户存在
    FILE *fp = fopen(USER_DB, "r");
    if (!fp) {
        printf("No user in this system, please register one.\n");
        return 0;
    }
    fclose(fp);
    
    if (!user_exists(name)) {
        printf("Warning! Account name not found.\n");
        return 0;
    }
    
    if (verify_user(name, pwd)) {
        strcpy(out_name, name);
        printf("Login successful. Welcome %s!\n", name);
        return 1;
    } else {
        printf("Warning! Incorrect password.\n");
        return 0;
    }
}

// ---------- 列表文件工具（好友/待确认） ----------

// 读取字符串列表文件
int load_list(const char *path, char arr[][MAX_NAME], int max_count) {
    FILE *fp = fopen(path, "r");
    if (!fp) return 0;
    int count = 0;
    char line[MAX_LINE];
    while (count < max_count && fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        if (strlen(line) == 0) continue;
        strncpy(arr[count], line, MAX_NAME - 1);
        arr[count][MAX_NAME - 1] = '\0';
        count++;
    }
    fclose(fp);
    return count;
}

// 保存字符串列表文件
void save_list(const char *path, char arr[][MAX_NAME], int count) {
    FILE *fp = fopen(path, "w");
    if (!fp) {
        printf("Failed to write file: %s\n", path);
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n", arr[i]);
    }
    fclose(fp);
}

// 列表是否包含目标
int list_contains(char arr[][MAX_NAME], int count, const char *target) {
    for (int i = 0; i < count; i++) {
        if (str_equal(arr[i], target)) return 1;
    }
    return 0;
}

// 从列表移除元素
int list_remove(char arr[][MAX_NAME], int count, const char *target) {
    int new_count = 0;
    for (int i = 0; i < count; i++) {
        if (!str_equal(arr[i], target)) {
            strcpy(arr[new_count++], arr[i]);
        }
    }
    return new_count;
}

// 构建路径 - 使用平台特定的分隔符
void build_path(char *out, size_t len, const char *dir, const char *name, const char *suffix) {
    snprintf(out, len, "%s" PATH_SEP "%s%s", dir, name, suffix);
}

// ---------- 消息读写 ----------

// 读取所有消息到动态数组
int load_messages(const char *user, Message **out_msgs, int *out_count) {
    char path[MAX_LINE];
    build_path(path, sizeof(path), MSG_DIR, user, ".txt");
    FILE *fp = fopen(path, "r");
    if (!fp) {
        *out_msgs = NULL;
        *out_count = 0;
        return 1;
    }
    int capacity = 32;
    int count = 0;
    Message *arr = (Message *)malloc(sizeof(Message) * capacity);
    if (!arr) {
        fclose(fp);
        return 0;
    }
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        if (strlen(line) == 0) continue;

        // 手动解析：以 '|' 为分隔，前四个 '|' 拆出前四字段，剩余作为 content（允许 content 含 '|'）
        char *p = line;
        char *fields[5] = {0};
        int fi = 0;
        char *start = p;
        while (*p != '\0' && fi < 4) {
            if (*p == '|') {
                *p = '\0';
                fields[fi++] = start;
                start = p + 1;
            }
            p++;
        }
        // 剩下的作为第5字段（content）
        fields[fi++] = start;

        if (fi < 5) {
            // 格式不符合，跳过
            continue;
        }
        Message msg;
        strncpy(msg.status, fields[0], sizeof(msg.status) - 1);
        msg.status[sizeof(msg.status) - 1] = '\0';
        strncpy(msg.date, fields[1], sizeof(msg.date) - 1);
        msg.date[sizeof(msg.date) - 1] = '\0';
        strncpy(msg.time_str, fields[2], sizeof(msg.time_str) - 1);
        msg.time_str[sizeof(msg.time_str) - 1] = '\0';
        strncpy(msg.sender, fields[3], sizeof(msg.sender) - 1);
        msg.sender[sizeof(msg.sender) - 1] = '\0';
        strncpy(msg.content, fields[4], sizeof(msg.content) - 1);
        msg.content[sizeof(msg.content) - 1] = '\0';

        if (count >= capacity) {
            capacity *= 2;
            Message *tmp = (Message *)realloc(arr, sizeof(Message) * capacity);
            if (!tmp) {
                free(arr);
                fclose(fp);
                return 0;
            }
            arr = tmp;
        }
        arr[count++] = msg;
    }
    fclose(fp);
    *out_msgs = arr;
    *out_count = count;
    return 1;
}

// 保存消息数组到文件
int save_messages(const char *user, Message *msgs, int count) {
    char path[MAX_LINE];
    build_path(path, sizeof(path), MSG_DIR, user, ".txt");
    FILE *fp = fopen(path, "w");
    if (!fp) {
        printf("Failed to write message file: %s\n", path);
        return 0;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s|%s|%s|%s|%s\n",
                msgs[i].status, msgs[i].date, msgs[i].time_str, msgs[i].sender, msgs[i].content);
    }
    fclose(fp);
    return 1;
}

// 追加消息到收件人文件
int append_message(const char *receiver, const char *sender, const char *content) {
    char path[MAX_LINE];
    build_path(path, sizeof(path), MSG_DIR, receiver, ".txt");
    FILE *fp = fopen(path, "a");
    if (!fp) {
        printf("Cannot write to message file: %s\n", path);
        return 0;
    }
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date[11];
    char timebuf[9];
    snprintf(date, sizeof(date), "%04d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    snprintf(timebuf, sizeof(timebuf), "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);
    fprintf(fp, "UNREAD|%s|%s|%s|%s\n", date, timebuf, sender, content);
    fclose(fp);
    return 1;
}

// ---------- 日期辅助 ----------

// 解析 dd/mm/yyyy
int parse_input_date(const char *s, struct tm *out) {
    int d, m, y;
    if (sscanf(s, "%d/%d/%d", &d, &m, &y) != 3) return 0;
    memset(out, 0, sizeof(struct tm));
    out->tm_mday = d;
    out->tm_mon = m - 1;
    out->tm_year = y - 1900;
    out->tm_isdst = -1;
    return 1;
}

// 解析 YYYY-MM-DD
int parse_iso_date(const char *s, struct tm *out) {
    int y, m, d;
    if (sscanf(s, "%d-%d-%d", &y, &m, &d) != 3) return 0;
    memset(out, 0, sizeof(struct tm));
    out->tm_year = y - 1900;
    out->tm_mon = m - 1;
    out->tm_mday = d;
    out->tm_isdst = -1;
    return 1;
}

// 日期比较（仅日期部分）
int compare_date(struct tm *a, struct tm *b) {
    time_t ta = mktime(a);
    time_t tb = mktime(b);
    if (ta < tb) return -1;
    if (ta > tb) return 1;
    return 0;
}

int date_in_range(struct tm *target, struct tm *start, struct tm *end) {
    return compare_date(target, start) >= 0 && compare_date(target, end) <= 0;
}

// ---------- 好友/待确认操作 ----------

void show_list(char arr[][MAX_NAME], int count) {
    for (int i = 0; i < count; i++) {
        printf("%2d. %s\n", i + 1, arr[i]);
    }
}

// 读取空格分隔的索引选择
int parse_indexes(const char *line, int max, int *selected) {
    for (int i = 0; i < max; i++) selected[i] = 0;
    char buf[MAX_LINE];
    strncpy(buf, line, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    char *token = strtok(buf, " ");
    int any = 0;
    while (token) {
        if (str_equal(token, "All") || str_equal(token, "all")) {
            for (int i = 0; i < max; i++) selected[i] = 1;
            return 1;
        }
        int idx = atoi(token);
        if (idx >= 1 && idx <= max) {
            selected[idx - 1] = 1;
            any = 1;
        }
        token = strtok(NULL, " ");
    }
    return any;
}

// 添加好友请求
void add_friends_flow(const char *user) {
    char friends_path[MAX_LINE], waiting_path[MAX_LINE];
    build_path(friends_path, sizeof(friends_path), FRIEND_DIR, user, ".txt");
    build_path(waiting_path, sizeof(waiting_path), WAIT_DIR, user, ".txt");

    char friend_list[256][MAX_NAME];
    char waiting_list[256][MAX_NAME];
    int friend_count = load_list(friends_path, friend_list, 256);
    int waiting_count = load_list(waiting_path, waiting_list, 256);

    char line[MAX_LINE];
    prompt_line("Enter usernames to add (in one line separated by space): ", line, sizeof(line));
    if (strlen(line) == 0) return;

    char buf[MAX_LINE];
    strncpy(buf, line, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    char *token = strtok(buf, " ");
    while (token) {
        const char *target = token;
        if (str_equal(target, user)) {
            printf("You cannot send a friend request to yourself.\n");
        } else if (!user_exists(target)) {
            printf("Account %s does not exist.\n", target);
        } else if (list_contains(friend_list, friend_count, target)) {
            printf("%s is already in your friend list.\n", target);
        } else if (list_contains(waiting_list, waiting_count, target)) {
            // 修改为 sample 所期望的提示词
            printf("Friend request to %s is already pending.\n", target);
        } else {
            // 检查是否已在对方待确认列表（即目标已向你发请求）
            char target_wait[MAX_LINE];
            build_path(target_wait, sizeof(target_wait), WAIT_DIR, target, ".txt");
            char target_wait_list[256][MAX_NAME];
            int target_wait_count = load_list(target_wait, target_wait_list, 256);
            if (list_contains(target_wait_list, target_wait_count, user)) {
                printf("%s has sent friend request to you.\n", target);
            } else {
                FILE *fp = fopen(target_wait, "a");
                if (!fp) {
                    printf("Cannot update %s's waiting list.\n", target);
                } else {
                    fprintf(fp, "%s\n", user);
                    fclose(fp);
                    printf("Friend request sent to %s.\n", target);
                }
            }
        }
        token = strtok(NULL, " ");
    }
}

// 接受好友
void accept_friends_flow(const char *user) {
    char waiting_path[MAX_LINE], friends_path[MAX_LINE];
    build_path(waiting_path, sizeof(waiting_path), WAIT_DIR, user, ".txt");
    build_path(friends_path, sizeof(friends_path), FRIEND_DIR, user, ".txt");

    char waiting_list[256][MAX_NAME];
    char friend_list[256][MAX_NAME];
    int waiting_count = load_list(waiting_path, waiting_list, 256);
    int friend_count = load_list(friends_path, friend_list, 256);

    if (waiting_count == 0) {
        printf("No pending friend requests for %s.\n", user);
        return;
    }
    printf("Pending friend requests for %s:\n", user);
    show_list(waiting_list, waiting_count);
    printf("%2d. All\n%2d. Back\n", waiting_count + 1, waiting_count + 2);

    char line[MAX_LINE];
    prompt_line("Enter indices (space separated), press Enter to finish: ", line, sizeof(line));
    int selected[256] = {0};
    if (!parse_indexes(line, waiting_count + 2, selected)) {
        printf("No valid selection.\n");
        return;
    }
    // Back
    if (selected[waiting_count + 1]) return;
    // All
    if (selected[waiting_count]) {
        for (int i = 0; i < waiting_count; i++) selected[i] = 1;
    }

    int accepted_any = 0;
    for (int i = 0; i < waiting_count; i++) {
        if (!selected[i]) continue;
        const char *target = waiting_list[i];
        // 添加双方好友
        if (!list_contains(friend_list, friend_count, target)) {
            strncpy(friend_list[friend_count++], target, MAX_NAME - 1);
            friend_list[friend_count - 1][MAX_NAME - 1] = '\0';
        }
        char target_friend_path[MAX_LINE];
        build_path(target_friend_path, sizeof(target_friend_path), FRIEND_DIR, target, ".txt");
        char target_friends[256][MAX_NAME];
        int target_friend_count = load_list(target_friend_path, target_friends, 256);
        if (!list_contains(target_friends, target_friend_count, user)) {
            strncpy(target_friends[target_friend_count++], user, MAX_NAME - 1);
            target_friends[target_friend_count - 1][MAX_NAME - 1] = '\0';
            save_list(target_friend_path, target_friends, target_friend_count);
        }
        printf("Friend requests updated for %s.\n", target);
        accepted_any = 1;
    }
    // 清理等待列表
    int new_wait_count = 0;
    for (int i = 0; i < waiting_count; i++) {
        if (!selected[i]) {
            strcpy(waiting_list[new_wait_count++], waiting_list[i]);
        }
    }
    save_list(waiting_path, waiting_list, new_wait_count);
    save_list(friends_path, friend_list, friend_count);
}

// 删除双方消息
void delete_messages_between(const char *user, const char *friend_name) {
    Message *msgs = NULL;
    int count = 0;
    if (!load_messages(user, &msgs, &count)) return;
    int new_count = 0;
    for (int i = 0; i < count; i++) {
        if (!str_equal(msgs[i].sender, friend_name)) {
            msgs[new_count++] = msgs[i];
        }
    }
    save_messages(user, msgs, new_count);
    free(msgs);
}

// 删除好友
void delete_friends_flow(const char *user) {
    char friends_path[MAX_LINE];
    build_path(friends_path, sizeof(friends_path), FRIEND_DIR, user, ".txt");
    char friend_list[256][MAX_NAME];
    int friend_count = load_list(friends_path, friend_list, 256);
    if (friend_count == 0) {
        printf("You have no friends.\n");
        return;
    }
    printf("Your friends:\n");
    show_list(friend_list, friend_count);
    printf("%2d. All\n%2d. Back\n", friend_count + 1, friend_count + 2);

    char line[MAX_LINE];
    prompt_line("Enter friend numbers (separated by space), press Enter to finish: ", line, sizeof(line));
    int selected[256] = {0};
    if (!parse_indexes(line, friend_count + 2, selected)) {
        printf("No valid selection.\n");
        return;
    }
    if (selected[friend_count + 1]) return; // Back
    if (selected[friend_count]) {
        for (int i = 0; i < friend_count; i++) selected[i] = 1;
    }
    
    // 显示删除进度
    for (int i = 0; i < friend_count; i++) {
        if (selected[i]) {
            const char *target = friend_list[i];
            if (friend_count == 1) {
                printf("Deleting %s...\n", target);
            } else if (selected[friend_count]) {
                printf("Deleting all...\n");
                break;
            } else {
                printf("Deleting %s...\n", target);
            }
        }
    }
    
    int new_count = 0;
    for (int i = 0; i < friend_count; i++) {
        if (selected[i]) {
            const char *target = friend_list[i];
            // 从对方好友列表删除
            char target_friend_path[MAX_LINE];
            build_path(target_friend_path, sizeof(target_friend_path), FRIEND_DIR, target, ".txt");
            char target_friends[256][MAX_NAME];
            int tcount = load_list(target_friend_path, target_friends, 256);
            tcount = list_remove(target_friends, tcount, user);
            save_list(target_friend_path, target_friends, tcount);
            // 删除双方消息
            delete_messages_between(user, target);
            delete_messages_between(target, user);
        } else {
            strcpy(friend_list[new_count++], friend_list[i]);
        }
    }
    save_list(friends_path, friend_list, new_count);
    printf("Friend list updated.\n");
}

// 展示好友
void show_friends_flow(const char *user) {
    char friends_path[MAX_LINE];
    build_path(friends_path, sizeof(friends_path), FRIEND_DIR, user, ".txt");
    char friend_list[256][MAX_NAME];
    int friend_count = load_list(friends_path, friend_list, 256);
    if (friend_count == 0) {
        printf("You have no friends.\n");
        return;
    }
    printf("Your friends:\n");
    show_list(friend_list, friend_count);
}

// ---------- 消息操作 ----------

void send_message_flow(const char *user) {
    char friends_path[MAX_LINE];
    build_path(friends_path, sizeof(friends_path), FRIEND_DIR, user, ".txt");
    char friend_list[256][MAX_NAME];
    int friend_count = load_list(friends_path, friend_list, 256);
    if (friend_count == 0) {
        printf("No friends to send messages to.\n");
        return;
    }
    
    char line[MAX_LINE];
    prompt_line("Enter message (max 255 chars), press Enter to finish: ", line, sizeof(line));
    if (strlen(line) == 0) {
        printf("Message is empty, cancelled.\n");
        return;
    }
    
    printf("Your friends:\n");
    show_list(friend_list, friend_count);
    printf("%2d. All\n%2d. Back\n", friend_count + 1, friend_count + 2);

    char selection[MAX_LINE];
    prompt_line("Enter friend numbers (separated by space), press Enter to finish: ", selection, sizeof(selection));
    int selected[256] = {0};
    if (!parse_indexes(selection, friend_count + 2, selected)) {
        printf("No valid selection.\n");
        return;
    }
    if (selected[friend_count + 1]) return; // Back
    if (selected[friend_count]) {
        for (int i = 0; i < friend_count; i++) selected[i] = 1;
    }
    
    bool is_all = selected[friend_count];
    int sent_count = 0;
    for (int i = 0; i < friend_count; i++) {
        if (selected[i]) {
            if (append_message(friend_list[i], user, line)) {
                if (!is_all) {
                    printf("Message sent to %s\n", friend_list[i]);
                }
                sent_count++;
            }
        }
    }
    
    if (sent_count > 0 && is_all) {
        printf("Message sent to All\n");
    }
}

void read_messages_flow(const char *user) {
    Message *msgs = NULL;
    int count = 0;
    if (!load_messages(user, &msgs, &count)) {
        printf("Failed to read messages.\n");
        return;
    }
    
    if (count == 0) {
        printf("No messages found.\n");
        free(msgs);
        return;
    }
    
    printf("1. Read all messages\n");
    printf("2. Read unread messages only\n");
    printf("3. Back\n");
    printf("Choose an option: ");
    
    int choice;
    if (scanf("%d", &choice) != 1) {
        clear_stdin();
        printf("Invalid choice! Please enter a number between 1 and 3.\n");
        free(msgs);
        return;
    }
    clear_stdin();
    
    if (choice == 3) {
        free(msgs);
        return;
    }
    
    int unread_only = (choice == 2);
    int found = 0;
    
    for (int i = 0; i < count; i++) {
        if (unread_only && !str_equal(msgs[i].status, "UNREAD")) continue;
        
        // 解析时间字符串为更易读的格式
        if (strlen(msgs[i].time_str) == 8) {
            // 格式已经是 HH:MM:SS
            printf("[%s %s] From: %s\n", msgs[i].date, msgs[i].time_str, msgs[i].sender);
        } else {
            printf("[%s] From: %s\n", msgs[i].date, msgs[i].sender);
        }
        printf("%s\n", msgs[i].content);
        
        if (str_equal(msgs[i].status, "UNREAD")) {
            strcpy(msgs[i].status, "READ");
        }
        found = 1;
    }
    
    if (!found) {
        if (unread_only) {
            printf("Found no messages.\n");
        } else {
            printf("No messages found.\n");
        }
    }
    
    save_messages(user, msgs, count);
    free(msgs);
}

void delete_messages_flow(const char *user) {
    Message *msgs = NULL;
    int count = 0;
    if (!load_messages(user, &msgs, &count)) {
        printf("Failed to read messages.\n");
        return;
    }
    
    if (count == 0) {
        printf("No messages found.\n");
        return;
    }
    
    char start_str[32], end_str[32], account[64];
    prompt_line("Enter start date (dd/mm/yyyy): ", start_str, sizeof(start_str));
    prompt_line("Enter end date (dd/mm/yyyy): ", end_str, sizeof(end_str));
    prompt_line("Enter account name (or 'all'): ", account, sizeof(account));

    struct tm start_tm, end_tm;
    if (!parse_input_date(start_str, &start_tm) || !parse_input_date(end_str, &end_tm)) {
        printf("Invalid date format.\n");
        free(msgs);
        return;
    }
    
    int removed_count = 0;
    int new_count = 0;
    for (int i = 0; i < count; i++) {
        struct tm msg_tm;
        if (!parse_iso_date(msgs[i].date, &msg_tm)) {
            msgs[new_count++] = msgs[i]; // 无法解析则保留
            continue;
        }
        int in_range = date_in_range(&msg_tm, &start_tm, &end_tm);
        int match_account = str_equal(account, "all") || str_equal(msgs[i].sender, account);
        if (in_range && match_account) {
            removed_count++;
            continue; // 删除
        }
        msgs[new_count++] = msgs[i];
    }
    
    save_messages(user, msgs, new_count);
    free(msgs);
    printf("Removed %d message(s) from %s in period %s - %s.\n", 
           removed_count, account, start_str, end_str);
}

// ---------- 菜单 ----------

void manage_friends_menu(const char *user) {
    int choice = 0;
    while (1) {
        printf("\n==================== Manage Friends ====================\n");
        printf("1. Add friends\n");
        printf("2. Accept friends\n");
        printf("3. Delete friends\n");
        printf("4. Show current friends\n");
        printf("5. Back\n");
        printf("========================================================\n");
        printf("Choose an option (1-5): ");
        if (scanf("%d", &choice) != 1) {
            clear_stdin();
            printf("Invalid choice! Please enter a number between 1 and 5.\n");
            continue;
        }
        clear_stdin();
        switch (choice) {
            case 1: add_friends_flow(user); break;
            case 2: accept_friends_flow(user); break;
            case 3: delete_friends_flow(user); break;
            case 4: show_friends_flow(user); break;
            case 5: return;
            default: printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    }
}

void manage_messages_menu(const char *user) {
    int choice = 0;
    while (1) {
        printf("\n==================== Manage Messages ====================\n");
        printf("1. Send a message\n");
        printf("2. Read messages\n");
        printf("3. Delete messages\n");
        printf("4. Back\n");
        printf("=========================================================\n");
        printf("Choose an option (1-4): ");
        if (scanf("%d", &choice) != 1) {
            clear_stdin();
            printf("Invalid choice! Please enter a number between 1 and 4.\n");
            continue;
        }
        clear_stdin();
        switch (choice) {
            case 1: send_message_flow(user); break;
            case 2: read_messages_flow(user); break;
            case 3: delete_messages_flow(user); break;
            case 4: return;
            default: printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }
    }
}

void main_service_menu(const char *user) {
    int choice = 0;
    while (1) {
        printf("\n==================== Main Service ====================\n");
        printf("1. Manage friends\n");
        printf("2. Manage messages\n");
        printf("3. Back\n");
        printf("======================================================\n");
        printf("Choose an option (1-3): ");
        if (scanf("%d", &choice) != 1) {
            clear_stdin();
            printf("Invalid choice! Please enter a number between 1 and 3.\n");
            continue;
        }
        clear_stdin();
        switch (choice) {
            case 1: manage_friends_menu(user); break;
            case 2: manage_messages_menu(user); break;
            case 3: return;
            default: printf("Invalid choice! Please enter a number between 1 and 3.\n");
        }
    }
}

// ---------- 主入口 ----------

int main(void) {
    // 启用UTF-8支持（Windows）
    enable_utf8_windows();
    
    ensure_base_dirs();
    int running = 1;
    while (running) {
        printf("\n==================== Login ====================\n");
        printf("1. Login\n");
        printf("2. Register (If you do not have an account)\n");
        printf("3. Exit\n");
        printf("===============================================\n");
        printf("Choose an option (1-3): ");
        int choice = 0;
        if (scanf("%d", &choice) != 1) {
            clear_stdin();
            printf("Invalid choice! Please enter a number between 1 and 3.\n");
            continue;
        }
        clear_stdin();
        if (choice == 1) {
            char username[MAX_NAME];
            if (login_flow(username)) {
                main_service_menu(username);
            }
        } else if (choice == 2) {
            register_flow();
        } else if (choice == 3) {
            printf("Byebye!\n");
            printf("Press any key to continue...\n");
            getchar(); // 等待按键
            running = 0;
        } else {
            printf("Invalid choice! Please enter a number between 1 and 3.\n");
        }
    }
    return 0;
}
