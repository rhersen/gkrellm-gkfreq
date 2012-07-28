#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void formatFrequencies(char* info, int* freq, int count) {
    int less(const void* v1, const void* v2) {
        const int* p1 = v1;
        const int* p2 = v2;
        return *p2 - *p1;
    }

    void sameFrequency(int f) {
        sprintf(info, "%.1f GHz", f * 1e-6);
    }

    void oneDifferent(int one, int rest) {
        sprintf(info, "%.1f¹%.1f³", one * 1e-6, rest * 1e-6);
    }

    char* multiplicity(int n) {
        if (n == 1) {
            return "¹";
        }

        if (n == 2) {
            return "²";
        }

        if (n == 3) {
            return "³";
        }

        return "¨";
    }

    int getMultiplicity(int* f) {
        int r = 1;

        while (f[0] == f[r]) {
            ++r;
        }

        return r;
    }

    qsort(freq, count, sizeof(int), less);

    if (freq[0] == freq[count - 1]) {
        sameFrequency(freq[0]);
    } else {
        int i = 0;
        info[0] = 0;

        while (i < count) {
            if (freq[i]) {
                int mult = getMultiplicity(freq + i);
                sprintf(info + strlen(info),
                        "%.1f%s",
                        freq[i] * 1e-6, multiplicity(mult));
                i += mult;
            }
        }
    }
}
