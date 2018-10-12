/* problema jantar dos filosofos
 Autor: Felipe Augusto Ferreira de Castro
programa usando implementaçao de semaforos de acordo com o exercicio 3 do Bonus III*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define garfo_esquerda (*filosofo)%5
#define garfo_direita ((*filosofo)+1)%5


sem_t sema;
//sem_t sem_garfo[5];
int garfo[5]={1,1,1,1,1};
// neste programa foi convencionado que o valor i sera usado para distinguir os filosofos;

int pensar(int i)
{

  printf("filosofo[%d] esta pensando\n",i);
  sleep(2);                       // o filsofo pensa por 2 segundos
  return 1;                       //apenas um aviso que o filosofo terminou de pensar
}

int pegar_garfo(int garf,int i)           // retorna 1 se sucesso e 0 caso fracasso
{
  int flag =1;
while(flag){
    sem_wait(&sema);
    if(garfo[garf]){
      printf("filosofo[%d] pegou garfo\n",i);
      garfo[garf]=0;
      flag=0;                  // pega o garfo
    }
    sem_post(&sema);
    if(flag){
    printf("filosofo[%d] esta esperando garfo\n",i);
      sleep(2);
    };
}
    return 1;
}

int por_garfo(int garf,int i)
{
    sem_wait(&sema);
    printf("filosofo[%d] pos garfo\n",i);
    garfo[garf]=1;      // libera o garfo
    sem_post(&sema);

  return 1;
}
int comer(int i)
{
      printf("filosofo[%d] esta comendo\n",i);
       sleep(rand()%10);
       return 1;
}



void* filosofo(void* i)
{
       int* filosofo= (int*) i;   // convertendo o void* devolta para um valor inteiro
while(1)
{     int flag=1;
      pensar(*filosofo);
      pegar_garfo(garfo_esquerda,(*filosofo));
      pegar_garfo(garfo_direita,(*filosofo));
      comer((*filosofo));
      por_garfo(garfo_esquerda,(*filosofo));
      por_garfo(garfo_direita,(*filosofo));



}

}


int main ()
{   pthread_t tid;
  int i[5];

    sem_init(&sema,0,1);


     for( int j=0;j<=4;j++)
    {
       i[j]=j;
       pthread_create(&tid,NULL,filosofo,(void*)(&i[j]));
     }
  pthread_join(tid,NULL);
  return 1;
}
