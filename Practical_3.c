#include<stdio.h>
#include <pthread.h>
#include <unistd.h>

int marks[5] = {75, 80, 65, 90, 85};
int total = 0;
float percentage = 0.0;
pthread_mutex_t lock;

void* thread1_total(void* arg) {
    pthread_mutex_lock(&lock);
    total = 0;
    for (int i = 0; i < 5; i++) {
        total += marks[i];
        printf("Adding mark %d: %d\n", i+1, marks[i]);
        sleep(1);
    }
    printf("Total Marks = %d\n", total);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void* thread2_percentage(void* arg) {
    sleep(2);
    
    pthread_mutex_lock(&lock);
    percentage = (float)total / 5;
    printf("Percentage = %.2f\n", percentage);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void* thread3_result(void* arg) {
    sleep(4);
    
    pthread_mutex_lock(&lock);
    if (percentage >= 40)
        printf("Result: PASS\n");
    else
        printf("Result: FAIL\n");
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }
    
    printf("Main: Program started\n");
    printf("Main: Creating thread 1 (Total Calculation)\n");
    
    if (pthread_create(&threads[0], NULL, thread1_total, NULL) != 0) {
        printf("Failed to create thread 1\n");
        return 1;
    }
    
    printf("Main: Creating thread 2 (Percentage Calculation)\n");
    
    if (pthread_create(&threads[1], NULL, thread2_percentage, NULL) != 0) {
        printf("Failed to create thread 2\n");
        return 1;
    }
    
    printf("Main: Creating thread 3 (Result Determination)\n");
    
    if (pthread_create(&threads[2], NULL, thread3_result, NULL) != 0) {
        printf("Failed to create thread 3\n");
        return 1;
    }
    
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
        printf("Main: Thread %d has terminated\n", i+1);
    }
    
    pthread_mutex_destroy(&lock);
    
    printf("Main: Program completed\n");
    return 0;
}
void thread2_percentage() {
    float percentage = (float)total / 5;
    printf("Percentage = %.2f\n", percentage);
}

void thread3_result() {
    if ((float)total / 5 >= 40) {
        printf("Result: PASS \n");
    } else {
        printf("Result: FAIL \n");
    }
}

int main() {
    // Taking user input
    printf("Enter marks of 5 subjects:\n");
    for (int i = 0; i < 5; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%d", &marks[i]);
    }

    thread1_total();
    thread2_percentage();
    thread3_result();

    return 0;
}
