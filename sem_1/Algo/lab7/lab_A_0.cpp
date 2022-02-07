////
//// Created by mailo on 10.12.2021.
////
//
//
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <map>
//
//using namespace std;
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
//void task_A_0() {
//    ifstream fin(R"(balance.in)");
//    ofstream fout(R"(balance.out)");
//    int n;
//    fin >> n;
//    vector<vector<int>> tree;
//    if (n == 0) {
//        fout << 0;
//        fin.close();
//        fout.close();
//        return;
//    }
//    tree.resize(n + 1);
//
//
//
//    for (int i = 0; i < n; i++) {
//        tree[i + 1].resize(4);
//        fin >> tree[i + 1][0] >> tree[i + 1][1] >> tree[i + 1][2];
//    }
//    set_height(1, tree);
//    for (int i = 1; i < n + 1; i++) {
//        fout << get_balance_height_node(i, tree) << endl;
//        //fout << get_balance_height(i, tree) << endl;
//    }
//
//    fin.close();
//    fout.close();
//}
///*
//int main() {
//    task_A_0();
//    return 0;
//}
//*/
