#include <math.h>
#include "canvasimg/canvasimg.h"

inline double deg2rad(double degree) {return degree * (M_PI/180);}


uint8 circleColorStyle(double angle, uint8 color)
{

    if(angle >= 0.8)
    {
        if(color == 1) return 0;
        if(color == 2) return 190;
        if(color == 3) return 0;
    }
    else if(angle >= 0.45)
    {
        if(color == 1) return 14;
        if(color == 2) return 128;
        if(color == 3) return 193;
    } else if(angle >= 0.15)
    {
        if(color == 1) return 170;
        if(color == 2) return 122;
        if(color == 3) return 44;
    } else
    {
        if(color == 1) return 193;
        if(color == 2) return 26;
        if(color == 3) return 14;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int y, x;
    double angle;
    uint8 circleLineCounter;

    /* Configuration */
        int circleSize = 20;
        int circleShiftX = 20;
        int circleShiftY = 20;
        double circleAngle = 270*0.50;
        double circleAnglePrecision = 0.01;
        double circleShiftAngle = 135;
        uint8 circleLineWidth = 10;
    /* Configuration End */


    canimg_init(100, 100, 1, 1);

    for(angle = 0; angle < circleAngle; angle = angle + circleAnglePrecision)
    {
        for(circleLineCounter = 0; circleLineCounter < circleLineWidth ; circleLineCounter++)
        {
            x = round(cos(deg2rad(angle + circleShiftAngle)) * (circleSize-circleLineCounter)) + circleShiftX;
            y = round(sin(deg2rad(angle + circleShiftAngle)) * (circleSize-circleLineCounter)) + circleShiftY;
            canimg_setpx(x, y, circleColorStyle(angle/270, 1), circleColorStyle(angle/270, 2), circleColorStyle(angle/270, 3));
        }
    }


    canimg_close("test.html");

    return 0;
}
