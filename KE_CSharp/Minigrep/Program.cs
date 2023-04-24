using System.Text.RegularExpressions;

namespace Minigrep
{
    internal class Program
    {
        static void Main(string[] args)
        {
            switch (args.Length)
            {
                case 0:
                    Console.Error.WriteLine("You need to pass in a file as the first argument.");
                    return;
                case 1:
                    Console.Error.WriteLine("You need to pass in a pattern to look for as the second argument.");
                    return;
            }

            string contents = "";
            try
            {
                contents = System.IO.File.ReadAllText(args[0]);
            } catch (Exception ex)
            {
                Console.Error.WriteLine(ex.Message);
                return;
            }

            ExpandableBitVec bv = new ExpandableBitVec(256);

            foreach (string line in contents.Split('\n'))
            {
                Match match = Regex.Match(line, args[1]);
                if (match.Success)
                {
                    foreach (Capture capture in match.Captures)
                    {
                        for (int i = capture.Index; i < (capture.Index + capture.Length); i++)
                        {
                            bv.set(i);
                        }
                    }
                }

                int col = 0;
                foreach (char c in line.ToCharArray())
                {
                    if (bv.index(col))
                    {
                        Console.ForegroundColor = ConsoleColor.Green;
                    }
                    Console.Write(c);
                    Console.ForegroundColor= ConsoleColor.White;

                    col++;
                }
                Console.WriteLine("");

                bv.clear();
            }
        }
    }
}