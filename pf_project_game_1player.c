Enable desktop notifications for NUCES-FAST Mail.
   OK  No thanks

Conversations
 
Program Policies
Powered by Google
Last account activity: 1 hour ago
Details
	
Pause mobile notifications while you're using this device
To pause Chat mobile notifications while you’re active on this device, allow your browser to detect if you’re active or away. Click Continue and then Allow when prompted by your browser.

 #include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAZE_SIZE 10
#define NUM_ZOMBIES 5
#define TIME_LIMIT 120 // 2 minutes in seconds

// Function to print the maze
void printMaze(char maze[MAZE_SIZE][MAZE_SIZE]) {
    int i, j;
    for (i = 0; i < MAZE_SIZE; i++) {
        for (j = 0; j < MAZE_SIZE; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

// Function to move the zombies
void moveZombies(char maze[MAZE_SIZE][MAZE_SIZE], int zombieX[], int zombieY[]) {
    int i;
    for (i = 0; i < NUM_ZOMBIES; i++) {
        int newX, newY;
        do {
            int dx = rand() % 3 - 1;
            int dy = rand() % 3 - 1;
            newX = zombieX[i] + dx;
            newY = zombieY[i] + dy;
        } while (newX < 0 || newX >= MAZE_SIZE || newY < 0 || newY >= MAZE_SIZE || maze[newY][newX] != ' ');

        // Clear the previous zombie position
        maze[zombieY[i]][zombieX[i]] = ' ';

        // Set the new zombie position
        maze[newY][newX] = 'Z';
        zombieX[i] = newX;
        zombieY[i] = newY;
    }
}

// Function to check if the exit is in front of the player
int checkForExit(char direction, int playerX, int playerY, char maze[MAZE_SIZE][MAZE_SIZE]) {
    if (direction == 'W' || direction == 'w') {
        return maze[playerY - 1][playerX] == 'E';
    } else if (direction == 'A' || direction == 'a') {
        return maze[playerY][playerX - 1] == 'E';
    } else if (direction == 'S' || direction == 's') {
        return maze[playerY + 1][playerX] == 'E';
    } else if (direction == 'D' || direction == 'd') {
        return maze[playerY][playerX + 1] == 'E';
    }
    return 0; // Not moving towards exit
}

int main() {
    char maze[MAZE_SIZE][MAZE_SIZE] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', 'E', '#'} // Exit marked with 'E'
    };

    int playerX = 1, playerY = 1; // Starting position for the player
    int zombieX[NUM_ZOMBIES], zombieY[NUM_ZOMBIES];
    time_t startTime, currentTime;
    int eliminations = 0; // Track eliminations for the player
    int health = 0; // Track health for the player

    // Initialize the zombie positions
    srand(time(NULL));
    int i;
    for (i = 0; i < NUM_ZOMBIES; i++) {
        do {
            zombieX[i] = rand() % (MAZE_SIZE - 2) + 1;
            zombieY[i] = rand() % (MAZE_SIZE - 2) + 1;
        } while (maze[zombieY[i]][zombieX[i]] != ' ');
        maze[zombieY[i]][zombieX[i]] = 'Z';
    }

    // Mark the starting point of the maze
    maze[playerY][playerX] = 'P'; // Player representation

    char direction;

    printf("Welcome to the maze! Use WASD to move, O to eliminate zombies, and Q to quit.\n");
    printMaze(maze);

    // Get the start time
    startTime = time(NULL);

    while (1) {
        // Get the current time
        currentTime = time(NULL);

        // Check if the time limit has been reached
        if (currentTime - startTime >= TIME_LIMIT) {
            printf("Time's up! Game over.\n");
            break;
        }

        printf("\nEnter direction (WASD/O/Q): ");
        scanf(" %c", &direction);

        if (direction == 'Q' || direction == 'q') {
            printf("Exiting game...\n");
            break;
        }

        // Check for exit condition before moving
        if (checkForExit(direction, playerX, playerY, maze)) {
            printf("Congratulations, you won!!! :D\n");
            printf("Zombies eliminated: %d\n", eliminations);
            break; // End the game immediately
        }

        // Handle zombie elimination logic
        int zombieInFront = 0;
        if (direction == 'W' || direction == 'w') {
            if (maze[playerY - 1][playerX] == 'Z') zombieInFront = 1;
        } else if (direction == 'A' || direction == 'a') {
            if (maze[playerY][playerX - 1] == 'Z') zombieInFront = 1;
        } else if (direction == 'S' || direction == 's') {
            if (maze[playerY + 1][playerX] == 'Z') zombieInFront = 1;
        } else if (direction == 'D' || direction == 'd') {
            if (maze[playerY][playerX + 1] == 'Z') zombieInFront = 1;
        }

        if (zombieInFront) {
            printf("Warning: Zombie in front! Press 'O' twice to eliminate it.\n");
            char eliminationInput[3]; // To hold user input for elimination
            scanf("%s", eliminationInput); // Read two characters

            if (eliminationInput[0] == 'O' && eliminationInput[1] == 'O') {
                // Eliminate the zombie and move the player to the zombie's position
                if (direction == 'W' || direction == 'w') {
                    maze[playerY - 1][playerX] = ' '; // Clear the zombie
                    playerY -= 1; // Move player to the zombie's position
                } else if (direction == 'A' || direction == 'a') {
                    maze[playerY][playerX - 1] = ' '; // Clear the zombie
                    playerX -= 1; // Move player to the zombie's position
                } else if (direction == 'S' || direction == 's') {
                    maze[playerY + 1][playerX] = ' '; // Clear the zombie
                    playerY += 1; // Move player to the zombie's position
                } else if (direction == 'D' || direction == 'd') {
                    maze[playerY][playerX + 1] = ' '; // Clear the zombie
                    playerX += 1; // Move player to the zombie's position
                }

                health++;
                eliminations++;
                printf("Zombie eliminated! Health increased to %d.\n", health);
                maze[playerY][playerX] = 'P'; // Update player position
                printMaze(maze);
                continue; // Skip movement since elimination is done
            } else {
                printf("Elimination failed. You must enter 'OO' to eliminate the zombie.\n");
                printMaze(maze);
                continue;
            }
        }

        // Move the player based on the direction
        int newPlayerX = playerX, newPlayerY = playerY;

        switch (direction) {
            case 'W':
            case 'w':
                newPlayerY--;
                break;
            case 'A':
            case 'a':
                newPlayerX--;
                break;
            case 'S':
            case 's':
                newPlayerY++;
                break;
            case 'D':
            case 'd':
                newPlayerX++;
                break;
            default:
                printf("Invalid direction. Try again.\n");
                printMaze(maze);
                continue;
        }

        // Check if the new position is valid
        if (maze[newPlayerY][newPlayerX] == ' ' || maze[newPlayerY][newPlayerX] == 'E') {
            // Clear the previous player position
            maze[playerY][playerX] = ' ';

            // Update player position
            playerX = newPlayerX;
            playerY = newPlayerY;

            // Set the new player position
            maze[playerY][playerX] = 'P'; // Player representation

            // Check if the player has reached the exit
            if (maze[playerY][playerX] == 'E') {
                printf("Congratulations, you won!!! :D\n");
                printf("Zombies eliminated: %d\n", eliminations);

                break; // Ends game
            }
        } else {
            printf("You can't move there!\n");
            continue; // Skip the rest of the loop
        }

        // Move the zombies
        moveZombies(maze, zombieX, zombieY);

        // Print the updated maze
        printMaze(maze);
    }

    return 0;
}
