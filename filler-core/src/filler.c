#include "filler.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdio.h>

void filler_execute(const char *dest_path, const char *source_path, int pixel_x, int pixel_y, filler_color_t new_color)
{
    //1. read image by stbi_load
    int width, height, channels;
    uint8_t *data = stbi_load(source_path, &width, &height, &channels, 0);

    //2. apply filler algorithm (source_data, width, height, channels, pixel_x, pixel_y, new_color)
    filler_algo_execute(data, width, height, channels, pixel_x, pixel_y, new_color);

    //3. write new image in dest_path
    stbi_write_png(dest_path, width, height, channels, data, 0);

    stbi_image_free(data);
}

// void filler_algo_recursive(uint8_t *source_data, int width, int height, int channels, int pixel_x, int pixel_y, filler_color_t new_color, filler_color_t sample_color)
// {
//     if (pixel_y >= height || pixel_y < 0)
//         return;
//     if (pixel_x >= width || pixel_x < 0)
//         return;
//     int current_pixel_index = (pixel_y * width + pixel_x) * channels;
//
//     filler_color_t *current_color = (filler_color_t *)(&source_data[current_pixel_index]);
//     if (current_color->r != sample_color.r)
//         return;
//     if (current_color->g != sample_color.g)
//         return;
//     if (current_color->b != sample_color.b)
//         return;
//     source_data[current_pixel_index + 0] = new_color.r;
//     source_data[current_pixel_index + 1] = new_color.g;
//     source_data[current_pixel_index + 2] = new_color.b;
//
//     filler_algo_recusive(source_data, width, height, channels, pixel_x + 1, pixel_y + 0, new_color, sample_color);
//     filler_algo_recusive(source_data, width, height, channels, pixel_x - 1, pixel_y + 0, new_color, sample_color);
//     filler_algo_recusive(source_data, width, height, channels, pixel_x + 0, pixel_y + 1, new_color, sample_color);
//     filler_algo_recusive(source_data, width, height, channels, pixel_x + 0, pixel_y - 1, new_color, sample_color);
// }

error_type_e filler_algo_iterative(uint8_t *source_data, int width, int height, int channels, int pixel_x, int pixel_y, filler_color_t new_color)
{
    if (pixel_y >= height || pixel_y < 0)
        return out_of_bounds;
    if (pixel_x >= width || pixel_x < 0)
        return out_of_bounds;
    if (channels > 4)
        return channels_number_out_of_bounds;
    size_t pixel_start = pixel_y * width + pixel_x;
    size_t len = ((size_t)width * (size_t)height);
    for (size_t i = pixel_start; i < len; i++)
    {
        for (size_t j = 0; j < channels; j++)
        {
            source_data[i * channels + j] = *(&new_color.r + j);
        }
    }
    return LAST;
}

error_type_e filler_algo_execute(uint8_t *source_data, int width, int height, int channels, int pixel_x, int pixel_y, filler_color_t new_color)
{
    if (pixel_y >= height || pixel_y < 0)
        return out_of_bounds;
    if (pixel_x >= width || pixel_x < 0)
        return out_of_bounds;
    if (channels > 4)
        return channels_number_out_of_bounds;
    //1. Find pixel data as filler_color_t current_color
    int current_pixel_index = (pixel_y * width + pixel_x) * channels;
    //filler_color_t* current_color = (filler_color_t*)(&source_data[current_pixel_index]);

    filler_color_t current_color;
    for (size_t i = 0; i < channels; i++)
    {
        *(&current_color.r + i * sizeof(uint8_t)) = source_data[current_pixel_index + i];
    }
    for (size_t i = channels; i < sizeof(filler_color_t); i++)
    {
        *(&current_color.r + i * sizeof(uint8_t)) = 0;
    }
    //Controllare se il colore non e' gia uguale.
    if (memcmp(&new_color, &current_color, sizeof(filler_color_t)) == 0)
    {
        return same_color;
    }

    //2. Moving CROSS from current pixel until pixel == current_color OR stay within boundaries
    return filler_algo_iterative(source_data, width, height, channels, pixel_x, pixel_y, new_color);
}