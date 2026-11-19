#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 10
#define MAX_SALES 30

typedef struct { int day, month, year; } Date;
typedef enum { PACKAGED, COOKED, COMBO } ItemKind;

typedef struct { Date expiry; } PackagedData;
typedef struct { int hour, minute; } CookedData;
typedef struct { int component_ids[3]; int count; } ComboData;

typedef struct {
    int id;
    char name[40];
    ItemKind kind;
    float price;
    int stock;
    union {
        PackagedData packaged;
        CookedData cooked;
        ComboData combo;
    } detail;
} Item;

typedef struct { int item_id; int quantity; float revenue; } Sale;

static Item items[MAX_ITEMS] = {
    {1, "Milk", PACKAGED, 30.0f, 8, {.packaged = {{20, 11, 2026}}}},
    {2, "Sandwich", COOKED, 55.0f, 5, {.cooked = {9, 30}}},
    {3, "Meal Combo", COMBO, 100.0f, 3, {.combo = {{1, 2, 0}, 2}}}
};
static Sale sales[MAX_SALES];
static int sale_count = 0;

static int date_value(Date d) { return d.year * 10000 + d.month * 100 + d.day; }

Item *find_item(int id)
{
    for (int i = 0; i < MAX_ITEMS; ++i)
        if (items[i].id == id) return &items[i];
    return NULL;
}

int record_sale(int id, int quantity)
{
    Item *it = find_item(id);
    if (it == NULL || quantity <= 0 || quantity > it->stock || sale_count >= MAX_SALES)
        return 0;
    it->stock -= quantity;
    sales[sale_count++] = (Sale){id, quantity, it->price * quantity};
    return 1;
}

void expiry_warning(Date today)
{
    for (int i = 0; i < MAX_ITEMS; ++i) {
        if (items[i].kind == PACKAGED) {
            Date e = items[i].detail.packaged.expiry;
            int days = date_value(e) - date_value(today);
            if (days >= 0 && days <= 2)
                printf("EXPIRY WARNING: %s expires on %02d/%02d/%04d\n",
                       items[i].name, e.day, e.month, e.year);
        }
    }
}

void print_revenue_summary(void)
{
    Sale copy[MAX_SALES];
    for (int i = 0; i < sale_count; ++i) copy[i] = sales[i];
    for (int i = 0; i < sale_count - 1; ++i) {
        int best = i;
        for (int j = i + 1; j < sale_count; ++j)
            if (copy[j].revenue > copy[best].revenue) best = j;
        if (best != i) { Sale t = copy[i]; copy[i] = copy[best]; copy[best] = t; }
    }
    printf("Revenue summary (descending):\n");
    for (int i = 0; i < sale_count; ++i) {
        Item *it = find_item(copy[i].item_id);
        printf("%s qty=%d revenue=%.2f\n", it ? it->name : "Unknown",
               copy[i].quantity, copy[i].revenue);
    }
}

int main(void)
{
    Date today = {19, 11, 2026};
    printf("Normal sale: %s\n", record_sale(1, 2) ? "accepted" : "rejected");
    printf("Excess-stock sale: %s\n", record_sale(2, 99) ? "accepted" : "rejected");
    printf("Cooked-item sale: %s\n", record_sale(2, 1) ? "accepted" : "rejected");
    printf("Combo sale: %s\n", record_sale(3, 1) ? "accepted" : "rejected");
    expiry_warning(today);
    print_revenue_summary();
    printf("Milk stock remaining: %d\n", find_item(1)->stock);
    return 0;
}
