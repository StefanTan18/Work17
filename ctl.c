#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

union semun {
  int val;
  struct semid_ds *buf;
  struct seminfo *_buf;
};

int main() {
  key_t key;
  int shmid, semid, fd;
  char *data;
  char *story;
  char r[200];
  union semun arg;
  char *args[] = {"cat", "story.txt"};

  key = ftok("ctl.c", 'R');
  
  fgets(r, 200, stdin);
  if (!strcmp(r, "-c\n")) {
    shmid = shmget(key, 200, 0644 | IPC_CREAT);
    data = shmat(shmid, (void *)0, 0);

    semid = semget(key, 1, IPC_CREAT | IPC_EXCL );

    semctl(semid, 0, SETVAL, 1);
    
    fd = open("story.txt", O_CREAT | O_TRUNC, 0644);
    close(fd);
  }
  
  if (!strcmp(r, "-r\n")) {
    shmid = shmget(key, 200, 0);
    semid = semget(key, 1, 0);
    
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);

    semctl(semid, 0, IPC_RMID, arg);

    printf("The story so far...\n");
    fd = open("story.txt", O_RDONLY);
    read(fd, story, 250);
    printf("%s\n", story);
    close(fd);
  }

  if (!strcmp(r, "-v\n")) {
    printf("The story so far...\n");
    fd = open("story.txt", O_RDONLY);
    read(fd, story, 250);
    printf("%s\n", story);
    close(fd);
  }

  return 0;
}
