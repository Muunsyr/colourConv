#include <iostream>
#include <string>
#include <stdio.h>
#include "colourConverter.h"

#define TEST_VALS 7
#define ERROR_MARGIN 0.01
using namespace std;

bool sameColour(float *, float *);
void diag(float*);

int main()
{
    bool pass = true; // Used to detect failures and print diagnostics
    float h = 0.0, c = 0.75, l = 0.5;
    float rgb[3] = {0, 0, 0}; // Result var
    float expected[3] = {0, 0, 0};

    float testHues[TEST_VALS] = {0.0, 0.0, 0.0, 0.0, 30.0, 75.0, 120.0};
    float testChromas[TEST_VALS] = {1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0};
    float testSats[TEST_VALS] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0};
    float testLumas[TEST_VALS] = {0.3, 0.0, 0.5, 1.0, 0.595, 0.815, 0.59};
    float testHPrimes[TEST_VALS] = {0.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.5};

    float expectedReds[TEST_VALS] = {1.0, 0.0, 0.5, 1.0, 1.0, 0.75, 0.0};
    float expectedGreens[TEST_VALS] = {0.0, 0.0, 0.5, 1.0, 0.5, 1.0, 1.0};
    float expectedBlues[TEST_VALS] = {0.0, 0.0, 0.5, 1.0, 0.0, 0.0, 0.0};
    float expectedMinorComp[TEST_VALS] = {0.0, 0.0, 0.0, 0.0, 0.5, 1.0, 0.5};

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
            printf("FAIL - HCL to RGB conversion.\n");
            printf("Hue: %f Expected:\n", testHues[i]);
            diag(expected);
            printf("Actual:\n");
            pass = false;
            break;
        }

        // Ensure values are in correct range
        for (int i = 0; i < 3; i++) {
            if (rgb[i] < -0.000001 || rgb[i] > 1.000001) {
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
        printf("SUCCESS!\n");
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
        float diff = expected[i] - actual[i];
        if (diff < 0.0)
            diff *= -1;

        if (diff > ERROR_MARGIN) {
            result = false;
            break;
        }
    }
    return result;
}

void diag(float *rgb) {
    // Transform to ints with appropriate rounding.
    int r, g, b;
    r = int(rgb[0]*255);
    g = int(rgb[1]*255);
    b = int(rgb[2]*255);

    if (rgb[0] - r >= 0.5)
        r++;
    if (rgb[1] - g >= 0.5)
        g++;
    if (rgb[2] - b >= 0.5)
        b++;

    printf("Red: %d\n", r);
    printf("Green: %d\n", g);
    printf("Blue: %d\n", b);
}
