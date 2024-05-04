//
// Created by saw_henry_min on 2/17/24.
//

#include "stdio.h"
#include "stdlib.h"
#include "time.h"


#define MAX_LENGTH 30
#define Transaction_File "point_transactions.txt"
#define MAX_Transactions 30


void menu();
void adminLogin();
void adminMenu(int admin_id);
void updateInfo(int admin_id,int update_id);
void suspendUser(int admin_id,int suspend_id);
void deleteUser(int delete_id);
void login();
void registration();
int emailScanner(char to_check_email[MAX_LENGTH]);
void email_valid(char to_valid_email[MAX_LENGTH]);
void copyTwoCharArray(char database[MAX_LENGTH],char reg[MAX_LENGTH]);
void loginChecking(char checkEmail[MAX_LENGTH],char checkPass[MAX_LENGTH]);
void myInfo(int user_id);
void userInfoChange(int user_id);
int compareTwoCharArray(char database[MAX_LENGTH],char log[MAX_LENGTH]);
int checkArraySize(char array[MAX_LENGTH]);
int check_phone(char receiver_ph[]);
int phoneNumberExists(char* phone_number);
void transferPoints(int sender_id, int receiver_id, int points);
void recordTransaction(int sender_id,int receiver_id, int points);
void displayTransaction();
void writeData();
void readData();
void readTransaction();

int isUpperCase(char ch) {
    return (ch >= 'A' && ch <= 'Z');
}

int isLowerCase(char ch) {
    return (ch >= 'a' && ch <= 'z');
}

int isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

int isSpecialChar(char ch) {
    return (ch == '!' || ch == '@' || ch == '#' || ch == '$' || ch == '%' || ch == '^');
}



typedef struct{
    int user_id;
    int points;
    int owner_account;
    int suspended;
    char user_name[MAX_LENGTH];
    char user_email[MAX_LENGTH];
    char user_password[MAX_LENGTH];
    char phone_number[MAX_LENGTH];
    char address[MAX_LENGTH];
    char postal_code[MAX_LENGTH];
}db;

db data[10];

int g_user_login_check = -1;
int g_user_count = 0;
int email_validation = -1;
int transaction_count = 0;

int main(){

    readData();

    menu();

    return 0;
}

void menu(){

    while(1){
        int option = 0;
        printf("\n=== Welcome to Registration Form ===\nChoose your option:\n");
        printf("Press 1 to Admin Login\nPress 2 to User Login\nPress 3 to Register\nPress 4 to Exit\nEnter:");
        scanf("%d", &option);


        if(option == 1){
            adminLogin();
        }
        else if(option == 2){
            login();
        }
        else if(option == 3){
            registration();
        }
        else if(option == 4){
            exit(1);
        }
        else{
            printf("\nWrong option!Exit the program!\n");
            exit(1);
        }

    }
}

void adminLogin() {
    int admin_id;
    char admin_email[MAX_LENGTH];
    char admin_password[MAX_LENGTH];

    printf("\n=== Admin Login ===\n");
    printf("Enter Admin Email: ");
    scanf(" %[^\n]", admin_email);

    printf("Enter Admin Password: ");
    scanf(" %[^\n]", admin_password);

    loginChecking(admin_email, admin_password);

    if (g_user_login_check != -1) {
        int admin_index = -1;  // Variable to store the index of the matching admin

        // Check admin credentials
        if ((compareTwoCharArray(admin_email, "saw@gmail.com\0") == 1 &&
             compareTwoCharArray(admin_password, "Saw123!") == 1) ||
            (compareTwoCharArray(admin_email, "henry@gmail.com\0") == 1 &&
             compareTwoCharArray(admin_password, "Henry123!") == 1) ||
            (compareTwoCharArray(admin_email, "min@gmail.com\0") == 1 &&
             compareTwoCharArray(admin_password, "Min123!") == 1)) {
            admin_index = g_user_login_check;
        }

        if (admin_index != -1) {
            // Admin login successful
            printf("Admin login Successful. Admin ID: %d User name: %s\n\n",
                   data[admin_index].user_id, data[admin_index].user_name);
            admin_id = data[admin_index].user_id;
            adminMenu(admin_id - 1);
        } else {
            // Invalid admin credentials
            printf("Invalid admin credentials\n");
        }
    } else {
        // Admin login failed
        printf("Admin login failed!\n");
    }
}


void login(){
    char l_email[MAX_LENGTH];
    char l_password[MAX_LENGTH];

    printf("\n=== This is Login ===\n");
    printf("Enter your email:");
    scanf(" %[^\n]",l_email);

    printf("Enter your password:");
    scanf(" %[^\n]",l_password);

    loginChecking(l_email,l_password);

    if(g_user_login_check != -1){
        if(!data[g_user_login_check].suspended) {
            printf("Login Successful!\n");
            myInfo(g_user_login_check);
        }
    }else{
        printf("Login Failed!\n");
    }

}

void myInfo(int user_id){
    int m_option = -1;
    printf("Your ID: %d\n",data[user_id].user_id);
    printf("Your user name: %s\n",data[user_id].user_name);
    printf("Your phone number: %s\n",data[user_id].phone_number);
    printf("Your address: %s\n",data[user_id].address);
    printf("Your postal code: %s\n",data[user_id].postal_code);
    printf("Your points: %d (ASM points)\n", data[user_id].points);

    printf("\n=== Choose what you want to do ===\nPress 1 to menu\nPress 2 to change user info\n"
           "Press 3 to transfer points to another user\nPress 4 to display point transaction record\nPress 5 to exit\nEnter:");
    scanf("%d",&m_option);
    if(m_option == 1){
        menu();
    }
    else if(m_option == 2){
        userInfoChange(user_id);
        writeData();
    }
    else if(m_option == 3){
        int receiver_id, points;
        char receiver_ph[MAX_LENGTH];
        printf("Enter receiver phone number of the user:");
        scanf(" %[^\n]", receiver_ph);

        receiver_id = check_phone(receiver_ph);

        if(receiver_id != -1){
            printf("Enter the number of points to transfer:");
            scanf("%d", &points);
            transferPoints(user_id, receiver_id - 1, points);
        }else{
            printf("This phone number is not available in our system!\n\n");
            return;
        }

    }
    else if(m_option == 4){
        displayTransaction();

        printf("Press 1 to go back user information\nPress 2 to exit\nEnter: ");
        scanf("%d",&m_option);

        if(m_option == 1){
            myInfo(user_id);
        }
        else if(m_option == 2){
            exit(1);
        }
    }
    else if(m_option == 5){
        exit(1);
    }
    else{
        printf("\nWrong Option!Exit The program.\n");
        exit(1);
    }
}

int check_phone(char receiver_ph[]){
    for(int i=0; i<g_user_count; i++){
        if(compareTwoCharArray(data[i].phone_number,receiver_ph) == 1){
            return data[i].user_id;
        }
    }
    return -1;
}

void userInfoChange(int user_id){
    int change_option;
    printf("Press 1 to change user name\nPress 2 to change user email\nPress 3 to change password\nPress 4 to change phone number\n");
    printf("Press 5 to change address\nPress 6 to change postal code\nPress 7 to go back user information\nEnter:");
    scanf("%d",&change_option);

    if(change_option == 1){
        char newUserName[MAX_LENGTH];
        printf("\n=== To change user name ===\n");
        printf("This is your user name: %s\n",data[user_id].user_name);
        printf("Enter new user name:");
        scanf(" %[^\n]",newUserName);

        // clear previous name
        for(int i = 0; i < MAX_LENGTH; i++){
            data[user_id].user_name[i] = '\0';
        }

        copyTwoCharArray(data[user_id].user_name,newUserName);
        printf("This is your new user name: %s\n",data[user_id].user_name);

    }
    else if(change_option == 2){
        char newEmail[MAX_LENGTH];
        printf("\n=== To change user email ===\n");
        printf("This is your email: %s\n",data[user_id].user_email);
        printf("Enter new email:");
        scanf(" %[^\n]",newEmail);

        // clear previous email
        for(int i = 0; i < MAX_LENGTH; i++){
            data[user_id].user_email[i] = '\0';
        }

        copyTwoCharArray(data[user_id].user_email,newEmail);
        printf("This is your new email: %s\n",data[user_id].user_email);

    }

    else if(change_option == 3){
        char newPassword[MAX_LENGTH];
        printf("\n=== To change user password ===\n");
        printf("This is your password: %s\n",data[user_id].user_password);
        printf("Enter new password:");
        scanf(" %[^\n]",newPassword);

        // clear previous password
        for(int i = 0; i < MAX_LENGTH; i++){
            data[user_id].user_password[i] = '\0';
        }

        copyTwoCharArray(data[user_id].user_password,newPassword);
        printf("This is your new password: %s\n",data[user_id].user_password);
    }

    else if(change_option == 4){
        char newPhone[MAX_LENGTH];
        printf("\n=== To change user phone number ===\n");
        printf("This is your phone number: %s\n",data[user_id].phone_number);
        printf("Enter new phone number:");
        scanf(" %[^\n]",newPhone);

        // clear previous phone number
        for(int i = 0; i < MAX_LENGTH; i++){
            data[user_id].phone_number[i] = '\0';
        }

        copyTwoCharArray(data[user_id].phone_number,newPhone);
        printf("This is your new phone number: %s\n",data[user_id].phone_number);
    }

    else if(change_option == 5){
        char newAddress[MAX_LENGTH];
        printf("\n=== To change user address ===\n");
        printf("This is your address: %s\n",data[user_id].address);
        printf("Enter new address:");
        scanf(" %[^\n]",newAddress);

        // clear previous address
        for(int i = 0; i < MAX_LENGTH; i++){
            data[user_id].address[i] = '\0';
        }

        copyTwoCharArray(data[user_id].address,newAddress);
        printf("This is your new address: %s\n",data[user_id].address);
    }
    else if(change_option == 6){
        char newPostalCode[MAX_LENGTH];
        printf("\n=== To change user postal code ===\n");
        printf("This is your postal code: %s\n",data[user_id].postal_code);
        printf("Enter new postal code:");
        scanf(" %[^\n]",newPostalCode);

        // clear previous postal code
        for(int i = 0; i < MAX_LENGTH; i++){
            data[user_id].postal_code[i] = '\0';
        }

        copyTwoCharArray(data[user_id].postal_code,newPostalCode);
        printf("This is your new postal code %s\n",data[user_id].postal_code);
    }
    else if(change_option == 7){
        myInfo(user_id);
    }
    else{
        printf("\nWrong Option!Exit The Program!\n");
        exit(1);
    }
}

void loginChecking(char checkEmail[MAX_LENGTH],char checkPass[MAX_LENGTH]){
    g_user_login_check = -1;

    for(int i = 0; i < g_user_count; i++){
        int email_check = compareTwoCharArray(data[i].user_email,checkEmail);

        if(email_check == 1){
            int pass_check = compareTwoCharArray(data[i].user_password,checkPass);
            if(pass_check == 1){
                g_user_login_check = i;

                if(data[g_user_login_check].suspended == 1){
                    printf("Sorry!You are suspended by admin.Operation not allowed.\n");
                    g_user_login_check = -1; // Reset login check
                }
                break;
            }
        }
    }
}

int compareTwoCharArray(char database[MAX_LENGTH],char log[MAX_LENGTH]){
    int size1 = checkArraySize(database);
    int size2 = checkArraySize(log);
    int sameCount = 0;

    if(size1 == size2){
        for(int i = 0; i < size1; i++){
            if(database[i] == log[i]){
                sameCount++;
            }
        }
    }
    if(size1 == sameCount){
        return 1;
    } else{
        return 0;
    }

}

int checkArraySize(char array[MAX_LENGTH]){
    int size = 0;
    for(int i = 0;i < MAX_LENGTH; i++){
        if(array[i] == '\0'){
            break;
        }
        size++;
    }
    return size;
}



void registration(){
    char r_userName[MAX_LENGTH];
    char r_userEmail[MAX_LENGTH];
    char r_userPassword[MAX_LENGTH];
    char r_userPhoneNumber[MAX_LENGTH];
    char r_userAddress[MAX_LENGTH];
    char r_postalCode[MAX_LENGTH];

    if(g_user_count >= 10){
        printf("Warning: Maximum user count reached!You can not register.\n");
        return;
    }

    printf("\n=== This is Register ===\n");

    printf("Enter user name to Register:");
    scanf(" %[^\n]",r_userName);
    int email_exist = -1;

    while(email_exist == -1){
        printf("Enter email to Register:");
        scanf(" %[^\n]",r_userEmail);

        email_exist = emailScanner(r_userEmail);
        if(email_exist == -1){
            printf("Your email => %s <= is already register!\n",r_userEmail);
            printf("Enter new email!\n");
        }
    }

    while (email_validation == -1) {

        email_valid(r_userEmail);

        if (email_validation == -1) {
            printf("Email is not valid:\n");
            printf("Enter your email again:");
            scanf(" %[^\n]", r_userEmail);
        } else {
            break;
        }
    }

    // Reset email_validation before each attempt
    email_validation = -1;


    // Get and validate password
    int valid_password = 0;
    while (!valid_password) {
        printf("Enter password to Register (at least 6 characters with uppercase, lowercase, number, and special character):");
        scanf(" %[^\n]", r_userPassword);

        // Check password strength
        int len = 0, has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
        while (r_userPassword[len] != '\0') {
            if (isUpperCase(r_userPassword[len])) {
                has_upper = 1;
            } else if (isLowerCase(r_userPassword[len])) {
                has_lower = 1;
            } else if (isDigit(r_userPassword[len])) {
                has_digit = 1;
            } else if (isSpecialChar(r_userPassword[len])) {
                has_special = 1;
            }
            len++;
        }

        if (len >= 6 && has_upper && has_lower && has_digit && has_special) {
            valid_password = 1;
        } else {
            printf("Invalid password! Please ensure it meets the criteria.\n");
        }
    }


    // Phone validation
    int phone_exists = -1;
    while(phone_exists == -1){
        printf("Enter phone number to Register:");
        scanf(" %[^\n]",r_userPhoneNumber);

        phone_exists = phoneNumberExists(r_userPhoneNumber);
        if(phone_exists == -1){
            printf("Your phone number => %s <= is already register!\n",r_userPhoneNumber);
            printf("Enter new phone number!\n");
        }
    }


    printf("Enter address to Register:");
    scanf(" %[^\n]",r_userAddress);

    printf("Enter postal code to Register:");
    scanf(" %[^\n]",r_postalCode);

    data[g_user_count].user_id = g_user_count + 1;

    printf("\nID: %d",data[g_user_count].user_id);

    copyTwoCharArray(data[g_user_count].user_name,r_userName);
    printf("\nChecking for user name: %s",data[g_user_count].user_name);

    copyTwoCharArray(data[g_user_count].user_email,r_userEmail);
    printf("\nChecking for email: %s",data[g_user_count].user_email);

    copyTwoCharArray(data[g_user_count].user_password,r_userPassword);
    printf("\nChecking for password: %s",data[g_user_count].user_password);

    copyTwoCharArray(data[g_user_count].phone_number,r_userPhoneNumber);
    printf("\nChecking for phone number: %s",data[g_user_count].phone_number);

    copyTwoCharArray(data[g_user_count].address,r_userAddress);
    printf("\nChecking for address: %s",data[g_user_count].address);

    copyTwoCharArray(data[g_user_count].postal_code,r_postalCode);
    printf("\nChecking for postal code: %s",data[g_user_count].postal_code);

    // Initialize user points to 1000 for the registered user
    data[g_user_count].points = 1000;

    printf("\nChecking for points: %d (ASM points)\n", data[g_user_count].points);

    g_user_count++;

    writeData();

}

void copyTwoCharArray(char database[MAX_LENGTH],char reg[MAX_LENGTH]){
    int i;
    for(i = 0; i < MAX_LENGTH; i++){
        if(reg[i] == '\0'){
            break;
        }
        else{
            database[i] = reg[i];
        }
    }
}

int phoneNumberExists(char* phone_number){
    int phone_exists;
    if(g_user_count == 0){
        return 1;
    }else{
        for(int i = 0;i < g_user_count;i++){
            phone_exists = compareTwoCharArray(data[i].phone_number,phone_number);
            if(phone_exists == 1){
                return -1;
            }
        }
    }
    return 1;
}

int emailScanner(char to_check_email[MAX_LENGTH]){
    int email_exist_or_not;
    if(g_user_count == 0){
        return 1;
    }else{
        for(int i = 0;i < g_user_count;i++){
            email_exist_or_not = compareTwoCharArray(data[i].user_email,to_check_email);
            if(email_exist_or_not == 1){
                return -1;
            }
        }
    }
    return 1;
}


void email_valid(char to_valid_email[MAX_LENGTH]) {
    // Define valid email domains
    char* valid_domains[] = {"@gmail.com", "@yahoo.com", "@outlook.com", "@apple.com", "@iCloud.com", "@GMX.com", "@zahomail.com", "@n1c.com"};
    int num_valid_domains = 8;  // the number of valid domains


    // Check the first part of the email
    int first_count = 0;
    int i;
    for (i = 0; to_valid_email[i] != '@'; ++i) {
        if ((to_valid_email[i] >= '0' && to_valid_email[i] <= '9') || (to_valid_email[i] >= 'a' && to_valid_email[i] <= 'z')) {
            first_count++;
        } else {
            email_validation = -1;
            return;
        }
    }

    // Check if the first part is not empty and doesn't match the full email length
    if (first_count == 0 || first_count == checkArraySize(to_valid_email) || first_count > 64) {
        email_validation = -1;
        return;
    }

    // Extract the second part of the email
    char second_part[MAX_LENGTH];
    int j = 0;
    for (; to_valid_email[i] != '\0'; ++i, ++j) {
        second_part[j] = to_valid_email[i];
    }
    second_part[j] = '\0';

    // Check the second part of the email
    int valid_domain_found = 0;
    for (int k = 0; k < num_valid_domains; ++k) {
        int match = compareTwoCharArray(second_part, valid_domains[k]);
        if (match) {
            valid_domain_found = 1;
            break;
        }
    }

    // Set the email validation result
    email_validation = valid_domain_found ? 1 : -1;

}


void transferPoints(int sender_id, int receiver_id, int points) {
    if (sender_id >= 0 && sender_id < g_user_count && receiver_id >= 0 && receiver_id < g_user_count) {

        // Check if the receiver is suspended
        if(data[receiver_id].suspended){
            printf("Points transfer to suspended user is not allowed!\n\n");
            return myInfo(sender_id);
        }

        // Calculate transaction charge (10%)
        int transactionCharge = (points * 10) / 100;

        // Deduct points and transaction charge from sender
        if (data[sender_id].points >= (points + transactionCharge)) {
            data[sender_id].points -= (points + transactionCharge);
            data[receiver_id].points += points;

            // Addition transaction charge to owner account
            data[0].owner_account += transactionCharge;

            writeData();

            recordTransaction(sender_id,receiver_id,points);

            printf("Points transferred successfully!\n\n");

            printf("Sender - %s is transferring %d points to %s\n",data[sender_id].user_name,
                   points,data[receiver_id].user_name);

            printf("Receiver - %s received %d points from %s\n\n",data[receiver_id].user_name,
                   points,data[sender_id].user_name);

            // Display transaction charge information
            printf("Transaction charge (10%%): %d points\n\n",transactionCharge);

            int p_option;
            printf("Press 1 to go back user information\nPress 2 to exit\nEnter:");
            scanf("%d",&p_option);
            if(p_option == 1){
                myInfo(sender_id);
            }
            else if(p_option == 2){
                exit(1);
            }

        } else {
            printf("Insufficient points to transfer!\n\n");
            return myInfo(sender_id);
        }
    } else {
        printf("Invalid user IDs!\n");
    }
}

void recordTransaction(int sender_id,int receiver_id, int points){

    readTransaction();

    FILE *transactionFile = fopen(Transaction_File,"a");

    if(transactionFile == NULL){
        perror("Error opening transaction file!");
        return;
    }

    // Get current time
    time_t rawTime;
    struct tm *timeInfo;
    time(&rawTime);
    timeInfo = localtime(&rawTime);

    // Format the time string
    char timeStr[50];
    strftime(timeStr,sizeof(timeStr),"%Y-%m-%d %H:%M:%S",timeInfo);

    fprintf(transactionFile,"Transaction time: %s\n",timeStr);
    fprintf(transactionFile,"Sender ID: %d -  %s is transferring %d points to %s\n",
            data[sender_id].user_id,data[sender_id].user_name,points,data[receiver_id].user_name);
    fprintf(transactionFile,"Receiver ID: %d - %s received %d points from %s\n",
            data[receiver_id].user_id,data[receiver_id].user_name,points,data[sender_id].user_name);
    fprintf(transactionFile,"Owner points: %d points\n\n",data[0].owner_account);

    transaction_count++;

    if(transaction_count == MAX_Transactions){
        printf("Transaction record limit reached!\nNext transaction will be recorded from beginning.\n\n");
    }

    if(transaction_count > MAX_Transactions){
        printf("Clearing recorded transactions...\nStart recording from beginning.\n\n");
        transaction_count = 0;

        // Clear the contents of the transaction file
        fclose(transactionFile);
        transactionFile = fopen(Transaction_File,"w");
        fprintf(transactionFile,"Transaction time: %s\n",timeStr);
        fprintf(transactionFile,"Sender ID: %d -  %s is transferring %d points to %s\n",
                data[sender_id].user_id,data[sender_id].user_name,points,data[receiver_id].user_name);
        fprintf(transactionFile,"Receiver ID: %d - %s received %d points from %s\n",
                data[receiver_id].user_id,data[receiver_id].user_name,points,data[sender_id].user_name);
        fprintf(transactionFile,"Owner points: %d points\n\n",data[0].owner_account);
        fclose(transactionFile);
        return;
    }

    fclose(transactionFile);

}

void readTransaction() {
    FILE *readFile = fopen(Transaction_File, "r");

    if (readFile == NULL) {
        perror("Error opening transaction file for reading!");
        return;
    }

    transaction_count = 0;

    // Set the cursor to the beginning of the file
    fseek(readFile, 0, SEEK_SET);

    while (fscanf(readFile, "Transaction time: %*[^\n]\n"
                            "Sender ID: %*d - %*s is transferring %*d points to %*s\n"
                            "Receiver ID: %*d - %*s received %*d points from %*s\n"
                            "Owner points: %*d points\n\n") != EOF) {
        transaction_count++;
    }

    fclose(readFile);
}


void displayTransaction(){

    FILE *transactionFile = fopen(Transaction_File,"r");


    if(transactionFile == NULL){
        printf("\nNo transactions recorded yet!\n\n");
        return;
    }

    char transaction[1000];

    printf("\n=== Point Transactions ===\n");

    while (fgets(transaction,sizeof(transaction),transactionFile) != NULL){
        printf("%s",transaction);
    }

    fclose(transactionFile);

}

void readData(){
    FILE *fptr = fopen("database.txt","r");

    if(!fptr){
        perror("read data!");
        return;
    }

    printf("Reading Data...\n");

    g_user_count = 0;

    while(fscanf(fptr,"ID = %d, Username = %[^,], Email = %[^,], Password = %[^,], Phone = %[^,], Address = %[^,], Postal Code = %[^,], Points = %d, Suspended = %d\n",&data[g_user_count].user_id,data[g_user_count].user_name,data[g_user_count].user_email,
                 data[g_user_count].user_password,data[g_user_count].phone_number,data[g_user_count].address,data[g_user_count].postal_code,
                 &data[g_user_count].points,&data[g_user_count].suspended) == 9){

        g_user_count++;
        if(g_user_count >= 10){
            printf("Warning: Maximum user count reached!\n");
            printf("Overwriting and updating database...\n");
            writeData();
            break;
        }
    }

    printf("Success! Loaded %d user(s).\n",g_user_count);
    fclose(fptr);

}

void writeData(){
    FILE *fptr = fopen("database.txt","w");

    if(!fptr){
        perror("write data!");
        return;
    }

    printf("Recording User Data...\n");


    for(int i = 0; i < g_user_count; i++){
        fprintf(fptr,"ID = %d, Username = %s, Email = %s, Password = %s, Phone = %s, Address = %s, Postal Code = %s, Points = %d, Suspended = %d\n",
                data[i].user_id,data[i].user_name,data[i].user_email,data[i].user_password,data[i].phone_number,
                data[i].address, data[i].postal_code,data[i].points,data[i].suspended);
    }

    printf("Success!\n\n");
    fclose(fptr);
}


void adminMenu(int admin_id){
    while(1){
        int admin_option;
        int update_id;
        int suspend_id;
        int delete_id;
        printf("Press 1 to go my information\n");
        printf("Press 2 to update user information\n");
        printf("Press 3 to suspend/un-suspend user\n");
        printf("Press 4 to delete user\n");
        printf("Press 5 to logout\n");
        printf("Enter: ");
        scanf("%d",&admin_option);


        switch(admin_option){

            case 1:
                myInfo(admin_id);
                break;
            case 2:
                printf("Enter user ID to update:");
                scanf("%d",&update_id);
                updateInfo(admin_id,update_id - 1);
                writeData();
                break;
            case 3:
                printf("Enter user ID to suspend/un-suspend:");
                scanf("%d",&suspend_id);
                suspendUser(admin_id,suspend_id -1 );
                break;
            case 4:
                printf("Enter user ID to delete:");
                scanf("%d",&delete_id);
                deleteUser(delete_id -1 );
                break;
            case 5:
                printf("Admin logout Successfully!\n");
                return;
            default:
                printf("Wrong option!Please try again.\n\n");
        }
    }
}

void updateInfo(int admin_id,int update_id){

    int update_option;
    printf("Press 1 to update user name\nPress 2 to update user email\nPress 3 to update password\n");
    printf("Press 4 to update phone number\nPress 5 to update address\nPress 6 to update postal code\n");
    printf("Press 7 to go back admin menu\nEnter:");
    scanf("%d",&update_option);

    if(update_option == 1){
        char newUserName[MAX_LENGTH];
        printf("\n=== To update user name ===\n");
        printf("This is old user name: %s\n",data[update_id].user_name);
        printf("Enter update user name:");
        scanf(" %[^\n]",newUserName);

        // clear previous name
        for(int i = 0; i < MAX_LENGTH; i++){
            data[update_id].user_name[i] = '\0';
        }

        copyTwoCharArray(data[update_id].user_name,newUserName);
        printf("This is update user name: %s\n",data[update_id].user_name);
    }

    else if(update_option == 2){
        char newEmail[MAX_LENGTH];
        printf("\n=== To update user email ===\n");
        printf("This is old user email: %s\n",data[update_id].user_email);
        printf("Enter update user email:");
        scanf(" %[^\n]",newEmail);

        // clear previous email
        for(int i = 0;i < MAX_LENGTH; i++){
            data[update_id].user_email[i] = '\0';
        }

        copyTwoCharArray(data[update_id].user_email,newEmail);
        printf("This is update user email: %s\n",data[update_id].user_email);
    }

    else if(update_option == 3){
        char newPassword[MAX_LENGTH];
        printf("\n=== To update user password  ===\n");
        printf("This is old password: %s\n",data[update_id].user_password);
        printf("Enter update password:");
        scanf(" %[^\n]",newPassword);

        // clear previous email
        for(int i = 0;i < MAX_LENGTH; i++){
            data[update_id].user_password[i] = '\0';
        }

        copyTwoCharArray(data[update_id].user_password,newPassword);
        printf("This is update user password: %s\n",data[update_id].user_password);
    }

    else if(update_option == 4){
        char newPhone[MAX_LENGTH];
        printf("\n=== To update user phone number ===\n");
        printf("This is old phone number: %s\n",data[update_id].phone_number);
        printf("Enter update phone number:");
        scanf(" %[^\n]",newPhone);

        // clear previous phone number
        for(int i = 0;i < MAX_LENGTH; i++){
            data[update_id].phone_number[i] = '\0';
        }

        copyTwoCharArray(data[update_id].phone_number,newPhone);
        printf("This is update phone number: %s\n",data[update_id].phone_number);
    }

    else if(update_option == 5){
        char newAddress[MAX_LENGTH];
        printf("\n=== To update user address ===\n");
        printf("This is old address: %s\n",data[update_id].address);
        printf("Enter update address:");
        scanf(" %[^\n]",newAddress);

        // clear previous address
        for(int i = 0;i < MAX_LENGTH; i++){
            data[update_id].address[i] = '\0';
        }

        copyTwoCharArray(data[update_id].address,newAddress);
        printf("This is update user address: %s\n",data[update_id].address);
    }

    else if(update_option == 6){
        char newPostal[MAX_LENGTH];
        printf("\n=== To update postal code ===\n");
        printf("This is old postal code: %s\n",data[update_id].postal_code);
        printf("Enter update postal code:");
        scanf(" %[^\n]",newPostal);

        // clear previous postal code
        for(int i = 0;i < MAX_LENGTH; i++){
            data[update_id].postal_code[i] = '\0';
        }

        copyTwoCharArray(data[update_id].postal_code,newPostal);
        printf("This is update postal code: %s\n",data[update_id].postal_code);
    }

    else if(update_option == 7){
        adminMenu(admin_id);
    }
    else{
        printf("\nWrong option!Exit the program.\n");
    }
}

void suspendUser(int admin_id,int suspend_id){
    if (suspend_id >= 0 && suspend_id < g_user_count){
        if (suspend_id < 3){
            printf("You can not suspend admin!\n\n");
            return;
        }
        data[suspend_id].suspended = !data[suspend_id].suspended;
        printf("User ID %d has been %s by Admin ID %d.\n",data[suspend_id].user_id,
               data[suspend_id].suspended ? "suspended" : "un-suspended",data[admin_id].user_id);
        writeData();
    }else{
        printf("Invalid user ID!\n\n");
    }
}

void deleteUser(int delete_id){
    if(delete_id >= 0 && delete_id < g_user_count){

        if(delete_id < 3){
            printf("You can not delete admin!\n\n");
            return;
        }
        else {
            printf("Deleting User ID %d...\n", data[delete_id].user_id);


            for (int i = delete_id; i < g_user_count - 1; i++) {
                data[i] = data[i + 1]; //next user data overwrite to deleted user data
                data[i].user_id -= 1; //if admin delete ID 4,ID 5 will become ID 4
            }

            g_user_count--;

            printf("User deleted successfully!\n");

            writeData();
        }
    }
    else{
        printf("Invalid User ID!\n\n");
    }
}
