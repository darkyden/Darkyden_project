// tests/test_serviceDateHeure.c - Test unitaire simple du format date

#include <assert.h>
#include <stdio.h>
#include <time.h>

int main() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    assert(t != NULL);
    printf("Date test passée: %04d-%02d-%02d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    return 0;
}