#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100

void rotateCounterClockwise(char map[MAX_ROWS][MAX_COLS], int rows, int cols)
{
    for (int j = 0; j < cols; j++) {
        for (int i = rows - 1; i >= 0; i--) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	FILE *file = fopen(av[1], "r");

    if (file == NULL) {
        perror("Error opening file");
        return (1);
    }

    char map[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0;

    // Read the map from the file
    while (fgets(map[rows], MAX_COLS, file) != NULL) {
        cols = strlen(map[rows]);
        rows++;
    }

    // Close the file
    fclose(file);

    // Print the original map
    printf("Original Map:\n");
    for (int i = 0; i < rows; i++) {
        printf("%s", map[i]);
    }

    // Print the rotated map
    printf("\nRotated Map:\n");
    rotateCounterClockwise(map, rows, cols);

    return (0);
}
