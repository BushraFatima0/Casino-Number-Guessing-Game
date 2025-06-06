#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Casinogame{
    public:
    int number;
    int guess;
    int attempts;

    Casinogame() {
        srand(time(0));
        number=rand() % 10 + 1;
    }
    
    void rules(){
        cout << "\nRULES OF THE GAME:\n";
        cout << "1. I will think of a number between 1 and 10.\n";
        cout << "2. You have to guess the number within a limited number of attempts based on the Level Of Difficulty you choose.\n";
        cout << "3. If you guess the number correctly, you win!\n";
        cout << "4. If you run out of attempts, you lose.\n";
        cout << "\nGOOD LUCK!\n";
    }
    void difficulty() {
        int difficultyLevel;
        cout<<"\nCHOOSE THE LEVEL OF DIFFICULTY:\n";
        cout<<"1. Easy: 10 attempts\n";
        cout<<"2. Medium: 5 attempts\n";
        cout<<"3. Hard: 3 attempts\n";
        cout<<"Enter your choice (1-3): ";
        cin >> difficultyLevel;
        switch (difficultyLevel) {
            case 1:
                cout << "\nEASY MODE:\n> You have 10 attempts to guess the number.\n";
                play(10);
                break;
            case 2:
                cout << "\nMEDIUM MODE:\n> You have 5 attempts to guess the number.\n";
                play(5);
                break;
            case 3:
                cout << "\nHARD MODE:\n> You have 3 attempts to guess the number.\n";
                play(3);
                break;
            default:
                cout << "Invalid choice! Please select a valid difficulty level.\n";
                difficulty(); 
        }
    }
    void play(int attempts) {
        for (int i = 1; i <= attempts; i++) {
            cout << "\nENTER YOUR GUESS:";
            cin>> guess;
            if (guess < 1 || guess > 10){
                cout << "Invalid guess! Please enter a number between 1 and 10.\n";
            }
            else if(i == attempts && guess!= number) {
                cout << "You've used all your attempts.\nThe number was " << number << ".\n";
                cout << "YOU LOSE!\n";
            }
            else{
                if (guess == number) {
                    cout << "Congratulations! You guessed the number " << number << " correctly!\n";
                    cout << "YOU WIN!\n";
                    return;
                } 
                else if (guess < number) {
                    cout << "Too low. Try again.\n";
                } 
                else {
                    cout << "Too high. Try again.\n";
                }
            }
        }
    }
};

int main() {
    Casinogame game;
    cout << "\n\t\t\t\t\t\t\t WELCOME \t\t\n";
    cout << "\t\t\t\t\t\t\t   TO   \t\t\n";
    cout << "\t\t\t\t\t\t CASINO NUMBER GUESSING GAME \t\n";
    game.rules();
    game.difficulty();
    while(true) {
        char playAgain;
        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;
        if (playAgain == 'y' || playAgain == 'Y') {
            game = Casinogame();
            game.difficulty();
        } else if (playAgain == 'n' || playAgain == 'N') {
            cout << "Thank you for playing! Goodbye!\n";
            break;
        } else {
            cout << "Invalid input! Please enter 'y' or 'n'.\n";
        }
    }
    return 0;
}
