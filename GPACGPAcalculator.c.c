#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning (disable:4996)

#define MAX_STUDENTS 5000
#define MAX_SEMESTERS 3
#define MAX_COURSES_PER_SEMESTER 10

// Structure to store course information
struct Course
{
    char courseCode[10];
    int creditHours;
    char grade[3]; 
};

// Structure to store student information
struct Student
{
    char name[50];
    char studentID[10];
    int numSemesters;
    struct Course semesters[MAX_SEMESTERS][MAX_COURSES_PER_SEMESTER];
};

struct Student students[MAX_STUDENTS];
int numStudents = 0;

// Function to calculate GPA for a student in a specific semester
double calculateSemesterGPA(struct Student student, int semester) {
    double totalQualityPoints = 0.0;
    int totalCreditHours = 0;

    if (semester <= student.numSemesters && semester > 0) {
        for (int i = 0; i < MAX_COURSES_PER_SEMESTER; i++) {
            if (student.semesters[semester - 1][i].creditHours > 0) {
                double gradePoint = 0.00;
                char* grade = student.semesters[semester - 1][i].grade;

                if (strcmp(grade, "A") == 0) {
                    gradePoint = 4.00;
                }
                else if (strcmp(grade, "A-") == 0) {
                    gradePoint = 3.75;
                }
                else if (strcmp(grade, "B+") == 0) {
                    gradePoint = 3.50;
                }
                else if (strcmp(grade, "B") == 0) {
                    gradePoint = 3.00;
                }
                else if (strcmp(grade, "B-") == 0) {
                    gradePoint = 2.75;
                }
                else if (strcmp(grade, "C+") == 0) {
                    gradePoint = 2.50;
                }
                else if (strcmp(grade, "C") == 0) {
                    gradePoint = 2.00;
                }
                else if (strcmp(grade, "F") == 0) {
                    gradePoint = 0.00;
                }

                totalQualityPoints += gradePoint * student.semesters[semester - 1][i].creditHours;
                totalCreditHours += student.semesters[semester - 1][i].creditHours;
            }
        }
    }

    if (totalCreditHours == 0) {
        return 0.0;
    }

    return totalQualityPoints / totalCreditHours;
}

// Function to find a student's index by ID
int findStudentIndex(char studentID[]) {
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].studentID, studentID) == 0) {
            return i;
        }
    }
    return -1; // Student not found
}

// Function to add a new student
void addStudent() {
    struct Student student;
    printf("\n\t\t\t\t\tEnter student's name: ");
    scanf("%49s", student.name); // Limit the input to 49 characters to avoid buffer overflow
    rewind(stdin);
    printf("\t\t\t\t\tEnter student's ID (e.g., KPKL12345): ");
    scanf("%9s", student.studentID); // Limit the input to 9 characters
    rewind(stdin);
    printf("\t\t\t\t\tEnter the number of semesters: ");
    scanf("%d", &student.numSemesters);

    // Input course details for each semester
    for (int i = 0; i < student.numSemesters && i < MAX_SEMESTERS; i++) {
        printf("\n\t\t\t\t\tSemester %d:\n", i + 1);
        for (int j = 0; j < MAX_COURSES_PER_SEMESTER; j++) {
            printf("\t\t\t\t\tEnter course code (or enter '0' to stop entering courses): ");
            scanf("%9s", student.semesters[i][j].courseCode); // Limit the input to 9 characters

            if (strcmp(student.semesters[i][j].courseCode, "0") == 0) {
                break;
            }

            printf("\t\t\t\t\tEnter credit hours for %s: ", student.semesters[i][j].courseCode);
            scanf("%d", &student.semesters[i][j].creditHours);
            rewind(stdin);

            // Use a string to read the grade
            printf("\t\t\t\t\tEnter grade obtained (A/A-/B+/B/B-/C+/C/F) for %s: ", student.semesters[i][j].courseCode);
            scanf("%2s", student.semesters[i][j].grade);

            // Check if the entered grade is valid
            if (!(strcmp(student.semesters[i][j].grade, "A") == 0 ||
                strcmp(student.semesters[i][j].grade, "A-") == 0 ||
                strcmp(student.semesters[i][j].grade, "B+") == 0 ||
                strcmp(student.semesters[i][j].grade, "B") == 0 ||
                strcmp(student.semesters[i][j].grade, "B-") == 0 ||
                strcmp(student.semesters[i][j].grade, "C+") == 0 ||
                strcmp(student.semesters[i][j].grade, "C") == 0 ||
                strcmp(student.semesters[i][j].grade, "F") == 0)) {
                printf("\t\t\t\t\tInvalid grade entered. Defaulting to 'F'.\n");
                strcpy(student.semesters[i][j].grade, "F");
            }

            rewind(stdin);
        }
    }

    // Add student to the list
    students[numStudents] = student;
    numStudents++;

    printf("\t\t\t\t\tStudent information added successfully!\n\n");
}

// Function to calculate CGPA for a student with multiple semesters
double calculateCGPA(struct Student student) {
    double totalQualityPoints = 0.0;
    int totalCreditHours = 0;

    for (int i = 0; i < student.numSemesters; i++) {
        for (int j = 0; j < MAX_COURSES_PER_SEMESTER; j++) {
            if (student.semesters[i][j].creditHours > 0) {
                double gradePoint = 0.00;
                char* grade = student.semesters[i][j].grade;

                if (strcmp(grade, "A") == 0) {
                    gradePoint = 4.00;
                }
                else if (strcmp(grade, "A-") == 0) {
                    gradePoint = 3.75;
                }
                else if (strcmp(grade, "B+") == 0) {
                    gradePoint = 3.50;
                }
                else if (strcmp(grade, "B") == 0) {
                    gradePoint = 3.00;
                }
                else if (strcmp(grade, "B-") == 0) {
                    gradePoint = 2.75;
                }
                else if (strcmp(grade, "C+") == 0) {
                    gradePoint = 2.50;
                }
                else if (strcmp(grade, "C") == 0) {
                    gradePoint = 2.00;
                }
                else if (strcmp(grade, "F") == 0) {
                    gradePoint = 0.00;
                }

                totalQualityPoints += gradePoint * student.semesters[i][j].creditHours;
                totalCreditHours += student.semesters[i][j].creditHours;
            }
        }
    }

    if (totalCreditHours == 0) {
        return 0.0;
    }

    return totalQualityPoints / totalCreditHours;
}

// Function to display details for all students
void displayAllStudentDetails() {
    printf("\n\t\t\t\t\t============================================\n");
    printf("\t\t\t\t\tStudent Details\n");

    for (int i = 0; i < numStudents; i++) {
        printf("\n\t\t\t\t\tStudent %d\n", i + 1);
        printf("\t\t\t\t\tName: %s\n", students[i].name);
        printf("\t\t\t\t\tStudent ID: %s\n", students[i].studentID);
        printf("\t\t\t\t\tNumber of Semesters: %d\n", students[i].numSemesters);

        for (int j = 0; j < students[i].numSemesters; j++) {
            printf("\n\t\t\t\t\tSemester %d:\n", j + 1);

            for (int k = 0; k < MAX_COURSES_PER_SEMESTER; k++) {
                if (students[i].semesters[j][k].creditHours > 0) {
                    printf("\t\t\t\t\tCourse Code: %s\n", students[i].semesters[j][k].courseCode);
                    printf("\t\t\t\t\tCredit Hours: %d\n", students[i].semesters[j][k].creditHours);
                    printf("\t\t\t\t\tGrade: %s\n", students[i].semesters[j][k].grade);
                }
            }

            printf("\t\t\t\t\tGPA: %.2f\n", calculateSemesterGPA(students[i], j + 1));
        }

        printf("\n\t\t\t\t\tCGPA: %.2f\n", calculateCGPA(students[i]));
    }

    printf("\t\t\t\t\t============================================\n\n");
}

// Function to display GPA and CGPA scores for a student
void displayStudentScores(char studentID[]) {
    int studentIndex = findStudentIndex(studentID);
    if (studentIndex != -1) {
        printf("\n\t\t\t\t\t===========================================\n");
        printf("\t\t\t\t\tStudent ID: %s\n", studentID);
        printf("\t\t\t\t\tName: %s\n", students[studentIndex].name);
        printf("\t\t\t\t\tNumber of Semesters: %d\n", students[studentIndex].numSemesters);

        for (int i = 0; i < students[studentIndex].numSemesters; i++) {
            printf("\n\t\t\t\t\tSemester %d:\n", i + 1);

            for (int j = 0; j < MAX_COURSES_PER_SEMESTER; j++) {
                if (students[studentIndex].semesters[i][j].creditHours > 0) {
                    printf("\t\t\t\t\tCourse Code: %s\n", students[studentIndex].semesters[i][j].courseCode);
                    printf("\t\t\t\t\tCredit Hours: %d\n", students[studentIndex].semesters[i][j].creditHours);
                    printf("\t\t\t\t\tGrade: %s\n", students[studentIndex].semesters[i][j].grade);
                }
            }

            printf("\t\t\t\t\tGPA: %.2f\n", calculateSemesterGPA(students[studentIndex], i + 1));
        }

        printf("\n\t\t\t\t\tCGPA: %.2f\n", calculateCGPA(students[studentIndex]));
        printf("\t\t\t\t\t============================================\n");
    }
    else {
        printf("\t\t\t\t\tStudent not found. Please enter a valid student ID.\n");
    }
}

int main() {
    int choice;
    printf("\t\t\t\t\t============================================\n");
    printf("\t\t\t\t\t Welcome to Kolej Pasar GPA/CGPA Calculator!\n");
    printf("\t\t\t\t\t============================================\n");

    while (1) {
        printf("\n\t\t\t\t\tPlease select a mode to proceed:\n");
        printf("\t\t\t\t\t1. Kolej Pasar Staff Administrator Mode\n");
        printf("\t\t\t\t\t2. Kolej Pasar Student Mode\n");
        printf("\t\t\t\t\t3. Exit calculator\n");
        printf("\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // Staff Administrator Mode
            char password[50] = "123456";
            printf("\n\t\t\t\t\tEnter staff password: ");
            scanf("%s", password);

            if (strcmp(password, "123456") == 0) { // Replace with your desired staff password
                printf("\n\t\t\t\t\tStaff Administrator Mode\n");
                int adminChoice;

                while (1) {
                    printf("\t\t\t\t\t1. Add Student\n");
                    printf("\t\t\t\t\t2. Display All Student Details\n");
                    printf("\t\t\t\t\t3. Back to Main Menu\n");
                    printf("\t\t\t\t\tEnter your choice: ");
                    scanf("%d", &adminChoice);

                    if (adminChoice == 1) {
                        // Add a new student
                        addStudent();
                    }
                    else if (adminChoice == 2) {
                        // Display all student details
                        displayAllStudentDetails();
                    }
                    else if (adminChoice == 3) {
                        // Return to Main Menu
                        break;
                    }
                    else {
                        printf("\t\t\t\t\tInvalid choice. Please select a valid option.\n");
                    }
                }
            }
            else {
                printf("\t\t\t\t\tInvalid password. Access denied.\n");
            }
        }
        else if (choice == 2) {
            // Student Mode
            printf("\n\t\t\t\t\tStudent Mode\n");
            char studentID[10];
            printf("\t\t\t\t\tEnter student ID to log in (e.g., KPKL12345): ");
            scanf("%s", studentID);

            // Display student details
            displayStudentScores(studentID);
        }
        else if (choice == 3) {
            // Exit the program
            printf("\n\t\t\t\t\tThank you for using Kolej Pasar GPA/CGPA Calculator. Goodbye!\n");
            break;
        }
        else {
            printf("\n\t\t\t\t\tInvalid choice. Please select a valid option.\n");
        }
    }

    system("pause");
}