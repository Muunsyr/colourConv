#include <iostream>
#include <string>
#include <stdio.h>

#include "colourConverter.h"
using namespace std;

void diag(float*);
int main()
{
    float h = 0.0, c = 0.75, l = 0.5;
    float rgb[3] = {0, 0, 0};
    
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
        if (rgb[i] < 0 || rgb[i] > 1) {
            printf("FAIL - outside range [0, 255]\n");
            diag(rgb);
            break;
        }
    }

    return 0;
}

void diag(float *rgb) {
    printf("Red: %d\n", int(rgb[0]*255));
    printf("Green: %d\n", int(rgb[1]*255));
    printf("Blue: %d\n", int(rgb[2]*255));
}
