#include <signal.h>
#include <stdio.h>
#include <unistd.h>
void rotina(int p)
{
	fwrite("nao vou termininar\n",stdout)
	sleep(2);
}

int main()
{
	int i=0;
	signal(3, rotina);
	signal(SIGHUP, rotina);

	while(1){ printf("[%d]\n",i++);}
return 1;
} 
