#include <iostream>
#include <string>

#include "colourConverter.h"
using namespace std;

int main()
{
    float h = 0.0, c = 0.75, l = 0.5;
    int rgb[3] = {0, 0, 0};
    
    colourConverter::hcl_to_rgb(h, c, l, rgb);
    
    // smoke test, ensure rgb is modified.
    if (rgb[0] == 0) {
        printf("FAIL - values not modified.\n");
    }
        
    // Ensure values are in correct range
    for (int i = 0; i < 3; i++) {
        if (rgb[i] < 0 || rgb[i] > 255) {
            printf("FAIL - outside range [0, 255]\n");
        }
    }
    
    printf("Red: %d\n", rgb[0]);
    printf("Green: %d\n", rgb[1]);
    printf("Blue: %d\n", rgb[2]);
    return 0;
}
