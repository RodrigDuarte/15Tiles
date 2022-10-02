typedef struct tree {
    void *data;
    ARRAY children;
} *TREE;

TREE create_tree(void *data) {
    TREE tree = (TREE) malloc(sizeof(struct tree));

    tree->data = data;
    tree->children = create_array(1);

    return tree;
}

void destroy_tree(TREE tree) {
    for (int i = 0; i < tree->children->size; i++) {
        destroy_tree(tree->children->data[i]);
    }
    destroy_array(tree->children);
    free(tree);
}

void add_child(TREE tree, TREE child) {
    add_array(tree->children, child);
}

void remove_child(TREE tree, int index) {
    remove_array(tree->children, index);
}


