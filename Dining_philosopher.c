#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "myipc.h"

semaphore mutex,S[N];
int states[N]={HUNGRY};
union semun sem_union;

void take_forks(int i);
void put_forks(int i);
void test(int i);
void phliosophere(int no);


// union semun {
//                int              val;    /* Value for SETVAL */
//                struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
//                unsigned short  *array;  /* Array for GETALL, SETALL */
//                struct seminfo  *__buf;  /* Buffer for IPC_INFO
//                                            (Linux-specific) */
//            };            //用于设置信号量所需要的联合体
 
 
//  int semid;
  
//  int sem_del(int semid)  //删除一个信号量集
//  {
//     int ret;
//     ret=semctl(semid,0,IPC_RMID,0);  //不知道信号量集合中有几个信号量，故对第2个参数设为0
//     if (ret==-1)
//         printf("semdel falied\n");
//     return 0;
//  }
  
 
//  void wait_for_2fork(int no)
//  {
//      int left =no;    //左刀叉
//      int right = (no+1)%5;    //右刀叉
//      struct sembuf buf[2] ={{left,-1,0},{right,-1,0}}; //-1表示为P操作
      
//      semop(semid,buf,2);  //等待获取刀叉(资源)
//  }
  
//   void free_2fork(int no)
//  {
//      int left =no;    //左刀叉
//      int right = (no+1)%5;    //右刀叉
//      struct sembuf buf[2] ={{left,1,0},{right,1,0}}; //-1表示为P操作
      
//      semop(semid,buf,2);  //释放获取的刀叉(资源)
//  }

void take_forks(int i){
    sem_p(mutex);
    //printf("wrong\n");
    states[i]=HUNGRY;
    test(i);
    sem_v(mutex);
    sem_p(S[i]);
}

void put_forks(int i){
    sem_p(mutex);
    states[i]=THINKING;
    test(LEFT);
    test(RIGHT);
    sem_v(mutex);
}

void test(int i){
    //printf("wrong\n");
    if(states[i]==HUNGRY&&states[LEFT]!=EATING&&states[RIGHT]!=EATING){
        //printf("wrong\n");
        states[i]=EATING;
        sem_v(S[i]);
    }
}

 void phliosophere(int no)
 {
     //srand(getpid());      //以进程号作为随机数的种子
     while(1)
     {
         printf("philosophere %d is thinking\n",no);
         sleep(1);
         printf("philosophere %d is hungry\n",no);
         //sleep(rand()%5+1);
         //printf("wrong\n");
         take_forks(no);            //获取刀叉
         printf("philosophere %d is eating\n",no);
         sleep(1);
         put_forks(no);             //释放刀叉
     }
 }
  
 int main()
 {

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
     
    int no=0;    //进程id
    pid_t pid;
    for(int i=1;i<5;i++)
    {
        pid=fork();
        if(pid==-1)
        {
            printf("fork failed\n");
            return 0;
        }
        if(pid==0)   //子进程
        {
            no=i;
            break;
        }
    }
    for(int i=0;i<N;i++){
        states[i]=HUNGRY;
    }
    phliosophere(no);         //哲学家行为实现
 
    return 0;
 }