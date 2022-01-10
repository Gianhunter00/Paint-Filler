#include "hello.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "stb_image_write.h"

#include "filler.h"

int main(int argc, char *argv[])
{
    // char* file_name = ".\\bin\\resources\\red-square-16x16.png";
    // char *file_name = ".\\bin\\resources\\red-square-2048x2048copy.png";
    char *file_name = ".\\bin\\resources\\red-square-4-1280x720.png";
    int width, height, channels;
    unsigned char *data = stbi_load(file_name, &width, &height, &channels, 0);

    printf("width: %d, height: %d, channels: %d\n", width, height, channels);
    int size = width * height * channels;
    printf("size: %d\n", size);

    printf("pixel0: %d, %d, %d, %d\n", (int)data[0], (int)data[1], (int)data[2],(int)data[3]);
    stbi_image_free(data);


    //stbi_write_png(output_filename, width, height, channels, data, 0);

    /*
        Input:
            - filename_input
            - pixel coordinates
            - new color
            - filename_output
            OPTIONAL
            - file output type (* nice to have)
            - save in place (* nice to have)
     */

    filler_color_t green = {0, 255, 0, 0};
    filler_color_t blu = {0, 0, 255, 0};
    filler_color_t channels2 = {128, 128, 0, 0};
    filler_color_t random2 = {43, 164, 35, 0};
    filler_color_t channels4 = {134, 56, 245, 134};

    filler_execute(".\\bin\\result\\destination-3-16x16.png", ".\\bin\\resources\\red-square-3-16x16.png", 8, 8, green);
    filler_execute(".\\bin\\result\\destination-3-64x64.jpg", ".\\bin\\resources\\red-square-3-64x64.jpg", 24, 32, blu);
    filler_execute(".\\bin\\result\\destination-2-640x640.png", ".\\bin\\resources\\red-square-2-640x640.png", 13, 15, channels2);
    filler_execute(".\\bin\\result\\destination-3-2048x2048.png", ".\\bin\\resources\\red-square-3-2048x2048.png", 100, 100, random2);
    filler_execute(".\\bin\\result\\destination-4-1280x720.png", ".\\bin\\resources\\red-square-4-1280x720.png", 640, 500, channels4);

    return 0;
}