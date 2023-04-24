import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Optional;

public class Main {
    private static final int TEXT_HEIGHT = 20;
    private static final int BUFFER = 15;

    private static final int WIDTH = 400;
    private static final int HEIGHT = 300;

    public static void main(String[] args) {
        GuessingGame game = new GuessingGame();

        JFrame frame = new JFrame("Guessing Game");

        JLabel welcomeLabel = new JLabel("Welcome to the Number Guessing Game!");
        welcomeLabel.setBounds(BUFFER, BUFFER, WIDTH - BUFFER*2, TEXT_HEIGHT);
        frame.add(welcomeLabel);

        JLabel guessLabel = new JLabel("Try to guess the number between " + GuessingGame.MIN + " and " + GuessingGame.MAX + ".");
        guessLabel.setBounds(BUFFER, BUFFER*2 + TEXT_HEIGHT, WIDTH - BUFFER*2, TEXT_HEIGHT);
        frame.add(guessLabel);

        JTextField textField = new JTextField();
        textField.setBounds(BUFFER, BUFFER*3 + TEXT_HEIGHT*2, WIDTH - BUFFER*2, TEXT_HEIGHT);
        frame.add(textField);

        JLabel msgLabel = new JLabel();
        msgLabel.setBounds(BUFFER, BUFFER*4 + TEXT_HEIGHT*3, WIDTH - BUFFER*2, TEXT_HEIGHT);
        frame.add(msgLabel);

        JButton guessBtn = new JButton("Guess");
        guessBtn.setBounds(BUFFER, BUFFER*5 + TEXT_HEIGHT*4, (WIDTH - BUFFER) / 2, TEXT_HEIGHT);
        frame.add(guessBtn);

        guessBtn.addActionListener(e -> {
            try {
                int guess = Integer.parseInt(textField.getText());
                game.AddGuess(guess);
                game.ordering().ifPresent(Ordering -> {
                    msgLabel.setText("Your guess was " + Ordering + ".");
                });
            } catch (NumberFormatException ex) {
                System.err.println("Error parsing input: " + ex.getMessage());
                textField.setText("");
            }
        });

        JButton resetBtn = new JButton("Reset");
        resetBtn.setBounds(WIDTH / 2 + BUFFER, BUFFER*5 + TEXT_HEIGHT*4, WIDTH / 2 - BUFFER, TEXT_HEIGHT);
        frame.add(resetBtn);

        resetBtn.addActionListener(e -> {
            game.Reset();
            textField.setText("");
        });

        frame.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        frame.setSize(WIDTH + BUFFER * 2, HEIGHT);
        frame.setLayout(null);
        frame.setVisible(true);
    }
}