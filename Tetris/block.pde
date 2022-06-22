class Point{
    int x;
    int y;
    Point(int x ,int y){
        this.x = x;
        this.y = y;
    }

}

class Block{
    int colour;
    Point[] coords;
    Block(int colour, Point[] coords){
        this.colour = colour;
        this.coords = coords;
    }
    void fill_block_matrix(int[][] m){
        for(int i = 0; i < coords.length;i++)
            m[coords[i].x][coords[i].y] = colour;
    }

    boolean is_in_coords(int x, int y){
        for(int i = 0; i < coords.length;i++)
            if(coords[i].x == x && coords[i].y == y)
                return true;
        return false;
    }

    boolean has_space_under(int[][] m){
        int check = 0;
        for(int i = 0; i < coords.length;i++){
            if((coords[i].x+ 1) < m.length && (m[coords[i].x+1][coords[i].y] == 0 || is_in_coords(coords[i].x +1, coords[i].y)))
                check++;
        }
        return check == coords.length;
    }

    boolean is_playable(){
        for(int i = 0; i < coords.length;i++)
            if(coords[i].x >= 2)
                return true;
        return false;
    }

    boolean block_fits_start(int[][]m){
        int check = 0;
        for(int i = 0; i < coords.length;i++)
            if(m[coords[i].x][coords[i].y] == 0)
                check++;
        return check == coords.length;
    }

    boolean block_fits_effective(int[][]m){
        int check = 0;
        for(int i = 0; i < coords.length;i++)
            if(m[coords[i].x+2][coords[i].y] == 0)
                check++;
        return check == coords.length;
    }

    boolean has_space_left(int[][] m){
        int check = 0;
        for(int i = 0; i < coords.length;i++){
            if((coords[i].y -  1) >= 0 && (m[coords[i].x][coords[i].y-1] == 0 || is_in_coords(coords[i].x, coords[i].y-1)))
                check++;
        }
        return check == coords.length;
    }

    boolean has_space_right(int[][] m){
        int check = 0;
        for(int i = 0; i < coords.length;i++){
            if((coords[i].y +1) < m[0].length && (m[coords[i].x][coords[i].y+1] == 0 || is_in_coords(coords[i].x, coords[i].y+1)))
                check++;
        }
        return check == coords.length;
    }


    void rotate_90(int[][]m){
        Point pivot = coords[1];
        for(int i = 0; i < coords.length;i++){
            Point current = coords[i];
            int new_x = current.y + pivot.x - pivot.y;
            int new_y = pivot.x + pivot.y - current.x;
            coords[i].x = new_x;
            coords[i].y = new_y;
        }
        
    }

    boolean can_rotate(int[][]m){
        Point pivot = coords[1];
        for(int i = 0; i < coords.length;i++){
            Point current = coords[i];
            int new_x = current.y + pivot.x - pivot.y;
            int new_y = pivot.x + pivot.y - current.x;
            if(new_x >= m.length || new_x < 0 || new_y >= m[0].length || new_y < 0 || (m[new_x][new_y] != 0 && !is_in_coords(new_x, new_y)))
                return false;
        }
        return true;
    }


}