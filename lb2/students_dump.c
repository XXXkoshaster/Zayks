#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "student.h"

void usage(void);
int readstudent(student *s);
void writeStudents(const char* filename);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        usage();
        return 1;
    }
    
    writeStudents(argv[1]);

    return 0;
}   

void usage(void)
{
    printf("Usage: program filename\n");
}

int readstudent(student *s)
{
    return scanf("%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%d\n", s->surname, s->initials, s->sex, &s->group, &s->mark_e, &s->mark_z) == 6;
}

void writeStudents(const char* filename) {
    
    student s;
    FILE *out = fopen(filename, "wb");
    
    while (readstudent(&s)) {
        fwrite(&s, sizeof(s), 1, out);
    }

    fclose(out);

    printf("File '%s' created sucsesful.\n", filename);
}