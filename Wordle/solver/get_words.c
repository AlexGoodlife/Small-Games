#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void strings_readwords(FILE *f,FILE *e)
{
  char word[256];
  while (fscanf(f, "%s", word) != EOF){
    if(strlen(word) == 5){
        printf("here\n");
        fprintf(e, "%s%s", "\n", word);
    }
  }
}

int main(int argc, char **argv){
    const char* input = argv[1];
    //const char* output= argv[1];
    FILE *f = fopen(input, "r");
    FILE *e = fopen("words.txt", "w");
    strings_readwords(f,e);
    return 0;
}