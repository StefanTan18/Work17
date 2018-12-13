#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define SEM_KEY 1234

union semun {
  int val;
  struct semid_ds *buf;
  struct seminfo *_buf;
}

int ctl() {
  key_t key;
  int shmid, semd, fd;
  char *data;
  char r[200];
  union semun arg;
  
  fgets(r, 200, stdin);
  if (!strcmp(r, "-c\n")) {
    key = ftok("file", 'R');
    shmid = shmget(key, 200, 0644 | IPC_CREAT);
    data = shmat(shmid, (void *)0, 0);

    semd = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL );

    fd = open("story.txt", O_CREAT | O_TRUNC | O_EXCL);
  }
  
  if (!strcmp(r, "-r\n")) {
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);

    semctl(semd, 0, IPC_RMID, arg);

    //excvp(cat)
  }
