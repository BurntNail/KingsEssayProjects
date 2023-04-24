package com.jackmaguire;

import javax.swing.*;
import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        final char[] ASCII = " .:;+=xX$&".toCharArray();
        final int asciiLenMinusOne = ASCII.length - 1;

        final int WIDTH = 50;
        final int HEIGHT = 35;

        final float RE_START = -2.0f;
        final float RE_END = 1.0f;
        final float IM_START = -1.0f;
        final float IM_END = 1.0f;

        final int MAX_ITERS = 25;

        List<Integer> iters = new ArrayList<>();
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                float real = (((float)x / (float)WIDTH) * (RE_END - RE_START)) + RE_START;
                float imaginary = (((float)y / (float)HEIGHT) * (IM_END - IM_START)) + IM_START;

                float re = 0.0f;
                float im = 0.0f;
                int iter = 0;
                while (re * re + im * im < 4.0 && iter < MAX_ITERS)
                {
                    re = re * re - im * im + real;
                    im = re * im + re * im + imaginary;
                    iter++;
                }

                iters.add(iter);
            }
        }

        int max = 0, min = Integer.MAX_VALUE;
        for(int iter : iters) {
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

        StringBuilder s = new StringBuilder();
        int row_pos = 0;
        for (int iter : iters)
        {
            if (iter == MAX_ITERS)
            {
                s.append(ASCII[asciiLenMinusOne]);
            }
            else
            {
                int mapped = iter - min;
                float pos = (float)mapped / diff;
                s.append(ASCII[(int) (pos * (float) asciiLenMinusOne)]);
            }


            row_pos++;
            if (row_pos == WIDTH)
            {
                row_pos = 0;
                s.append("\n");
            }
        }

        System.out.println(s);
    }
}