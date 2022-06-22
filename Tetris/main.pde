//
// Tetris tradicional com design circular, inclui pontuação, preview de proxima peça, ecrã de game over, animação de limpeza de linhas e botão de reset
// As Peças empilham, rodam, movem-se em todas as direções e encaixam umas com as outras
//

//import processing.sound.*; 
int row = 20 + 2;
int col = 10;
int window_x = 700;
int window_y = 700;
float block_size = 0.04918 * window_y;
color white = color(31,32,34);
color red = color(168, 0, 0);
color green = color(0, 186, 113);
color blue = color(0,194,222);
color black = color(255,255,255);
color orange = color(250, 137, 1);
color purple = color(95, 40, 121);
color yellow = color(250, 215, 23);
color deep_blue = color(0,65,141);
color gray = color(54,69,79);

color[] colors = {white, red, green, blue, orange, purple, yellow, deep_blue, black, gray};

Board board;
Board display;
Block[] blocks;
PFont f;
PImage img;
// SoundFile file;

int[] block_order = {1,6,3,2,4,6,0,5,4,0,6,3,4,1,2,6,2,1,4,6,1,3,0,5};
int counter = 0;
int [][] dis;

public void settings(){
    size(window_x,window_y);
}


void setup(){
    f = createFont("Minecraft.ttf", 150);
    img = loadImage("pepe.png");
    // file = new SoundFile(this, "tetris_remix.mp3");
    // file.loop();

    //s 
    Point block_coords = new Point(0,3);
    Point block_coords_2 = new Point(0,4);
    Point block_coords_3 = new Point(1,4);
    Point block_coords_4 = new Point(1,5);
    Point[] coords_1 = {block_coords, block_coords_2, block_coords_3, block_coords_4};

    // square
    Point block_2_coords_1 = new Point(0,4);
    Point block_2_coords_2 = new Point(1,4);
    Point block_2_coords_3 = new Point(0,5);
    Point block_2_coords_4 = new Point(1,5);
    Point[] coords_2 = {block_2_coords_1, block_2_coords_2, block_2_coords_3, block_2_coords_4};
    
    // line
    Point block_3_coords_1 = new Point(0,2);
    Point block_3_coords_2 = new Point(0,3);
    Point block_3_coords_3 = new Point(0,4);
    Point block_3_coords_4 = new Point(0,5);
    Point[] coords_3 = {block_3_coords_1, block_3_coords_2, block_3_coords_3, block_3_coords_4};

    // l
    Point block_4_coords_1 = new Point(0,3);
    Point block_4_coords_2 = new Point(1,3);
    Point block_4_coords_3 = new Point(1,4);
    Point block_4_coords_4 = new Point(1,5);
    Point[] coords_4 = {block_4_coords_1, block_4_coords_2, block_4_coords_3, block_4_coords_4};

    // l_2
    Point block_5_coords_1 = new Point(1,3);
    Point block_5_coords_2 = new Point(1,4);
    Point block_5_coords_3 = new Point(1,5);
    Point block_5_coords_4 = new Point(0,5);
    Point[] coords_5 = {block_5_coords_1, block_5_coords_2, block_5_coords_3, block_5_coords_4};

    // t
    Point block_6_coords_1 = new Point(1,3);
    Point block_6_coords_2 = new Point(1,4);
    Point block_6_coords_3 = new Point(1,5);
    Point block_6_coords_4 = new Point(0,4);
    Point[] coords_6 = {block_6_coords_1, block_6_coords_2, block_6_coords_3, block_6_coords_4};

    // s_2
    Point block_7_coords_1 = new Point(0,5);
    Point block_7_coords_2 = new Point(0,4);
    Point block_7_coords_3 = new Point(1,3);
    Point block_7_coords_4 = new Point(1,4);
    Point[] coords_7 = {block_7_coords_1, block_7_coords_2, block_7_coords_3, block_7_coords_4};

    int [] board_delete = {-1,-1,-1,-1};
    int [] display_delete = {-1,-1,-1,-1};

    int[][] m = new int[row][col];
    int[][]d = {
    {9,9,8,8,8,8,8},
    {9,9,8,8,8,8,8},
    {9,9,8,8,8,8,8},
    };
    Block s = new Block(1, coords_1);
    Block square = new Block(2, coords_2);
    Block line = new Block(3, coords_3);
    Block l = new Block(4, coords_4);
    Block l_2 = new Block(5, coords_5);
    Block t = new Block(6, coords_6);
    Block s_2 = new Block(7, coords_7);
    Block[] save_blocks = {s, square, line, l, l_2, t, s_2};
    blocks = save_blocks;
    Block start = copy_block(blocks[block_order[counter++]]);
    Block next = copy_block(blocks[block_order[counter++]]);
    Block start_display = copy_block(start);
    Block next_display = copy_block(next);
    Board board_save = new Board(m,block_size, start, 0,next, true, board_delete, false, false);
    Board display_save = new Board(d,block_size,start_display,0,next_display,true, display_delete,false, false);
    display = display_save;
    board = board_save;
    for(int i = 0; i < board.current.coords.length;i++)
        board.current.coords[i].x +=2;
    board.current.fill_block_matrix(board.m);
    dis = d;

}

int frames = 0;

void end_game(){
    Point block_null_coords = new Point(21,0);
    Point block_null_coords_2 = new Point(21,1);
    Point []coords_null = {block_null_coords, block_null_coords_2};
    Block nothing = new Block(board.m[21][0],coords_null);
    board.current = nothing;
    board.game_over = true;
    // file.stop();
}

void new_piece(){
    if(board.next.block_fits_effective(board.m)){
        for(int i = 0; i < board.next.coords.length;i++){
            board.next.coords[i].x += 2;
        }
    }
    if(!board.game_over){
        board.clear_buffer();
        Block copy = copy_block(blocks[block_order[counter % block_order.length]]);
        counter++;
        board.current = board.next;
        board.current.fill_block_matrix(board.m);
        board.next = copy;
        display.next = copy;
    }
}

void update_tetris(){
     if(!board.control_delete){
        if(board.current.is_playable())
            new_piece();
        else
            end_game();
    }
}

void update(){
    board.can_fall = board.game_over ? false : board.current.has_space_under(board.m);
    if(frameCount % 45 == 0 && board.can_fall){
        board.current_fall();
    }
    if(!board.can_fall&& frames == 0){
        frames = frameCount + 30;
    }
    if(frameCount >= frames && !board.can_fall){
        board.update_board();
        frames = 0;
        update_tetris();
    }
}

int deletion = 0;

void reset_animation(){
    board.control_delete = false;
        int shifts = occurences_n(board.lines_to_delete);
        for(int i = 0; i < shifts;i++){
            board.shift_down(board.lines_to_delete[i]);
            // fill_zero(board.m[0]);
        }
        fill_x(board.lines_to_delete, -1);
}

void delete_block(){
    for(int i = 0; i < board.lines_to_delete.length;i++){
        if(board.lines_to_delete[i] != -1 && deletion != -1)
            board.m[board.lines_to_delete[i]][deletion] = 0;
    }
}

void update_animation(){
    if(deletion == -1){
        reset_animation();
    }
    delete_block();
    deletion++;
    deletion = deletion < board.m[0].length ? deletion : -1;
    delay(15);
}

float x_rect_score = 0.615 * window_x;
float y_rect_score = 0.1623 * window_y;
float rect_score_w = 0.2868 * window_x;
float rect_score_h = 0.1147 * window_y;
float score_text_x = 0.675 * window_x;
float score_text_y = 0.1467 * window_y;
float score_int_x = 0.7283 * window_x;
float score_int_y = 0.2299 * window_y;
float font_size = 0.14 * rect_score_w;

void draw_score(){
    textFont(f,font_size);                 
    fill(153);
    rect(x_rect_score, y_rect_score, rect_next_w, rect_score_h,8,8,8,8);
    fill(255,255,255);
    text("SCORE", score_text_x, score_text_y);                         
    text(board.score,score_int_x,score_int_y);
}

float x_next = 0.55 * window_x;
float y_next = 0.49 * window_y;
float x_rect_next = 0.611475 * window_x;
float y_rect_next = 0.4509 * window_y;
float rect_next_w = 0.2622 * window_x;
float rect_next_h = 0.1639 * window_y;
float next_text_x = 0.6885 * window_x;
float next_text_y = 0.4370 * window_y;

void draw_next_piece(){
    fill(153);
    rect(x_rect_next, y_rect_next, rect_next_w, rect_next_h,8,8,8,8);
    fill(255,255,255);
    text("NEXT\n",next_text_x,next_text_y);  
    display.draw_next(x_next,y_next);
}

float game_over_w = window_x / 2;
float game_over_h = window_y / 4;
float game_over_rect_x = window_x/2 - game_over_w/2;
float game_over_rect_y = window_y/2 - game_over_h/2;
float font_size_2 = 0.1 *game_over_w;
float over_text_x = window_x/2 - (0.9*game_over_w/2);
float over_text_y = window_y/2 - game_over_h/4; 


void draw_game_over(){
    fill(255,255,255);
    textFont(f,font_size_2);
    rect(game_over_rect_x, game_over_rect_y, game_over_w, game_over_h,8,8,8,8);
    fill(0);
    text("GAME OVER\n Press R to restart\n",over_text_x, over_text_y);
}

float x_board = 0.02786 * window_x;
float y_board = 0.03114 * window_y;
float background_x = x_board-(block_size/2);
float background_y = y_board-(block_size/2);
float background_w = block_size * col;
float background_h = block_size * (row-2);


void draw_board_background(){
    // fill(53,57,53);
    fill(0);
    rect(background_x, background_y, background_w, background_h);
}

void reset_board(){
    board.reset_matrix();
    board.score = 0;
    counter = 2;
    board.current = copy_block(blocks[block_order[0]]);
    board.next = copy_block(blocks[block_order[1]]);
    display.next = copy_block(blocks[block_order[1]]);
    for(int i = 0; i < board.current.coords.length;i++)
        board.current.coords[i].x += 2;
    board.current.fill_block_matrix(board.m);
    board.game_over = false;
    frames = 0;
    // file.loop();
}

void keyPressed(){
    if(keyCode == DOWN){
        if(board.can_fall)
            board.current_fall();
    }
    else if(keyCode == LEFT){
        if(!board.can_fall)
            frames = 0;
        board.current_shift_left();
    }
    else if(keyCode == RIGHT){
        if(!board.can_fall)
            frames = 0;
        board.current_shift_right();
    }
    else if(key == 'r'){
       reset_board();
    }
}

void keyReleased() {
  if (keyCode == UP) {
    board.handle_rotation();
  } 
}

void draw(){
    background(54,69,79);
    draw_board_background();
    if(!board.control_delete)
        update();
    else
        update_animation();
    draw_score();
    draw_next_piece();
    board.draw_board(x_board,y_board);
    if(board.game_over){
        image(img,0,0);
        draw_game_over();
    }
}