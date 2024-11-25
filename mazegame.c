 #include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAZE_SIZE 20
#define BASE_NUM_ZOMBIES 5
#define TIME_LIMIT_EASY 120 // 2 minutes EZ
#define TIME_LIMIT_MODERATE 90 // 1.5 min MID
#define TIME_LIMIT_HARD 60 // 1 min H A R D

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
void moveZombies(char maze[MAZE_SIZE][MAZE_SIZE], int zombieX[], int zombieY[], int numZombies) {
    int i;
	for (i = 0; i < numZombies; i++) {
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

// Function to check for zombies in front and handle elimination
int checkForZombiesAndEliminate(char direction, int* playerX, int* playerY, char maze[MAZE_SIZE][MAZE_SIZE], char playerChar) {
    int zombieInFront = 0;
    if (direction == 'W' || direction == 'w') {
        if (maze[*playerY - 1][*playerX] == 'Z') zombieInFront = 1;
    } else if (direction == 'A' || direction == 'a') {
        if (maze[*playerY][*playerX - 1] == 'Z') zombieInFront = 1;
    } else if (direction == 'S' || direction == 's') {
        if (maze[*playerY + 1][*playerX] == 'Z') zombieInFront = 1;
    } else if (direction == 'D' || direction == 'd') {
        if (maze[*playerY][*playerX + 1] == 'Z') zombieInFront = 1;
    }

    if (zombieInFront) {
        printf("Warning: Zombie in front! Press '%c' twice to eliminate it.\n", playerChar == 'X' ? 'O' : 'O');
        char eliminationInput[3];
        scanf("%s", eliminationInput); // Read two characters

        if (eliminationInput[0] == 'O' && eliminationInput[1] == 'O') {
            if (direction == 'W' || direction == 'w') {
                maze[*playerY - 1][*playerX] = ' '; // Clear the zombie
                (*playerY)--; // Move player to the zombie's position
            } else if (direction == 'A' || direction == 'a') {
                maze[*playerY][*playerX - 1] = ' '; // Clear the zombie
                (*playerX)--; // Move player to the zombie's position
            } else if (direction == 'S' || direction == 's') {
                maze[*playerY + 1][*playerX] = ' '; // Clear the zombie
                (*playerY)++; // Move player to the zombie's position
            } else if (direction == 'D' || direction == 'd') {
                maze[*playerY][*playerX + 1] = ' '; // Clear the zombie
                (*playerX)++; // Move player to the zombie's position
            }
            return 1; // Indicate a zombie was eliminated
        } else {
            printf("Elimination failed. You must enter 'OO' to eliminate the zombie.\n");
            return 0; // Indicate failure to eliminate
        }
    }
    return 0; // No zombie in front
}

int main() {
    char maze[MAZE_SIZE][MAZE_SIZE] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', '#', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', '#', ' ', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#', '#', '#', ' ', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', ' ', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'E', '#'}, // Exit marked with 'E'
    };

    int playerX[2] = {1, 1}; // Starting position for Player 1
    int playerY[2] = {1, 7}; // Starting position for Player 2 (below Player 1)
    int zombieX[BASE_NUM_ZOMBIES], zombieY[BASE_NUM_ZOMBIES];
    time_t startTime, currentTime;
    int eliminations[2] = {0, 0}; // Track eliminations for both players
    int health[2] = {0, 0}; // Track health for both players
    char playerChar[2] = {'X', 'Y'}; // Player representations
    int numZombies = BASE_NUM_ZOMBIES; // Number of zombies
    int timeLimit; // Time limit for the current mode

    // Select the game mode
    char mode;
    printf("Select game mode (E: Easy, M: Moderate, H: Hard): ");
    scanf(" %c", &mode);
    switch (mode) {
        case 'E': case 'e':
            timeLimit = TIME_LIMIT_EASY;
            break;
        case 'M': case 'm':
            timeLimit = TIME_LIMIT_MODERATE;
            numZombies = BASE_NUM_ZOMBIES + 3; // Increase number of zombies
            break;
        case 'H': case 'h':
            timeLimit = TIME_LIMIT_HARD;
            numZombies = BASE_NUM_ZOMBIES + 5; // Further increase number of zombies
            break;
        default:
            printf("Invalid mode selected. Defaulting to Easy mode.\n");
            timeLimit = TIME_LIMIT_EASY;
            break;
    }

    // Initialize the zombie positions
    srand(time(NULL));
    int i;
    for ( i = 0; i < numZombies; i++) {
        do {
            zombieX[i] = rand() % (MAZE_SIZE - 2) + 1;
            zombieY[i] = rand() % (MAZE_SIZE - 2) + 1;
        } while (maze[zombieY[i]][zombieX[i]] != ' ');
        maze[zombieY[i]][zombieX[i]] = 'Z';
    }

    // Mark the starting points of the maze
    maze[playerY[0]][playerX[0]] = 'X'; // Player 1 representation
    maze[playerY[1]][playerX[1]] = 'Y'; // Player 2 representation

    char direction;
    printf("Welcome to the maze! Use WASD to move, O to eliminate zombies, and Q to quit.\n");
    printMaze(maze);

    // Get the start time
    startTime = time(NULL);

    while (1) {
        // Get the current time
        currentTime = time(NULL);

        // Check if the time limit has been reached
        if (currentTime - startTime >= timeLimit) {
            printf("Time's up! Game over.\n");
            break;
        }
        int player;

        for (player = 0; player < 2; player++) {
            printf("\nPlayer %d (%c), enter direction (WASD/O/Q): ", player + 1, playerChar[player]);
            scanf(" %c", &direction);

            if (direction == 'Q' || direction == 'q') {
                printf("Exiting game...\n");
                return 0;
            }

            // Check for exit condition before moving
            if (checkForExit(direction, playerX[player], playerY[player], maze)) {
                printf("Congratulations, Player %d wins!!! :D\n", player + 1);
                printf("Zombies eliminated by Player 1: %d, Player 2: %d\n", eliminations[0], eliminations[1]);
                return 0; // End the game immediately
            }

            // Handle zombie elimination logic
            if (checkForZombiesAndEliminate(direction, &playerX[player], &playerY[player], maze, playerChar[player])) {
                health[player]++;
                eliminations[player]++;
                printf("Zombie eliminated! Player %d's health increased to %d.\n", player + 1, health[player]);
                maze[playerY[player]][playerX[player]] = playerChar[player]; // Update player position
                printMaze(maze);
                continue; // Skip movement since elimination is done
            }

            // Move the player based on the direction
            int newPlayerX = playerX[player], newPlayerY = playerY[player];

            switch (direction) {
                case 'W': case 'w': newPlayerY--; break;
                case 'A': case 'a': newPlayerX--; break;
                case 'S': case 's': newPlayerY++; break;
                case 'D': case 'd': newPlayerX++; break;
                default:
                    printf("Invalid direction. Try again.\n");
                    printMaze(maze);
                    continue;
            }

            // Check if the new position is valid
            if (maze[newPlayerY][newPlayerX] == ' ' || maze[newPlayerY][newPlayerX] == 'E') {
                // Clear the previous player position
                maze[playerY[player]][playerX[player]] = ' ';

                // Update player position
                playerX[player] = newPlayerX;
                playerY[player] = newPlayerY;

                // Set the new player position
                maze[playerY[player]][playerX[player]] = playerChar[player];

                // Check if the player has reached the exit
                if (maze[playerY[player]][playerX[player]] == 'E') {
                    printf("Congratulations, Player %d wins!!! :D\n", player + 1);
                    printf("Zombies eliminated by Player 1: %d, Player 2: %d\n", eliminations[0], eliminations[1]);
                    return 0; // Ends game
                }
            } else {
                printf("You can't move there!\n");
                continue; // Skip the rest of the loop
            }

            // Move the zombies
            moveZombies(maze, zombieX, zombieY, numZombies);

            // Print the updated maze
            printMaze(maze);
        }
    }

    return 0;
}
