#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



//static char input[128] = " ";

typedef struct{
    char character;
    int number;
}StringInt;

StringInt * letter_indexes(char *s, int *returnSize){
    StringInt *result = (StringInt*)malloc(sizeof(StringInt)*5);
    for(int i = 0; s[i]!= '\n';i++){
        if(s[i] != '*'){
            result[(*returnSize)].character = s[i];
            result[(*returnSize)++].number = i;
        }  
    }
    result = (StringInt*)realloc(result, sizeof(StringInt)*(*returnSize));
    return result;
}

int read(const char **a)
{
  int result = 0;
  FILE *f = fopen("words.txt", "r");
  char word[64];
  while (fscanf(f, "%s", word) != EOF)
    a[result++] = strdup(word);
  return result;
}

bool is_valid(StringInt a, const char *s){
    return s[a.number] == a.character;
}

bool valid_word(StringInt *a,int n, const char *s){
    for(int i = 0; i <n;i++){
        if(!is_valid(a[i], s))
            return false;
    }
    return true;
}

int add_words(StringInt *a, int n, const char **b, int m, const char **c){
    int result = 0;
    for(int i = 0; i < m;i++){
        if(valid_word(a,n,b[i]))
            c[result++] = b[i];
    }
    return result;
}

void print_array(const char **a , int n){
    for(int i = 0; i < n;i++)
        printf("%s\n", a[i]);
}


void input(void){
    printf("Enter the choice word: unknown letters should be displayed with a '*'\n Example: audi* or **dio both represent the word 'AUDIO'\n");
    char initial[16];
    const char *words[13000];
    int n_words = read(words);
    int n_letters = 0;
    fgets(initial,sizeof initial, stdin);
    if(initial != NULL && strlen(initial) == 6){
        StringInt* indexes = letter_indexes(initial,&n_letters);
        const char *output[10000];
        int n_output = add_words(indexes, n_letters, words, n_words, output);
        printf("\nALL POSSIBLE ANSWERS:\n");
        print_array(output,n_output);
    }
}

int main(void){
    input();
    return 0;
}
