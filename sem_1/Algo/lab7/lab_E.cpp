////
//// Created by mailo on 10.12.2021.
////
//
//
//#include <iostream>
//#include <fstream>
//#include <vector>
//
//using namespace std;
//
//class AVL_tree {
//    struct Node {
//        int height;
//        int value;
//        Node *left{};
//        Node *right{};
//
//        int index;
//
//        Node(int value, int left, int right, int index) : value(value), left(nullptr), right(nullptr),
//                                                          index(index) {}
//
//        Node(int value, int index) : value(value), left(nullptr), right(nullptr),
//                                     index(index), height(1) {}
//
//    };
//
//    int size;
//    Node *root;
//
//    void insert_start(vector<vector<int>> &input) {
//        root = new Node(input[1][0], 1);
//        insert_array(input, root);
//        set_height_for_all(root);
//    }
//
//    void insert_array(vector<vector<int>> &input, Node *t) {
//        size++;
//        for (int i = 1; i < 3; i++) {
//
//            if (input[t->index][i] == 0) {
//                if (i == 1) {
//                    t->left = nullptr;
//                }
//                if (i == 2) {
//                    t->right = nullptr;
//                }
//            } else {
//                if (i == 1) {
//                    t->left = new Node(input[input[t->index][i]][0], input[t->index][i]);
//                    insert_array(input, t->left);
//                }
//                if (i == 2) {
//                    t->right = new Node(input[input[t->index][i]][0], input[t->index][i]);
//                    insert_array(input, t->right);
//                }
//            }
//        }
//    }
//
//    Node *insert(Node *t, int value) {
//        if (t == nullptr) {
//            size++;
//            return new Node(value, size);
//        }
//        if (value < t->value) {
//            t->left = insert(t->left, value);
//        } else {
//            t->right = insert(t->right, value);
//        }
//        return balance(t);
//    }
//
//
//    /*
//    Node *insert(int x, int left, int right, int index, Node *t) {
//        if (t == nullptr) {
//            t = new Node(x, left, right, index);
//        } else if (x < t->value) {
//            t->left = insert(x, left, right, index, t->left);
//        } else if (x > t->value) {
//            t->right = insert_arrays(x, left, right, index, t->right);
//        }
//        t->height = max(t->left == nullptr ? 0 : t->left->height, t->right == nullptr ? 0 : t->right->height) + 1;
//        return t;
//    }
//     */
//
//    Node *find_min(Node *t) {
//        if (t == nullptr) {
//            return nullptr;
//        } else if (t->left == nullptr) {
//            return t;
//        } else {
//            return find_min(t->left);
//        }
//    }
//
//    Node *find_max(Node *t) {
//        if (t == nullptr) {
//            return nullptr;
//        } else if (t->right == nullptr) {
//            return t;
//        } else {
//            return find_max(t->right);
//        }
//    }
//
//    Node *remove(int x, Node *t) {
//        if (t == nullptr) {
//            return nullptr;
//        }
//        if (x != t->value) {
//            if (x < t->value) {
//                t->left = remove(x, t->left);
//            } else {
//                t->right = remove(x, t->right);
//            }
//        } else {
//            if (t->left == nullptr && t->right == nullptr) {
//                return nullptr;
//            }
//            if (t->left == nullptr) {
//                t = t->right;
//                return balance(t);
//            }
//            Node *max_in_left = find_max(t->left);
//            t->value = max_in_left->value;
//            t->left = remove(t->value, t->left);
//        }
//
//        return balance(t);
//    }
//
//
//    Node *exist(int x, Node *t) {
//        if (t == nullptr || t->value == x) {
//            return t;
//        } else {
//            return exist(x, x < t->value ? t->left : t->right);
//        }
//    }
//
//
//    void get_tree_array(Node *t, int &count, vector<vector<int>> &output) {
//        //fout << tree[node][0] << ' ' << (tree[node][1] == 0 ? 0 : (count + 1)) << ' ' << (tree[node][2] == 0 ? 0 : (count + 2)) << endl;
//
//        //cout << ' ' <<t->value << ' ';
//        output[count][0] = t->value;
//
//        output[count][1] = (t->left == nullptr ? 0 : (count));
//        output[count][2] = (t->right == nullptr ? 0 : (count));
//        output[count][3] = t->height;
//        int index = count;
//
//        count++;
//        if (t->left != nullptr) {
//            output[index][1] = count;
//            get_tree_array(t->left, count, output);
//        }
//
//        if (t->right != nullptr) {
//            output[index][2] = count;
//            get_tree_array(t->right, count, output);
//        }
//
//    }
//
//    static int height_left(Node *t) {
//        return (t->left != nullptr) ? t->left->height : 0;
//    }
//
//    static int height_right(Node *t) {
//        return (t->right != nullptr) ? t->right->height : 0;
//    }
//
//    static int count_balance(Node *t) {
//        int left = height_left(t);
//        int right = height_right(t);
//        return right - left;
//    }
//
//    static void set_height(Node *t) {
//        t->height = max(height_right(t), height_left(t)) + 1;
//    }
//
//    static Node *rotate_right(Node *t1) {
//        Node *t2 = t1->left;
//        t1->left = t2->right;
//        t2->right = t1;
//
//        set_height(t1);
//        set_height(t2);
//        return t2;
//    }
//
//    static Node *rotate_left(Node *t1) {
//        Node *t2 = t1->right;
//        t1->right = t2->left;
//        t2->left = t1;
//
//        set_height(t1);
//        set_height(t2);
//        return t2;
//    }
//
//    static Node *rotate_right_left(Node *t) {
//        t->right = rotate_right(t->right);
//        return rotate_left(t);
//    }
//
//    static Node *rotate_left_right(Node *t) {
//        t->left = rotate_left(t->left);
//        return rotate_right(t);
//    }
//
//    static Node *balance(Node *t) {
//        set_height(t);
//        if (count_balance(t) > 1) {
//            if (count_balance(t->right) < 0) {
//                return rotate_right_left(t);
//                cout << "b_left" << endl;
//            } else {
//                return rotate_left(t);
//                cout << "s_left" << endl;
//            }
//        }
//
//        if (count_balance(t) < -1) {
//            if (count_balance(t->left) > 0) {
//                return rotate_left_right(t);
//            } else {
//                return rotate_right(t);
//            }
//        }
//
//        return t;
//    }
//
//    void set_height_for_all(Node *t) {
//        if (t->right != nullptr) {
//            set_height_for_all(t->right);
//        }
//        if (t->left != nullptr) {
//            set_height_for_all(t->left);
//        }
//        set_height(t);
//    }
//
//
//public:
//    AVL_tree() {
//        root = nullptr;
//        size = 0;
//    }
//
////    void insert_arrays(int x, int left, int right, int index) {
////        if (!exist(x)) {
////            size++;
////            root = insert_arrays(x, left, right, index, root);
////        }
////    }
//    void insert_arrays(vector<vector<int>> input) {
//        insert_start(input);
//    }
//
//    void insert(int value) {
//        if (!exist(value)) {
//            root = insert(root, value);
//        }
//    }
//
//    void remove(int value) {
//        if (exist(value)) {
//            size--;
//            root = remove(value, root);
//        }
//    }
//
//    int height(int x) {
//        Node *tmp = exist(x, root);
//        return tmp->height;
//    }
//
//    int get_balance(int x) {
//        Node *tmp = exist(x, root);
//        int left = (tmp->left != nullptr) ? tmp->left->height : 0;
//        int right = (tmp->right != nullptr) ? tmp->right->height : 0;
//        return right - left;
//    }
//
//    int get_root_balance() {
//        if (root != nullptr) {
//            return get_balance(root->value);
//        }
//        return 0;
//    }
//
//
//    bool exist(int x) {
//        return exist(x, root) != nullptr;
//    }
//
//
//    int get_size() const {
//        return size;
//    }
//
//    void get_tree_array(vector<vector<int>> &output) {
//        int count = 1;
//        get_tree_array(root, count, output);
//    }
//
//    void balance() {
//        root = balance(root);
//    }
//
//
//};
//
//
//void task_E() {
//    ifstream fin(R"(avlset.in)");
//    ofstream fout(R"(avlset.out)");
//
//    AVL_tree t;
//    vector<int> values;
//
//    int n;
//    fin >> n;
//
//    for (int i = 0; i < n; i++) {
//        string in;
//        int x;
//        fin >> in >> x;
//        if (in == "A") {
//            t.insert(x);
//            fout << t.get_root_balance() << endl;
//        } else if (in == "D") {
//            t.remove(x);
//            fout << t.get_root_balance() << endl;
//        } else if (in == "C") {
//            fout << (t.exist(x) ? "Y" : "N") << endl;
//        }
//    }
//
//
//    fin.close();
//    fout.close();
//}
//
//int main() {
//    task_E();
//    return 0;
//}
