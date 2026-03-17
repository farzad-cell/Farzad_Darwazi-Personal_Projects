
// By Farzad Darwazi 9/28/25

#include<iostream>
#include<random>

using namespace std;


int main() {

    bool exit = false;
    char player, roll, pick;

    cout<<endl;
    cout<<"-----------------------------------------"<<endl;
    cout<<"Welcome to Flip A Coin. Exit code (Q/q).\n-----------------------------------------\nEnter ONLY one of the following\n-----------------------------------------\nCompetitive MODE   --> Y or y\nStandard MODE      --> N or n"<<endl;
    cout<<"-----------------------------------------"<<endl;


    random_device rd;
    mt19937_64 rnd(rd());
    uniform_int_distribution<int> dist(0,1);

    // Main Loop for both Modes
    while (!exit) {
        cin>>player;

        if (player == 'q' || player == 'Q') {
            exit = true;
            break;
        }

        if (player == 'Y' || player == 'y' || player == 'N' || player == 'n') {


            if (player == 'Y' || player =='y'){

                cout<<"Welcome to the Competitive Mode | Exit code (Q/q), Main Menu (B/b)"<<endl;

                cout << "\n************\nH/h - Heads\nT/t - Tails\n************" << endl;

                // Competitive Mode
                while(true) {

                    
                    cout << endl;
                    cin>>pick;
                    cout << endl;

                    if (pick == 'q' || pick == 'Q') {
                        exit = true;
                        break;
                    }

                    int fc = dist(rnd);

                    if (pick == 'B' || pick == 'b') {
                        cout<< "Main menu | Exit(Q/q) \nPick ONLY one MODE (Y/y or N/n) \nCompetitive mode   --> Y or y\nFlip a coin        --> N or n" <<endl;
                        break;
                    }

                    if (pick == 'H' || pick == 'h' || pick == 'T' || pick == 't') {
                        if (pick == 'H' || pick == 'h') {
                            cout << "You: Heads" << endl;
                        }
                        else if (pick == 'T' || pick == 't') {
                            cout << "You: Tails" << endl;
                        }
                        else
                            cout << "Invalid input! | Chose only one H/h or T/t" << endl;

                        if (fc == 0) {
                            cout << "Coin Flip is...\nHeads" << endl;
                            
                        }
                        else if (fc == 1) {
                            cout << "Coin Flip is...\nTails" << endl;
                            
                        }
                        if (pick == 'H' || pick == 'h' && fc == 0) {
                            cout << "Good Guess :D" << endl;
                        }else if (pick == 'T' || pick == 't' && fc == 1) {
                            cout << "Good Guess :D" << endl;
                        }else
                            cout << "Wrong guess :p  Try again" << endl;
                        
                        
                    }
                }
            }else if (player == 'N' || player == 'n') {

                cout<< "Welcome to the Standard Coin Flip | Exit(Q/q), Main Menu (B/b)" <<endl;
                cout<<"Press Any alphabet for coin flip"<<endl;

                // Standard Mode loop
                while(true) {

                    cin>> roll;


                    if (roll == 'q' || roll == 'Q') {
                        exit = true;
                        break;
                    }

                    int fc = dist(rnd);

                    if(roll == 'B' || roll == 'b') {
                        cout<< "Main menu | Exit(Q/q) \nPick ONLY one MODE (Y/y or N/n) \nCompetitive mode   --> Y or y\nFlip a coin        --> N or n" <<endl;
                        break;
                    }

                    cout<<"Coin Flip: ";
                    if(fc == 1) {
                        cout<<"Tails"<<endl;
                    }else if (fc == 0){
                        cout<<"Heads"<<endl;
                    }
                }
                }


        }else
            cout<<"Invalid input! | Chose only one Y,y or N,n"<<endl;
                continue;
        }

    }

