/*
    Algorithms Assignment Project.
    A Student Tracker.

    Author: Ruán Murgatroyd
    C. Date: 10/04/23
    IDE: VS Code
    Compiler: GCC
    OS: Windows 10
*/

// Req'd Libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Neat trick which makes clearing the input buffer easier.
#define CLEAR while(getchar() != '\n');

// These will be used to define the size of string arrays.
#define SMALL 10
#define MEDIUM 25
#define LARGE 50

// The limits of all the courses
// Global variables are defined here, to make course occupancy control easier.
#define PTHDLIMIT 13 // DT265A Limit
#define PTMQLIMIT 9  // DT265C Limit
#define FTMQLIMIT 14 // DT265B Limit
#define FTIMQLIMIT 6 // DT8900 Limit
#define ALLSTUDENTS PTHDLIMIT + PTMQLIMIT + FTMQLIMIT + FTIMQLIMIT

int DT265AFree = PTHDLIMIT;
int DT265CFree = PTMQLIMIT;
int DT265BFree = FTMQLIMIT;
int DT8900Free = FTIMQLIMIT;

// Student Record Struct
// 
struct studentRecord{
    char firstName[MEDIUM];
    char surname[LARGE];
    char studentID[MEDIUM];
    int courseCode; // 1 = DT265A, 2 = DT265B, 3 = DT265C, 4 = DT8900.
    int year; // 1 = 1st Year, 2 = 2nd Year, 3 = 3rd Year, 4 = 4th Year.
};

struct node{
    struct studentRecord studentRecord; // Student Data.
    struct node *nextNode; // Pointer to the next node in the linked list.
};

// Function Signatures

struct node* addStudent(struct node *);
struct node* removeStudent(struct node *);
void searchStudent(char*);
struct node* generateData(struct studentRecord [], struct studentRecord [], struct studentRecord [], struct studentRecord [], struct node *, int, int, int, int);
void sortCourseArray(struct studentRecord [], int);
void viewCourseData(struct studentRecord [], int);
struct node* createLinkedList(struct studentRecord [], struct studentRecord [], struct studentRecord [], struct studentRecord [], struct node *);
void merge(struct studentRecord [], int, int, int);
void mergeSort(struct studentRecord [], int, int);
const char* getCourseName(int);
int modifyCourseOccupancy(int, int);

int main(){


    struct node listHead;
    struct studentRecord DT265A[13];
    struct studentRecord DT265B[14];
    struct studentRecord DT265C[9];
    struct studentRecord DT8900[6];


    int loopActive = 1;
    char userChoice = '0';
    char studentName[] = "";

    while(loopActive){
        printf("--=<[Please Choose an Action]>=--\n");
        printf("1. Add User\n2. Remove User\n3. Search for User\n4. View Course Information\n5. Generate Test Data\n6. End Program\n");

        scanf("%c", &userChoice);
        CLEAR

        switch(userChoice){
            case '1':{
                addStudent(&listHead);
                break;
            }

            case '2':{
                removeStudent(&listHead);
                break;
            }

            case '3':{
                printf("Enter the Student's Surname: ");
                fgets(studentName, LARGE, stdin);
                //searchStudent(studentName);
                break;
            }

            case '4':{
                char courseChoice = '0';
                printf("Which course do you want to view?\n1. DT265A\n2. DT265B\n3. DT265C\n4. DT8900\n");
                scanf("%c", &courseChoice);

                switch(courseChoice){
                    case '1':{
                        int amountOfStudents = sizeof(DT265A) / sizeof(DT265A[0]);
                        viewCourseData(DT265A, amountOfStudents);
                        break;
                    }

                    case '2':{
                        int amountOfStudents = sizeof(DT265B) / sizeof(DT265B[0]);
                        viewCourseData(DT265B, amountOfStudents);
                        break;
                    }

                    case '3':{
                        int amountOfStudents = sizeof(DT265C) / sizeof(DT265C[0]);
                        viewCourseData(DT265C, amountOfStudents);
                        break;
                    }

                    case '4':{
                        int amountOfStudents = sizeof(DT8900) / sizeof(DT8900[0]);
                        viewCourseData(DT8900, amountOfStudents);
                        break;
                    }

                    default:{
                        printf("Invalid option!\n");
                        break;
                    }
                }
                break;
            }

            case '5':{
                generateData(DT265A, DT265B, DT265C, DT8900, &listHead, sizeof(DT265A), sizeof(DT265B), sizeof(DT265C), sizeof(DT8900));
                break;
            }

            case '6':{
                printf("Goodbye!");
                loopActive = 0;
                break;
            }

            default:{
                printf("Not a valid option, try again.\n");
                break;
            }
        }
    }
    
    return 0;
} // end main

// addStudent will add the student to the linked list.
// Call this function with a completed Student Record Struct
// This returns a pointer to the array of students.
struct node* addStudent(struct node *head){
    // Req'd Local Variables
    int courseSelect = 0;

    /* Note to Programmer:
    TO-DO:
    - New Struct
    - Get Data
    - Validate Data
    - Malloc & Validate
    - Linked List
    */
    
    // We need a temporary malloc'd variable to store this information as it is entered,
    // then it is written to the linked list and freed.
    // When adding to the struct, use arrow notation.
    struct studentRecord *addingStudent = malloc(sizeof(struct studentRecord));

    printf("\n---==<[STUDENT ADDITION MENU]>==---\n");
    
    // Error-checking and prevention.
    // Number is given as character, checked if it is a real number then checked if it is in-range.
    while(courseSelect == 0){
        printf("Select Course Code:\n1. DT265A\n2. DT265B\n3. DT265C\n4. DT8900\n5. Exit\n");

        char course;
        scanf("%c", &course);
        CLEAR

        if(isdigit(course) == 0){
            printf("\n!ERROR! You must enter a DIGIT!\n");
        }
        else{
            // C stores chars as ASCII integers, taking away the ASCII value of '0' from the char number gives an integer value!
            // This would cause problems if it was not a number ('A' for example), but the parent if-statement catches that.
            int courseNum = course - '0';

            if(courseNum > 0 && courseNum < 5){
                if(modifyCourseOccupancy(courseNum, 1) == 1){
                    printf("Course %s selected!\n", getCourseName(courseNum));
                    courseSelect = 1;
                }
                else{
                    printf("Insufficient space. Please Select another course!\n");
                }
            }
            else if(courseNum == 5){
                printf("Exiting Student Addition Menu.\n\n");
                return '\0';
            }
            else{
                printf("%d is not a valid value!", courseNum);
            }
        }
    }

    printf("Please enter Student's FIRST Name: ");
    fgets((addingStudent) -> firstName, MEDIUM, stdin);

    printf("Please enter the Student's SURNAME: ");
    fgets((addingStudent) -> surname, LARGE, stdin);

    printf("Please enter the Student's ID: ");
    fgets((addingStudent) -> studentID, MEDIUM, stdin);

    printf("What year is the student in?\n");
    scanf("%d", &(addingStudent) -> year);

}

struct node* removeStudent(struct node *head){

}

// Parses the 1-4 (and edge-case numbers) when making course code human-readable.
// When assigning to a variable, you MUST do the following: const char* [VARNAME] = getCourseName([VAL]);
// It is reccommended that you simply call the function as opposed to assigning to variables.
const char* getCourseName(int courseID){
    switch(courseID){
        case 1:{
            return "DT265A";
            break;
        }

        case 2:{
            return "DT265B";
            break;
        }

        case 3:{
            return "DT265C";
            break;
        }

        case 4:{
            return "DT8900";
            break;
        }

        default:{
            return '\0';
            break;
        }
    }
}

// This is given the courseID as a number and how many places to add or remove.
// Any positive number will REMOVE that many from the free spaces,
// Any negative number will ADD that many to the free spaces.
// It will return an integer '1' if it is successful, or a '0' if not.
int modifyCourseOccupancy(int courseID, int modifyAmount){
    switch(courseID){
        case 1:{
            if(DT265AFree - modifyAmount >= 0){
                DT265AFree = DT265AFree - modifyAmount;
                return 1;
            }
            else{
                return 0;
            }

            break;
        }

        case 2:{
            if(DT265BFree - modifyAmount >= 0){
                DT265BFree = DT265BFree - modifyAmount;
                return 1;
            }
            else{
                return 0;
            }

            break;
        }

        case 3:{
            if(DT265CFree - modifyAmount >= 0){
                DT265CFree = DT265CFree - modifyAmount;
                return 1;
            }
            else{
                return 0;
            }

            break;
        }

        case 4:{
            if(DT8900Free - modifyAmount >= 0){
                DT8900Free = DT8900Free - modifyAmount;
                return 1;
            }
            else{
                return 0;
            }

            break;
        }

        default:{
            return 0;
            break;
        }
    }
}

// This will generate random student Data for each of the 4 courses and then add it correctly to the linked list.
// Pass it the 4 course struct arrays and the linked list double-pointer.
// Then give it the 4 array sizes, in order.
// This will override all data currently in the arrays.
struct node* generateData(struct studentRecord DT265A[], struct studentRecord DT265B[], struct studentRecord DT265C[], struct studentRecord DT8900[], struct node *head, int DT265ASize, int DT265BSize, int DT265CSize, int DT8900Size){
    // Names for Random Generation
    char *firstNames[] = {"Emma", "Liam", "Olivia", "Noah", "Ava", "Oliver", "Sophia", "Elijah", "Isabella", "William", "Mia", "James", "Benjamin", "Charlotte", "Lucas", "Amelia", "Henry", "Harper", "Alexander", "Evelyn"};
    char *surnames[] = {"Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor", "Anderson", "Thomas", "Jackson", "White", "Harris", "Martin", "Thompson", "Garcia", "Martinez", "Robinson"};
    char *idNums[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

    // Initialising RNG
    time_t lTime;
    srand((unsigned) time(&lTime));

    printf("\nWriting DT265A's Test Data.\n");
    // Building DT265A's Test Data
    for(int i = 0; i < PTHDLIMIT; i++){

        // Randomly Generating Name
        strcpy(DT265A[i].firstName, firstNames[rand() % 20]);
        strcpy(DT265A[i].surname, surnames[rand() % 20]);
        
        // Randomly Generating 3-digit Student ID
        char tempStudentID[6] = "DT";
        for(int j = 0; j < 3; j++){
            strcat(tempStudentID, idNums[rand() % 10]);
        }

        strcpy(DT265A[i].studentID, tempStudentID);

        // Adding Course Code
        DT265A[i].courseCode = 1;

        // Adding Random Year
        DT265A[i].year = (rand() % 4) + 1;

        // Displaying Data
        printf("Added new student: %s %s\n", DT265A[i].firstName, DT265A[i].surname);

        // Modifying the Course Occupancy
        modifyCourseOccupancy(1, 1);
    }

    printf("\nDT265A complete, starting DT265B.\n");

    // Building DT265B's Test Data
    for(int i = 0; i < FTMQLIMIT; i++){

        // Randomly Generating Name
        strcpy(DT265B[i].firstName, firstNames[rand() % 20]);
        strcpy(DT265B[i].surname, surnames[rand() % 20]);
        
        // Randomly Generating 3-digit Student ID
        char tempStudentID[6] = "DT";
        for(int j = 0; j < 3; j++){
            strcat(tempStudentID, idNums[rand() % 10]);
        }

        strcpy(DT265B[i].studentID, tempStudentID);

        // Adding Course Code
        DT265B[i].courseCode = 2;

        // Adding Random Year
        DT265B[i].year = (rand() % 4) + 1;

        // Displaying Data
        printf("Added new student: %s %s\n", DT265B[i].firstName, DT265B[i].surname);

        // Modifying the Course Occupancy
        modifyCourseOccupancy(2, 1);
    }

    printf("\nDT265B complete, starting DT265C.\n");

    // Building DT265C's Test Data
    for(int i = 0; i < PTMQLIMIT; i++){

        // Randomly Generating Name
        strcpy(DT265C[i].firstName, firstNames[rand() % 20]);
        strcpy(DT265C[i].surname, surnames[rand() % 20]);
        
        // Randomly Generating 3-digit Student ID
        char tempStudentID[6] = "DT";
        for(int j = 0; j < 3; j++){
            strcat(tempStudentID, idNums[rand() % 10]);
        }

        strcpy(DT265C[i].studentID, tempStudentID);

        // Adding Course Code
        DT265C[i].courseCode = 3;

        // Adding Random Year
        DT265C[i].year = (rand() % 4) + 1;

        // Displaying Data
        printf("Added new student: %s %s\n", DT265C[i].firstName, DT265C[i].surname);

        // Modifying the Course Occupancy
        modifyCourseOccupancy(3, 1);
    }

    printf("\nDT265C complete, starting DT8900.\n");

    // Building DT8900's Test Data
    for(int i = 0; i < FTIMQLIMIT; i++){

        // Randomly Generating Name
        strcpy(DT8900[i].firstName, firstNames[rand() % 20]);
        strcpy(DT8900[i].surname, surnames[rand() % 20]);
        
        // Randomly Generating 3-digit Student ID
        char tempStudentID[6] = "DT";
        for(int j = 0; j < 3; j++){
            strcat(tempStudentID, idNums[rand() % 10]);
        }

        strcpy(DT8900[i].studentID, tempStudentID);

        // Adding Course Code
        DT8900[i].courseCode = 4;

        // Adding Random Year
        DT8900[i].year = (rand() % 4) + 1;

        // Displaying Data
        printf("Added new student: %s %s\n", DT8900[i].firstName, DT8900[i].surname);

        // Modifying the Course Occupancy
        modifyCourseOccupancy(4, 1);
    }

    printf("\nAll course data written! Sorting courses...\n\n");

    int courseSize = DT265ASize / sizeof(DT265A[0]);
    sortCourseArray(DT265A, courseSize);
    
    printf("DT265A sorted!\n");

    courseSize = DT265BSize / sizeof(DT265B[0]);
    sortCourseArray(DT265B, courseSize);
    
    printf("DT265B sorted!\n");

    courseSize = DT265CSize / sizeof(DT265C[0]);
    sortCourseArray(DT265C, courseSize);
    
    printf("DT265C sorted!\n");

    courseSize = DT8900Size / sizeof(DT8900[0]);
    sortCourseArray(DT8900, courseSize);
    
    printf("DT8900 sorted!\nAll arrays sorted. Sorting all students...\n");

    createLinkedList(DT265A, DT265B, DT265C, DT8900, head);

}

// This will sort the course arrays by SURNAME.
// Pass the course array as the first argument.
// Pass sizeof(courseArray) / sizeof(courseArray[0]) as the second argument.
void sortCourseArray(struct studentRecord sRec[], int elementsList){
    for(int i = 0; i < elementsList; i++){
        struct studentRecord currentRecord = sRec[i];

        int j = i - 1;

        while(j >= 0 && strcmp(sRec[j].surname, currentRecord.surname) > 0){
            // Swapping the structs
            sRec[j + 1] = sRec[j];
            j = j - 1;
        }

        sRec[j + 1] = currentRecord;
    }
}

// Pass this function a course array struct and it will list all of the students attending it.
void viewCourseData(struct studentRecord courseArray[], int elements){
    printf("\n\n---==<[%s Student Records]>==---\n", getCourseName(courseArray[0].courseCode));

    for(int i = 0; i < elements; i++){
        printf("<[STUDENT %d]>\nNAME: %s, %s\nID: %s\nYEAR: %d\n\n", i + 1, courseArray[i].surname, courseArray[i].firstName, courseArray[i].studentID, courseArray[i].year);
    }

    printf("<[END OF LIST]>\n");
}

struct node* createLinkedList(struct studentRecord DT265A[], struct studentRecord DT265B[], struct studentRecord DT265C[], struct studentRecord DT8900[], struct node *head){
    struct studentRecord allStudents[ALLSTUDENTS];

    for(int i = 0; i < ALLSTUDENTS; i++){
        if(i < PTHDLIMIT){
            allStudents[i] = DT265A[i];
        }
        else if(i < PTHDLIMIT + FTMQLIMIT && i >= PTHDLIMIT){
            allStudents[i] = DT265B[i - PTHDLIMIT];
        }
        else if(i < PTHDLIMIT + FTMQLIMIT + PTMQLIMIT && i >= PTHDLIMIT + FTMQLIMIT){
            allStudents[i] = DT265C[i - (PTHDLIMIT + FTMQLIMIT)];
        }
        else if(i < PTHDLIMIT + FTMQLIMIT + PTMQLIMIT + FTIMQLIMIT && i >= i < PTHDLIMIT + FTMQLIMIT + PTMQLIMIT){
            allStudents[i] = DT8900[i - (PTHDLIMIT + FTMQLIMIT + PTMQLIMIT)];
        }
    }

    mergeSort(allStudents, 0, ALLSTUDENTS - 1);
    printf("List of all students sorted by Surname. Creating linked list...\n\n");

    for(int i = 0; i < ALLSTUDENTS; i++){
        struct node *listElement = malloc(sizeof(struct node));

        strcpy(listElement->studentRecord.firstName, allStudents[i].firstName);
        strcpy(listElement->studentRecord.surname, allStudents[i].surname);
        strcpy(listElement->studentRecord.studentID, allStudents[i].studentID);
        listElement->studentRecord.courseCode = allStudents[i].courseCode;
        listElement->studentRecord.year = allStudents[i].year;

        struct node current = *head;

        while(current.nextNode != NULL){
            current = *current.nextNode;
        }

        current.nextNode = listElement;
    }

    printf("Linked list created!\n\n");
}

void merge(struct studentRecord sRec[], int start, int mid, int end){
    int tempArr1 = mid - start + 1;
    int tempArr2 = end - mid;

    struct studentRecord startTempArr[tempArr1], endTempArr[tempArr2];

    for(int i = 0; i < tempArr1; i++){
        startTempArr[i] = sRec[start + i];
    }

    for(int j = 0; j < tempArr2; j++){
        endTempArr[j] = sRec[mid + 1 + j];
    }

    int i, j, k;
    i = 0;
    j = 0;
    k = start;

    while(i < tempArr1 && j < tempArr2){
        if(strcmp(startTempArr[i].surname, endTempArr[j].surname) < 0){
            sRec[k] = startTempArr[i];
            i++;
        }
        else{
            sRec[k] = endTempArr[j];
            j++;
        }

        k++;
    }

    // Adding remaining elements in the startTempArray
    while(i < tempArr1){
        sRec[k] = startTempArr[i];
        i++;
        k++;
    }

    // Adding remaining elements in the endTempArray
    while(j < tempArr2){
        sRec[k] = endTempArr[j];
        j++;
        k++;
    }
}

void mergeSort(struct studentRecord sRec[], int start, int end){
    if(start < end){
        int mid = start + (end - start) / 2;

        mergeSort(sRec, start, mid);
        mergeSort(sRec, mid + 1, end);

        merge(sRec, start, mid, end);
    }
}