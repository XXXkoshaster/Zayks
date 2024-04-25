#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

void usage(void);

void findMostFrequentGroup(int* list, int n);
void findGroupWithMaxAverage(char* filename);

void printStudentData(student* s);
void printFile(char* filename);

int main(int argc, char* argv[])
{
    if (strcmp(argv[1], "-p") == 0 && argc == 3)
        findGroupWithMaxAverage(argv[2]);
    else if (strcmp(argv[1], "-f") == 0 && argc == 3)
        printFile(argv[2]); 
    else
        usage();
    
    return 0;
}

void usage(void)
{
    printf("Usage: program parametr(f/p) filename\n");
}

void findMostFrequentGroup(int* list, int n)
{
    int maxCount = 0;
    int mostFrequent;
    int count;

    for (int i = 0; i < n; ++i) {
        count = 1;
        for(int j = 0; j < n; j++) {
            if (list[i] == list[j]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            mostFrequent = list[i];
        }
    }
    
    printf("Group with the highest average female marks: %d\n", mostFrequent);
}

void findGroupWithMaxAverage(char* filename) {
    
    student s;
    double max_avg = 0.0;
    int l[100];
    int i = 0;
    
    FILE *in = fopen(filename, "rb");

    while (fread(&s, sizeof(s), 1, in) == 1) {
        if (strcmp(s.sex, "female") == 0) {
            double avg = (double)(s.mark_e + s.mark_z) / 2.0;
            if (avg > max_avg) {
                max_avg = avg;
                l[0] = s.group;
                i = 0;
            } else if (avg == max_avg) 
                l[++i] = s.group;  
        }
    }

    fclose(in);
    if (sizeof(l))
        findMostFrequentGroup(l, i+1);
    else
        printf("No people, avarage mark is not defined\n");
}

void printStudentData(student* s)
{
    printf("----------------------------------------------------------\n");
    printf("%-10s | %-9s | %-6s | %-7d | %-6d | %-4d\n", s->surname, s->initials, s->sex, s->group, s->mark_e, s->mark_z);
}

void printFile(char* filename) 
{
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    student s;
    
    printf("%-10s | %-9s | %-6s | %-7s | %-6s | %-4s\n", "Surname", "Initials", "Sex", "Group", "Examen", "Test");
    
    while (fread(&s, sizeof(student), 1, file) == 1) {
        printStudentData(&s);
    }

    fclose(file);
}
