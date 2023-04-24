namespace Mandlebrot
{
    internal class Program
    {
        private const String ASCII = " .:;+=xX$&";

        private const int WIDTH = 50;
        private const int HEIGHT = 35;

        private const float RE_START = -2.0f;
        private const float RE_END = 1.0f;
        private const float IM_START = -1.0f;
        private const float IM_END = 1.0f;

        private const int MAX_ITERS = 25;
        
        static void Main(String[] args)
        {
            char[] asciiChars = ASCII.ToCharArray();
            int asciiLenMinusOne = asciiChars.Length - 1;
            
            List<int> iters = new List<int>();
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
                    
                    iters.Add(iter);
                }
            }

            int max = (from iter in iters where iter < MAX_ITERS select iter).Max();
            int min = iters.Min();

            float diff = (float)(max - min);


            String s = "";
            int row_pos = 0;
            foreach (int iter in iters)
            {
                if (iter == MAX_ITERS)
                {
                    s += asciiChars[asciiLenMinusOne];
                }
                else
                {
                    int mapped = iter - min;
                    float pos = (float)mapped / diff;
                    s += asciiChars[(int)(pos * (float)asciiLenMinusOne)];
                }


                row_pos++;
                if (row_pos == WIDTH)
                {
                    row_pos = 0;
                    s += "\n";
                }
            }

            Console.WriteLine(s);
        }
    }
}