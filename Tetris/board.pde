class Board {
    int [][] m;
    float block_width;
    Block current;
    int score;
    Block next;
    boolean can_fall;
    int lines_to_delete[];
    boolean control_delete;
    boolean game_over;
    Board(int[][] m, float block_width, Block current, int score, Block next, boolean can_fall, int []lines_to_delete, boolean control_delete,boolean game_over) {
        this.m = m;
        this.block_width = block_width;
        this.current = current;
        this.score = score;
        this.next = next;
        this.can_fall = can_fall;
        this.lines_to_delete = lines_to_delete;
        this.control_delete = control_delete;
        this.game_over = game_over;
    }

    void draw_board(float x, float y){
        strokeCap(PROJECT);
        strokeJoin(MITER);
        strokeWeight(4);
        float save = x;
        for(int i = 2; i < m.length;i++){
            for(int j = 0; j < m[i].length;j++){
                color colour = colors[m[i][j]];
                fill(colour);
                circle(x, y, block_width);
                x += block_width;
            }
            y+= block_width;
            x = save;
        }
    }
 

    void draw_next(float x, float y){
        // fill_matrix_x(m, 8);
        reset_next();
        float save = x;
        next.fill_block_matrix(m);
        for(int i = 0; i < m.length;i++){
            for(int j = 0; j < m[i].length;j++){
                if((m[i][j] != 8) && (m[i][j] != 9)){
                    color colour = colors[m[i][j]];
                    fill(colour);
                    circle(x, y, block_width);
                }
                x += block_width;

            }
            y+= block_width;
            x = save;
        }
        stroke(0,0,0);
        strokeCap(PROJECT);
        strokeJoin(MITER);
        strokeWeight(4);
    }

    void current_fall(){
        if(current.has_space_under(m)){
            can_fall = true;
            score++;
            for(int i = 0; i < current.coords.length;i++){
                board.m[current.coords[i].x][current.coords[i].y] = 0;
                current.coords[i].x++;
                current.fill_block_matrix(m);
            }
        }
        else
            can_fall = false;
    }

    void current_shift_left(){
        if(current.has_space_left(m)){
            for(int i = 0; i < current.coords.length;i++){
                board.m[current.coords[i].x][current.coords[i].y] = 0;
                current.coords[i].y--;
                current.fill_block_matrix(m);
            }
        }
    }

    void current_shift_right(){
        if(current.has_space_right(m)){
            for(int i = 0; i < current.coords.length;i++){
                board.m[current.coords[i].x][current.coords[i].y] = 0;
                current.coords[i].y++;
                current.fill_block_matrix(m);
            }
        }
    }

    void current_rotate(){
        for(int i = 0; i < current.coords.length;i++){
            board.m[current.coords[i].x][current.coords[i].y] = 0;            
        }
        current.rotate_90(m);
        current.fill_block_matrix(m);

    }

    void handle_rotation(){
        if(current.can_rotate(m))
            current_rotate();
    }

    void shift_down(int stop){
        for(int i = stop; i > 0; i--){
            for(int j = 0; j < m[i].length;j++){
                    m[i][j] = m[i-1][j];
                }
        }
    }


    void reset_matrix(){
        for(int i = 0; i < m.length;i++)
            fill_zero(m[i]);
    }

    void clear_buffer(){
        for(int i = 0; i < 2;i++){
            fill_x(m[i], 0);
        }
    }

    void update_board(){
        int count = 0;
        int size = 0;
        for(int i = 0; i < m.length;i++){
            if(array_is_full(m[i])){
                control_delete = true;
                lines_to_delete[size++] = i;
                count++;
            }
        }
        double to_add = count == 0 ? 0 : Math.pow(100, (count));
        board.score += to_add;
    }


    void reset_next(){
       for(int i = 0; i < m.length;i++){
           for(int j = 2; j <m[i].length;j++)
                m[i][j] = 8;
       }
    }

}