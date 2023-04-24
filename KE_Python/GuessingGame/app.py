from random import randint

MAX = 10
MIN = -10

class GuessingGameApp:
    def __init__(self):
        self.current_number = 0
        self.lastGuess = None

    def reset (self):
        self.lastGuess = None
        self.current_number = randint(MIN, MAX)

    def add_guess (self, guess):
        self.lastGuess = guess

    def ordering (self):
        if self.lastGuess is not None:
            if self.lastGuess < self.current_number:
                return "Smaller"
            elif self.lastGuess > self.current_number:
                return "Bigger"
            else:
                return "Same"
        else:
            return ""