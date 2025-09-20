#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>   // for sleep()
#include <stdbool.h>

volatile bool isAnswered = false;   // shared flag between threads

// Timer thread function
void* timerFunc(void* arg) {
    for (int i = 10; i >= 1; i--) {
        if (isAnswered) {
            return NULL; // Exit timer if user already answered
        }
        printf(" >> %d\n", i);
        sleep(1); // wait for 1 second
    }

    if (!isAnswered) {
        printf("\nTIME'S UP!\n");
        exit(0); // terminate program if no answer
    }
    return NULL;
}

// Quiz thread function
void* quizFunc(void* arg) {
    char answer[100];

    printf("What is the capital of Japan?\n");
    printf("Your answer: ");
    fflush(stdout);

    fgets(answer, sizeof(answer), stdin);
    // remove newline character
    answer[strcspn(answer, "\n")] = 0;

    isAnswered = true;

    if (strcasecmp(answer, "Tokyo") == 0) {
        printf("Correct! You're a winner!\n");
    } else {
        printf("Sorry, the correct answer is Tokyo.\n");
    }

    exit(0); // end program after answer
    return NULL;
}

int main() {
    pthread_t timerThread, quizThread;

    printf("Quiz starts now! You have 10 seconds.\n");

    // create threads
    pthread_create(&timerThread, NULL, timerFunc, NULL);
    pthread_create(&quizThread, NULL, quizFunc, NULL);

    // wait for threads to finish (if they don't exit earlier)
    pthread_join(timerThread, NULL);
    pthread_join(quizThread, NULL);

    return 0;
}
