#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "array_utils.h"
#include "tree_utils.h"
#include "board.h"

BOARD solution;

void solution_tree(TREE tree, BOARD board, int level) {
    if (level <= 0 || tree == NULL || board == NULL) { return; }

    ARRAY succ = successors(board);
    for (int i = 0; i < succ->size; i++) {
        BOARD succ_board = (BOARD) succ->data[i];
        TREE child = create_tree(succ_board);
        tree->children = add_array(tree->children, (void *) child);
        solution_tree(child, succ_board, level - 1);
    }

    free(succ);
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

    BOARD board = generate_board(2, 2);
    solution = generate_solution(board);

    TREE tree = create_tree(board);
    solution_tree(tree, board, 2);
    print_tree(tree, 0);

    /*
    printf("Is a valid board: %s\n", is_valid(board) ? "true" : "false");
    print_board(board);


    printf("Printing successrors:\n");
    ARRAY succ = successors(board);
    for (int i = 0; i < succ->size; i++) {
        print_board(succ->data[i]);
        printf("Is a valid board: %s\n", is_valid(board) ? "true" : "false");
        printf("\n");
    }
    
    TREE tree = create_tree(board);
    ARRAY succ = successors(board);
    printf("Succ size: %d\n", succ->size);
    for (int i = 0; i < succ->size; i++) {
        add_child(tree, create_tree(succ->data[i]));
    }
    
    printf("Tree size: %d\n", tree->children->size);
    for (int i = 0; i < tree->children->size; i++) {
        TREE child = tree->children->data[i];
        ARRAY succ_in = successors((BOARD) child->data);
        for (int j = 0; j < succ_in->size; j++) {
            add_child(child, create_tree(succ_in->data[j]));
        }
    }
    
    printf("Root of tree\n");
    print_board(tree->data);
    for (int i = 0; i < tree->children->size; i++) {
        TREE child = tree->children->data[i];
        printf("Children %d of root\n", i);
        print_board((BOARD) child->data);
        for (int j = 0; j < child->children->size; j++) {
            printf("Children %d of child %d\n", j, i);
            TREE child_in = child->children->data[j];
            print_board((BOARD) child_in->data);
        }
    }
    */
    
    destroy_board(board);
    destroy_tree(tree);

    return 0;
}