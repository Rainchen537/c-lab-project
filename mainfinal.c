#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

// Platform-specific headers and functions
#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #define MKDIR(dir) _mkdir(dir)
    #define PATH_SEP "\\"
    // Enable UTF-8 support on Windows console
    void enable_utf8_windows(void) {
        SetConsoleOutputCP(65001); // UTF-8 code page
    }
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define MKDIR(dir) mkdir(dir, 0755)
    #define PATH_SEP "/"
    #define enable_utf8_windows() // Not needed on Unix/Linux
#endif

// File and path constants - using platform-specific separator
#define DATA_DIR "data"
#define FRIEND_DIR "data" PATH_SEP "friends"
#define WAIT_DIR "data" PATH_SEP "waiting"
#define MSG_DIR "data" PATH_SEP "messages"
#define USER_DB "data" PATH_SEP "users.txt"

// Character length limits
#define MaxName 32
#define MaxPwd 32
#define MaxLine 512
#define MaxMessage 512

typedef struct {
    char status[8];   // UNREAD or READ
    char date[11];    // YYYY-MM-DD
    char strTime[9]; // HH:MM:SS
    char sender[MaxName];
    char content[MaxMessage];
} Message;

// ---------- Basic utilities ----------

// Remove trailing newline characters
void trim_newline(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

// Simple string equality check
int strEqual(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}

// Clear input buffer - cross-platform version
void ClearStdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Recursively create directories - cross-platform version
int create_directory_recursive(const char *path) {
    char temp[MaxLine];
    char *p = NULL;
    size_t len;
    
    snprintf(temp, sizeof(temp), "%s", path);
    len = strlen(temp);
    
    // Remove trailing slash (if any)
    if (len > 0 && (temp[len - 1] == '/' || temp[len - 1] == '\\')) {
        temp[len - 1] = '\0';
        len--;
    }
    
    // Create directories step by step
    for (p = temp + 1; *p; p++) {
        if (*p == '/' || *p == '\\') {
            char old_char = *p;
            *p = '\0';
            
            // Try to create directory
            MKDIR(temp);
            
            *p = old_char;
        }
    }
    
    // Create final directory
    if (MKDIR(temp) != 0) {
        // Directory may already exist, not an error
        #ifdef _WIN32
            if (GetLastError() != ERROR_ALREADY_EXISTS) {
                return -1;
            }
        #endif
    }
    
    return 0;
}

// Ensure directory exists
void ensure_dir(const char *path) {
    create_directory_recursive(path);
}

void ensure_base_dirs(void) {
    ensure_dir(DATA_DIR);
    ensure_dir(FRIEND_DIR);
    ensure_dir(WAIT_DIR);
    ensure_dir(MSG_DIR);
}

// Read a line of input (including spaces)
void PromptLine(const char *tip, char *buf, size_t len) {
    printf("%s", tip);
    if (fgets(buf, (int)len, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    trim_newline(buf);
}

// ---------- User management ----------

// Check if user accnt exists
int user_exists(const char *name) {
    FILE *fp = fopen(USER_DB, "r");
    if (!fp) return 0;
    char line[MaxLine];
    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        char *sep = strchr(line, '|');
        if (!sep) continue;
        *sep = '\0';
        if (strEqual(line, name)) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// Add new accnt
int add_user(const char *name, const char *pwd) {
    FILE *fp = fopen(USER_DB, "a");
    if (!fp) {
        // Keep diagnostic message for debugging
        printf("Cannot write to user database, check permissions.\n");
        return 0;
    }
    fprintf(fp, "%s|%s\n", name, pwd);
    fclose(fp);
    return 1;
}

// Verify login
int verify_user(const char *name, const char *pwd) {
    FILE *fp = fopen(USER_DB, "r");
    if (!fp) return 0;
    char line[MaxLine];
    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        char *sep = strchr(line, '|');
        if (!sep) continue;
        *sep = '\0';
        const char *stored_pwd = sep + 1;
        if (strEqual(line, name) && strEqual(stored_pwd, pwd)) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// Registration flow
void register_flow(void) {
    char name[MaxName];
    char pwd1[MaxPwd];
    char pwd2[MaxPwd];
    PromptLine("Enter accnt name: ", name, sizeof(name));
    if (strchr(name, ' ') || strlen(name) == 0) {
        printf("Invalid username: cannot contain spaces or be empty.\n");
        return;
    }
    if (user_exists(name)) {
        printf("Accnt name already exists.\n");
        return;
    }
    PromptLine("Enter password: ", pwd1, sizeof(pwd1));
    PromptLine("Confirm password: ", pwd2, sizeof(pwd2));
    if (!strEqual(pwd1, pwd2)) {
        printf("Passwords do not match. Registration failed.\n");
        return;
    }
    if (add_user(name, pwd1)) {
        printf("Registration successful! You can now login.\n");
    } else {
        printf("Registration failed.\n");
    }
}

// Login flow
int login_flow(char *out_name) {
    char name[MaxName];
    char pwd[MaxPwd];
    PromptLine("Please input your accnt name: ", name, sizeof(name));
    PromptLine("and password: ", pwd, sizeof(pwd));
    
    // Check whether any user exists
    FILE *fp = fopen(USER_DB, "r");
    if (!fp) {
        printf("No user in this system, please register one.\n");
        return 0;
    }
    fclose(fp);
    
    if (!user_exists(name)) {
        printf("Warning! Accnt name not found.\n");
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

// ---------- List file utilities (friends/waiting) ----------

// Load string list file
int LoadList(const char *path, char arr[][MaxName], int max_cnt) {
    FILE *fp = fopen(path, "r");
    if (!fp) return 0;
    int cnt = 0;
    char line[MaxLine];
    while (cnt < max_cnt && fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        if (strlen(line) == 0) continue;
        strncpy(arr[cnt], line, MaxName - 1);
        arr[cnt][MaxName - 1] = '\0';
        cnt++;
    }
    fclose(fp);
    return cnt;
}

// Save string list file
void SaveList(const char *path, char arr[][MaxName], int cnt) {
    FILE *fp = fopen(path, "w");
    if (!fp) {
        printf("Failed to write file: %s\n", path);
        return;
    }
    for (int i = 0; i < cnt; i++) {
        fprintf(fp, "%s\n", arr[i]);
    }
    fclose(fp);
}

// Does list contain target
int list_contains(char arr[][MaxName], int cnt, const char *target) {
    for (int i = 0; i < cnt; i++) {
        if (strEqual(arr[i], target)) return 1;
    }
    return 0;
}

// Remove element from list
int list_remove(char arr[][MaxName], int cnt, const char *target) {
    int new_cnt = 0;
    for (int i = 0; i < cnt; i++) {
        if (!strEqual(arr[i], target)) {
            strcpy(arr[new_cnt++], arr[i]);
        }
    }
    return new_cnt;
}

// Build path - using platform-specific separator
void BuildPath(char *out, size_t len, const char *dir, const char *name, const char *suffix) {
    snprintf(out, len, "%s" PATH_SEP "%s%s", dir, name, suffix);
}

// ---------- Message read/write ----------

// Load all messages into dynamic array
int load_messages(const char *user, Message **out_msg, int *out_cnt) {
    char path[MaxLine];
    BuildPath(path, sizeof(path), MSG_DIR, user, ".txt");
    FILE *fp = fopen(path, "r");
    if (!fp) {
        *out_msg = NULL;
        *out_cnt = 0;
        return 1;
    }
    int capacity = 32;
    int cnt = 0;
    Message *arr = (Message *)malloc(sizeof(Message) * capacity);//dynamic memory allocation for messages
    if (!arr) {
        fclose(fp);
        return 0;
    }
    char line[MaxLine];
    while (fgets(line, sizeof(line), fp)) {//use fgetsto get string 
        trim_newline(line);
        if (strlen(line) == 0) {
            continue;
        }

        // Manual parse: split by '|' - take first four fields, rest as content (allow '|' in content)
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
        // Remaining is the 5th field (content)
        fields[fi++] = start;

        if (fi < 5) {
            // Format invalid, skip
            continue;
        }
        Message msg;
        strncpy(msg.status, fields[0], sizeof(msg.status) - 1);
        msg.status[sizeof(msg.status) - 1] = '\0';
        strncpy(msg.date, fields[1], sizeof(msg.date) - 1);
        msg.date[sizeof(msg.date) - 1] = '\0';
        strncpy(msg.strTime, fields[2], sizeof(msg.strTime) - 1);
        msg.strTime[sizeof(msg.strTime) - 1] = '\0';
        strncpy(msg.sender, fields[3], sizeof(msg.sender) - 1);
        msg.sender[sizeof(msg.sender) - 1] = '\0';
        strncpy(msg.content, fields[4], sizeof(msg.content) - 1);
        msg.content[sizeof(msg.content) - 1] = '\0';

        if (cnt >= capacity) {
            capacity *= 2;
            Message *tmp = (Message *)realloc(arr, sizeof(Message) * capacity);
            if (!tmp) {
                free(arr);
                fclose(fp);
                return 0;
            }
            arr = tmp;
        }
        arr[cnt++] = msg;
    }
    fclose(fp);
    *out_msg = arr;
    *out_cnt = cnt;
    return 1;
}

// Save message array to file
int save_messages(const char *user, Message *msg, int cnt) {
    char path[MaxLine];
    BuildPath(path, sizeof(path), MSG_DIR, user, ".txt");
    FILE *fp = fopen(path, "w");
    if (!fp) {
        printf("Failed to write message file: %s\n", path);
        return 0;
    }
    for (int i = 0; i < cnt; i++) {
        fprintf(fp, "%s|%s|%s|%s|%s\n",
                msg[i].status, msg[i].date, msg[i].strTime, msg[i].sender, msg[i].content);
    }
    fclose(fp);
    return 1;
}

// Append message to receiver's file
int AppendMsg(const char *receiver, const char *sender, const char *content) {
    char path[MaxLine];
    BuildPath(path, sizeof(path), MSG_DIR, receiver, ".txt");
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

// ---------- Date helpers ----------

// Parse dd/mm/yyyy
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

// Parse YYYY-MM-DD
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

// Date comparison (date only)
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

// ---------- Friend/waiting operations ----------

void ShowList(char arr[][MaxName], int cnt) {//void ShowList
    for (int i = 0; i < cnt; i++) {//use loop
        printf("%2d. %s\n", i + 1, arr[i]);//printf
    }
}

// Parse space-separated index selections
int parse_indexes(const char *line, int max, int *selected) {
    for (int i = 0; i < max; i++) selected[i] = 0;
    char buf[MaxLine];
    strncpy(buf, line, sizeof(buf) - 1);//use strncpy
    buf[sizeof(buf) - 1] = '\0';
    char *token = strtok(buf, " ");//use strtok
    int any = 0;
    while (token) {
        if (strEqual(token, "All") || strEqual(token, "all")) {
            for (int i = 0; i < max; i++) selected[i] = 1;
            return 1;
        }
        int idx = atoi(token);//change char into int
        if (idx >= 1 && idx <= max) {
            selected[idx - 1] = 1;
            any = 1;
        }
        token = strtok(NULL, " ");//use strtok
    }
    return any;
}

// Add friend requests
void add_friends_flow(const char *user) {
    char FriendsPath[MaxLine], WaitingPath[MaxLine];
    BuildPath(FriendsPath, sizeof(FriendsPath), FRIEND_DIR, user, ".txt");
    BuildPath(WaitingPath, sizeof(WaitingPath), WAIT_DIR, user, ".txt");

    char FriendList[256][MaxName];
    char WaitingList[256][MaxName];
    int friend_cnt = LoadList(FriendsPath, FriendList, 256);
    int waiting_cnt = LoadList(WaitingPath, WaitingList, 256);

    char line[MaxLine];
    PromptLine("Enter usernames to add (in one line separated by space): ", line, sizeof(line));
    if (strlen(line) == 0){
        return;
    }

    char buf[MaxLine];
    strncpy(buf, line, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    char *token = strtok(buf, " ");
    while (token) {
        const char *target = token;
        if (strEqual(target, user)) {
            printf("You cannot send a friend request to yourself.\n");
        } else if (!user_exists(target)) {
            printf("Accnt %s does not exist.\n", target);
        } else if (list_contains(FriendList, friend_cnt, target)) {
            printf("%s is already in your friend list.\n", target);
        } else if (list_contains(WaitingList, waiting_cnt, target)) {
            // Changed to sample expected prompt
            printf("Friend request to %s is already pending.\n", target);
        } else {
            // Check if the target has already sent a request to you (i.e., target's waiting list contains you)
            char target_wait[MaxLine];
            BuildPath(target_wait, sizeof(target_wait), WAIT_DIR, target, ".txt");
            char target_wait_list[256][MaxName];
            int target_wait_cnt = LoadList(target_wait, target_wait_list, 256);//use function LoadList
            if (list_contains(target_wait_list, target_wait_cnt, user)) {
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

// Accept friends
void accept_friends_flow(const char *user) {
    char WaitingPath[MaxLine], FriendsPath[MaxLine];
    BuildPath(WaitingPath, sizeof(WaitingPath), WAIT_DIR, user, ".txt");
    BuildPath(FriendsPath, sizeof(FriendsPath), FRIEND_DIR, user, ".txt");

    char WaitingList[256][MaxName];
    char FriendList[256][MaxName];
    int waiting_cnt = LoadList(WaitingPath, WaitingList, 256);
    int friend_cnt = LoadList(FriendsPath, FriendList, 256);

    if (waiting_cnt == 0) {
        printf("No pending friend requests for %s.\n", user);
        return;
    }
    printf("Pending friend requests for %s:\n", user);
    ShowList(WaitingList, waiting_cnt);//use ShowList function to show
    printf("%2d. All\n%2d. Back\n", waiting_cnt + 1, waiting_cnt + 2);//print the result

    char line[MaxLine];
    PromptLine("Enter indices (space separated), press Enter to finish: ", line, sizeof(line));//use function
    int selected[256] = {0};
    if (!parse_indexes(line, waiting_cnt + 2, selected)) {
        printf("No valid selection.\n");
        return;
    }
    // Back
    if (selected[waiting_cnt + 1]) return;
    // All
    if (selected[waiting_cnt]) {
        for (int i = 0; i < waiting_cnt; i++) selected[i] = 1;
    }
    int accepted_any = 0;
    for (int i = 0; i < waiting_cnt; i++) {
        if (!selected[i]) {
            continue;
        }
        const char *target = WaitingList[i];
        // Add both sides as friends
        if (!list_contains(FriendList, friend_cnt, target)) {
            strncpy(FriendList[friend_cnt++], target, MaxName - 1);
            FriendList[friend_cnt - 1][MaxName - 1] = '\0';
        }
        char TargetFriendPath[MaxLine];
        BuildPath(TargetFriendPath, sizeof(TargetFriendPath), FRIEND_DIR, target, ".txt");
        char TargetFriend[256][MaxName];
        int TargetFriend_cnt = LoadList(TargetFriendPath, TargetFriend, 256);
        if (!list_contains(TargetFriend, TargetFriend_cnt, user)) {
            strncpy(TargetFriend[TargetFriend_cnt++], user, MaxName - 1);
            TargetFriend[TargetFriend_cnt - 1][MaxName - 1] = '\0';
            SaveList(TargetFriendPath, TargetFriend, TargetFriend_cnt);
        }
        printf("Friend requests updated for %s.\n", target);
        accepted_any = 1;
    }
    // Clean waiting list
    int NewWait_cnt = 0;
    for (int i = 0; i < waiting_cnt; i++) {
        if (!selected[i]) {
            strcpy(WaitingList[NewWait_cnt++], WaitingList[i]);//use strcpy
        }
    }
    SaveList(WaitingPath, WaitingList, NewWait_cnt);//save the process
    SaveList(FriendsPath, FriendList, friend_cnt);//save the process
}
// Delete messages between two users
void DeleteMsg_between(const char *user, const char *friend_name) {
    Message *msg = NULL;
    int cnt = 0;
    if (!load_messages(user, &msg, &cnt)) {
        return;
    }
    int new_cnt = 0;
    for (int i = 0; i < cnt; i++) {
        if (!strEqual(msg[i].sender, friend_name)) {
            msg[new_cnt++] = msg[i];
        }
    }
    save_messages(user, msg, new_cnt);//use save_messages function
    free(msg);
}
// Delete friends
void delete_friends_flow(const char *user) {
    char FriendsPath[MaxLine];
    BuildPath(FriendsPath, sizeof(FriendsPath), FRIEND_DIR, user, ".txt");
    char FriendList[256][MaxName];
    int friend_cnt = LoadList(FriendsPath, FriendList, 256);
    if (friend_cnt == 0) {
        printf("You have no friends.\n");
        return;
    }
    printf("Your friends:\n");
    ShowList(FriendList, friend_cnt);
    printf("%2d. All\n%2d. Back\n", friend_cnt + 1, friend_cnt + 2);

    char line[MaxLine];
    PromptLine("Enter friend numbers (separated by space), press Enter to finish: ", line, sizeof(line));
    int selected[256] = {0};
    if (!parse_indexes(line, friend_cnt + 2, selected)) {
        printf("No valid selection.\n");
        return;
    }
    if (selected[friend_cnt + 1]) {
        return;
    }// Back
    if (selected[friend_cnt]) {
        for (int i = 0; i < friend_cnt; i++) selected[i] = 1;
    }
    
    // Show deletion progress
    for (int i = 0; i < friend_cnt; i++) {
        if (selected[i]) {
            const char *target = FriendList[i];
            if (friend_cnt == 1) {
                printf("Deleting %s...\n", target);
            } else if (selected[friend_cnt]) {
                printf("Deleting all...\n");
                break;
            } else {
                printf("Deleting %s...\n", target);
            }
        }
    }
    
    int new_cnt = 0;
    for (int i = 0; i < friend_cnt; i++) {
        if (selected[i]) {
            const char *target = FriendList[i];
            // Remove from target's friend list
            char TargetFriendPath[MaxLine];
            BuildPath(TargetFriendPath, sizeof(TargetFriendPath), FRIEND_DIR, target, ".txt");
            char TargetFriend[256][MaxName];
            int tcnt = LoadList(TargetFriendPath, TargetFriend, 256);
            tcnt = list_remove(TargetFriend, tcnt, user);
            SaveList(TargetFriendPath, TargetFriend, tcnt);
            // Delete messages on both sides
            DeleteMsg_between(user, target);
            DeleteMsg_between(target, user);
        } else {
            strcpy(FriendList[new_cnt++], FriendList[i]);//use strcpy
        }
    }
    SaveList(FriendsPath, FriendList, new_cnt);//use SaveList function
    printf("Friend list updated.\n");
}
// Show friends
void show_friends_flow(const char *user) {
    char FriendsPath[MaxLine];
    BuildPath(FriendsPath, sizeof(FriendsPath), FRIEND_DIR, user, ".txt");
    char FriendList[256][MaxName];
    int friend_cnt = LoadList(FriendsPath, FriendList, 256);
    if (friend_cnt == 0) {
        printf("You have no friends.\n");
        return;
    }
    printf("Your friends:\n");
    ShowList(FriendList, friend_cnt);
}

// ---------- Message operations ----------

void send_message_flow(const char *user) {
    char FriendsPath[MaxLine];
    BuildPath(FriendsPath, sizeof(FriendsPath), FRIEND_DIR, user, ".txt");
    char FriendList[256][MaxName];
    int friend_cnt = LoadList(FriendsPath, FriendList, 256);
    if (friend_cnt == 0) {
        printf("No friends to send messages to.\n");
        return;
    }
    
    char line[MaxLine];
    PromptLine("Enter message (max 255 chars), press Enter to finish: ", line, sizeof(line));
    if (strlen(line) == 0) {
        printf("Message is empty, cancelled.\n");
        return;
    }
    
    printf("Your friends:\n");
    ShowList(FriendList, friend_cnt);
    printf("%2d. All\n%2d. Back\n", friend_cnt + 1, friend_cnt + 2);

    char selection[MaxLine];
    PromptLine("Enter friend numbers (separated by space), press Enter to finish: ", selection, sizeof(selection));
    int selected[256] = {0};
    if (!parse_indexes(selection, friend_cnt + 2, selected)) {
        printf("No valid selection.\n");
        return;
    }
    if (selected[friend_cnt + 1]) return; // Back
    if (selected[friend_cnt]) {
        for (int i = 0; i < friend_cnt; i++) selected[i] = 1;
    }
    
    bool is_all = selected[friend_cnt];
    int sent_cnt = 0;
    for (int i = 0; i < friend_cnt; i++) {
        if (selected[i]) {
            if (AppendMsg(FriendList[i], user, line)) {
                if (!is_all) {
                    printf("Message sent to %s\n", FriendList[i]);
                }
                sent_cnt++;
            }
        }
    }
    
    if (sent_cnt > 0 && is_all) {
        printf("Message sent to All\n");
    }
}

void read_messages_flow(const char *user) {
    Message *msg = NULL;
    int cnt = 0;
    if (!load_messages(user, &msg, &cnt)) {
        printf("Failed to read messages.\n");
        return;
    }
    
    if (cnt == 0) {
        printf("No messages found.\n");
        free(msg);
        return;
    }
    
    printf("1. Read all messages\n");
    printf("2. Read unread messages only\n");
    printf("3. Back\n");
    printf("Choose an option: ");
    
    int choice;
    if (scanf("%d", &choice) != 1) {
        ClearStdin();
        printf("Invalid choice! Please enter a number between 1 and 3.\n");
        free(msg);
        return;
    }
    ClearStdin();
    
    if (choice == 3) {
        free(msg);
        return;
    }
    
    int unread_only = (choice == 2);
    int found = 0;
    
    for (int i = 0; i < cnt; i++) {
        if (unread_only && !strEqual(msg[i].status, "UNREAD")) continue;
        
        // Format timestamp for display
        if (strlen(msg[i].strTime) == 8) {
            // Already HH:MM:SS
            printf("[%s %s] From: %s\n", msg[i].date, msg[i].strTime, msg[i].sender);
        } else {
            printf("[%s] From: %s\n", msg[i].date, msg[i].sender);
        }
        printf("%s\n", msg[i].content);
        
        if (strEqual(msg[i].status, "UNREAD")) {
            strcpy(msg[i].status, "READ");
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
    
    save_messages(user, msg, cnt);
    free(msg);
}

void delete_messages_flow(const char *user) {
    Message *msg = NULL;
    int cnt = 0;
    if (!load_messages(user, &msg, &cnt)) {
        printf("Failed to read messages.\n");
        return;
    }
    
    if (cnt == 0) {
        printf("No messages found.\n");
        return;
    }
    
    char start_str[32], end_str[32], accnt[64];
    PromptLine("Enter start date (dd/mm/yyyy): ", start_str, sizeof(start_str));
    PromptLine("Enter end date (dd/mm/yyyy): ", end_str, sizeof(end_str));
    PromptLine("Enter accnt name (or 'all'): ", accnt, sizeof(accnt));

    struct tm start_tm, end_tm;
    if (!parse_input_date(start_str, &start_tm) || !parse_input_date(end_str, &end_tm)) {
        printf("Invalid date format.\n");
        free(msg);
        return;
    }
    
    int removed_cnt = 0;
    int new_cnt = 0;
    for (int i = 0; i < cnt; i++) {
        struct tm msg_tm;
        if (!parse_iso_date(msg[i].date, &msg_tm)) {
            msg[new_cnt++] = msg[i]; // Keep if cannot parse
            continue;
        }
        int in_range = date_in_range(&msg_tm, &start_tm, &end_tm);
        int match_accnt = strEqual(accnt, "all") || strEqual(msg[i].sender, accnt);
        if (in_range && match_accnt) {
            removed_cnt++;
            continue; // Delete
        }
        msg[new_cnt++] = msg[i];
    }
    
    save_messages(user, msg, new_cnt);
    free(msg);
    printf("Removed %d message(s) from %s in period %s - %s.\n", 
           removed_cnt, accnt, start_str, end_str);
}

// ---------- Menus ----------

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
            ClearStdin();
            printf("Invalid choice! Please enter a number between 1 and 5.\n");
            continue;
        }
        ClearStdin();
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
            ClearStdin();
            printf("Invalid choice! Please enter a number between 1 and 4.\n");
            continue;
        }
        ClearStdin();
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
            ClearStdin();
            printf("Invalid choice! Please enter a number between 1 and 3.\n");
            continue;
        }
        ClearStdin();
        switch (choice) {
            case 1: manage_friends_menu(user); break;
            case 2: manage_messages_menu(user); break;
            case 3: return;
            default: printf("Invalid choice! Please enter a number between 1 and 3.\n");
        }
    }
}

// ---------- Main entry ----------

int main(void) {
    // Enable UTF-8 support (Windows)
    enable_utf8_windows();
    
    ensure_base_dirs();
    int running = 1;
    while (running) {
        printf("\n==================== Login ====================\n");
        printf("1. Login\n");
        printf("2. Register (If you do not have an accnt)\n");
        printf("3. Exit\n");
        printf("===============================================\n");
        printf("Choose an option (1-3): ");
        int choice = 0;
        if (scanf("%d", &choice) != 1) {
            ClearStdin();
            printf("Invalid choice! Please enter a number between 1 and 3.\n");
            continue;
        }
        ClearStdin();
        if (choice == 1) {
            char username[MaxName];
            if (login_flow(username)) {
                main_service_menu(username);
            }
        } else if (choice == 2) {
            register_flow();
        } else if (choice == 3) {
            printf("Byebye!\n");
            running = 0;
        } else {
            printf("Invalid choice! Please enter a number between 1 and 3.\n");
        }
    }
    return 0;
}
