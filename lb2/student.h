#ifndef __STUDENT_H__
#define __STUDENT_H__

#define MAX_NAME_LEN 10
#define MAX_INITIALS_LEN 5
#define MAX_SEX_LEN 7

typedef struct {
    char surname[MAX_NAME_LEN];
    char initials[MAX_INITIALS_LEN];
    char sex[MAX_SEX_LEN];
    int group;
    int mark_e;
    int mark_z;
} student;

#endif