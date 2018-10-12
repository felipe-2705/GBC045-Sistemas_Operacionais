/// bonus comunicaçao entre processos
///Autor: Felipe Augusto Ferreira de Castro
///Universidade federal de uberlândia
/// processos produtores p4,p5,p6


#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <signal.h>

#define MEM_SZ 100 // 10*4 para o tamanho da fila + 4 do controle de posiçao da fila + 4 para o semafaro
#define fila_sz 10 // 10*size(int) = 40 bytes


// fila 1 compartilhada  entre os p1,p2,p3,p4(consumidor em outro arquivo.c)
struct fila_1{
  int prox; // proxima posiçao a ser incirida, quanto o valor for 10 a fila estara cheia;
  sem_t mutex;
  sem_t cheia;
  sem_t pid;
  pid_t process4;
  int fila[fila_sz];
};

struct fila_1 * signal_handler;
///////////////////////////////////////////////////////
// funçoes para manipular a fila compartilhada

int fila1_init(struct fila_1* f)
{

  if(f==NULL)
  {
    return -1;
  }

  f->prox=0;
  if(sem_init(&f->mutex,1,1)==-1)
  {
    printf ("erro ao iniciar o semafaro da fila 1\n");
    return 0;
  }
  if(sem_init(&f->cheia,1,0)==-1)
  {
    printf ("erro ao iniciar o semafaro da fila 1\n");
    return 0;
  }
  if(sem_init(&f->pid,1,0)==-1)
  {
    printf ("erro ao iniciar o semafaro da fila 1\n");
    return 0;
  }


  return 1;
}
int fila1_cheia(struct fila_1* f)
{
  if(f==NULL)
  {
    return -1;
  }

  if(f->prox>=10)
  {
    return 1;  // fila esta cheia;
  }

  return 0;
}

void remove_fila(int p)
{
 sem_wait(&signal_handler->cheia);
  for(int i=0;i<fila_sz;i++)
  {
    printf("%d\n",signal_handler->fila[i]);
  }
  signal_handler->prox=0;
 sem_post(&signal_handler->mutex);
}


////////////////////////////////////////////////////


int main ()
{
pid_t pids[2]={-1,-1}; // guardo o pid do processo; nao sera diferenciado os tres filhos, pois nao sera necessario
int status; // estatus para o wait();
key_t key =43210; // chave de acesso para a fila compartilhada;
struct fila_1 * fila_ptr;  // ponteiro para a area compartilhada formatada
void* shared_memory = (void*)0; // um ponteiro nulo para receber o endereço da area compartilhada
int shmid;



//////////////////////////////////////////////////////////////
// criando e formatando a fila compartilhada 1;
    shmid = shmget(key,MEM_SZ,0666|IPC_CREAT);   // cria uma area de escrita e leitura entre processos
if(shmid== -1)
{
  printf("error shmget\n");
  exit(-1);
}
      shared_memory= shmat(shmid,(void*)0,0);
      if(shared_memory == (void*)-1)
      {
        printf(" ERROR shmat\n");
        exit(-1);
      }
      fila_ptr = (struct fila_1*)shared_memory;  // convertendo a area na estrutura de fila_1

      if(fila1_init(fila_ptr)!=1)
      {
         exit(-1);

      }

      //////////////////////////////////////// fim da criaçao da area compatilhada /////////////////////////////
  // criando processos produtores p5,p6;
   fila_ptr->process4 = getpid();
   sem_post(&fila_ptr->pid);// sinaliza que o pid esta colocado

  for(int i=0;i<2;i++)
  {
    pids[i]=fork();
    if(pids[i]==0)break;
  };
/// processos filhos
  if(pids[0]==0 && pids[1]!=0) //processo 5
  {
        getchar();
  }
  if(pids[0]!=0 && pids[1]==0)//processo 6
  {
        getchar();
  }
  if(pids[0]!=0 && pids[1]!=0){ // processo 4

  while(1){
    signal_handler=fila_ptr;
     signal(3,remove_fila);

   };
  }
  getchar();
  return 1;
}
