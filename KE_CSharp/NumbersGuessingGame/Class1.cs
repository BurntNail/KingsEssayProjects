namespace NumbersGuessingGame
{
    internal class GuessingGameApp
    {
        public const int MAX = 10;
        public const int MIN = -10;

        private int currentNumber;
        private int? lastGuess;
        private Random random;

        public GuessingGameApp ()
        {
            random = new Random();
            currentNumber = random.Next(MIN, MAX);
            lastGuess = null;
        }

        public void Reset ()
        {
            lastGuess = null;
            currentNumber = random.Next(MIN, MAX);
        }

        public void AddGuess (int guess)
        {
            lastGuess = guess;
        }

        public String? ordering ()
        {
            if (!lastGuess.HasValue)
            {
                return null;
            }

            if (lastGuess.Value < currentNumber)
            {
                return "Smaller";
            } else if (lastGuess.Value > currentNumber)
            {
                return "Greater";
            } else
            {
                return "Same";
            }
        }
    }
}
