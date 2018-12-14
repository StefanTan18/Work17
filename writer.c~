#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

union semun{
  int val;
  struct semid_ds* buf;
  struct seminfo* _buf;
};


void writer(int semdesc,key_t key){

  union semun arg;
  struct sembuf buf;
  
  int semVal = semctl(semdesc,0,GETVAL,arg);
  
  if(semVal > 0){
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flag = SEM_UNDO;

    printf("Enter next line: \n");
    fgets(
	  );

    buf.sem_num = 0;
    buf.sem_op = +1;
    buf.sem_flag = SEM_UNDO;
  }
  
  printf("Semctrl %d %d %s\n",semVal,errno,strerror(errno));
  return;
}


