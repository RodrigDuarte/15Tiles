#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "includes/array_utils.h"
#include "includes/tree_utils.h"
#include "includes/list_utils.h"
#include "board.h"

BOARD solution;

void solution_tree(TREE tree_head, TREE tree, BOARD board, int level) {
    if (level <= 0 || tree == NULL || board == NULL) { return; }

    ARRAY succ = successors(board);
    for (int i = 0; i < succ->size; i++) {
        if (find_node(tree_head, succ->data[i], compare_boards)) {
            //printf("Found a duplicate board! Skipping...\n");
            continue;
        }
        
        BOARD succ_board = (BOARD) succ->data[i];
        TREE child = create_tree(succ_board);
        tree->children = add_array(tree->children, (void *) child);
        solution_tree(tree_head, child, succ_board, level - 1);
    }

    free(succ);
}

BOARD find_best_board(TREE tree) {
    if (tree == NULL) { return NULL; }

    BOARD best_board = tree->data;
    int best_score = evaluate_board(best_board, solution);

    for (int i = 0; i < tree->children->size; i++) {
        BOARD child_board = find_best_board(tree->children->data[i]);
        if (child_board == NULL) { continue; }
        else {
            int child_score = evaluate_board(child_board, solution);
            if (child_score >= best_score) {
                best_score = child_score;
                best_board = child_board;
            }
        }
    }

    return best_board;
}

void print_tree(TREE tree, int level) {
    if (tree == NULL) { return; }

    printf("level %2d -> \n", level);
    print_board(tree->data);

    for (int i = 0; i < tree->children->size; i++) {
        print_tree(tree->children->data[i], level + 1);
    }
}

int main(void) {
    srand(time(NULL));

    BOARD Test = generate_board(3, 3);
    int Test_board[3][3] = {
        {8, 3, 5},
        {7, 0, 1},
        {2, 4, 6}
    };

    for (int i = 0; i < Test->height; i++) {
        for (int j = 0; j < Test->width; j++) {
            Test->matrix[i][j] = Test_board[i][j];
            Test->array[i * Test->width + j] = Test_board[i][j];
        }
    }

    BOARD board = generate_board(3, 3);
    solution = generate_solution(board);
    printf("Original board:\n");
    print_board(Test);

    
    int depth = 10;

    BOARD best_board = Test;
    while (compare_boards(best_board,solution) == false) {
        TREE tree = create_tree(best_board);
        solution_tree(tree, tree, best_board, depth);
        printf("Number of boards generated: %d | Depth: %2d\n", count_nodes(tree), depth);
        best_board = find_best_board(tree);
        depth++;
    }

    printf("Solution found!\n");
    print_board(best_board);

    //destroy_board(board);
    //destroy_tree(tree);

    return 0;
}