#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"

void formatFrequencies(char* buf, size_t bufsize, int* frequencies, size_t nCpus) {
    int less(const void* v1, const void* v2) {
        const int* p1 = v1;
        const int* p2 = v2;
        return *p2 - *p1;
    }

    void sameFrequency(int f) {
        sprintf(buf, "%.1f GHz", f * 1e-6);
    }

    char* superscript(int n) {
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

    int getMultiplicity(int* f, int max) {
        int r = 1;

        while (f[0] == f[r] && r < max) {
            ++r;
        }

        return r;
    }

    qsort(frequencies, nCpus, sizeof(int), less);

    if (frequencies[0] == frequencies[nCpus - 1]) {
        sameFrequency(frequencies[0]);
    } else {
        int i = 0;
        char* pos = buf;

        buf[0] = 0;

        while (i < nCpus) {
            int mult = getMultiplicity(frequencies + i, nCpus - i);
            int remaining = bufsize - (pos - buf);
            int required = snprintf(pos,
                                    remaining,
                                    "%.1f%s",
                                    frequencies[i] * 1e-6, superscript(mult));

            i += mult;

            if (remaining <= required) {
                pos[0] = 0;
                return;
            } else {
                pos += required;
            }
        }
    }
}
