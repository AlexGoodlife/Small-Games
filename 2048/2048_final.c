#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <conio.h>
const char* author = "Alexandre Boavida 68781";

#define BOARD_SIZE 4

void print_board(int *a, int n){
    if (n > 0)
    {   if(a[0] == 0)
            printf("[%s]", "    ");
        else
            printf("[%4d]", a[0]);
        for (int i = 1; i < n; i++)  // i = 1
            if(a[i] == 0)
                printf(" [%s]", "    ");
            else
                printf(" [%4d]", a[i]);
    }
    printf("\n");
}

void display_board(int n, int a[n][n]){
    for(int i = 0; i < n;i++)
        print_board(a[i], n);
}

//copy symetric matrix a to matrix b
void matrix_copy(int n, int a[n][n], int b[n][n]){
    for(int i = 0; i < n;i++)
        for(int j = 0; j< n;j++)
            b[i][j] = a[i][j];
}

int matrix_equals(int n, int a[n][n], int b[n][n]){
    int count = 0;
    for(int i = 0; i < n;i++)
        for(int j = 0; j < n;j++)
            if(a[i][j] != b[i][j])
                count++;
    return count == 0;
}

int rand_to(int n)
{
  assert(n > 0);
  long long int m = RAND_MAX + 1L;
  long long int w = m / n;
  long long int limit = n * w;
  long long r;
  do
    r = rand();  
  while (r >= limit); 
  return (int)(r / w);
}

void fill_zero(int n, int a[n][n]){
    for(int i = 0; i < n;i++){
        for(int j = 0; j < n; j++)
            a[i][j] = 0;
    }
}

int check_slot(int n, int a[n][n], int i, int j){
    return a[i][j] == 0;
}

int is_full(int n,int a[n][n]){
    for(int i = 0; i < n;i++){
        for(int j = 0; j < n;j++)
            if(a[i][j] == 0)
                return 0;
    }
    return 1;
}

void spawn_number(int n,int a[n][n]){
    int chance = rand_to(10);
    int i ;
    int j;
    if(!is_full(n,a)){
        do{
            i = rand_to(n);
            j = rand_to(n);
        }
        while(!check_slot(n, a, i, j));
        a[i][j] = chance <= 6 ? 2 : 4;
    }
}

void start_board(int n, int a[n][n]){
    spawn_number(n,a);
    spawn_number(n,a);
}

int has_zero_below(int n,int a[n][n]){
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n;j++)
            if(a[i+1][j] == 0 && a[i][j] != 0)
                return 1;
    return 0;
}

void shift_down(int n, int a[n][n]){
    while(has_zero_below(n,a))
    {
        for(int i = 0; i < n-1; i++)
            for(int j = 0; j < n;j++)
                if(a[i+1][j] == 0){
                    a[i+1][j] = a[i][j];
                    a[i][j] = 0;
                }
    }
}

void join_down(int n, int a[n][n]){
    for(int i =n; i >= 1;i--)
        for(int j = n-1; j >= 0; j--)
            if(a[i-1][j] == a[i][j]){
                a[i][j] = a[i][j] * 2;
                a[i-1][j] = 0;
            }

}

int has_zero_above(int n, int a[n][n]){
    for(int i = 1; i < n; i++)
        for(int j = 0; j < n;j++)
            if(a[i-1][j] == 0 && a[i][j] != 0)
                return 1;
    return 0;
}

void shift_up(int n, int a[n][n]){
    while(has_zero_above(n,a))
    {
        for(int i = 1; i < n; i++)
            for(int j = 0; j < n;j++)
                if(a[i-1][j] == 0){
                    a[i-1][j] = a[i][j];
                    a[i][j] = 0;
                }
    }
}

void join_up(int n,int a[n][n]){
    for(int i =1; i < n-1;i++)
        for(int j = 0; j < n; j++)
            if(a[i-1][j] == a[i][j]){
                a[i][j] = a[i][j] * 2;
                a[i-1][j] = 0;
            }

}

int has_zero_right(int n,int a[n][n]){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n-1;j++)
            if(a[i][j+1] == 0 && a[i][j] != 0)
                return 1;
    return 0;
}

void shift_right(int n, int a[n][n]){
    while(has_zero_right(n, a))
    {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n-1;j++)
                if(a[i][j+1] == 0){
                    a[i][j+1] = a[i][j];
                    a[i][j] = 0;
                }
    }
}

void join_right(int n, int a[n][n]){
    for(int i =0; i < n;i++)
        for(int j = n-1; j > 0; j--)
            if(a[i][j-1] == a[i][j]){
                a[i][j] = a[i][j] * 2;
                a[i][j-1] = 0;
            }

}

int has_zero_left(int n, int a[n][n]){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n-1;j++)
            if(a[i][j+1] != 0 && a[i][j] == 0)
                return 1;
    return 0;
}

void shift_left(int n, int a[n][n]){
    while(has_zero_left(n, a))
    {
        for(int i = 0; i < n; i++)
            for(int j = 1; j < n;j++)
                if(a[i][j-1] == 0){
                    a[i][j-1] = a[i][j];
                    a[i][j] = 0;
                }
    }
}

void join_left(int n, int a[n][n]){
    for(int i =0; i < n;i++)
        for(int j = 1; j < n; j++)
            if(a[i][j-1] == a[i][j]){
                a[i][j-1] = a[i][j] * 2;
                a[i][j] = 0;
            }

}

int is_solved(int n,int a[n][n]){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(a[i][j] == 2048)
                return 1;
    return 0;
}

int can_move(int n, int a[n][n], int x, int i, int j){
    int check = 0;
    if(i-1 >= 0)
        if(a[i-1][j] == x || a[i-1][j] == 0)
            check++;
    if(i+1 < n && i-1 >= 0)
        if(a[i+1][j] == x || a[i-1][j] == 0)
            check++;
    if(j+1 < n)
        if(a[i][j+1] == x || a[i][j+1] == 0)
            check++;
    if(j-1 >= 0)
        if(a[i][j-1] == x || a[i][j-1] == 0)
            check++;
    return check != 0;
}

int is_possible(int n, int a[n][n]){
    int check = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n;j++)
            if(can_move(n, a, a[i][j], i, j))
                check++;
    return check != 0;
}

void pressed_left(int n, int a[n][n], int b[n][n]){
    shift_left(n ,a);
    join_left(n,a);
    shift_left(n,a);
    if(!matrix_equals(n, a, b))
        spawn_number(n,a);
    system("cls");
    printf("\n");
    display_board(n,a);

}

void pressed_right(int n, int a[n][n], int b[n][n]){
    shift_right(n ,a);
    join_right(n,a);
    shift_right(n,a);
    if(!matrix_equals(n, a, b))
        spawn_number(n,a);
    system("cls");
    printf("\n");
    display_board(n,a);

}

void pressed_up(int n, int a[n][n], int b[n][n]){
    shift_up(n ,a);
    join_up(n,a);
    shift_up(n,a);
    if(!matrix_equals(n, a, b))
        spawn_number(n,a);
    system("cls");
    printf("\n");
    display_board(n,a);

}

void pressed_down(int n, int a[n][n], int b[n][n]){
    shift_down(n ,a);
    join_down(n,a);
    shift_down(n,a);
    if(!matrix_equals(n, a, b))
        spawn_number(n,a);
    system("cls");
    printf("\n");
    display_board(n,a);

}

int pressed_redo(int n, int a[n][n], int b[n][n],int x){
    if(x == 1){
        printf("This is your first move\n");
        return x;
    }
    matrix_copy(n,b,a);
    system("cls");
    printf("backtracking\n");
    printf("\n");
    display_board(n,a);
    x -= 2;
    return x;

}

int handle_input(int n, int a[n][n], int b[n][n], int c[n][n], char input, int counter){
    switch (input)
    {
    case 'w':
        pressed_up(n,a,b);
        break;
    case 's':
        pressed_down(n,a,b);
        break;
    case 'a':
        pressed_left(n, a, b);
        break;
    case 'd':
        pressed_right(n,a,b);
        break;
    case 'q':
        counter = pressed_redo(n, a, c, counter);
        break;
    case 'p':
        counter = -1;
        break;
    default:
        printf("Not a valid input, controls are wasd, q to redo and p to exit\n");
        break;
    }
    return counter;
}

void game(void){
    printf("Welcome to 2048!\nControls are wasd, q to redo, p to exit\n");
    int counter = 0;
    int n = BOARD_SIZE;
    int board[n][n];
    int save[n][n];
    int redo[n][n];
    fill_zero(n,board);
    start_board(n, board);
    display_board(n, board);
    while(counter != -1 && is_possible(n,board) && !is_solved(n,board)){
        matrix_copy(n, board, save);
        char input = _getch();
        counter++;
        counter = handle_input(n, board, save, redo, input, counter);
        matrix_copy(n, save, redo);
    }
    printf("GAME OVER! Thank you for playing\n Press r to retry or any other key to close\n");
    char retry = _getch();
    if(retry == 'r'){
        system("cls");
        game();
    }
}


int main(void){
    time_t seconds = time(NULL);  
    srand(seconds);
    game();
    return 0;
}