#include <stdio.h>
#include <string.h>

typedef struct { int systolic; int diastolic; } BloodPressure;
typedef struct { int day; int month; int year; } VisitDate;
typedef struct {
    char name[50];
    int age;
    char phone[16];
    BloodPressure bp;
    VisitDate visit;
} Patient;

void addPatient(Patient *p, const char *name, int age, const char *phone,
                BloodPressure bp, VisitDate visit)
{
    if (p == NULL || name == NULL || phone == NULL) return;
    snprintf(p->name, sizeof p->name, "%s", name);
    p->age = age;
    snprintf(p->phone, sizeof p->phone, "%s", phone);
    p->bp = bp;
    p->visit = visit;
}

int main(void)
{
    Patient patients[2];
    addPatient(&patients[0], "Anitha", 42, "9876543210",
               (BloodPressure){120, 80}, (VisitDate){19, 11, 2026});
    addPatient(&patients[1], "Bala", 35, "9123456780",
               (BloodPressure){118, 76}, (VisitDate){18, 11, 2026});

    for (size_t i = 0; i < 2; ++i)
        printf("%s, age %d, phone %s, BP %d/%d, visit %02d/%02d/%04d\n",
               patients[i].name, patients[i].age, patients[i].phone,
               patients[i].bp.systolic, patients[i].bp.diastolic,
               patients[i].visit.day, patients[i].visit.month, patients[i].visit.year);
    return 0;
}
