#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define size 1048576


 void main(){
char buffer[size];
int i;
i = read(0,&buffer,size);
while (i>0){
write(1,&buffer,size);
i = read(0,&buffer,size);
}

}
