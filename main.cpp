#include <iostream>
#include <string>
#include <stdio.h>

#include "colourConverter.h"
using namespace std;

void diag(int*);
int main()
{
    float h = 0.0, c = 0.75, l = 0.5;
    int rgb[3] = {0, 0, 0};
    
    colourConverter::hcl_to_rgb(h, c, l, rgb);
    
    // smoke test, ensure rgb is modified.
    if (rgb[0] == 0) {
        printf("FAIL - values not modified.\n");
    }

    // Test minor component
    int numTests = 4;
    colourConverter cc;
    float testHPrimes[4] = {0.0, 0.5, 1.0, 1.5};
    float testChromas[4] = {1.0, 1.0, 1.0, 1.0};
    float expectedResults[4] = {0.0, 0.5, 1.0, 0.5};
    float actualResult;
    for (int i = 0; i < numTests; i++) {
        actualResult = cc.minorComponent(testHPrimes[i], testChromas[i]);
        if (expectedResults[i] != actualResult) {
            printf("FAIL - Expected MC: %f, actual MC: %f\n",
                expectedResults[i], actualResult);
                break;
        }
    }

    // Ensure values are in correct range
    for (int i = 0; i < 3; i++) {
        if (rgb[i] < 0 || rgb[i] > 255) {
            printf("FAIL - outside range [0, 255]\n");
            diag(rgb);
            break;
        }
    }

    return 0;
}

void diag(int *rgb) {
    printf("Red: %d\n", rgb[0]);
    printf("Green: %d\n", rgb[1]);
    printf("Blue: %d\n", rgb[2]);
}
