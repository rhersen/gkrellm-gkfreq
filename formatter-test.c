#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define assertEqualsI(a,e) _assertEqualsI(a,e,__FILE__,__LINE__)

static void _assertEqualsI(int actual, int expected, char *file, int line) {
    if (actual == expected) {
        printf("%s:%d:\033[0;32m %d OK\033[0m\n", file, line, actual);
    } else {
        printf("%s:%d:\033[0;31m expected %d but got %d\033[0m\n",
               file, line, expected, actual);
    }
}

#define assertEqualsD(a,e,d) _assertEqualsD(a,e,d,__FILE__,__LINE__)

static void _assertEqualsD(double actual, double expected, double delta, char *file, int line) {
    double diff = actual > expected ? actual - expected : expected - actual;
    if (diff < delta) {
        printf("%s:%d:\033[0;32m %f OK\033[0m\n", file, line, actual);
    } else {
        printf("%s:%d:\033[0;31m expected %f but got %f\033[0m\n",
               file, line, expected, actual);
    }
}

#define assertEqualsS(a,e) _assertEqualsS(a,e,__FILE__,__LINE__)

static void _assertEqualsS(char* actual, char* expected, char *file, int line) {
    if (strcmp(actual, expected) == 0) {
        printf("%s:%d:\033[0;32m '%s' OK\033[0m\n", file, line, actual);
    } else {
        printf("%s:%d:\033[0;31m expected '%s' but got '%s'\033[0m\n",
               file, line, expected, actual);
    }
}

#define assertFalse(a) _assertTrue(!(a),__FILE__,__LINE__)
#define assertTrue(a) _assertTrue((a),__FILE__,__LINE__)

static void _assertTrue(int actual, char *file, int line) {
    if (actual) {
        printf("%s:%d:\033[0;32m %d OK\033[0m\n", file, line, actual);
    } else {
        printf("%s:%d:\033[0;31m got %d\033[0m\n", file, line, actual);
    }
}

static double getElapsedSecondsSince(struct timeval* start) {
    struct timeval now;
    gettimeofday(&now, 0);
    int usec = now.tv_usec - start->tv_usec;
    int sec = now.tv_sec - start->tv_sec;

    return usec * 1e-6 + sec;
}

#include "formatter.h"

int main(void) {
    struct timeval start;
    gettimeofday(&start, 0);

    char result[32];

    {
        int frequencies[8] = { 1000000, 800000, 1400000, 1200000 };
        formatFrequencies(result, 32, frequencies, 4);
        assertEqualsS(result, "1.4¹1.2¹1.0¹0.8¹");
    }

    {
        int frequencies[8] = { 800000, 800000, 800000, 800000 };
        formatFrequencies(result, 32, frequencies, 4);
        assertEqualsS(result, "0.8 GHz");
    }

    {
        int frequencies[8] = { 1400000, 800000, 800000, 800000 };
        formatFrequencies(result, 32, frequencies, 4);
        assertEqualsS(result, "1.4¹0.8³");
    }

    {
        int frequencies[8] = { 1400000, 1400000, 800000, 800000 };
        formatFrequencies(result, 32, frequencies, 4);
        assertEqualsS(result, "1.4²0.8²");
    }

    {
        int frequencies[8] = { 1400000, 1400000, 800000, 800000, 800000 };
        formatFrequencies(result, 32, frequencies, 4);
        assertEqualsS(result, "1.4²0.8²");
    }

    {
        int frequencies[8] = { 1000000, 800000, 1400000, 1200000 };
        formatFrequencies(result, 3, frequencies, 4);
        assertEqualsS(result, "");
    }

    {
        int frequencies[8] = { 1000000, 800000, 1400000, 1200000 };
        formatFrequencies(result, 7, frequencies, 4);
        assertEqualsS(result, "1.4¹");
    }

    {
        int frequencies[8] = { 1000000, 800000, 1400000, 1200000 };
        formatFrequencies(result, 11, frequencies, 4);
        assertEqualsS(result, "1.4¹1.2¹");
    }

    printf("%f seconds\n", getElapsedSecondsSince(&start));

    return 0;
}
