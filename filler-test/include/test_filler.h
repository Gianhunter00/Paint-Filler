#pragma once

#include "clove.h"
#include "filler.h"
#include <string.h>
#include <stdio.h>
#include "stb_image.h"
#include "test-utils.h"

CLOVE_TEST(Filler_RedSquare16x16)
{
    char *source = concat_path(CLOVE_EXEC_BASE_PATH, "\\resources\\red-square-16x16.png");
    char *dest = concat_path(CLOVE_EXEC_BASE_PATH, "\\resources\\test16x16.png");
    filler_color_t new_color = {0, 255, 0};
    filler_execute(dest, source, 0, 0, new_color);
    int result_width, result_height, result_channels;
    int source_width, source_height, source_channels;
    unsigned char *result_file = stbi_load(dest, &result_width, &result_height, &result_channels, 0);
    unsigned char *source_file = stbi_load(source, &source_width, &source_height, &source_channels, 0);
    // Check all destination image.
    CLOVE_IS_TRUE(result_width == source_width);
    CLOVE_IS_TRUE(result_height == source_height);
    CLOVE_IS_TRUE(result_channels == source_channels);
    for (size_t i = 0; i < strlen((char *)result_file); i++)
    {
        CLOVE_IS_TRUE(0 == result_file[(i * result_channels)]);
        CLOVE_IS_TRUE(255 == result_file[(i * result_channels) + 1]);
        CLOVE_IS_TRUE(0 == result_file[(i * result_channels) + 2]);
    }

    free(dest);
    free(source);
}