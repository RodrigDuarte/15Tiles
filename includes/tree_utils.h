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

bool find_node(TREE tree, void *data, int (*compare)(void *, void *)) {
    if (tree == NULL) { return false; }

    if (compare(tree->data, data)) { return true; }

    for (int i = 0; i < tree->children->size; i++) {
        if (find_node(tree->children->data[i], data, compare)) { return true; }
    }

    return false;
}

int count_nodes(TREE tree) {
    if (tree == NULL) { return 0; }

    int count = 1;
    for (int i = 0; i < tree->children->size; i++) {
        count += count_nodes(tree->children->data[i]);
    }

    return count;
}