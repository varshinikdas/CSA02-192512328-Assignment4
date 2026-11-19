#include <stdio.h>

struct account { int number; float balance; };

void addInterest(struct account *a, float rate)
{
    if (a == NULL) return;
    printf("inside addInterest address: %p\n", (void *)a);
    a->balance += a->balance * rate / 100.0f;
}

int main(void)
{
    struct account list[3] = {{101, 5000}, {102, 12000}, {103, 800}};
    printf("main first account address: %p\n", (void *)&list[0]);
    for (int i = 0; i < 3; ++i) addInterest(&list[i], 4.0f);
    {
        const struct account *p = list;
        for (int i = 0; i < 3; ++i)
            printf("%d %.2f\n", p[i].number, p[i].balance);
    }
    return 0;
}
