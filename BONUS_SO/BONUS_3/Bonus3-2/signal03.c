#include <signal.h>
#include <stdio.h>
#include <unistd.h>

main()
{
   while(3)
   {
	kill(2426, SIGHUP); 
     /*??? é o pid do processo criado com a execucao do signal01.c*/
	sleep(5);	
   }
} 
 
