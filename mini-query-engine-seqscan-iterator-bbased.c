#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 6

typedef struct
{
    int stud_id;
    char name[256];
    char sub_name[256];
    int marks;
} student_record;

/* Sample table data */
student_record student_record_table[MAX_STUDENTS] = {
    {101, "Almas", "Physics", 100},
    {102, "Ismail", "Physics", 100},
    {103, "Rohit", "Physics", 85},
    {104, "Saami", "Physics", 65},
    {105, "Sahith", "Physics", 60},
    {106, "Shiva", "Physics", 75}};

/* ---------------- Table Scan ---------------- */
int curr_row;

void table_scan_open()
{
    curr_row = 0;
    printf("table_scan is opened..\n");
}

student_record *table_scan_next()
{
    if (curr_row >= MAX_STUDENTS)
        return NULL;
    return &student_record_table[curr_row++];
}

void table_scan_close()
{
    curr_row = 0;
    printf("table_scan is closed.\n");
}

/* ---------------- Filter ---------------- */
void filter_open()
{
    table_scan_open();
    printf("filter is opened..\n");
}

student_record *filter_next()
{
    student_record *rec = NULL;
    while ((rec = table_scan_next()) != NULL)
    {
        if ((rec->marks > 70) && (strcmp(rec->sub_name, "Physics") == 0))
        {
            return rec;
        }
    }
    return NULL; // no more rows
}

void filter_close()
{
    table_scan_close();
    printf("filter is closed.\n");
}

/* ---------------- Projection ---------------- */
void projection_open()
{
    filter_open();
    printf("projection is opened..\n");
}

void projection_next()
{
    student_record *rec = NULL;
    printf("\nQuery Result:\n");
    printf("----------------------------\n");
    while ((rec = filter_next()) != NULL)
    {
        printf("student name: %-10s marks: %d\n", rec->name, rec->marks);
    }
    printf("----------------------------\n");
}

void projection_close()
{
    filter_close();
    printf("projection is closed.\n");
}

/* ---------------- Main ---------------- */
int main()
{
    projection_open();
    projection_next();
    projection_close();
    return 0;
}
