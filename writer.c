#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

union semun{
  int val;
  struct semid_ds* buf;
  struct seminfo* _buf;
};


int main(){

  key_t key = ftok("ctl.c", 'R');
  union semun arg;
  struct sembuf buf;
  char line[250];

  int fd = open("story.txt", O_WRONLY|O_APPEND);
  int shmid = shmget(key, 200, 0644);
  int semid = semget(key, 1, 0);
  int semVal = semctl(semid,0,GETVAL,arg);

  if (!semVal) {
    printf("Segment is unavailable.\n");
    return 0;
  }
  
  buf.sem_num = 0;
  buf.sem_op = -1;
  buf.sem_flg = SEM_UNDO;

  semop(semid,&buf,1);

  char *prev_line = shmat(shmid,0,0);
  if (!*prev_line) {
    printf("New Story!\n");
  }
  else {
    printf("Previous line: %s \n", prev_line);
  }

  printf("Enter next line: ");
  fgets(line,250,stdin);
  line[strlen(line) - 1] = '\0';
  strcpy(prev_line,line);
  write(fd,line,250);
  close(fd);
  
  buf.sem_op = 1;
  semop(semid,&buf,1);
  
  //printf("Semctrl %d %d %s\n",semVal,errno,strerror(errno));
  return 0;
}


