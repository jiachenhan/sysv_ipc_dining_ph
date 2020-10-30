#define KEY_MUTEX 100
#define s(i) 101+i
#define N 5
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef int semaphore;

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

extern void sem_p(semaphore sem_id);
extern void sem_v(semaphore sem_id);