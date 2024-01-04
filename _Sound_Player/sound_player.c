#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 256

void play_sound(const char *soundFileName)
{
    // Use afplay to play the sound file
    char command[MAX_BUFFER_SIZE];
    snprintf(command, sizeof(command), "afplay %s", soundFileName);
    system(command);
}

int main()
{
    const char *filePath = "sound.txt";
    const char *soundsFolder = "/";

    FILE *file = fopen(filePath, "r");
    if (file == NULL)
	{
        perror("Error opening file");
        return 1;
    }

    char buffer[MAX_BUFFER_SIZE];
    while (1)
	{
        // Read from the file
        fseek(file, 0, SEEK_SET);
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            // Remove trailing newline character
            buffer[strcspn(buffer, "\n")] = '\0';

            // Check the content of the buffer and play the corresponding sound
            if (strcmp(buffer, "sound1") == 0) {
                playSound(strcat(soundsFolder, "sound1.bzz"));
            } else if (strcmp(buffer, "sound2") == 0) {
                playSound(strcat(soundsFolder, "sound2.bzz"));
            } else {
                // Handle unknown command
                printf("Unknown command: %s\n", buffer);
            }
        }

        // Sleep for a short duration before checking again
        usleep(50000);  // 0.05 seconds
    }

    fclose(file);
    return 0;
}