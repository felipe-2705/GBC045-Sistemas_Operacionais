#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define Buffer_size 1048576
void main(){
char buffer[Buffer_size];
int i;
i = fread(&buffer, 1, Buffer_size, stdin);
while (i>0){
fwrite(&buffer, 1, Buffer_size, stdout);
i = fread(&buffer,1, Buffer_size, stdin);
}
}
