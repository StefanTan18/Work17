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


void writer(int semdesc,key_t key,int size){

  union semun arg;
  struct sembuf buf;
  char line[250];

  int fd = open("story.txt", O_WRONLY|O_APPEND);
  int shmid = shmget(key,size,0644);
  int semVal = semctl(semdesc,0,GETVAL,arg);
  
  buf.sem_num = 0;
  buf.sem_op = -1;
  buf.sem_flag = SEM_UNDO;

  semop(semdesc,&buf,1);

  char *prev_line = shmat(shmid,0,0);
  printf("Previous line: %s \n", prev_line);

  printf("Enter next line: ");
  fgets(line,250,stdin);
  line[strlen(line) - 1] = '\0';
  strcpy(prev_line,line);
  write(fd,line,250);
  clode(fd);

  buf.sem_op = +1;
  semop(semdesc,&buf,1);
  
  //printf("Semctrl %d %d %s\n",semVal,errno,strerror(errno));
  return;
}


