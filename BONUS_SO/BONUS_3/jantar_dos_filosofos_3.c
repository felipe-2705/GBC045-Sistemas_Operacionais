/* problema jantar dos filosofos
 Autor: Felipe Augusto Ferreira de Castro
programa usando implementaçao de semaforos e para resolver o problema do deadlock de acordo com o exercicio 4 do Bonus III*/
// fonte livro do tanembaum

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define pensando 0
#define comendo 1
#define esperando 2
#define garfo_esquerda (*filosofo)%5
#define garfo_direita ((*filosofo)+1)%5
#define esquerda (i+5-1)%5
#define direita  (i+1)%5

sem_t sema;                        // semafaro para regiao critica
sem_t filo[5];                     // semafaro para cada filosofo
int estado_filosofo[5]={-1,-1,-1,-1,-1}; // vetor que guarda o estado de cada filosofo

// neste programa foi convencionado que o valor i sera usado para distinguir os filosofos;

int pensar(int i)
{

  printf("filosofo[%d] esta pensando\n",i);
  sleep(2);                       // o filsofo pensa por 2 segundos
  return 1;                       //apenas um aviso que o filosofo terminou de pensar
}
int teste(int i)
{
  if(estado_filosofo[i]=esperando && estado_filosofo[esquerda]!= comendo && estado_filosofo[direita] != comendo)
  {
     estado_filosofo[i]=comendo;
     printf("filosofo[%d] pegou os garfos e esta comendo\n",i);
     sem_post(&filo[i]);                                   // libera o filosofo da espera caso estivesse esperando
  }
}

int pegar_garfos(int i)           // retorna 1 se sucesso e 0 caso fracasso
{
  sem_wait(&sema);          // entra na regiao critica
   estado_filosofo[i]=esperando;
   teste(i);                        // testa se os filosofos adjacentes nao estao comendo
   sem_post(&sema);
   sem_wait(&filo[i]);
    return 1;
}

int por_garfos(int i)
{
    sem_wait(&sema);
    estado_filosofo[i]=pensando;
    printf("filosofo[%d] pos os garfos\n",(i));
    teste(esquerda);                // caso o filosofo estiver esperando , libera-o
    teste(direita);
    sem_post(&sema);
  return 1;
}
int comer(int i)
{
       sleep(rand()%10);
       return 1;
}



void* filosofo(void* i)
{
       int* filosofo= (int*) i;   // convertendo o void* devolta para um valor inteiro
while(1)
{     int flag=1;
      pensar(*filosofo);
      pegar_garfos(*filosofo);
      comer((*filosofo));
      por_garfos(*filosofo);


}

}


int main ()
{   pthread_t tid;
  int i[5];

  for(int j=0;j<5;j++)
  {
      if(sem_init(&filo[j],0,1)==-1)
      {
        printf("erro ao inicializar o semafaro");
        exit(0);
      }
  }
  sem_init(&sema,0,1);

     for( int j=0;j<=4;j++)
    {
       i[j]=j;
       pthread_create(&tid,NULL,filosofo,(void*)(&i[j]));
     }
  pthread_join(tid,NULL);
  return 1;
}
