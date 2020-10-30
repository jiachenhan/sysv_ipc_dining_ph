#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "myipc.h"

int main(int argc, char *argv[])
{
	semaphore mutex,S[N];
    int states[N];
    union semun sem_union;

	if ( (mutex=semget((key_t)KEY_MUTEX,1,0666|IPC_CREAT)) == -1 ) {
		fprintf(stderr,"Failed to create semaphore!"); 
		exit(EXIT_FAILURE);
	}
    for(int i=0;i<N;i++){
        if((S[i]=semget((key_t)s(i),1,0666|IPC_CREAT))==-1){
            fprintf(stderr,"Failed to creat semaphore!");
            exit(EXIT_FAILURE);
        }
    }
    sem_union.val = 1;
    if (semctl(mutex, 0, SETVAL, sem_union) == -1) {
	    fprintf(stderr,"Failed to set semaphore!"); 
	    exit(EXIT_FAILURE);
	}
    for(int i=0;i<N;i++){
        sem_union.val=1;
        if(semctl(S[i],0,SETVAL,sem_union)==-1){
            fprintf(stderr,"Failed to set semaphore!");
            exit(EXIT_FAILURE);
        }
    }


  	exit(EXIT_SUCCESS);
}
