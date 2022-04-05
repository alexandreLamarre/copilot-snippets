#include <cstdlib>
#include <iostream>

struct RGB
{
    int r;
    int g;
    int b;
};

struct Image
{
    int width;
    int height;
    RGB *pixels;
};

// Takes an image and flips it vertically
void flip_vertical(Image *image)
{
    int i, j;
    RGB temp;

    for (i = 0; i < image->height / 2; i++)
    {
        for (j = 0; j < image->width; j++)
        {
            temp = image->pixels[i * image->width + j];
            image->pixels[i * image->width + j] = image->pixels[(image->height - i - 1) * image->width + j];
            image->pixels[(image->height - i - 1) * image->width + j] = temp;
        }
    }
}

// Creates a new random image
Image *create_image(int width, int height)
{
    Image *image = (Image *)malloc(sizeof(Image));
    image->width = width;
    image->height = height;
    image->pixels = (RGB *)malloc(sizeof(RGB) * width * height);

    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image->pixels[i * width + j].r = rand() % 256;
            image->pixels[i * width + j].g = rand() % 256;
            image->pixels[i * width + j].b = rand() % 256;
        }
    }

    return image;
}

// Print the image to the console
void print_image(Image *image)
{
    int i, j;
    for (i = 0; i < image->height; i++)
    {
        for (j = 0; j < image->width; j++)
        {
            printf("%3d %3d %3d ", image->pixels[i * image->width + j].r, image->pixels[i * image->width + j].g, image->pixels[i * image->width + j].b);
        }
        printf("\n");
    }
}

// do vectorized addition on two images
void add_images(Image *image1, Image *image2)
{
    int i, j;
    for (i = 0; i < image1->height; i++)
    {
        for (j = 0; j < image1->width; j++)
        {
            image1->pixels[i * image1->width + j].r += image2->pixels[i * image2->width + j].r;
            image1->pixels[i * image1->width + j].g += image2->pixels[i * image2->width + j].g;
            image1->pixels[i * image1->width + j].b += image2->pixels[i * image2->width + j].b;
        }
    }
}

// python bindings for the above functions
extern "C"
{
    Image *create_image_py(int width, int height)
    {
        return create_image(width, height);
    }

    void flip_vertical_py(Image *image)
    {
        flip_vertical(image);
    }

    void print_image_py(Image *image)
    {
        print_image(image);
    }

    void add_images_py(Image *image1, Image *image2)
    {
        add_images(image1, image2);
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    Image *image = create_image(10, 10);
    print_image(image);
    std::cout << "\n";
    flip_vertical(image);
    print_image(image);
    return 0;
}