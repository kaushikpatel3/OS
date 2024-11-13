#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>  // Add this line

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid, semid;

    printf("Client program: Shared Memory Key = %d\n", key);

    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    char *shm = (char *)shmat(shmid, NULL, 0);

    printf("Client program: Process attached at address %p\n", shm);

    semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    while (1) {
        // Wait for the semaphore to be signaled by the server
        struct sembuf sb = {0, -1, 0};
        semop(semid, &sb, 1);

        printf("Client program: Reading message from shared memory...\n");
        printf("Message from server: %s\n", shm);
    }

    shmdt(shm);

    return 0;
}

