#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node 
{
    int Rno;
    char Name[50];
    char City[50];
    int Marks;
    struct Node* next;
};

struct DBMS 
{
    struct Node* first;
};

int Counter = 1;

struct Node* createNode(const char* name, const char* city, int marks) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->Rno = Counter++;
    strcpy(newNode->Name, name);
    strcpy(newNode->City, city);
    newNode->Marks = marks;
    newNode->next = NULL;
    return newNode;
}

void initializeDBMS(struct DBMS *db) {
    db->first = NULL;
    printf("DBMS initialized successfully...\n");
    printf("Student Table created successfully...\n");
}

void Display(struct DBMS *db) {
    printf("Data from the student table is:\n");
    printf("--------------------------------------------------------------\n");
    struct Node* temp = db->first;
    while (temp != NULL) {
        printf("%d\t%s\t%s\t%d\n", temp->Rno, temp->Name, temp->City, temp->Marks);
        temp = temp->next;
    }
    printf("--------------------------------------------------------------\n");
}

void InsertIntoTable(struct DBMS *db, const char* name, const char* city, int marks) {
    struct Node* newNode = createNode(name, city, marks);
    if (db->first == NULL) {
        db->first = newNode;
    } else {
        struct Node* temp = db->first;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Record inserted at the end...\n");
}

void SelectStarFrom(struct DBMS *db) {
    Display(db);
}

void SelectStarFromWhereCity(struct DBMS *db, const char* city) {
    printf("Data from the student table where city is: %s\n", city);
    printf("--------------------------------------------------------------\n");
    struct Node* temp = db->first;
    while (temp != NULL) {
        if (strcmp(temp->City, city) == 0) {
            printf("%d\t%s\t%s\t%d\n", temp->Rno, temp->Name, temp->City, temp->Marks);
        }
        temp = temp->next;
    }
    printf("--------------------------------------------------------------\n");
}

void SelectCount(struct DBMS *db) {
    struct Node* temp = db->first;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("Number of records in the table: %d\n", count);
}

void SelectSum(struct DBMS *db) {
    struct Node* temp = db->first;
    int sum = 0;
    while (temp != NULL) {
        sum = sum + temp->Marks;
        temp = temp->next;
    }
    printf("Sum of Marks column is: %d\n", sum);
}

void SelectAvg(struct DBMS *db) {
    struct Node* temp = db->first;
    int sum = 0;
    int count = 0;
    while (temp != NULL) {
        sum = sum + temp->Marks;
        count++;
        temp = temp->next;
    }
    if (count > 0) {
        printf("Average of Marks column is: %.2f\n", (float)sum / count);
    } else {
        printf("No records found.\n");
    }
}

void SelectMax(struct DBMS *db) 
{
    struct Node* temp = db->first;
    if (temp == NULL) {
        printf("No records found.\n");
        return;
    }
    int max = temp->Marks;
    while (temp != NULL) {
        if (temp->Marks > max) {
            max = temp->Marks;
        }
        temp = temp->next;
    }
    printf("Maximum of Marks column is: %d\n", max);
}

void SelectMin(struct DBMS *db) {
    struct Node* temp = db->first;
    if (temp == NULL) {
        printf("No records found.\n");
        return;
    }
    int min = temp->Marks;
    while (temp != NULL) {
        if (temp->Marks < min) {
            min = temp->Marks;
        }
        temp = temp->next;
    }
    printf("Minimum of Marks column is: %d\n", min);
}

void SelectStarFromName(struct DBMS *db, const char* name) {
    printf("Information of all students with the name: %s\n", name);
    struct Node* temp = db->first;
    while (temp != NULL) {
        if (strcmp(temp->Name, name) == 0) {
            printf("%d\t%s\t%s\t%d\n", temp->Rno, temp->Name, temp->City, temp->Marks);
        }
        temp = temp->next;
    }
}

void UpdateCity(struct DBMS *db, int rno, const char* city) {
    struct Node* temp = db->first;
    while (temp != NULL) {
        if (temp->Rno == rno) {
            strcpy(temp->City, city);
            printf("Record updated...\n");
            return;
        }
        temp = temp->next;
    }
    printf("Record not found...\n");
}

void DeleteFrom(struct DBMS *db, int rno) {
    struct Node* temp = db->first;
    if (temp == NULL) {
        printf("List is empty!\n");
        return;
    }

    if (temp->Rno == rno) {
        db->first = temp->next;
        free(temp);
        printf("Record with Rno %d deleted...\n", rno);
        return;
    }

    while (temp->next != NULL) {
        if (temp->next->Rno == rno) {
            struct Node* delNode = temp->next;
            temp->next = delNode->next;
            free(delNode);
            printf("Record with Rno %d deleted...\n", rno);
            return;
        }
        temp = temp->next;
    }
    printf("Record with Rno %d not found...\n", rno);
}

int main() {
    struct DBMS *db = (struct DBMS *)malloc(sizeof(struct DBMS));
    if (db == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    initializeDBMS(db);

    int choice;
    char name[50], city[50];
    int marks, rno;

    while (1) {
        printf("\n1. Insert into Table\n2. Display\n3. Select by City\n4. Select Count\n5. Select Sum\n6. Select Avg\n7. Select Max\n8. Select Min\n9. Select by Name\n10. Update City\n11. Delete Record\n12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter city: ");
                scanf("%s", city);
                printf("Enter marks: ");
                scanf("%d", &marks);
                InsertIntoTable(db, name, city, marks);
                break;
            case 2:
                Display(db);
                break;
            case 3:
                printf("Enter city to search: ");
                scanf("%s", city);
                SelectStarFromWhereCity(db, city);
                break;
            case 4:
                SelectCount(db);
                break;
            case 5:
                SelectSum(db);
                break;
            case 6:
                SelectAvg(db);
                break;
            case 7:
                SelectMax(db);
                break;
            case 8:
                SelectMin(db);
                break;
            case 9:
                printf("Enter name to search: ");
                scanf("%s", name);
                SelectStarFromName(db, name);
                break;
            case 10:
                printf("Enter Rno of record to update: ");
                scanf("%d", &rno);
                printf("Enter new city: ");
                scanf("%s", city);
                UpdateCity(db, rno, city);
                break;
            case 11:
                printf("Enter Rno of record to delete: ");
                scanf("%d", &rno);
                DeleteFrom(db, rno);
                break;
            case 12:
                while (db->first != NULL) {
                    DeleteFrom(db, db->first->Rno);
                }
                free(db);
                return 0;
            default:
                printf("Invalid choice!\n");
                break;
        }
    }

    return 0;
}
