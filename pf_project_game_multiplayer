#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAZE_SIZE 20
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

// Function to handle player input (including Player 2 movement with IJKL)
char getPlayerInput(int playerNum) {
    char direction = 0;
    if (playerNum == 1) {
        // Player 1 uses WASD
        printf("\nPlayer 1 (X), enter direction (WASD) or TT to eliminate zombie: ");
    } else {
        // Player 2 uses IJKL
        printf("\nPlayer 2 (Y), enter direction (IJKL) or OO to eliminate zombie: ");
    }
    scanf(" %c", &direction);
    return direction;
}

int main() {
    char maze[MAZE_SIZE][MAZE_SIZE] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' '},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', ' ', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' '},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', 'E', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };

    int player1X = 1, player1Y = 1;  // Starting position for player 1
    int player2X = 18, player2Y = 1; // Starting position for player 2
    int zombieX[NUM_ZOMBIES], zombieY[NUM_ZOMBIES];
    time_t startTime, currentTime;
    int eliminations1 = 0, eliminations2 = 0;
    int health1 = 0, health2 = 0;
    char direction1, direction2;

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

    // Mark the starting points of the maze
    maze[player1Y][player1X] = 'X'; // Player 1 (X)
    maze[player2Y][player2X] = 'Y'; // Player 2 (Y)

    printf("Choose the game mode:\n");
    printf("1. Single Player\n");
    printf("2. Two Player\n");
    printf("Enter 1 or 2: ");
    int gameMode;
    scanf("%d", &gameMode);

    // Clear input buffer
    while (getchar() != '\n');

    if (gameMode == 1) {
        printf("You chose Single Player.\nPlayer 1 controls using WASD keys and OO for zombie elimination.\n");
    } else if (gameMode == 2) {
        printf("You chose Two Player.\nPlayer 1 (X) uses WASD for movement and TT for zombie elimination.\nPlayer 2 (Y) uses IJKL for movement and OO for zombie elimination.\n");
    } else {
        printf("Invalid choice, exiting game.\n");
        return 0;
    }

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

        // Display elapsed time
        printf("Elapsed Time: %ld seconds\n", currentTime - startTime);

        // Player 1's turn (WASD or TT for elimination)
        if (gameMode == 1 || gameMode == 2) {
            direction1 = getPlayerInput(1);

            // Check for exit condition before moving for player 1
            if (checkForExit(direction1, player1X, player1Y, maze)) {
                printf("Player 1 wins!!! :D\n");
                printf("Zombies eliminated: %d\n", eliminations1);
                break;
            }

            // Process player 1 movement (WASD)
            if (direction1 == 'W' || direction1 == 'w') {
                if (maze[player1Y - 1][player1X] == ' ') {
                    maze[player1Y][player1X] = ' ';
                    player1Y--;
                    maze[player1Y][player1X] = 'X';
                }
            } else if (direction1 == 'A' || direction1 == 'a') {
                if (maze[player1Y][player1X - 1] == ' ') {
                    maze[player1Y][player1X] = ' ';
                    player1X--;
                    maze[player1Y][player1X] = 'X';
                }
            } else if (direction1 == 'S' || direction1 == 's') {
                if (maze[player1Y + 1][player1X] == ' ') {
                    maze[player1Y][player1X] = ' ';
                    player1Y++;
                    maze[player1Y][player1X] = 'X';
                }
            } else if (direction1 == 'D' || direction1 == 'd') {
                if (maze[player1Y][player1X + 1] == ' ') {
                    maze[player1Y][player1X] = ' ';
                    player1X++;
                    maze[player1Y][player1X] = 'X';
                }
            }

            // Eliminate zombies (TT for Player 1)
            if (direction1 == 'T' || direction1 == 't') {
                char eliminationInput[3];
                printf("Press 'T' twice to eliminate zombie: ");
                scanf("%s", eliminationInput);

                if (eliminationInput[0] == 'T' && eliminationInput[1] == 'T') {
                    // Eliminate zombie and increase health
                    if (maze[player1Y - 1][player1X] == 'Z') {
                        maze[player1Y - 1][player1X] = ' ';
                        health1++;
                        eliminations1++;
                    } else if (maze[player1Y + 1][player1X] == 'Z') {
                        maze[player1Y + 1][player1X] = ' ';
                        health1++;
                        eliminations1++;
                    } else if (maze[player1Y][player1X - 1] == 'Z') {
                        maze[player1Y][player1X - 1] = ' ';
                        health1++;
                        eliminations1++;
                    } else if (maze[player1Y][player1X + 1] == 'Z') {
                        maze[player1Y][player1X + 1] = ' ';
                        health1++;
                        eliminations1++;
                    }
                    printf("Zombie eliminated by Player 1!\n");
                }
            }
        }

        // Player 2's turn (IJKL or OO for elimination)
        if (gameMode == 2) {
            direction2 = getPlayerInput(2);

            // Check for exit condition before moving for player 2
            if (checkForExit(direction2, player2X, player2Y, maze)) {
                printf("Player 2 wins!!! :D\n");
                printf("Zombies eliminated: %d\n", eliminations2);
                break;
            }

            // Process player 2 movement (IJKL)
            if (direction2 == 'I') {
                if (maze[player2Y - 1][player2X] == ' ') {
                    maze[player2Y][player2X] = ' ';
                    player2Y--;
                    maze[player2Y][player2X] = 'Y';
                }
            } else if (direction2 == 'J') {
                if (maze[player2Y][player2X - 1] == ' ') {
                    maze[player2Y][player2X] = ' ';
                    player2X--;
                    maze[player2Y][player2X] = 'Y';
                }
            } else if (direction2 == 'K') {
                if (maze[player2Y + 1][player2X] == ' ') {
                    maze[player2Y][player2X] = ' ';
                    player2Y++;
                    maze[player2Y][player2X] = 'Y';
                }
            } else if (direction2 == 'L') {
                if (maze[player2Y][player2X + 1] == ' ') {
                    maze[player2Y][player2X] = ' ';
                    player2X++;
                    maze[player2Y][player2X] = 'Y';
                }
            }

            // Eliminate zombies (OO for Player 2)
            if (direction2 == 'O' || direction2 == 'o') {
                char eliminationInput[3];
                printf("Press 'O' twice to eliminate zombie: ");
                scanf("%s", eliminationInput);

                if (eliminationInput[0] == 'O' && eliminationInput[1] == 'O') {
                    // Eliminate zombie and increase health
                    if (maze[player2Y - 1][player2X] == 'Z') {
                        maze[player2Y - 1][player2X] = ' ';
                        health2++;
                        eliminations2++;
                    } else if (maze[player2Y + 1][player2X] == 'Z') {
                        maze[player2Y + 1][player2X] = ' ';
                        health2++;
                        eliminations2++;
                    } else if (maze[player2Y][player2X - 1] == 'Z') {
                        maze[player2Y][player2X - 1] = ' ';
                        health2++;
                        eliminations2++;
                    } else if (maze[player2Y][player2X + 1] == 'Z') {
                        maze[player2Y][player2X + 1] = ' ';
                        health2++;
                        eliminations2++;
                    }
                    printf("Zombie eliminated by Player 2!\n");
                }
            }
        }

        // Move zombies
        moveZombies(maze, zombieX, zombieY);

        // Print the updated maze
        printMaze(maze);
    }

    return 0;
}


