#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRIALS 10000

// Function to simulate one game
int monty_hall(int switch_choice) {
    int car = rand() % 3;      // Car is randomly placed behind one of the doors
    int player_choice = rand() % 3; // Guess of the player
    int reveal; 

    // Reveal one door
    do {
        reveal = rand() % 3;
    } while (reveal == car || reveal == player_choice);

    // If switching, change player's choice to the remaining door
    if (switch_choice) {
        for (int i = 0; i < 3; i++) {
            if (i != player_choice && i != reveal) {
                player_choice = i;
                break;
            }
        }
    }
    
    return player_choice == car; 
}

int main() {
    srand(time(NULL)); // Randomness

    int switch_wins = 0, stay_wins = 0;

    for (int i = 0; i < TRIALS; i++) {
        switch_wins += monty_hall(1); // Simulate with switching
        stay_wins += monty_hall(0);   // Simulate without switching
    }

    printf("After %d trials:\n", TRIALS);
    printf("Winning by switching: %d (%.2f%%)\n", switch_wins, (switch_wins / (double)TRIALS) * 100);
    printf("Winning by staying: %d (%.2f%%)\n", stay_wins, (stay_wins / (double)TRIALS) * 100);

    return 0;
}
