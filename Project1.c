#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int SharedVariable = 0;

/*Create a void function called SimpleThread  
 *This function takes a pointer called i
 *This function will be used to create the child threads
 */
void *SimpleThread(void *i) {
    //Create an int pointer called p
    //Have the actual value of the pointer = i
    int *p;
    p = i;
    int num, val = 0;

    //For loop that loops through 0 - 20
    for (num = 0; num < 20; num++) {
        if (rand() > RAND_MAX / 2) {
            usleep(500);
        }
        val = SharedVariable;
        printf("*** thread %d sees value %d\n", *p, val);
        SharedVariable = val + 1;
    }
    val = SharedVariable;
    printf("Thread %d sees final value %d\n", *p, val);
}

int main(int argc, char *argv[]) {
    //create a pointer thread called tid
    pthread_t *threadID;
    int i;
    //check to see if the user argument is not 2 return an error
    if (argc != 2) {
        printf("Wrong command usage.");
        printf("Type: ./a.out #");
        return 0;
    }
    //if they use the command correctly
    else {
        //go through the argument vector and see if it's an integer
        bool isValidArgument[] = {true, false};
        bool valid = true;
        for (i = 0; i <strlen(argv[1]); i++) {
            //if the argument vector element is less than the characters
            //0 and 9 return false, because that means it's not an actual
            //integer (ASCII)
            if (argv[1][i] < '0' || argv[1][i] > '9') {
                valid = false;
                break;
            }
        }
        //if it's not a pos integer or an integer at all then tell them
        if (valid == false) {
            printf("\nPlease provide a positive integer: \n");
        }
        else {
            //convert the argument from string to an int
            int numberOfThreads = atoi(argv[1]);
            
            //make the actual threadID pointer equal to a pointer of the allocated 
            //memory size of the number of threads
            threadID = (pthread_t*)malloc(sizeof(pthread_t)*numberOfThreads);
            
            //create an integer pointer that gets the allocated memory size of
            //number of threads (child threads)
            int *numberOfChildThreads = (int *)malloc(sizeof(int)*numberOfThreads);
            
            //create the number for child threads in the pointer
            for (i = 0; i < numberOfThreads; i++) {
                numberOfChildThreads[i] = i;
            
            //at each index of threadID create a parent thread
            //with their child threads
            }
            for (i = 0; i < numberOfThreads; i++) {
                //create thread(at index of threadID, use default attributes, run Simplethread, and 
                //pass in the value at the current index of numberOfChildThreads)
                pthread_create(&threadID[i], NULL, SimpleThread, &numberOfChildThreads[i]);
            
            //join the child threads with their parent threads but do not copy the exit status
            //of the target thread into a location
            }
            for (i = 0; i < numberOfThreads; i++) {
                pthread_join(threadID[i], NULL);
            }
        }
    }
    //Terminate out of main function
    exit(0);
}