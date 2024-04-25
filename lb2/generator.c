#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "student.h"

char* getRandomString(char* arr[],int size);
int getRandomInt(int min, int max);
student generateData(void);
void writeData(FILE* f, student* s);

int main()
{
    FILE* f;
    int n = 20;
    char filename[] = "input.txt";

    f = fopen(filename, "w");
    
    srand(time(0));

    for (int i = 0; i < n; i++) {
        student s = generateData();
        writeData(f, &s);
    }  

    fclose(f);
    printf("File '%s' created sucsesful.\n", filename);

    return 0;
}

char* getRandomString(char* arr[],int size)
{
    int index = rand() % size;
    return arr[index];
}

int getRandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

student generateData(void)
{
    student s;
    char* surnames[] = {"Ivanov", "Petov", "Sidorov", "Kuznezov", "Smirnov", "Vorobyov", "Ivanova", "Petova", "Sidorova", "Kuznezova", "Smirnova", "Vorobyova"};
    char* initials[] = {"I.I.", "P.P.", "S.S.", "K.K.", "A.A.", "G.G."};
    char* sexes[] = { "female", "male"};
    int surnamesSize = sizeof(surnames) / sizeof(surnames[0]);
    int initialsSize = sizeof(initials) / sizeof(initials[0]);
    int sexesSize = sizeof(sexes) / sizeof(sexes[0]);

    strcpy(s.surname, getRandomString(surnames, surnamesSize));
    strcpy(s.initials, getRandomString(initials, initialsSize));
    strcpy(s.sex, getRandomString(sexes, sexesSize));
    s.group = getRandomInt(101, 115);
    s.mark_e = getRandomInt(2, 5);
    s.mark_z = getRandomInt(2, 5);

    return s;
}

void writeData(FILE* f, student* s)
{
    fprintf(f, "%s\t%s\t%s\t%d\t%d\t%d\n", s->surname, s->initials, s->sex, s->group, s->mark_e, s->mark_z);
}