#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Get medical data
void getMedicalData()
{
    float weight;
    float height;
    float rbs;
    int BPU;
    int BPL;
    printf("Enter the weight in Kg: ");
    scanf("%f", &weight);
    printf("Enter the height in cm:");
    scanf("%f", &height);
    printf("Enter your random blood sugar level: ");
    scanf("%f", &rbs);
}
// User handling
int validation()
{
    int selectedItem;
    FILE *users = fopen("users.bin", "ab+");
    printf("1-Login\n");
    printf("2-Register\n");
    printf("Please enter your selection: ");
    scanf("%d", &selectedItem);
    switch (selectedItem)
    {
    case 1:
        char enteredRefNo[500];
        printf("\nWelcome to -------\n\n");
        printf("Please enter your reference no: ");
        scanf("%s", &enteredRefNo);
        char readVal[500];
        while (fscanf(users, "%s %*s %*s %*s %*s %*s", readVal) == 1)
        {
            if (strcmp(readVal, enteredRefNo) == 0)
            {
                return 1;
            }
        }
        break;
    case 2:
        char isRegistrationDataCorrect[10] = "N";
        char yes[10] = "Y";
        int result = 1;
        char name[100], dob[100], address[1000], gender[100];
        int age;
        while (result != 0)
        {
            printf("Please enter your name: ");
            scanf("%s", &name);
            printf("Please enter your Date of birth(MM/DD/YYYY): ");
            scanf("%s", &dob);
            printf("Please enter your age: ");
            scanf("%d", &age);
            printf("Please enter your address without space(No,Street-name,City): ");
            scanf("%s", &address);
            printf("Please enter your gender(M/F): ");
            scanf("%s", &gender);
            printf("\n");
            printf("Your name is:\t\t\t%s\n", name);
            printf("Your date of birth is:\t\t%s\n", dob);
            printf("Your age is:\t\t\t%d\n", age);
            printf("Your address is:\t\t%s\n", address);
            printf("Your gender is(M/F):\t\t%s\n", gender);
            printf("\nAre you these data are correct (Y/N): ");
            scanf("%s", &isRegistrationDataCorrect);
            isRegistrationDataCorrect[0] = toupper(isRegistrationDataCorrect[0]);
            result = strcmp(isRegistrationDataCorrect, yes);
        }
        char val[4];
        while (fscanf(users, "%s %*s %*s %*s %*s %*s", val) == 1)
        {
        }
        int refLast = atoi(val);
        refLast = refLast + 1;
        if (users != NULL)
        {
            fprintf(users, "\n%04d\t\t%s\t\t%s\t\t%d\t\t%s\t\t%s", refLast, name, dob, age, gender, address);
        }
        return 1;
        break;
    default:
        printf("Invalid input");
        break;
    }
}

void main()
{
    int userState = validation();
    printf("%d", userState);
}
