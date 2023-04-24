import java.util.Optional;
import java.util.concurrent.ThreadLocalRandom;

public class GuessingGame {
    public static final int MAX = 10;
    public static final int MIN = -10;

    private int currentNumber;
    private Optional<Integer> lastGuess;
    private ThreadLocalRandom random;


    public GuessingGame () {
        lastGuess = Optional.empty();
        random = ThreadLocalRandom.current();
        currentNumber = random.nextInt(MIN, MAX + 1);
    }

    public void Reset ()
    {
        lastGuess = Optional.empty();
        currentNumber = random.nextInt(MIN, MAX + 1);
    }

    public void AddGuess (int guess)
    {
        lastGuess = Optional.of(guess);
    }

    public Optional<String> ordering ()
    {
        return lastGuess.map(value -> {
            if (value < currentNumber)
            {
                return "Smaller";
            } else if (value > currentNumber)
            {
                return "Greater";
            } else
            {
                return "Same";
            }
        });
    }
}
