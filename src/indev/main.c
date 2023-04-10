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

int DT265AFree = PTHDLIMIT;
int DT265CFree = PTMQLIMIT;
int DT265BFree = FTMQLIMIT;
int DT8900Free = FTIMQLIMIT;

// Student Record Struct
// This is a Linked List.
// 
struct studentRecord{
    char firstName[MEDIUM];
    char surname[LARGE];
    char studentID[MEDIUM];
    int courseCode; // 1 = DT265A, 2 = DT265B, 3 = DT265C, 4 = DT8900.
    int year; // 1 = 1st Year, 2 = 2nd Year, 3 = 3rd Year, 4 = 4th Year.
    struct studentRecord *nextNode; // Pointer to the next node in the linked list.
};

// Function Signatures

int* addStudent(struct studentRecord **);
int* removeStudent(struct studentRecord **);
const char* getCourseName(int);
int modifyCourseOccupancy(int, int);

int main(){
    struct studentRecord **sRec;

    addStudent(sRec);
    
    return 0;
} // end main

// addStudent will add the student to the linked list.
// Call this function with a completed Student Record Struct
// This returns a pointer to the array of students.
int* addStudent(struct studentRecord **head){
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
        printf("Select Course Code:\n1. DT265A\n2. DT265B\n3. DT265C\n4. DT8900\n");

        char course;
        scanf("%c", &course);
        CLEAR

        if(isdigit(course) == 0){
            printf("\n!ERROR! You must enter a DIGIT!\n");
        }
        else{
            // C stores chars as integers, taking away the ASCII value of '0' from the char number gives an integer value!
            // This would cause problems if it was not a number ('A' for example), but the parent if-statement catches that.
            int courseNum = course - '0';

            if(courseNum > 0 && courseNum < 5){
                if(modifyCourseOccupancy(courseNum, 1) == 1){
                    printf("Course %s selected!\n", getCourseName(courseNum));
                    courseSelect = 1;
                }
                else{
                    printf("Insuffecient space. Please Select another course!\n");
                }
            }
            else{
                printf("%d is not a valid value!", courseNum);
            }
        }
    }



    printf("Please enter Student's FIRST Name: ");
    fgets((addingStudent) -> firstName, MEDIUM, stdin);
}

int* removeStudent(struct studentRecord **sRec){

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