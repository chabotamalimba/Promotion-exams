#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Global variables */
char username[50];
char receiver[50];
float balance = 0.0f;
unsigned int passwordHash;

/* Remove newline from fgets input */
void removeNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

/* Simple password hash (educational) */
unsigned int hashPassword(const char *pass) {
    unsigned int hash = 0;
    while (*pass) {
        hash = hash * 31 + *pass;
        pass++;
    }
    return hash;
}

/* Safe float input */
int readAmount(float *amount) {
    char buffer[50];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return 0;
    return sscanf(buffer, "%f", amount) == 1;
}

/* Registration */
void registerUser() {
    char password[20];

    printf("\n--- User Registration ---\n");

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    removeNewline(username);

    printf("Create password: ");
    fgets(password, sizeof(password), stdin);
    removeNewline(password);

    passwordHash = hashPassword(password);
    printf("Registration successful!\n");
}

/* Login */
int login() {
    char user[50];
    char pass[20];

    printf("\n--- Login ---\n");

    printf("Username: ");
    fgets(user, sizeof(user), stdin);
    removeNewline(user);

    printf("Password: ");
    fgets(pass, sizeof(pass), stdin);
    removeNewline(pass);

    if (strcmp(user, username) == 0 &&
        hashPassword(pass) == passwordHash) {
        printf("Login successful!\n");
        return 1;
    }

    printf("Invalid login details!\n");
    return 0;
}

/* Deposit */
void deposit() {
    float amount;

    printf("\n--- Fund Deposit ---\n");
    printf("Enter amount: ");

    if (!readAmount(&amount) || amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    balance += amount;
    printf("Deposit successful!\n");
}

/* Withdraw */
void withdraw() {
    float amount;

    printf("\n--- Fund Withdrawal ---\n");
    printf("Enter amount: ");

    if (!readAmount(&amount) || amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    if (amount > balance) {
        printf("Insufficient balance!\n");
        return;
    }

    balance -= amount;
    printf("Withdrawal successful!\n");
}

/* Transfer */
void transfer() {
    float amount;

    printf("\n--- Online Fund Transfer ---\n");

    printf("Enter receiver username: ");
    fgets(receiver, sizeof(receiver), stdin);
    removeNewline(receiver);

    printf("Enter amount: ");
    if (!readAmount(&amount) || amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    if (amount > balance) {
        printf("Insufficient balance!\n");
        return;
    }

    balance -= amount;
    printf("Successfully transferred K %.2f to %s\n", amount, receiver);
}

/* Change password */
void changePassword() {
    char oldPass[20];
    char newPass[20];

    printf("\n--- Change Password ---\n");

    printf("Enter old password: ");
    fgets(oldPass, sizeof(oldPass), stdin);
    removeNewline(oldPass);

    if (hashPassword(oldPass) != passwordHash) {
        printf("Incorrect old password!\n");
        return;
    }

    printf("Enter new password: ");
    fgets(newPass, sizeof(newPass), stdin);
    removeNewline(newPass);

    passwordHash = hashPassword(newPass);
    printf("Password changed successfully!\n");
}

/* Check balance */
void checkBalance() {
    printf("\n--- Account Balance ---\n");
    printf("Balance: K %.2f\n", balance);
}

/* Main */
int main() {
    int choice;
    char buffer[10];

    registerUser();

    if (!login()) {
        return 0;
    }

    do {
        printf("\n============================\n");
        printf(" ONLINE BANKING SYSTEM MENU\n");
        printf("============================\n");
        printf("1. Deposit Funds\n");
        printf("2. Withdraw Funds\n");
        printf("3. Online Fund Transfer\n");
        printf("4. Change Password\n");
        printf("5. Check Balance\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        fgets(buffer, sizeof(buffer), stdin);
        choice = atoi(buffer);

        switch (choice) {
            case 1:
                deposit();
                break;
            case 2:
                withdraw();
                break;
            case 3:
                transfer();
                break;
            case 4:
                changePassword();
                break;
            case 5:
                checkBalance();
                break;
            case 6:
                printf("Thank you for using online banking.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}