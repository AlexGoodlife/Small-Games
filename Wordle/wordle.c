#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define WORDS_SIZE 4267

bool won = false;

char *colors[] = {"\033[0;31m", "\033[0;33m", "\033[0;32m"}; // indexes 0 is red, 1 is yellow, 2 is green

int random_number(int lower, int upper){
    return (rand() % (upper-lower+1)) + lower;
}

char* to_lower_case(char *s){
    char *r = (char*)malloc(sizeof(char)*strlen(s)+1);
    int result = 0;
    for(int i = 0;s[i];i++){
        if(s[i] >= 65 && s[i] <= 90)
            r[result++] = s[i] + 32;
        else
            r[result++] = s[i];
    }
    r[result] = '\0';
    return r;
}

int readwords(FILE *f,  char **a){
  int result = 0;
  char word[8];
  while (fscanf(f, "%s", word) != EOF)
    a[result++] = strdup(word);
  return result;
}

const char* setup(){
    char *words[WORDS_SIZE];
    FILE *f = fopen("words.txt", "r");
    int word_size = readwords(f,words);
    int random = random_number(0, word_size-1);
    const char *to_guess = words[random];
    return to_guess;
}

bool is_present(const char *s, char x, int* identifiers){
    for(int i = 0; s[i];i++)
        if(s[i] == x && identifiers[i] != 2)
            return true;
    return false;
}

void print_guess(char*s, int* identifiers){
    for(int i = 0; s[i];i++){
       printf("%s", colors[identifiers[i]]);
       printf("%c \033[0m", s[i]);
    }
    printf("\n");
}

bool game_loop(const char* to_guess){
    char input_[8];
    scanf("%s", input_);
    char* input = to_lower_case(input_);
    if(strlen(input) != 5){
        printf("\033[0;31mGuess must be 5 letters long!!\033[0m\n");
        return game_loop(to_guess);
    }
    int *identifiers = (int*)calloc(5, sizeof(int));
    for(int i = 0; input[i];i++)
        if(input[i] == to_guess[i])
            identifiers[i] = 2;
    for(int i = 0; input[i];i++){
        if(identifiers[i] != 2 &&is_present(to_guess,input[i], identifiers))
            identifiers[i] = 1;
        else if(identifiers[i] != 2)
            identifiers[i] = 0;
    }
    print_guess(input, identifiers);
    free(identifiers);
    if(strcmp(to_guess, input) == 0){
        won = true;
        return false;
    }
    return true;
}

void game(){
    printf("\033[1;35mWelcome to Wordle, you have 6 guesses\n GOOD LUCK\033[0m\n");
    const char *to_guess = setup();
    int tries = 0;
    printf("TRY NUMBER: %d\n", tries+1);
    while(game_loop(to_guess) && tries < 5){
        tries++;
        printf("TRY NUMBER: %d\n", tries+1);
    }
    if(won)
        printf("\033[1;32mCongratulations you got it right! Press r to play again\033[0m\n");
    else
        printf("\033[1;31mGame over! Word was \033[1;37m%s\033[0m\n Press r to play again\n", to_guess);
    char c = getch();
    if(c == 'r'){
        system("cls");
        won = false;
        game();
    }
}


int main(void){
    time_t seconds = time(NULL);
    srand(seconds);
    game();
    return 0;
}