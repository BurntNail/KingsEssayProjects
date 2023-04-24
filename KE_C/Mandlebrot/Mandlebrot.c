#include <stdio.h>
#include <stdlib.h>

const char *ASCII = " .:;+=xX$&";
const int ASCII_LEN_MINUS_ONE = 9;

const int WIDTH = 500;
const int HEIGHT = 350;

const float RE_START = -2.0;
const float RE_END = 1.0;
const float IM_START = -1.0;
const float IM_END = 1.0;

const int MAX_ITERS = 500;

int main()
{
    int *iters = malloc(sizeof(int) * WIDTH * HEIGHT);
    if (iters == NULL) {
        fprintf(stderr, "Error allocating iterators list.\n");
        return EXIT_FAILURE;
    }

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            float real = (((float)x / (float)WIDTH) * (RE_END - RE_START)) + RE_START;
            float imaginary = (((float)y / (float)HEIGHT) * (IM_END - IM_START)) + IM_START;

            float re = 0.0;
            float im = 0.0;
            int iter = 0;

            while (re * re + im * im < 4.0 && iter < MAX_ITERS)
            {
                re = re * re - im * im + real;
                im = re * im + re * im + imaginary;
                iter++;
            }

            iters[y * WIDTH + x] = iter;
        }
    }

    int max = 0, min = MAX_ITERS;
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        int iter = iters[i];
        if (iter < MAX_ITERS && iter > max)
        {
            max = iter;
        }
        else if (iter < min)
        {
            min = iter;
        }
    }
    float diff = (float)(max - min);

    char *s = malloc(sizeof(char) * (WIDTH + 1) * HEIGHT + 1);
    if (s == NULL) {
        fprintf(stderr, "Error allocating space for the string.\n");
        return EXIT_FAILURE;
    }
    int row_pos = 0;
    int string_i = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        int iter = iters[i];

        if (iter == MAX_ITERS)
        {
            s[string_i] = ASCII[ASCII_LEN_MINUS_ONE];
        }
        else
        {
            int mapped = iter - min;
            float pos = (float)mapped / diff;
            s[string_i] = ASCII[(size_t)(pos * (float)ASCII_LEN_MINUS_ONE)];
        }
        string_i++;

        row_pos++;
        if (row_pos == WIDTH)
        {
            row_pos = 0;
            s[string_i] = '\n';
            string_i++;
        }
    }

    s[string_i] = '\0';

    printf("%s", s);

    free(iters);
    free(s);

    return EXIT_SUCCESS;
}
