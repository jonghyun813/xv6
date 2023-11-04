#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    int d = clone();
    printf(1, "%d\n", d);
    exit();
}