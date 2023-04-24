namespace NumbersGuessingGame
{
    public partial class Form1 : Form
    {
        private GuessingGameApp app;

        public Form1()
        {
            app = new GuessingGameApp();
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //Submit

            string guess = textBox1.Text;
            int guessInt;
            if (Int32.TryParse(guess, out guessInt))
            {
                app.AddGuess(guessInt);
                if (app.ordering() is string Ordering)
                {
                    label3.Text = "Your guess was " + Ordering + ".";
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //Reset

            app.Reset();
            label3.Text = "";
        }
    }
}