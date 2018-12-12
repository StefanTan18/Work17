#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

union semun{
  int val;
  struct semid_ds* buf;
  struct seminfo* _buf;
}

void writer(int semdesc){

  union semun arg;
  
  int semVal = semctl(semdesc,0,GETVAL,arg);
  printf("Semctrl %d\n",semVal);
}

int main(){
  writer(1);
  return 0;
}
