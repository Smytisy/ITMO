//
// Created by mailo on 15.11.2021.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Tree {
    struct Node {
        int value;
        Node *left;
        Node *right;
    };


    Node *root;

    Node *insert(int x, Node *t) {
        if (t == NULL) {
            t = new Node;
            t->value = x;
            t->left = NULL;
            t->right = NULL;
        } else if (x < t->value) {
            t->left = insert(x, t->left);
        } else if (x > t->value) {
            t->right = insert(x, t->right);
        }
        return t;
    }

    Node *find_min(Node *t) {
        if (t == NULL) {
            return NULL;
        } else if (t->left == NULL) {
            return t;
        } else {
            return find_min(t->left);
        }
    }

    Node *find_max(Node *t) {
        if (t == NULL) {
            return NULL;
        } else if (t->right == NULL) {
            return t;
        } else {
            return find_min(t->right);
        }
    }

    Node *remove(int x, Node *t) {
        Node *tmp;
        if (t == NULL) {
            return t;
        }

        if (x < t->value) {
            t->left = remove(x, t->left);

        } else if (x > t->value) {
            t->right = remove(x, t->right);

        } else if (t->left != NULL && t->right != NULL) {
            tmp = find_min(t->right);
            t->value = tmp->value;
            t->right = remove(t->value, t->right);

        } else {
            if (t->left == NULL) {
                t = t->right;
            } else if (t->right == NULL) {
                t = t->left;
            }
        }
        return t;
    }


    Node *exist(int x, Node *t) {
        if (t == NULL || t->value == x) {
            return t;
        } else {
            return exist(x, x < t->value ? t->left : t->right);
        }
    }

    Node *next(int x, Node *t) {
        Node *smallest_of_the_big = NULL;
        while (t != NULL) {
            if (x >= t->value) {
                t = t->right;
            } else if (x < t->value) {
                smallest_of_the_big = t;
                t = t->left;
            } else if (x == t->value) {
                t = find_min(t->right);
                if (t != NULL) {
                    smallest_of_the_big = t;
                }
            }
        }
        return smallest_of_the_big;
    }

    Node *prev(int x, Node *t) {
        Node *biggest_of_the_small = NULL;
        while (t != NULL) {
            if (x <= t->value) {
                t = t->left;
            } else if (x > t->value) {
                biggest_of_the_small = t;
                t = t->right;
            } else if (x == t->value) {
                t = find_max(t->left);
                if (t != NULL) {
                    biggest_of_the_small = t;
                }
            }
        }
        return biggest_of_the_small;
    }

public:
    Tree() {
        root = NULL;
    }

    void insert(int x) {
        if (!exist(x)) {
            root = insert(x, root);
        }
    }

    void remove(int x) {
        if (exist(x)) {
            root = remove(x, root);
        }
    }

    bool exist(int x) {
        return exist(x, root) != NULL;
    }

    int prev(int x) {
        Node *tmp = prev(x, root);
        if (tmp == NULL) {
            return 2000000000;
        }
        return tmp->value;
    }

    int next(int x) {
        Node *tmp = next(x, root);
        if (tmp == NULL) {
            return 2000000000;
        }
        return tmp->value;
    }
};


void task_C() {
    ifstream fin(R"(bstsimple.in)");
    ofstream fout(R"(bstsimple.out)");


    string input;
    Tree t;
    while (fin >> input) {
        int x;
        if (input == "insert") {
            fin >> x;
            t.insert(x);
        } else if (input == "delete") {
            fin >> x;
            t.remove(x);
        } else if (input == "exists") {
            fin >> x;
            fout << (t.exist(x) ? "true" : "false") << endl;
        } else if (input == "next") {
            fin >> x;
            x = t.next(x);
            if (x == 2000000000) {
                fout << "none" << endl;
            } else {
                fout << x << endl;
            }
        } else if (input == "prev") {
            fin >> x;
            x = t.prev(x);
            if (x == 2000000000) {
                fout << "none" << endl;
            } else {
                fout << x << endl;
            }
        }
    }


    fin.close();
    fout.close();
}
/*
int main() {
    task_C();
    return 0;
}
*/
