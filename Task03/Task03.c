#include <stdio.h>

enum kind { TEMPERATURE, HUMIDITY, STATUS };
struct reading {
    enum kind type;
    union {
        float celsius;
        int percent;
        char status[8];
    } value;
};

void show(const struct reading *r)
{
    switch (r->type) {
        case TEMPERATURE: printf("Temp %.1f C\n", r->value.celsius); break;
        case HUMIDITY:    printf("Humidity %d %%\n", r->value.percent); break;
        case STATUS:      printf("Status %s\n", r->value.status); break;
        default:          printf("Invalid reading\n"); break;
    }
}

int main(void)
{
    struct reading log[3] = {
        {TEMPERATURE, {.celsius = 31.5f}},
        {HUMIDITY, {.percent = 68}},
        {STATUS, {.status = "OK"}}
    };
    printf("sizeof union = %zu, sizeof struct reading = %zu\n",
           sizeof log[0].value, sizeof log[0]);
    for (int i = 0; i < 3; ++i) show(&log[i]);

    log[0].value.celsius = 31.5f;
    printf("Misuse experiment: temperature stored; reading percent gives %d (implementation-dependent interpretation)\n",
           log[0].value.percent);
    return 0;
}
