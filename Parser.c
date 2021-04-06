#include <stdio.h>
#include <stdlib.h>

void readline(char *path)
{
    FILE *fp;
    fp = fopen(path,"r");
    size_t numBytes = 1048576;
    char *text = (char *) calloc(numBytes,sizeof(char ));
    fread(text,numBytes,1,fp);
    puts(text);
}

int main()
{
    char *path = ".gitignore";
    readline(path);
}
