#include "canvasimg.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct
{
    uint8 red;
    uint8 green;
    uint8 blue;
} RGB_t;

/* Library internal global-variables */
static FILE *fileDestiny; /* Pointer to output file */
static uint8 *pixelIsUsed_ptr; /* Pointer to table of used pixels */
static RGB_t *colorTable_ptr; /* Pointer to table of pixel colors */
static uint32 widthGlobal, heightGlobal; /* Image sizes */
static uint8 colorfulGlobal; /* if(1) image is colorful */
static double zoomGlobal; /* Proportionately multiplies the parameters width and height for zoom */

/* Library internal functions */
static void printHTML_BEGIN(void);
static void printHTML_END(void);


void *canimg_init(uint32 width, uint32 height, double zoom, uint8 colorful)
{
    /* Send local variables for global use */
    widthGlobal    = width;
    heightGlobal   = height;
    zoomGlobal     = zoom;
    colorfulGlobal = colorful;

    /* Allocate memory to know which pixel is used, with 0 */
    pixelIsUsed_ptr = calloc((uint32) ceil(width * height / 8.0), sizeof(uint8));

    /* Allocate memory for pixel's color */
    if(colorful) colorTable_ptr = calloc(width * height, sizeof(RGB_t));

    return (void *) 0;
} /* canimg_init */


void *canimg_close(char *file)
{
    uint32 counter_x, counter_y;

    /* Open the file */
    if((fileDestiny = fopen(file, "wb")) == NULL)
    {
        fprintf(stderr, "Unable to open the file: %s\n", file);
        return (void *) 1;
    }

    /* Print beginning HTML sequence */
    printHTML_BEGIN();

    /* Print image to file */
    for(counter_y = 0; counter_y < heightGlobal; counter_y++)
    {
        for(counter_x = 0; counter_x < widthGlobal ;counter_x++)
        {
            /* If pixel is used, draw it */
            if(pixelIsUsed_ptr[(uint32) floor((counter_x + widthGlobal * counter_y) / 8.0)]   &   (1 << (7 - ((counter_x + widthGlobal * counter_y) % 8))))
            {
                if(colorfulGlobal)
                {
                    fprintf(fileDestiny, "c(%d,%d,%d,%d,%d);", counter_x, counter_y,
                            colorTable_ptr[counter_x + widthGlobal * counter_y].red,
                            colorTable_ptr[counter_x + widthGlobal * counter_y].green,
                            colorTable_ptr[counter_x + widthGlobal * counter_y].blue);
                } else {
                    fprintf(fileDestiny, "b(%d,%d);", counter_x, counter_y);
                }
            }
        }
    }

    /* Print closing HTML sequence */
    printHTML_END();

    /* Close file */
    if(fclose(fileDestiny) == EOF)
    {
        fprintf(stderr, "Unable to close the file\n");
        return (void *) 1;
    }

    /* Free memory */
    free(pixelIsUsed_ptr);
    if(colorfulGlobal) free(colorTable_ptr);

    return (void *) 0;
} /* canimg_close */


void canimg_setpx(uint32 x, uint32 y, uint8 red, uint8 green, uint8 blue)
{
    /* Set pixel */
    pixelIsUsed_ptr[(uint32) floor((x + widthGlobal * y) / 8.0)] |= (1 << (7 - ((x + widthGlobal * y) % 8)));

    /* Set color */
    if(colorfulGlobal)
    {
        colorTable_ptr[x + widthGlobal * y].red = red;
        colorTable_ptr[x + widthGlobal * y].green = green;
        colorTable_ptr[x + widthGlobal * y].blue = blue;
    }
} /* canimg_setpx */


/***** HTML DATA *****/
static void printHTML_BEGIN(void)
{
    uint32 zoom_width  = round(widthGlobal  * zoomGlobal);
    uint32 zoom_height = round(heightGlobal * zoomGlobal);

    fprintf(fileDestiny,
            "<!DOCTYPE html>\n"
                    "<!-- Automatically generated file by [HTML5 Canvas Image for C] -->\n"
                    "<!-- Program autor: Michal Kozakiewicz, github.com/michal037 -->\n"
                    "<html>\n"
                    "\t<head>\n"
                    "\t\t<meta charset=\"UTF-8\">\n"
                    "\t\t<title>Canvas Image</title>\n"
                    "\t\t<style type=\"text/css\">\n"
                    "\t\t\tbody\n"
                    "\t\t\t{\n"
                    "\t\t\t\tbackground-color: %s;\n"
                    "\t\t\t}\n"
                    "\n"
                    "\t\t\tcanvas#canvas_img\n"
                    "\t\t\t{\n"
                    "\t\t\t\twidth: %dpx;\n"
                    "\t\t\t\theight: %dpx;\n"
                    "\t\t\t\tborder: 2px solid %s;\n"
                    "\t\t\t\tbackground-color: %s;\t\n"
                    "\t\t\t\tdisplay: block;\n"
                    "\t\t\t\tmargin-left: auto;\n"
                    "\t\t\t\tmargin-right: auto;\n"
                    "\t\t\t\timage-rendering: optimizeSpeed;\n"
                    "\t\t\t\timage-rendering: -moz-crisp-edges;\n"
                    "\t\t\t\timage-rendering: -webkit-optimize-contrast;\n"
                    "\t\t\t\timage-rendering: optimize-contrast;\n"
                    "\t\t\t\timage-rendering: pixelated;\n"
                    "\t\t\t\t-ms-interpolation-mode: nearest-neighbor;\n"
                    "\t\t\t}\n"
                    "\t\t</style>\n"
                    "\t</head>\n"
                    "\t<body>\n"
                    "\t\t<canvas id=\"canvas_img\" width=\"%d\" height=\"%d\">No support for HTML5 canvas.</canvas>\n"
                    "\t\t<script>\n"
                    "\t\t\tvar canvas = document.getElementById(\"canvas_img\");\n"
                    "\t\t\tvar canvasWidth = canvas.width;\n"
                    "\t\t\tvar canvasHeight = canvas.height;\n"
                    "\t\t\tvar ctx = canvas.getContext(\"2d\");\n"
                    "\t\t\tvar canvasData = ctx.getImageData(0, 0, canvasWidth, canvasHeight);\n"
                    "\n"
                    "\t\t\tfunction c(x, y, r, g, b) /* draw a colored pixel */\n"
                    "\t\t\t{\n"
                    "\t\t\t\tvar index = (x + y * canvasWidth) * 4;\n"
                    "\t\t\t\tcanvasData.data[index + 0] = r;\n"
                    "\t\t\t\tcanvasData.data[index + 1] = g;\n"
                    "\t\t\t\tcanvasData.data[index + 2] = b;\n"
                    "\t\t\t\tcanvasData.data[index + 3] = 255;\n"
                    "\t\t\t}\n"
                    "\t\t\tfunction b(x, y) /* draw a black pixel */\n"
                    "\t\t\t{\n"
                    "\t\t\t\tvar index = (x + y * canvasWidth) * 4;\n"
                    "\t\t\t\tcanvasData.data[index + 0] = 0;\n"
                    "\t\t\t\tcanvasData.data[index + 1] = 0;\n"
                    "\t\t\t\tcanvasData.data[index + 2] = 0;\n"
                    "\t\t\t\tcanvasData.data[index + 3] = 255;\n"
                    "\t\t\t}\n"
                    "\t\t\tfunction updateCanvas()\n"
                    "\t\t\t{\n"
                    "\t\t\t\tctx.putImageData(canvasData, 0, 0);\n"
                    "\t\t\t}\n"
                    "\t\t\t\n"
                    "\t\t\t/* Canvas Image Begin */\n\t\t\t", HTML_BACKGROUND_COLOR,
            zoom_width, zoom_height, CANVAS_BORDER_COLOR, CANVAS_BACKGROUND_COLOR,
            widthGlobal, heightGlobal);
} /* printHTML_BEGIN */


static void printHTML_END(void)
{
    fprintf(fileDestiny,
            "\n\t\t\t/* Canvas Image End */\n"
                    "\n"
                    "\t\t\tupdateCanvas();\n"
                    "\t\t</script>\n"
                    "\t</body>\n"
                    "</html>\n");
} /* printHTML_END */
/***** HTML DATA END *****/
