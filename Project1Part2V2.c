//For clarity, comments from part 1 will not be copied over to show the changes
//from the two source codes

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int SharedVariable = 0;

//initialize a mutex
pthread_mutex_t lock;

//initialize a barrier
pthread_barrier_t barrier;

void *SimpleThread(void *i) {
    int *p;
    p = i;
    int num, val = 0;

    for (num = 0; num < 20; num++) {
        
        #ifdef PTHREAD_SYNC
        //locks given mutex
        pthread_mutex_lock(&lock);
        #endif
        
        val = SharedVariable;
        printf("*** thread %d sees value %d\n", *p, val);
        SharedVariable = val + 1;

        #ifdef PTHREAD_SYNC
        //synchronization
        pthread_mutex_unlock(&lock);
        #endif
    }
    //add a barrier that each thread can read the value of SharedVariable  and show what is the final of each thread. 
    pthread_barrier_wait(&barrier);
    printf("Thread %d sees final value %d\n", *p,SharedVariable);
}

int main(int argc, char *argv[]) {
    pthread_t *threadID;
    int i;

    // initializing a mutex.
    pthread_mutex_init(&lock, NULL);

    if (argc != 2) {
        printf("Wrong command usage.");
        printf("Type: ./a.out #");
        return 0;
    }
    else {
        bool isValidArgument[] = {true, false};
        bool valid = true;
        for (i = 0; i <strlen(argv[1]); i++) {
            if (argv[1][i] < '0' || argv[1][i] > '9') {
                valid = false;
                break;
            }
        }
        if (valid == false) {
            printf("\nPlease provide a positive integer: \n");
        }
        else {
            int numberOfThreads = atoi(argv[1]);

            // creating a new barrier
            pthread_barrier_init(&barrier, NULL, numberOfThreads );

            threadID = (pthread_t*)malloc(sizeof(pthread_t)*numberOfThreads);
            
            int *numberOfChildThreads = (int *)malloc(sizeof(int)*numberOfThreads);
            
            for (i = 0; i < numberOfThreads; i++) {
                numberOfChildThreads[i] = i;
            }

            for (i = 0; i < numberOfThreads; i++) {
                pthread_create(&threadID[i], NULL, SimpleThread, &numberOfChildThreads[i]);
            }

            for (i = 0; i < numberOfThreads; i++) {
                pthread_join(threadID[i], NULL);
            }
        }
    }
    exit(0);
}