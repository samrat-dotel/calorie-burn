#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_SNAKES 14
#define NUM_LADDERS 9
#define DEFAULT_FINAL_SQUARE 100

void displayBoard(int numPlayers, char player[][20], int position[])
{
    printf("\nCurrent Board:\n");
    for (int i = 0; i < numPlayers; i++)
    {
        printf("%s: %d\t", player[i], position[i]);
    }
    printf("\n\n");
}

void playGame(int numPlayers, int finalSquare)
{
    char player[numPlayers][20];
    int position[numPlayers];
    int consecutiveSixCount[numPlayers];

    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL));

    for (int i = 0; i < numPlayers; i++)
    {
        printf("Enter player %d's name: ", i + 1);
        scanf("%s", player[i]);
        position[i] = 0;
        consecutiveSixCount[i] = 0;
    }
   
   
    // Define snakes and ladders
    int snakes[NUM_SNAKES][2] = {
        {23,7},
        {28,6},
        {36,8},
        {44,5},
        {46,16},
        {49,11},
        {54,22},
        {60,32},
        {68,22},
        {82,42},
        {91,18},
        {94,62},
        {97,8},
        {99,2}
        };
    int ladders[NUM_LADDERS][2] = {
        {3, 22},
        {7, 21},
        {14,43},
        {19, 42}, 
        {25, 65}, 
        {38, 89}, 
        {60, 81},
        {42,62},
        {69,98}
        };

    int turn = 0;
    while (1)
    {
        printf("%s is rolling now .... \n", player[(turn % numPlayers)]);

        int current = rand() % 6 + 1;
        printf("Rolled a %d \n", current);
        sleep(1);

        // Move the player
        if(!(position[turn % numPlayers] + current >100)){
            position[turn % numPlayers] += current;
        }

        // Check for snakes and ladders
        for (int i = 0; i < NUM_SNAKES; i++)
        {
            if (position[turn % numPlayers] == snakes[i][0])
            {
                printf("Oh no! Encountered a snake! Sliding down to %d.\n", snakes[i][1]);
                position[turn % numPlayers] = snakes[i][1]; // Corrected line
            }
        }

        for (int i = 0; i < NUM_LADDERS; i++)
        {
            if (position[turn % numPlayers] == ladders[i][0])
            {
                printf("Yay! Found a ladder! Climbing up to %d.\n", ladders[i][1]);
                position[turn % numPlayers] = ladders[i][1];
            }
        }

        

        // Check if the player reaches or passes the final square
        if (position[turn % numPlayers] >= finalSquare)
        {
            printf("Congratulations! %s reached the final square!, he is the winner!\n", player[turn % numPlayers]);
            displayBoard(numPlayers, player, position);
            return;
        }

        printf("%s's current position is now %d \n", player[turn % numPlayers], position[turn % numPlayers]);

        // Check for collisions with other players
        for (int i = 0; i < numPlayers; i++)
        {
            if (i != turn % numPlayers && position[i] == position[turn % numPlayers])
            {
                printf("Oh no! Collision with %s! %s eliminates %s, sending them back to square 1.\n", player[i], player[turn % numPlayers], player[i]);
                position[i] = 1; // The latest player eliminates the previous one
                printf("\n\n %s gets another chance",player[turn % numPlayers]);

                if(current == 6){
                    consecutiveSixCount[turn % numPlayers]++;
                }
                
                continue;
            }
        }

        // Check for consecutive sixes
        if (current == 6)
        {
            consecutiveSixCount[turn % numPlayers]++;
            if (consecutiveSixCount[turn % numPlayers] == 3)
            {
                printf("Oh no! %s rolled three consecutive 6s and gets a penalty of -6!\n", player[turn % numPlayers]);
                position[turn % numPlayers] -= 12;
                consecutiveSixCount[turn % numPlayers] = 0;
            }
            else
            {
                printf("Wow! %s rolled a 6 and gets another chance.\n", player[turn % numPlayers]);
                continue; // Bonus chance for rolling a 6
            }
        }
        else
        {
            consecutiveSixCount[turn % numPlayers] = 0;
        }

        displayBoard(numPlayers, player, position);
        sleep(1.5);
        turn += 1;

        // system("clear");
    }
}

int main()
{
    int numPlayers;

    printf("Enter the number of players: ");
    scanf("%d", &numPlayers);

    playGame(numPlayers, DEFAULT_FINAL_SQUARE);

    return 0;
}
