#ifndef COLOURCONVERTER_H
#define COLOURCONVERTER_H

#define LUMA_R_COEFF 0.30
#define LUMA_G_COEFF 0.59
#define LUMA_B_COEFF 0.11

class colourConverter
{
public:
    static void hsl_to_rgb(float, float, float, float *);
    static void hcl_to_rgb(float, float, float, float *);
    static float minorComponent(float, float);
private:
    static float checkedHue(float);
};

#endif // COLOURCONVERTER_H
