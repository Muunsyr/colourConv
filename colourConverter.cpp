#include "colourConverter.h"
#include <math.h>
#include <iostream>

void colourConverter::hsl_to_rgb(float hue, float saturation, float lightness, int * rgb_array)
{
    float hprime = 0.0;
    float chroma = 0.0;
    float x = 0.0; // working/swap variable
    float rprime = 0.0, gprime = 0.0, bprime = 0.0;
    int sector = 0;
    
    // calculate chroma
    chroma = (1- (fabs(2*lightness-1)) * saturation);
    // calculate sector in colour space
    hprime = checkedHue(hue);
    hprime /= 60.0;
    while (sector <= hprime) {
        sector++;
    }
    
    x = minorComponent(hprime, chroma);

    // assign partial values based on sector
    switch (sector) {
    case 1:
        rprime = chroma;
        gprime = x;
        break;
    case 2:
        rprime = x;
        gprime = chroma;
        break;
    case 3:
        gprime = chroma;
        bprime = x;
        break;
    case 4:
        gprime = x;
        bprime = chroma;
        break;
    case 5:
        bprime = chroma;
        rprime = x;
        break;
    case 6:
        bprime = x;
        rprime = chroma;
        break;
  }

  // Calculate luma difference
  x = lightness - 0.5 * chroma;
  
  rgb_array[0] = (rprime + x) * 255;
  rgb_array[1] = (gprime + x) * 255;
  rgb_array[2] = (bprime + x) * 255;
}

void colourConverter::hcl_to_rgb(float hue, float chroma, float luma, int * rgb_array)
{
    float hprime = 0.0;
    float x = 0.0; // working/swap variable
    float rprime = 0.0, gprime = 0.0, bprime = 0.0;
    int sector = 0;
    
    // calculate sector in colour space
    hprime = checkedHue(hue);
    hprime /= 60.0;
    while (sector <= hprime) {
        sector++;
    }
    
    x = minorComponent(hprime, chroma); 

    // assign partial values based on sector
    switch (sector) {
    case 1:
        rprime = chroma;
        gprime = x;
        break;
    case 2:
        rprime = x;
        gprime = chroma;
        break;
    case 3:
        gprime = chroma;
        bprime = x;
        break;
    case 4:
        gprime = x;
        bprime = chroma;
        break;
    case 5:
        bprime = chroma;
        rprime = x;
        break;
    case 6:
        bprime = x;
        rprime = chroma;
        break;
  }

  // Calculate luma difference
  x = luma - (LUMA_R_COEFF*rprime + LUMA_G_COEFF*gprime + LUMA_B_COEFF*bprime);
  
  rgb_array[0] = (rprime + x) * 255;
  rgb_array[1] = (gprime + x) * 255;
  rgb_array[2] = (bprime + x) * 255;
}

/**
 * @brief Caluculates a hues minor component value. Assumes hprime is
 * in range[0, 6)
 * @param hprime Hue modulo 60. 
 * @param chroma Chroma, needed to determine magnitude
 * @return minor component of colour before luma calc.
 */
float colourConverter::minorComponent(float hprime, float chroma) {
    float minor = fmod(hprime, 2.0);
    minor -= 1;
    minor = fabs(minor);
    minor = 1 - minor;
    minor *= chroma;
    return minor;
}

/**
 * @brief Ensures that a given hue value is within the range [0.0, 360)
 * @param hue A hue value, in or out of the range.
 * @return An equivalent hue value within the range.
 */
float colourConverter::checkedHue(float hue) {
    float checkedHue = hue;
    while (checkedHue >= 360.0) {
        checkedHue -= 360.0;
    }
    while (checkedHue < 0.0) {
        checkedHue += 360.0;
    }
    return checkedHue;
}
