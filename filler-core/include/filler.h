#pragma once
#include <stdint.h>

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} filler_color_t;

typedef enum error_type
{
    out_of_bounds,
    channels_number_out_of_bounds,
    same_color,
    LAST
} error_type_e;

/*
 * This function will apply paint filler algorithm, creating a new image filled with the new color
 * 
 * @param dest_path New image path
 * @param source_path Source image path
 * @param pixel_x X position of the pixel to replace with new color
 * @param pixel_y Y position of the pixel to replace with new color
 * @param new_color The new color to be used for filling
 */
void filler_execute(const char *dest_path, const char *source_path, int pixel_x, int pixel_y, filler_color_t new_color);

/*
 * This function will apply paint filler algorithm to the current image, you need to use stbi_write_png and then free the data with stbi_image_free
 * 
 * @param source_data Image data
 * @param width Image width
 * @param width Image height
 * @param channels channels number
 * @param pixel_x X position of the pixel to start replacing with the new color
 * @param pixel_y Y position of the pixel to start replacing with the new color
 * @param new_color The new color to be used for filling
 */
error_type_e filler_algo_execute(uint8_t *source_data, int width, int height, int channels, int pixel_x, int pixel_y, filler_color_t new_color);