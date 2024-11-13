#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <sys/ipc.h>


#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid, semid;

    printf("Server program: Shared Memory Key = %d\n", key);

    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    char *shm = (char *)shmat(shmid, NULL, 0);

    printf("Server program: Process attached at address %p\n", shm);

    semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    while (1) {
        char message[SHM_SIZE];
        printf("Server program: Enter a message to write to shared memory: ");
        fgets(message, SHM_SIZE, stdin);

       /* if (strncmp(message, "exit", 4) == 0) {
            break;
        }*/

        strcpy(shm, message);
        printf("Server program: Message written to shared memory.\n");

        // Signal the semaphore to notify the client
        struct sembuf sb = {0, 1, 0};
        semop(semid, &sb, 1);
    }

    shmdt(shm);

    // Mark the shared memory segment for removal
    shmctl(shmid, IPC_RMID, NULL);

    // Remove the semaphore
    semctl(semid, 0, IPC_RMID);

    return 0;
}

