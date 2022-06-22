//Util functions

Point copy_point(Point x){
    Point result = new Point(x.x, x.y);
    return result;
}

Block copy_block(Block x){
    Point[] points_copy = new Point[x.coords.length];
    for(int i = 0; i < x.coords.length;i++){
        points_copy[i]= copy_point(x.coords[i]);
    }
    Block result = new Block(x.colour, points_copy);
    return result;
}

boolean array_is_full(int a[]){
    int result = 0;
    for(int i = 0; i < a.length;i++)
        if(a[i]!= 0)
            result++;
    return result == a.length;
}

void fill_zero(int a[]){
    for(int i = 0; i < a.length;i++)
        a[i]= 0;
}

void fill_x(int a[], int x){
    for(int i = 0; i < a.length;i++)
        a[i]= x;
}

void fill_matrix_x(int a[][], int x){
    for(int i = 0; i < a.length;i++){
        fill_x(a[i], x);
    }
}


// return how many numbers in an array are not -1
int occurences_n(int a[]){
    int result = 0;
    for(int i = 0; i < a.length;i++)
        if(a[i] != -1)
            result++;
    return result;
}

void print_matrix(int m[][]){
    for (int i = 0; i < m.length; i++){
            print("\n");
            for (int j = 0; j < m[i].length; j++)
                print(m[i][j] + " ");
    }
}