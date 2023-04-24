#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>


const char* ASCII = " .:;+=xX$&";
// int ASCII_LEN_MINUS_ONE = (sizeof(ASCII) / sizeof(*ASCII)) - 1; Gives pointer size rather than array size
const size_t ASCII_LEN_MINUS_ONE = 9;

const size_t WIDTH = 50;
const size_t HEIGHT = 35;

const float RE_START = -2.0;
const float RE_END = 1.0;
const float IM_START = -1.0;
const float IM_END = 1.0;

const uint8_t MAX_ITERS = 50;

int main()
{
    std::vector<uint8_t> iters;

    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            float real = (((float)x / (float)WIDTH) * (RE_END - RE_START)) + RE_START;
            float imaginary = (((float)y / (float)HEIGHT) * (IM_END - IM_START)) + IM_START;

            float re = 0.0;
            float im = 0.0;
            uint8_t iter = 0;

            while (re * re + im * im < 4.0 && iter < MAX_ITERS) {
                re = re * re - im * im + real;
                im = re * im + re * im + imaginary;
                iter++;
            }

            iters.push_back(iter);
        }
    }


    uint8_t max = 0, min = MAX_ITERS;
    for (uint8_t iter : iters) {
        if (iter < MAX_ITERS && iter > max) {
            max = iter;
        }
        else if (iter < min) {
            min = iter;
        }
    }
    float diff = (float)(max - min);

    std::string s = "";
    size_t row_pos = 0;
    for (uint8_t iter : iters) {
        if (iter == MAX_ITERS) {
            s += ASCII[ASCII_LEN_MINUS_ONE];
        }
        else {
            uint8_t mapped = iter - min;
            float pos = (float)mapped / diff;
            s += ASCII[(size_t)(pos * (float)ASCII_LEN_MINUS_ONE)];
        }

        row_pos++;
        if (row_pos == WIDTH) {
            row_pos = 0;
            s += '\n';
        }
    }

    printf("%s", s.c_str());

}
