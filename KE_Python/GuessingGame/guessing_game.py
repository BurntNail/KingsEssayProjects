import PySimpleGUI as sg
from app import MIN,MAX,GuessingGameApp


if __name__ == "__main__":
    welcomeLabel = sg.Text("Welcome to the Number Guessing Game!")
    guessLabel = sg.Text(f"Try to guess the number between {MIN} and {MAX}.")
    tf = sg.Input(key='-IN-')
    msgLabel = sg.Text("", key='-GUESS-')
    guessBtn = sg.Button("Guess!")
    resetBtn = sg.Button("Reset.")

    layout = [[welcomeLabel], [guessLabel], [tf], [msgLabel], [guessBtn, resetBtn]]

    # Create the window
    window = sg.Window("Demo", layout)

    gg = GuessingGameApp()

    # Create an event loop
    while True:
        event, values = window.read()
        # End program if user closes window or
        # presses the OK button

        if event == sg.WIN_CLOSED:
            break
        elif event == 'Guess!':
            try:
                guess = int(values['-IN-'])
                gg.add_guess(guess)
                window['-GUESS-'].update(f"Your guess was {gg.ordering()}.")
            except:
                print("Invalid Input")
        elif event == 'Reset.':
            gg.reset()
            window['-GUESS-'].update("")


    window.close()