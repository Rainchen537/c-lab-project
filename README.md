# Course Project: e-Messaging System

*For COMP1023 Foundations of C Programming - 2025 Fall*

**Deadline: 11 pm, 24 December 2025**

-------
**Table of Contents**:

[[_TOC_]]

-------
## Background
This project is done through teamwork. The contribution of each member will be put in the excel file released with this document. You must write the code alone by yourself, no talking with friends not in your group, no copying from the Internet or other resources (except the code for time mentioned later in the requirements). If a group copies any piece of code from another group, both groups are given 0, no matter whether the copied one knows or not. It is the student’s responsibility to prevent his work from being copied.
Please read the whole document before you start. This project needs the knowledge from the lecture “File”. You can understand the requirements first. After the lecture "File" is finished, you can start programming. 
## System Requirements
> 1. In this project, you are going to develop a software system that can help communication between friends through e-messages. 
> 2. Each user of the system needs to register first and then login to use the system. There are three choices in the “Login” menu at the beginning of the system execution.  
```
    ==================== Login ====================
    1. Login
    2. Register (If you do not have an account)
    3. Exit
    ===============================================
    Choose an option (1-3): 
```
>> The user can input 1-3 to choose which operation to do. If it is the first time that the user uses this system, he must register first. If user chooses 3, the system will quit.
>> The user can choose 2 to register. The system will ask the user to input
>> 1\) account name  
>>> If the account name has not been used by others, the input account name can be used by this user. The user will be required to set up the password then; otherwise, the system gives a warning message. It is assumed that account name has no spaces.
>> 2\) password  
>>> The password should be input twice. The system will check if two passwords are the same.  
>>> a) If two passwords are the same, registration is successful.  
>>> b) If two passwords are different, the system gives a warning message  
>> No matter which message is shown above, the system will then go back to the “Login” menu. 
> 3. The user can choose 1 to login to use the services offered by the system. The following “Main Service” menu will be displayed.
```
    ==================== Main Service ====================
    1. Manage friends
    2. Manage messages
    3. Back
    ======================================================
    Choose an option (1-3): 
```
>> The user inputs an index number as the choice.
### 1\) Manage friends  
> The user can choose this item to manage friends. After this item is chosen, the “Manage friends” menu is displayed. 
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
> The user inputs an index number as the choice. For items 1-4, the system will go back to the current menu after the operations are finished.  
#### Add friends  
> The user can choose this item to add friends by offering their account names. Account names will be input in one line separated by space. For example, if the user wants to add friends whose account names are Andy, Bob, and Tony, he simply inputs Andy Bob Tony and presses the enter key.  
>> a\) If some account names do not exist, show a warning message.  
>> b\) A user cannot add himself/herself as a friend. If so, a warning message is shown.  
>> c\) Handle the existing account names according to the following rules:  
>>> i. For account names that have been in the friend list or “waiting to confirm” list of this user, the system shows the corresponding warning message for these accounts and will do nothing to these account names;  
>>> ii. Otherwise, the user’s account name will be put in reciprocal account’s “waiting to confirm” list (if the user’s account name is not in that list) and show the corresponding message. For example, if John wants to add Andy as a friend, the name “John” will be added to the “waiting to confirm” list of Andy. But if John is already in the “waiting to confirm” list of Andy, a warning message is shown.  
>>> iii. No matter which message is shown, the system will go back to the “Manage friends” menu again.  
#### Accept friends  
> When this item is chosen, all the account names from the user’s “waiting to confirm” list is shown.
```
        1. Account 1
        2. Account 2
        3. Account 3
        ...
        ...
        n-1. All
        n. Back
```
> The value of n in the above menu is determined by the actual number of account names in the waiting list. The user inputs the index numbers to accept people as friends. He can accept multiple accounts at one time. If the user inputs wrong index numbers, those numbers will be ignored. No warning is needed. Give a message to show which account names have been added. Go to upper menu. Once a friend is accepted, both sides will be friends and they can send messages to each other.
#### Delete friends  
> The user can choose this item to delete friends. The system will show a list of all the friends. The user can input the index numbers to delete the friends. He can delete multiple friends or all at one time. If a user deletes a friend, he will also be removed from the friend list of his friend. It is necessary to delete related messages. 
```
        1. Account 1
        2. Account 2
        3. Account 3
        ...
        ...
        n-1. All
        n. Back
```
> The value of n in the above menu is determined by the actual number of account names in the friend list. Once a friend is deleted, the user’s name will be automatically removed from his friend list. If the user inputs wrong index numbers, those numbers will be ignored. No warning message is needed.
#### Show current friends  
> This item will show all the friends in the friend list. 
#### Back  
> This choice will go back to the upper menu. 
### 2\) Manage messages  
> The user can choose this item to manage messages. After this item is chosen, the “Manage messages” menu is displayed. For items 1-3, the system will go back to the current menu after the operations are finished.
```
    ==================== Manage Messages ====================
    1. Send a message
    2. Read messages
    3. Delete messages
    4. Back
    =========================================================
    Choose an option (1-4): 
```
> The user can input an index number as the choice.
#### Send a message  
> When the user wants to send a message to a friend or some friends, the system will show the list of his friends for him to choose from. 
```
        1. Friend 1
        2. Friend 2
        3. Friend 3
        ...
        ...
        n-1. All
        n. Back
```
> The user can send a message to multiple friends or all at one time. The system prompts users to enter the message. It is assumed that the length of a message should not exceed 255 characters. You do not need to check this length in your program.  
> Each account has a file with the account name as the file name. The file name takes .txt as extension name. This file stores the messages from his friends. For example, user Andy has a file called Andy.txt for all the messages he has received.  
> When a message is received, the time and date of the receiving message will be included in the message file as well.
#### Read messages  
> A user can read the message. He can choose to read all messages or read unread messages. That means, once the message is read, the message in the file should be marked in a way to indicate that it has been read. Each message shown to the user should include the information: date and time, sender, message.  
#### Remove messages  
> A user can remove messages within a period. When the user chooses this operation, he must input start date, end date (inclusive) and account name. The date format is dd/mm/year. After this operation is finished, the corresponding message from that account name during that period will be removed from the user’s message file. If the account name is replaced by “all”, then the corresponding message from all friends during that period will be removed.  
#### Back
> This choice will go back to the upper menu.  
### 3\) Back
> This choice will go back to the upper menu.  
## Non-System Requirements
> 1. The messages in a file should be stored in a readable way.  
> 2.The program UI must be user-friendly.  
> 3. The program should be well structured, composed of one main function and some sub-functions.  
##  Hints:
> 1. To get the current day and time, you can use the `tm` structure and `time` functions which are defined in `time.h`. The code below is an example. However, you are not limited to the functions below. You can search on the Internet for the day and time related code. 
```
    #include <stdio.h>
    #include <time.h>
    int main(void)
    {
        struct tm *tblock;
        time_t current_time;
        
        time(&current_time);
        tblock = localtime(&current_time);
        printf("%d %d %d\n",tblock->tm_year, tblock->tm_mon, tblock->tm_mday);
        return 0;
    }
```
The struct `tm` has following members:
```
    struct tm {
        int tm_sec; /* second: [0,59] */
        int tm_min; /* minute: [0,59] */
        int tm_hour; /* hour : [0,23] */
        int tm_mday; /* day in a month: [1,31] */
        int tm_mon; /* month: [0,11] */
        int tm_year; /* year - 1900 */
        int tm_wday; /* weekday: [0,6] */
        int tm_yday; /* day in a year: [0,365] */
        int tm_isdst; /* Daylight Saving Time Identifier */
        long int tm_gmtoff; /* Dateline */
        const char *tm_zone; /*Timezone*/
    };
```
> 2. When you assign the functions for each team member, you should clearly declare the prototype of each function so the functions can be integrated together later. Draw a call relationship diagram to indicate the calling relationships between functions in the program.  
## Submission
> 1. You should submit a compressed file (with the name Group##.zip, where ## is replaced by your group name) that includes the following files.  
>> a) code files: `.c` files and `.h` files (if you declared .h files);   
>> b) three `.zip` files generated according to the instructions in [project25F_sample.md](project25F_sample.md);  
>> c) an excel file [Group_XX.xlsx](Group_XX.xlsx) (replace "XX" by your group name) to indicate each student’s contribution in your group. You do not need to give the exact contribution percentage. Instead, you simply use 2 to indicate “normal”, 1 for “rare”, and 0 for “none”.
> 2. Deadline: 11 pm, 24 December 2025
