#include <iostream>
#include <string>
#include <stdio.h>
#include "colourConverter.h"

#define TEST_VALS 4
using namespace std;

bool sameColour(float *, float *);
void diag(float*);

int main()
{
    bool pass = true; // Used to detect failures and print diagnostics
    float h = 0.0, c = 0.75, l = 0.5;
    float rgb[3] = {0, 0, 0}; // Result var
    float expected[3] = {0, 0, 0};

    float testHues[TEST_VALS] = {0.0, 30.0, 75.0, 120.0};
    float testChromas[TEST_VALS] = {0.0, 1.0, 1.0, 1.0};
    float testSats[TEST_VALS] = {0.0, 1.0, 1.0, 1.0};
    float testLumas[TEST_VALS] = {0.0, 0.25, 0.75, 1.0};
    float testHPrimes[TEST_VALS] = {0.0, 0.5, 1.0, 1.5};

    float expectedReds[TEST_VALS] = {1.0, 0.0, 0.0, 0.0};
    float expectedGreens[TEST_VALS] = {0.0, 0.0, 0.0, 0.0};
    float expectedBlues[TEST_VALS] = {0.0, 0.0, 0.0, 0.0};
    float expectedMinorComp[TEST_VALS] = {0.0, 0.5, 1.0, 0.5};

    colourConverter cc;
    
    colourConverter::hcl_to_rgb(h, c, l, rgb);
    
    // smoke test, ensure rgb is modified.
    if (rgb[0] == 0) {
        printf("FAIL - values not modified.\n");
    }

    for (int i = 0; i < TEST_VALS; i++) {
        // Test minor component
        float actualResult;
        actualResult = cc.minorComponent(testHPrimes[i], 1.0);
        if (expectedMinorComp[i] != actualResult) {
            printf("FAIL - Expected MC: %f, actual MC: %f\n",
                expectedMinorComp[i], actualResult);
            pass = false;
            break;
        }

        // Test conversion from HCL
        cc.hcl_to_rgb(testHues[i], testChromas[i], testLumas[i], rgb);
        expected[0] = expectedReds[i];
        expected[1] = expectedGreens[i];
        expected[2] = expectedBlues[i];
        if (!sameColour(expected, rgb)) {
            printf("FAIL - HCL to RGB conversion. Expected:\n");
            diag(expected);
            printf("Actual:\n");
            pass = false;
            break;
        }

        // Ensure values are in correct range
        for (int i = 0; i < 3; i++) {
            if (rgb[i] < 0 || rgb[i] > 1) {
                printf("FAIL - Comp '%d', outside range [0, 1.0] at %f.\n",
                    i, rgb[i]);
                pass = false;
                break;
            }
        }
        if (!pass) {
            break;
        }
    }

    if (!pass) {
        diag(rgb);
    }

    if (pass) {
        printf("SUCCESS!");
        return 0;
    }

    return 1;
}

/**
 * @brief Compares two float triplets
 * @param expected First float triplet (colour)
 * @param actual Secondi float triplet
 * @return true if triplets are the same, false otherwise
 */
bool sameColour(float *expected, float *actual) {
    float result = true;
    for (int i = 0; i < 3; i++) {
        if (expected[i] != actual[i]) {
            result = false;
            break;
        }
    }
    return result;
}

void diag(float *rgb) {
    printf("Red: %d\n", int(rgb[0]*255));
    printf("Green: %d\n", int(rgb[1]*255));
    printf("Blue: %d\n", int(rgb[2]*255));
}
