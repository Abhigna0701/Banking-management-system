#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
typedef struct Account
{
    char accountName[40];
    char accountNumber[20];
    char DateOfBirth[15];
    char address[50];
    char contactNum[15];
    float accountBalance;
} Account;
void createAccount();
void displayAllAccount();
void updateAccount();
void deleteAccount();
void searchAccount();
void transaction();
int main(){
    char option;
    while (option != '0'){
        system("cls");
        printf("\n\n\n");
        printf("\t\t\t====== Welcome To A Cube Bank  ======\n");
        printf("\n\t\t\t1. Create Account");
        printf("\n\t\t\t2. Display All Accounts Information");
        printf("\n\t\t\t3. Update Account Information");
        printf("\n\t\t\t4. Delete Account Information");
        printf("\n\t\t\t5. Search Account Information");
        printf("\n\t\t\t6. Transaction");
        printf("\n\t\t\t0. Exit");
        printf("\n\n\n\t\t\tEnter Your Option: ");
        scanf(" %c", &option);

        switch (option)
        {
        case '1':
            createAccount();
            break;
        case '2':
            displayAllAccount();
            break;
        case '3':
            updateAccount();
            break;
        case '4':
            deleteAccount();
            break;
        case '5':
            searchAccount();
            break;
        case '6':
            transaction();
            break;
        case '0':
            printf("\n\t\t\t====== Thank You for using A Cube Bank ===========\n");
            exit(0);
        default:
            printf("\n\t\t\tInvalid Option, Please Enter Right Option !\n");
        }
    }
}

void createAccount(){
    FILE *fileOne = fopen("accountInfo.bin", "ab+");

    if (fileOne == NULL){
        printf("\n\t\t\tError !\n");
    }

    Account accountInformation;
    system("cls");

    printf("\t\t\t====== Create Student Account ======\n");

    printf("\n\t\t\tEnter Account's Name : ");
    getchar();
    gets(accountInformation.accountName);
    printf("\t\t\tEnter Account's Number : ");
    gets(accountInformation.accountNumber);
    printf("\t\t\tEnter Account Holder's Date of birth : ");
    gets(accountInformation.DateOfBirth);
    printf("\t\t\tEnter Account Holder's Address : ");
    gets(accountInformation.address);
    printf("\t\t\tEnter Account Holder's Contact Number : ");
    gets(accountInformation.contactNum);
    printf("\t\t\tEnter Current Account Balance : $  ");
    scanf("%f", &accountInformation.accountBalance);

    fwrite(&accountInformation, sizeof(accountInformation), 1, fileOne);

    printf("\n\n\t\t\tAccount has been opened sucessfully\n");
    printf("\n\n\t\t\tEnter any keys to continue.......");
    getch();

    fclose(fileOne);
}

void displayAllAccount(){
    FILE *fileOne = fopen("accountInfo.bin", "rb");

    if (fileOne == NULL){
        printf("\n\t\t\tError !\n");
    }

    Account accountInformation;
    system("cls");
    printf("\t\t\t====== Display All Account's Information ======\n\n");
    while (fread(&accountInformation, sizeof(accountInformation), 1, fileOne) == 1){
        printf("\t\t\tAccount Name : %s\n\t\t\tAccount Number : %s\n\t\t\tDate of Birth : %s\n\t\t\tAddress : %s\n\t\t\tContact Number : %s\n\t\t\tCurrent Account's Balance : %.2f\n", accountInformation.accountName, accountInformation.accountNumber, accountInformation.DateOfBirth, accountInformation.address, accountInformation.contactNum, accountInformation.accountBalance);
        printf("\t\t\t---------------------------------------------------\n");
    }

    fclose(fileOne);
    printf("\n\n\t\t\tEnter any keys to continue.......");
    getch();
}

void updateAccount(){
    FILE *fileOne = fopen("accountInfo.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");

    Account accountInformation, tempInformation;

    int choice, flag = 0;

    if (fileOne == NULL || temp == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    system("cls");

    printf("\t\t\t\t====== Update Account Information ======\n");

    printf("\n\t\t\tEnter Account Number : ");
    getchar();
    gets(tempInformation.accountNumber);

    while (fread(&accountInformation, sizeof(accountInformation), 1, fileOne) == 1)
    {
        if (strcmp(accountInformation.accountNumber, tempInformation.accountNumber) == 0)
        {
            flag++;
            printf("\n\t\t\tChoose your option :\n\t\t\t1.Update Account Name\n\t\t\t2.Update Date of Birth.\n\t\t\t3.Update Address\n\t\t\t4.Update Contact No.");
            printf("\n\n\t\t\tEnter Your Option : ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("\n\t\t\tEnter Account's Name to Update: ");
                getchar();
                gets(tempInformation.accountName);
                strcpy(accountInformation.accountName, tempInformation.accountName);

                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 2)
            {
                printf("\n\t\t\tEnter Date of Birth to Update: ");
                getchar();
                gets(tempInformation.DateOfBirth);
                strcpy(accountInformation.DateOfBirth, tempInformation.DateOfBirth);

                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 3)
            {
                printf("\n\t\t\tEnter Address to Update: ");
                getchar();
                gets(tempInformation.address);
                strcpy(accountInformation.address, tempInformation.address);

                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 4)
            {
                printf("\n\t\t\tEnter Contact No. to Update: ");
                getchar();
                gets(tempInformation.contactNum);
                strcpy(accountInformation.contactNum, tempInformation.contactNum);

                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else
            {
                printf("\n\t\t\tInvalid Option.");
                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
            }
        }
        else
        {
            fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
        }
    }

    fclose(fileOne);
    fclose(temp);

    remove("accountInfo.bin");
    rename("temp.bin", "accountInfo.bin");

    if (flag == 0)
    {
        printf("\n\t\t\tAccount is not found");
    }

    printf("\n\n\t\t\tEnter any keys to continue.......");
    getch();
}

void deleteAccount()
{
    FILE *fileOne = fopen("accountInfo.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");

    Account accountInformation, tempInformation;

    int choice, flag = 0;

    if (fileOne == NULL || temp == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    system("cls");

    printf("\t\t\t\t====== Delete Account Information ======\n");

    printf("\n\t\t\tEnter Account Number : ");
    getchar();
    gets(tempInformation.accountNumber);

    while (fread(&accountInformation, sizeof(accountInformation), 1, fileOne) == 1)
    {
        if (strcmp(accountInformation.accountNumber, tempInformation.accountNumber) == 0)
        {
            flag++;
            printf("\n\t\t\tAre you sure to delete ??\n\t\t\t\t1.Yes\n\t\t\t\t2.Back\n\t\t\t\tEnter Your Option : ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("\n\n\t\t\tInformation has been deleted successfully!\n\n");
            }
            else if (choice == 2)
            {
                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
            }
            else
            {
                printf("\n\t\t\tInvalid Option");
                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
            }
        }
        else
        {
            fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
        }
    }

    fclose(fileOne);
    fclose(temp);

    remove("accountInfo.bin");
    rename("temp.bin", "accountInfo.bin");

    if (flag == 0)
    {
        printf("\n\t\t\tAccount is not found");
    }

    printf("\n\n\t\t\tEnter any keys to continue.......");
    getch();
}

void searchAccount()
{
    FILE *fileOne = fopen("accountInfo.bin", "rb");

    Account accountInformation;

    int choice, flag = 0;
    char searchAccountNumber[20], searchName[50];

    if (fileOne == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    system("cls");

    printf("\t\t\t\t====== Search Account Information ======\n");

    printf("\n\t\t\tChoose your option :\n\t\t\t1.Search by Account Number\n\t\t\t2.Search by Account's Name");
    printf("\n\n\t\t\tEnter Your Option : ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        system("cls");
        printf("\t\t\t\t====== Search Account Information ======\n");
        printf("\n\n\t\t\tEnter Account Number : ");
        getchar();
        gets(searchAccountNumber);
        while (fread(&accountInformation, sizeof(accountInformation), 1, fileOne) == 1)
        {
            if (strcmp(accountInformation.accountNumber, searchAccountNumber) == 0)
            {
                flag++;
                printf("\n\t\t\tAccount Name : %s\n\t\t\tAccount Number : %s\n\t\t\tDate of Birth : %s\n\t\t\tAddress : %s\n\t\t\tContact Number : %s\n\t\t\tCurrent Account's Balance : %.2f\n", accountInformation.accountName, accountInformation.accountNumber, accountInformation.DateOfBirth, accountInformation.address, accountInformation.contactNum, accountInformation.accountBalance);
            }
        }
        if (flag == 0)
        {
            printf("\n\t\t\tAccount is not found");
        }
    }
    else if (choice == 2)
    {
        system("cls");
        printf("\t\t\t\t====== Search Account Information ======\n");
        printf("\n\n\t\t\tEnter Account Name : ");
        getchar();
        gets(searchName);
        while (fread(&accountInformation, sizeof(accountInformation), 1, fileOne) == 1)
        {
            if (stricmp(accountInformation.accountName, searchName) == 0)
            {
                flag++;
                printf("\n\t\t\tAccount Name : %s\n\t\t\tAccount Number : %s\n\t\t\tDate of Birth : %s\n\t\t\tAddress : %s\n\t\t\tContact Number : %s\n\t\t\tCurrent Account's Balance : %.2f\n", accountInformation.accountName, accountInformation.accountNumber, accountInformation.DateOfBirth, accountInformation.address, accountInformation.contactNum, accountInformation.accountBalance);
                printf("\t\t\t---------------------------------------------------\n");
            }
        }
        if (flag == 0)
        {
            printf("\n\t\t\tAccount is not found");
        }
    }
    else
    {
        printf("\n\t\t\tInvalid Option");
    }

    fclose(fileOne);

    printf("\n\n\n\t\t\tEnter any keys to continue.......");
    getch();
}

void transaction()
{
    FILE *fileOne = fopen("accountInfo.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");

    Account accountInformation, tempInformation;

    int op, flag = 0;

    if (fileOne == NULL || temp == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    system("cls");

    printf("\t\t\t\t====== Account Transaction ======\n");

    printf("\n\t\t\tEnter Account Number : ");
    getchar();
    gets(tempInformation.accountNumber);

    while (fread(&accountInformation, sizeof(accountInformation), 1, fileOne) == 1)
    {
        if (strcmp(accountInformation.accountNumber, tempInformation.accountNumber) == 0)
        {
            flag++;
            printf("\n\n\t\t\tDo you want to\n\t\t\t1.Deposit\n\t\t\t2.Withdraw\n\n\t\t\tEnter your choice:");
            scanf("%d", &op);
            if (op == 1)
            {
                printf("\n\t\t\tCurrent Balance:$ %.2f", accountInformation.accountBalance);
                printf("\n\t\t\tEnter the amount you want to deposit:$ ");
                scanf("%f", &tempInformation.accountBalance);
                accountInformation.accountBalance += tempInformation.accountBalance;
                printf("\n\t\t\tCurrent Balance after Deposit:$ %.2f", accountInformation.accountBalance);

                fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                printf("\n\n\t\t\tDeposited successfully!\n\n");
            }
            else
            {
                printf("\n\t\t\tCurrent Balance:$ %.2f", accountInformation.accountBalance);
                printf("\n\t\t\tEnter the amount you want to withdraw:$ ");
                scanf("%f", &tempInformation.accountBalance);
                if (accountInformation.accountBalance < tempInformation.accountBalance)
                {
                    printf("\n\n\t\t\tInsufficient Balance!\n\n");
                    fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                }
                else
                {
                    accountInformation.accountBalance -= tempInformation.accountBalance;
                    printf("\n\t\t\tCurrent Balance after Withdraw:$ %.2f", accountInformation.accountBalance);

                    fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
                    printf("\n\n\t\t\tWithdraw successfully!\n\n");
                }
            }
        }
        else
        {
            fwrite(&accountInformation, sizeof(accountInformation), 1, temp);
        }
    }

    if (flag == 0)
    {
        printf("\n\t\t\tAccount is not found");
    }

    fclose(fileOne);
    fclose(temp);

    remove("accountInfo.bin");
    rename("temp.bin", "accountInfo.bin");

    printf("\n\n\t\t\tEnter any keys to continue.......");
    getch();
}
