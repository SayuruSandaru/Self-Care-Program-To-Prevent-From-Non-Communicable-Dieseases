#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Get medical data
void getMedicalData(char *referenceNo)
{
    float weight;
    float height;
    float rbs;
    int BPU;
    int BPL;
    char NCD;
    char is_alcoholic;
    char *bmi_state;
    char *bp_state;
    printf("Enter the weight in Kg: ");
    scanf("%f", &weight);
    printf("Enter the height in cm:");
    scanf("%f", &height);
    printf("Enter your random blood sugar level: ");
    scanf("%f", &rbs);
    printf("Enter your upper blood pressure: ");
    scanf("%f", &BPU);
    printf("Enter your lower blood pressure level: ");
    scanf("%f", &BPL);
    printf("Is anyone of your family member suffer from cancer, diabetes, cholestrol(Y/N)? ");
    scanf("%s", &NCD);
    printf("Do you use liquor, smoke, tobacco or areca nut(Y/N)? ");
    scanf("%s", &is_alcoholic);
    float bmi = weight / ((height / 100) * (height / 100));
    // Determine BMI state
    if (bmi < 18.5)
    {
        bmi_state = "Underweight";
    }
    else if (bmi < 24.9)
    {
        bmi_state = "Normal";
    }
    else if (bmi < 29.9)
    {
        bmi_state = "Obesity_class_1";
    }
    else if (bmi < 34.9)
    {
        bmi_state = "Obesity_class_2";
    }
    else
    {
        bmi_state = "Extreme_obesity";
    }

    // Determine BP state
    if (BPU <= 120 && BPL <= 80)
    {
        bp_state = "Normal";
    }
    else if (BPU <= 129 && BPL <= 80)
    {
        bp_state = "Elevated";
    }
    else if (BPU <= 139 && BPL < 89)
    {
        bp_state = "High_blood_pressure_stage_1";
    }
    else if (BPU >= 140 || BPL >= 90)
    {
        bp_state = "High_blood_pressure_stage_2";
    }
    else
    {
        bp_state = "Hypertensive_crisis";
    }
    // Determine blood sugar level state
    char *bsl_state;
    if (rbs <= 99)
    {
        bsl_state = "Normal";
    }
    else if (rbs <= 125)
    {
        bsl_state = "Prediabetes";
    }
    else
    {
        bsl_state = "Diabetes";
    }
    FILE *report = fopen("report.txt", "r");
    if (report == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    printf("\nAbove data will be stored. You can view and update them later.\n");
    // create a buffer to store the contents of the file
    char buffer[4096] = {0};
    char line[256];
    int found = 0;
    // read the file into the buffer
    while (fgets(line, sizeof(line), report))
    {
        if (strstr(line, referenceNo))
        {
            // if the reference number is found, set the flag and continue
            found = 1;
            continue;
        }
        // add the current line to the buffer
        strcat(buffer, line);
    }
    fclose(report); // close the file

    // open the file in write mode
    report = fopen("report.txt", "w");
    if (report == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    // write the buffer to the file
    fprintf(report, "%s", buffer);

    if (found == 0)
    {
        // if the reference number was not found, append the new data to the file
        fprintf(report, "\n%s\t%s\t\t%s\t%s", referenceNo, bp_state, bmi_state, bsl_state);
    }
    else
    {
        // otherwise, write the new data for the reference number
        fprintf(report, "\n%s\t%s\t\t%s\t%s", referenceNo, bp_state, bmi_state, bsl_state);
    }
    fclose(report);
    printf("\n");
    exitMenu();
}

// void addNewUser()
// {
//     char name[30];
//     char dob[12];
//     int age;
//     char gender[10];
//     char address[50];
//     printf("\033c");
//     printf("Please enter following details without any space.\n");
//     printf("Enter your name: ");
//     scanf("%s", name);
//     printf("Enter your date of birth(dd/mm/yyyy): ");
//     scanf("%s", dob);
//     printf("Enter your age: ");
//     scanf("%d", &age);
//     printf("Enter your gender(M/F): ");
//     scanf(" %c", gender);
//     printf("Enter your address: ");
//     scanf("%s", address);

//     int refLast = 0;
//     char temp[15];
//     int flag = 0;
//     FILE *users = fopen("users.txt", "a+");
//     if (!users)
//     {
//         printf("Error opening file!\n");
//         exit(1);
//     }

//     while (fgets(temp, sizeof(temp), users) != NULL)
//     {
//         refLast = atoi(temp);
//         flag = 1;
//     }

//     if (flag == 0)
//     {
//         refLast = 9999;
//     }
//     refLast++;

//     char ref_str[5];
//     sprintf(ref_str, "%04d", refLast);

//     fprintf(users, "\n%s\t\t%s\t\t%s\t\t%d\t\t%s\t\t%s", ref_str, name, dob, age, gender, address);
//     fclose(users);
// }

// User handling
int validation()
{
    int selectedItem;
    FILE *users = fopen("users.txt", "a+");
    printf("Please login or register to continue.\n\n");
    printf("1-Login\n");
    printf("2-Register\n");
    printf("Please enter your selection: ");
    scanf("%d", &selectedItem);
    switch (selectedItem)
    {
    case 1:
        char enteredRefNo[500];
        printf("\n\t\tWelcome back\n");
        printf("\t\t------------\n\n");
        printf("To begin please enter your reference no: ");
        scanf("%s", &enteredRefNo);
        char readVal[500];
        while (fscanf(users, "%s %*s %*s %*s %*s %*s", readVal) == 1)
        {
            if (strcmp(readVal, enteredRefNo) == 0)
            {
                printf("\033c");
                return 1;
            }
        }
        printf("we couldn't find your reference number");
        exit(0);
        break;
    case 2:
        char isRegistrationDataCorrect[10] = "N";
        char yes[10] = "Y";
        int result = 1;
        char name[100], dob[100], address[1000], gender[100];
        int age;
        while (result != 0)
        {
            printf("\033c");
            printf("Please enter the following details without using any space. You can use '_' character represent the space.\n\n");
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
        fseek(users, 0, SEEK_END);
        long fileSize = ftell(users);
        fseek(users, 0, SEEK_SET);
        char lastRef[10];
        char line[100];
        while (fgets(line, sizeof(line), users))
        {
            sscanf(line, "%s", lastRef);
        }
        int refLast = atoi(lastRef);
        refLast = refLast + 1;
        if (users != NULL)
        {
            fprintf(users, "\n%04d\t\t%s\t\t%s\t\t%d\t\t%s\t\t%s", refLast, name, dob, age, gender, address);
            fflush(users);
            fclose(users);
        }
        char refString[10];
        sprintf(refString, "%04d", refLast);
        printf("\nPlease enter your medical data.\n");
        getMedicalData(refString);
        return 1;
        break;
    default:
        printf("Invalid input");
        break;
    }
}

void updateMedicalData()
{
    char ref[10];
    printf("Please enter your reference number again: ");
    scanf("%s", &ref);
    printf("\033c");
    printf("Please enter following details.\n");
    FILE *users = fopen("users.txt", "a+");
    char val[10];
    while (fscanf(users, "%s %*s %*s %*s %*s %*s", val) == 1)
    {
        if (strcmp(val, ref) == 0)
        {
            getMedicalData(ref);
        }
    }
}

void seeReport()
{
    char referenceNo[10];
    printf("Please enter your reference number again: ");
    scanf("%s", referenceNo);
    FILE *report = fopen("report.txt", "r");
    FILE *users = fopen("users.txt", "r");
    if (report == NULL || users == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char line[256];
    char tRe[256], name[256], dob[256], age[256], gender[10], pressure[256], bmi[256];
    int found = 0;
    while (fgets(line, sizeof(line), report))
    {
        if (strstr(line, referenceNo))
        {
            found = 1;
            sscanf(line, "%s\t%s\t%s", tRe, pressure, bmi);
            while (fgets(line, sizeof(line), users))
            {
                if (strstr(line, referenceNo))
                {
                    sscanf(line, "%s\t%s\t%s\t%s\t%s", tRe, name, dob, age, gender);
                    break;
                }
            }
            printf(" \n");
            printf("Reference no:\t%s\n", referenceNo);
            printf("Name:\t\t%s\n", name);
            printf("Age:\t\t%s\n", age);
            printf("Gender:\t\t%s\n", gender);
            printf("___________________________________________________________\n");
            printf(" \n");
            printf("BMI: %s\tBlood pressure: %s\n", bmi, pressure);
            break;
        }
    }
    if (found == 0)
    {
        printf("The reference number %s was not found in the report.\n", referenceNo);
    }
    fclose(report);
    fclose(users);
}
void generateUniqueNumbers(int randomIndex[], int size)
{
    int i = 0;
    while (i < size)
    {
        int newNumber = rand() % 10 + 1; // generates a random number between 1 and 10
        int j;
        for (j = 0; j < i; j++)
        {
            if (randomIndex[j] == newNumber)
            { // check if the new number is already in the array
                break;
            }
        }
        if (j == i)
        {                               // if the number is not in the array
            randomIndex[i] = newNumber; // add it to the array
            i++;
        }
    }
}

void readWorkoutFile(char *fileName, int *randomIndex)
{
    FILE *workout_file = fopen(fileName, "r");
    if (workout_file == NULL)
    {
        printf("Error opening workout file!\n");
        return;
    }
    char workout[256];
    int count = 0;
    while (fgets(workout, sizeof(workout), workout_file))
    {
        for (int i = 0; i < 4; i++)
        {
            if (count == randomIndex[i])
            {
                printf("%s", workout);
            }
        }
        count++;
    }
    fclose(workout_file);
}

void displayWorkout()
{
    char referenceNo[10];
    printf("Please enter your reference number again: ");
    scanf("%s", referenceNo);
    int randomIndex[4];
    printf("\033c");
    generateUniqueNumbers(randomIndex, 4);
    FILE *report = fopen("report.txt", "r");
    if (report == NULL)
    {
        printf("Error opening report file!\n");
        return;
    }
    char tRe[256], bp_state[256], bmi_state[256], sugar_level[256];
    char line[256];
    while (fgets(line, sizeof(line), report))
    {
        if (strstr(line, referenceNo))
        {
            sscanf(line, "%s\t%s\t%s\t%s", tRe, bp_state, bmi_state, sugar_level);
            if (strcmp(sugar_level, "Diabetes") == 0 || strcmp(sugar_level, "Pre_Diabetes") == 0)
            {
                printf("You suffer from %s. So you need to do the following workout to manage the fitness and the blood sugar level.\n\n", sugar_level);
                readWorkoutFile("workout_diabetics.txt", randomIndex);
            }
            else if (strcmp(bmi_state, "Underweight") == 0)
            {
                printf("Your BMI is low. You should focus on doing following exercise to build up your muscles and increase overall strength.\n\n");
                readWorkoutFile("workout_underweight.txt", randomIndex);
            }
            else if (strcmp(bmi_state, "Normal") != 0)
            {
                printf("You are suffering from obesity. You need to focus on doing following execise to burn some calories, increase the strength and increase the muscle mass.\n\n");
                readWorkoutFile("workout_obesity.txt", randomIndex);
            }
            else if (strcmp(bp_state, "Normal") != 0 && strcmp(bp_state, "Elevated") != 0)
            {
                printf("Your blood pressure level is high. You need to focus on following exercise to lower your blood pressure and improve overall cardiovascular health. \n\n");
                readWorkoutFile("workout_pressure.txt", randomIndex);
            }
            else
            {
                printf("Your overall health is good. But keep doing some general workout to keep you healthier for future. \n");
            }
        }
    }
    fclose(report);
    exitMenu();
}

void displayDietPlan()
{
    char referenceNo[10];
    printf("Please enter your reference number again: ");
    scanf("%s", referenceNo);
    printf("\033c");
    int randomIndex[4];
    generateUniqueNumbers(randomIndex, 4);
    FILE *report = fopen("report.txt", "r");
    if (report == NULL)
    {
        printf("Error opening report file!\n");
        return;
    }
    char tRe[256], bp_state[256], bmi_state[256], sugar_level[256];
    char line[256];
    while (fgets(line, sizeof(line), report))
    {
        if (strstr(line, referenceNo))
        {
            sscanf(line, "%s\t%s\t%s\t%s", tRe, bp_state, bmi_state, sugar_level);
            if (strcmp(sugar_level, "Diabetes") == 0 || strcmp(sugar_level, "Pre_Diabetes") == 0)
            {
                printf("A diet plan for a you should focus on controlling blood sugar levels through the consumption of low-glycemic index foods, such as:\n\n");
                readWorkoutFile("diet_diabetics.txt", randomIndex);
                printf("It should also include regular meals and snacks throughout the day to maintain stable blood sugar levels and limit processed foods, added sugars, and saturated fats.\n");
                printf("It's also important to limit or avoid the consumption of sugary drinks and alcohol.\n");
            }
            else if (strcmp(bmi_state, "Underweight") == 0)
            {
                printf("The below diet plan is specifically designed for individuals who are underweight. It includes a variety of nutrient-dense foods that are high in calories and protein.\n");
                printf("These foods will help to increase muscle mass and overall body weight, which is important for individuals who are underweight.\n\n");
                readWorkoutFile("diet_underweight.txt", randomIndex);
            }
            else if (strcmp(bmi_state, "Normal") != 0)
            {
                printf("A diet plan for obesity should focus on reducing overall calorie intake while still providing the body with essential nutrients. Some key elements of a diet plan for obesity may include:\n\n");
                readWorkoutFile("diet_obesity.txt", randomIndex);
            }
            else if (strcmp(bp_state, "Normal") != 0 && strcmp(bp_state, "Elevated") != 0)
            {
                printf("Your blood pressure level is higher. So you should have a diet plan with followings: \n\n");
                readWorkoutFile("diet_pressure.txt", randomIndex);
            }
            else
            {
                printf("Your overall health is good. You do not need any specific diet plan. Take a balanced diet to continue a healthier lifestyle. \n");
            }
            printf("\n");
        }
    }
    fclose(report);
    exitMenu();
}

int mainMenu()
{
    int selectedOption;
    printf("1 - Update medical details\n");
    printf("2 - See report\n");
    printf("3 - Your workout plan\n");
    printf("4 - Your diet plan\n\n");
    printf("Please enter your choice from 1 to 4: ");
    scanf("%d", &selectedOption);
    printf("\033c");
    switch (selectedOption)
    {
    case 1:
        updateMedicalData();
        break;
    case 2:
        seeReport();
        break;
    case 3:
        displayWorkout();
        break;
    case 4:
        displayDietPlan();
        break;
    default:
        break;
    }
    return selectedOption;
}

int exitMenu()
{
    int selectedOption;
    printf("1 - Go back\n");
    printf("2 - Exit\n");
    printf("Please enter your choice from 1 or 2: ");
    scanf("%d", &selectedOption);
    printf("\033c");
    switch (selectedOption)
    {
    case 1:
        mainMenu();
        break;
    case 2:
        printf("Exiting program.\n");
        exit(0);
        break;
    default:
        break;
    }
    return selectedOption;
}

void main()
{
    printf("\n\t\t##############################################\n");
    printf("\t\t\tSelf care program to prevent NCD \n");
    printf("\t\t##############################################\n");
    printf("\n");
    validation();
    int option = mainMenu();
}
