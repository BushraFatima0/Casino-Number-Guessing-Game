#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

class Player {
    public:
    string name;
    int coins;
    int gameswon;
    int gameslost;
    int currentstreak;
    int longeststreak;

    Player( string playername="Guest"){
        name=playername;
        coins=100;
        gameswon=0;
        gameslost=0;
        currentstreak=0;
        longeststreak=0;
    }
    void addcoins(int amount){
        coins+=amount;
    }
    void loosecoins(int amount){
        coins-=amount;
    }
    void streak(bool won){
        if(won){
            currentstreak++;
            if(currentstreak> longeststreak){
                longeststreak=currentstreak;
            }
        }
        else{
            currentstreak=0;
        }
    }

    void display(){
        cout<<"\n---------------------------";
        cout<<"\nPLAYER DETAILS:";
        cout<<"\n---------------------------";
        cout<<"\nPLAYER NAME: "<<name;
        cout<<"\nCOINS: "<<coins;
        cout<<"\nGAMES WON: "<<gameswon;
        cout<<"\nGAMES LOST: "<<gameslost;
        cout<<"\nLONGEST WINNING STREAK: "<<longeststreak;
        cout<<"\n---------------------------\n";
    }

    void saveProfile() const {
        ofstream file(name + ".txt");
        if (file.is_open()) {
            file << name << "\n" << coins << "\n" << gameswon << "\n" << gameslost << "\n" << longeststreak << "\n";
            file.close();
        } else {
            cout << "Error saving profile.\n";
        }
    }

    void loadProfile() {
        if (name== "Guest") {
            cout << "\nNo profile to load. Starting a new game for " << name << ".\n";
            return;
        }
        ifstream file(name + ".txt");
        if (file.is_open()) {
            file >> name >> coins >> gameswon >> gameslost >> longeststreak;
            file.close();
            cout << "\nWelcome back, " << name << "! Profile loaded.\n";
        } else {
            cout << "\nNo existing profile found. Starting a new game for " << name << ".\n";
        }
    }
};

class Casinogame{
    public:
    int number;
    int guess;
    int attempts;
    Player* player;

    Casinogame(Player* p) {
        player =p;
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
        int bet;
        cout<< "\nYou have "<< player->coins<< " coins.\n";
        cout<< "Enter your bet amount: \n";
        cin>>bet;
        if(bet> player->coins || bet<=0) {
            cout<< "Invalid bet amount! \n";
            return;
        }

        for (int i = 1; i <= attempts; i++) {
            cout << "\nENTER YOUR GUESS:";
            cin>> guess;
            if (guess < 1 || guess > 10){
                cout << "Invalid guess! Please enter a number between 1 and 10.\n";
            }
            else if(i == attempts && guess!= number) {
                cout << "You've used all your attempts.\nThe number was " << number << ".\n";
                cout << "YOU LOST "<< bet << " COINS.\n";
                player->loosecoins(bet);
                player->gameslost++;
                player->streak(false);
            }
            else{
                if (guess == number) {
                    cout << "CORRECT!! YOU WON " << bet*2 << " COINS\n";
                    player->addcoins(bet*2);
                    player->gameswon++;
                    player->streak(true);
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

class gamemanager {
    private:
    Player* player;
    public:

    gamemanager() {
        cout << "\n\t\t\t\t\t\t\t WELCOME \t\t\n";
        cout << "\t\t\t\t\t\t\t   TO   \t\t\n";
        cout << "\t\t\t\t\t\t CASINO NUMBER GUESSING GAME \t\n";
        profile();
        mainmenu();
    }

    void profile(){
        string playername;
        cout<<"\nEnter your name: ";
        getline(cin, playername);
        if (playername.empty()) playername = "Guest";
        player=new Player(playername);
        player->loadProfile();
    }
    
    void mainmenu() {
        Casinogame game(player);
        game.rules();
        while(true) {
        Casinogame game(player);
        game.difficulty();
        player->display();
        char playAgain;
        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;
        if (playAgain == 'y' || playAgain == 'Y') {
            continue;
        } else if (playAgain == 'n' || playAgain == 'N') {
            cout << "Thank you for playing! Goodbye!\n";
            player->saveProfile();
            break;
        } else {
            cout << "Invalid input! Please enter 'y' or 'n'.\n";
        }
    }
}
};   

int main() {
    gamemanager manager;  
    return 0;
}