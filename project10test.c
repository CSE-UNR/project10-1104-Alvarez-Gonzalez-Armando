#include <stdio.h>

int loadWord(char word[]);
int validGuess(char guess[]);
void lowerGuess(char guess[]);
int checkGuess(char word[], char guess[]);
void winMessage(int guessCount);

int main() {
    char word[6];
    char guess[20];
    int guessCount = 0;
    int won = 0;

    if (!loadWord(word)) {
        printf("Could not open mystery.txt\n");
        return 0;
    }

    while (guessCount < 6 && won == 0) {
        if (guessCount == 5) {
            printf("FINAL GUESS: ");
        } else {
            printf("Guess %d: ", guessCount + 1);
        }

        scanf("%s", guess);

        while (!validGuess(guess)) {
            printf("Guess must be exactly 5 letters. Try again: ");
            scanf("%s", guess);
        }

        lowerGuess(guess);

        printf("====================\n");

        won = checkGuess(word, guess);
        guessCount++;
    }

    if (won) {
        winMessage(guessCount);
    } else {
        printf("You lost, better luck next time!\n");
    }

    return 0;
}

int loadWord(char word[]) {
    FILE *file;

    file = fopen("mystery.txt", "r");

    if (file == NULL) {
        return 0;
    }

    fscanf(file, "%s", word);
    fclose(file);

    return 1;
}

int validGuess(char guess[]) {
    int i = 0;

    while (guess[i] != '\0') {
        if (!((guess[i] >= 'a' && guess[i] <= 'z') ||
              (guess[i] >= 'A' && guess[i] <= 'Z'))) {
            return 0;
        }

        i++;
    }

    if (i != 5) {
        return 0;
    }

    return 1;
}

void lowerGuess(char guess[]) {
    int i = 0;

    while (guess[i] != '\0') {
        if (guess[i] >= 'A' && guess[i] <= 'Z') {
            guess[i] = guess[i] + 32;
        }

        i++;
    }
}

int checkGuess(char word[], char guess[]) {
    int i;
    int j;
    int correct = 0;
    int found;

    for (i = 0; i < 5; i++) {
        if (guess[i] == word[i]) {
            printf("%c", guess[i] - 32);
            correct++;
        } else {
            printf("%c", guess[i]);
        }
    }

    printf("\n");

    if (correct == 5) {
        return 1;
    }

    for (i = 0; i < 5; i++) {
        if (guess[i] == word[i]) {
            printf(" ");
        } else {
            found = 0;

            for (j = 0; j < 5; j++) {
                if (guess[i] == word[j]) {
                    found = 1;
                }
            }

            if (found) {
                printf("^");
            } else {
                printf(" ");
            }
        }
    }

    printf("\n");

    return 0;
}

void winMessage(int guessCount) {
    printf("You won in %d guesses!\n", guessCount);

    if (guessCount == 1) {
        printf("BIG DUBS\n");
    } else if (guessCount <= 3) {
        printf("Amazing\n");
    } else {
        printf("Nice\n");
    }
}
