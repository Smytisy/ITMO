////
//// Created by mailo on 10.12.2021.
////
//
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <map>
//#include <queue>
//
//using namespace std;
//
//
//int get_height_node(int node, vector<vector<int>> &tree) {
//
//    int left = tree[node][1] != 0 ? tree[tree[node][1]][3] : 0;
//    int right = tree[node][2] != 0 ? tree[tree[node][2]][3] : 0;
//    return max(left, right) + 1;
//}
//
//void small_turn_left(vector<vector<int>> &tree, int &root) {
//    int tmp = root;
//    root = tree[tmp][2];
//    tree[tmp][2] = tree[root][1];
//    tree[root][1] = tmp;
//
//    tree[tmp][3] = get_height_node(tmp, tree);
//    tree[root][3] = get_height_node(root, tree);
//}
//
//void big_turn_left(vector<vector<int>> &tree, int &root) {
//    int tmp = root;                         //tmp = root
//    root = tree[tree[tmp][2]][1];           // root = l2;
//    tree[tree[tmp][2]][1] = tree[root][2];  // l2 = r3
//    tree[root][2] = tree[tmp][2];           // r3 = r1
//    tree[tmp][2] = tree[root][1];           // r1 = l3
//    tree[root][1] = tmp;                    // l3 = tmp
//
//    tree[tree[root][1]][3] = get_height_node(tree[root][1], tree);
//    tree[tree[root][2]][3] = get_height_node(tree[root][2], tree);
//    tree[root][3] = get_height_node(tree[root][3], tree);
//}
//
//
//void write_tree(vector<vector<int>> &tree, int root, ofstream &fout, int &count, vector<vector<int>> &output) {
//    //fout << tree[root][0] << ' ' << (tree[root][1] == 0 ? 0 : (count + 1)) << ' ' << (tree[root][2] == 0 ? 0 : (count + 2)) << endl;
//    output[count][0] = tree[root][0];
//    output[count][1] = (tree[root][1] == 0 ? 0 : (count + 1));
//    output[count][2] = (tree[root][2] == 0 ? 0 : (count + 2));
//    int index = count;
//
//    count++;
//    if (tree[root][1] != 0) {
//        output[index][1] = count;
//        write_tree(tree, tree[root][1], fout, count, output);
//    }
//
//    if (tree[root][2] != 0) {
//        output[index][2] = count;
//        write_tree(tree, tree[root][2], fout, count, output);
//    }
//
//}
//
//
//int get_height(int root, vector<vector<int>> &tree) {
//    if (tree[root][1] == 0 && tree[root][2] == 0) {
//        return 1;
//    }
//    int left = tree[root][1] != 0 ? get_height(tree[root][1], tree) : 1;
//    int right = tree[root][2] != 0 ? get_height(tree[root][2], tree) : 1;
//
//    return left > right ? left + 1 : right + 1;
//}
//
//int set_height(int root, vector<vector<int>> &tree) {
//    if (tree[root][1] == 0 && tree[root][2] == 0) {
//        tree[root][3] = 1;
//        return 1;
//    }
//    int left = tree[root][1] != 0 ? set_height(tree[root][1], tree) : 1;
//    int right = tree[root][2] != 0 ? set_height(tree[root][2], tree) : 1;
//    tree[root][3] = max(left, right) + 1;
//    return max(left, right) + 1;
//}
//
//int get_balance_height(int root, vector<vector<int>> &tree) {
//    if (tree[root][1] == 0 && tree[root][2] == 0) {
//        return 0;
//    }
//    int left = tree[root][1] != 0 ? get_height(tree[root][1], tree) : 0;
//    int right = tree[root][2] != 0 ? get_height(tree[root][2], tree) : 0;
//    return right - left;
//}
//
//int get_balance_height_node(int root, vector<vector<int>> &tree) {
//    if (tree[root][1] == 0 && tree[root][2] == 0) {
//        return 0;
//    }
//    int left = tree[root][1] != 0 ? tree[tree[root][1]][3] : 0;
//    int right = tree[root][2] != 0 ? tree[tree[root][2]][3] : 0;
//    return right - left;
//}
//
//
//void task_B() {
//    ifstream fin(R"(rotation.in)");
//    ofstream fout(R"(rotation.out)");
//    int n;
//    fin >> n;
//    vector<vector<int>> tree;
//    vector<vector<int>> output;
//    if (n == 0) {
//        fout << 0;
//        fin.close();
//        fout.close();
//        return;
//    }
//    tree.resize(n + 1);
//    output.resize(n + 1);
//    for (int i = 0; i < n; i++) {
//        tree[i + 1].resize(4);
//        output[i + 1].resize(3);
//        fin >> tree[i + 1][0] >> tree[i + 1][1] >> tree[i + 1][2];
//    }
//
//    set_height(1, tree);
//
//    int root = 1;
//
//    if (get_balance_height_node(tree[root][2], tree) == -1) {
//        big_turn_left(tree, root);
//    } else {
//        small_turn_left(tree, root);
//    }
//    int count = 1;
//    //write_tree(tree, root, fout, count, output);
//
//    /*
//    queue<int> queue;
//    int index = 1;
//    int j = 0;
//    queue.push(root);
//    while (!queue.empty()) {
//        j++;
//        int children[2] = {0, 0};
//        int cur = queue.front();
//        queue.pop();
//
//        for (int i = 1; i < 3; i++) {
//            if (tree[cur][i] != 0) {
//                queue.push(tree[cur][i]);
//                children[i - 1] = ++index;
//            }
//        }
//        output[j][0] = tree[cur][0];
//        output[j][1] = children[0];
//        output[j][2] = children[1];
//
//    }
//    */
//    write_tree(tree, root, fout, count, output);
//    fout << n << endl;
//
//    for (int i = 1; i < n + 1; i++) {
//        fout << output[i][0] << ' ' << output[i][1] << ' ' << output[i][2] << endl;
//    }
//
//
//    fin.close();
//    fout.close();
//}
//
//int main() {
//    task_B();
//    return 0;
//}
//
