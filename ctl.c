#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define SEM_KEY 1234

int ctl() {
  key_t key;
  int shmid, fd;
  char *data;
  char r[200];
  
  fgets(r, 200, stdin);
  if (!strcmp(r, "-c\n")) {
    key = ftok("file", 'R');
    shmid = shmget(key, 200, 0644 | IPC_CREAT);
    data = shmat(shmid, (void *)0, 0);

    fd = open("story.txt", O_CREAT | O_TRUNC | O_EXCL);
  }
