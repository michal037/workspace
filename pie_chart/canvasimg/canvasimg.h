#include "tsimple.h"

#ifndef CANVASIMAGE_CANVASIMG_H
#define CANVASIMAGE_CANVASIMG_H

/* HTML5 Canvas Image for C, Library */


/* Optional Configuration */
#define HTML_BACKGROUND_COLOR "#252525"
#define CANVAS_BORDER_COLOR "#d0d0d0"
#define CANVAS_BACKGROUND_COLOR "#FFFFFF"
/* Optional Configuration end */


/*
 * This function initiates library for canvas image.
 *
 * Parameters:
 *   - uint32 width      : The width of the image [px].
 *   - uint32 height     : The height of the image [px].
 *   - double zoom    : Proportionately multiplies the parameters width and height for zoom.
 *   - uint8 colorful : if(1) use colors, if(0) image is black-and-white.
 *
 * Function return (optional):
 *   - 0 if all is OK or 1 if error occurs.
 */
void *canimg_init(uint32 width, uint32 height, double zoom, uint8 colorful);


/*
 * Write data and closing sequence to the file.
 *
 * Parameters:
 *   - char *file     : Path to file, where image will be saved.
 *
 * Function return (optional):
 *   - 0 if all is OK or 1 if error occurs.
 */
void *canimg_close(char *file);


/*
 * Draw a pixel on canvas image.
 * If 'colorful' variable from 'canimg_init' function is 0,
 * you don't have to use 'red', 'green' and 'blue' variable to define color.
 * Because color is always black.
 *
 * Parameters:
 *   - uint32 x       : x position.
 *   - uint32 y       : y position.
 *   - uint8 red   : color from 0 to 255;
 *   - uint8 green : color from 0 to 255;
 *   - uint8 blue  : color from 0 to 255;
 */
void canimg_setpx(uint32 x, uint32 y, uint8 red, uint8 green, uint8 blue);


#endif //CANVASIMAGE_CANVASIMG_H
