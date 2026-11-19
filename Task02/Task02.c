#include <stdio.h>

struct date { int day, month, year; };
struct address { char city[20]; int pincode; };
struct parcel { int id; float weight; struct address to; struct date booked; };

void print_parcel(const struct parcel *p)
{
    printf("%d %.1f kg %s-%d %02d/%02d/%04d\n",
           p->id, p->weight, p->to.city, p->to.pincode,
           p->booked.day, p->booked.month, p->booked.year);
}

void sort_by_weight(struct parcel p[], int n)
{
    for (int i = 0; i < n - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j)
            if (p[j].weight < p[min].weight) min = j;
        if (min != i) {
            struct parcel temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }
    }
}

int main(void)
{
    struct parcel list[3] = {
        {501, 4.5f, {"Madurai", 625001}, {12, 10, 2026}},
        {502, 1.2f, {"Chennai", 600077}, {12, 10, 2026}},
        {503, 2.8f, {"Coimbatore", 641001}, {13, 10, 2026}}
    };
    sort_by_weight(list, 3);
    for (int i = 0; i < 3; ++i) print_parcel(&list[i]);
    printf("Bytes in one whole-record swap: %zu\n", sizeof(struct parcel));
    printf("Receiver PIN of third parcel: %d\n", list[2].to.pincode);
    {
        struct parcel *ptr = &list[2];
        printf("Through pointer: %d\n", ptr->to.pincode);
    }
    return 0;
}
