/// bonus comunicaçao entre processos
///Autor: Felipe Augusto Ferreira de Castro
///Universidade federal de uberlândia

#include <stdio.h>
#include <stdlib.h>
#include <semapharo.h>
#include <pthread.h>





int main ()
{
pid_t pids[7]; // vetor para guardar os pids dos processos

  // criando processos produtores p1,p2,p3;
  for(int i=0;i<3;i++)
  {
    pids[i]=fork();
  }
  return 1;
}
