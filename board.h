typedef struct board{
    int height;
    int width;

    int **matrix;
    int *array;
} *BOARD;


BOARD create_board(int height, int width) {
    BOARD board = malloc(sizeof(struct board));
    board->height = height;
    board->width = width;

    board->matrix = malloc(sizeof(int *) * height);
    for (int i = 0; i < height; i++) {
        board->matrix[i] = calloc(width, sizeof(int));
    }

    board->array = malloc(sizeof(int) * height * width);

    return board;
}

BOARD copy_board(BOARD board) {
    BOARD copy = create_board(board->height, board->width);

    for (int i = 0; i < board->height; i++) {
        memcpy(copy->matrix[i], board->matrix[i], sizeof(int) * board->width);
    }

    memcpy(copy->array, board->array, sizeof(int) * board->height * board->width);

    return copy;
}

void destroy_board(BOARD board) {
    for (int i = 0; i < board->height; i++) {
        free(board->matrix[i]);
    }
    free(board->matrix);
    free(board->array);
    free(board);
}

void print_board(BOARD board) {
    for (int i = 0; i < board->height; i++) { printf("+---"); } printf("+\n");
    for (int i = 0; i < board->height; i++) {
        printf("|");
        for (int j = 0; j < board->width; j++) {
            printf("%2d |", board->matrix[i][j]);
        }
        printf("\n");
        for (int i = 0; i < board->height; i++) { printf("+---"); } printf("+\n");   
    }
}

BOARD generate_board(int height, int width) {
    BOARD board = create_board(height, width);

    for (int i = 0; i < height * width; i++) {
        int row = rand() % height;
        int col = rand() % width;

        if (board->matrix[row][col] == 0) {
            board->matrix[row][col] = i;
            board->array[row * width + col] = i;
        } else {
            i--;
        }
    }
    
    

    return board;
}

BOARD generate_solution(BOARD board) {
    BOARD solution = copy_board(board);

    for (int i = 0; i < board->height * board->width; i++) {
        int row = i / board->width;
        int col = i % board->width;

        solution->matrix[row][col] = i;
        solution->array[row * board->width + col] = i;
    }

    return solution;
}

bool compare_boards(BOARD board_1, BOARD board_2) {
    if (board_1->height != board_2->height || board_1->width != board_2->width) {
        return false;
    }

    for (int i = 0; i < board_1->height; i++) {
        for (int j = 0; j < board_1->width; j++) {
            if (board_1->matrix[i][j] != board_2->matrix[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool is_valid(BOARD board) {
    int *array = calloc(board->height * board->width, sizeof(int));
    
    for (int i = 0; i < board->height; i++) {
        for (int j = 0; j < board->width; j++) {
            if (array[board->matrix[i][j]] == 0) {
                array[board->matrix[i][j]] += 1;
            } else {
                return false;
            }
        }
    }

    for (int i = 0; i < board->height * board->width; i++) {
        if (array[i] != 1) {
            return false;
        }
    }
    
    return true;
}

ARRAY successors(BOARD board) {
    ARRAY succ = create_array(1);

    int zero_row = -1, zero_col = -1, zero_index = -1;

    // Finding zero position
    for (int i = 0; i < board->height; i++) {
        for (int j = 0; j < board->width; j++) {
            if (board->matrix[i][j] == 0) {
                zero_row = i;
                zero_col = j;
                zero_index = i * board->width + j;
                break;
            }
        }
    }

    if (zero_row != 0) {
        BOARD up = copy_board(board);
        up->matrix[zero_row][zero_col] = up->matrix[zero_row - 1][zero_col];
        up->matrix[zero_row - 1][zero_col] = 0;
        up->array[zero_index] = up->array[zero_index - board->width];
        up->array[zero_index - board->width] = 0;
        succ = add_array(succ, (void *) up);
    }
    if (zero_row != board->height - 1) {
        BOARD down = copy_board(board);
        down->matrix[zero_row][zero_col] = down->matrix[zero_row + 1][zero_col];
        down->matrix[zero_row + 1][zero_col] = 0;
        down->array[zero_index] = down->array[zero_index + board->width];
        down->array[zero_index + board->width] = 0;
        succ = add_array(succ, (void *) down);
    }
    if (zero_col != 0) {
        BOARD left = copy_board(board);
        left->matrix[zero_row][zero_col] = left->matrix[zero_row][zero_col - 1];
        left->matrix[zero_row][zero_col - 1] = 0;
        left->array[zero_index] = left->array[zero_index - 1];
        left->array[zero_index - 1] = 0;
        succ = add_array(succ, (void *) left);
    }
    if (zero_col != board->width - 1) {
        BOARD right = copy_board(board);
        right->matrix[zero_row][zero_col] = right->matrix[zero_row][zero_col + 1];
        right->matrix[zero_row][zero_col + 1] = 0;
        right->array[zero_index] = right->array[zero_index + 1];
        right->array[zero_index + 1] = 0;
        succ = add_array(succ, (void *) right);
    }

    return succ;
}