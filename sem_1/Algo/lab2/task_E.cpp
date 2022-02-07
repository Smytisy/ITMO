////
//// Created by mailo on 08.10.2021.
////
//
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <random>
//
//
//using namespace std;
//
//vector<int> a;
//int q_left; // индекс самого левого члена одинаковых пивотов
//random_device rd;
//
//int partition(int p, int r) {
//    int x, i;
//    x = a[r];
//    i = p - 1;
//    for (int j = p; j <= r - 1; j++) {
//        if (a[j] <= x) {
//            i = i + 1;
//            swap(a[i], a[j]);
//        }
//    }
//    swap(a[i + 1], a[r]);
//    q_left = i + 1;
//    while(a[q_left--] == x) {}
//    q_left += 2;
//    return i + 1;
//}
//
//
//int rand_partition(int p, int r) {
//    int rand_i = rd() % (r - p + 1) + p;
//    swap(a[r], a[rand_i]);
//    return partition(p, r);
//}
//
//
//
//int find(int p, int r, int k) {
//    if (p == r) {
//        return a[p];
//    }
//    int q = rand_partition(p, r);
//    int index_q = q - p + 1;
//    int index_ql = q_left - p + 1;
//    if ((index_q >= k) && (index_ql <= k)) {
//        return a[q];
//    }
//
//    if(index_q == k) {
//        return a[q];
//    } else if (k < index_q) {
//        return find(p, q_left - 1, k);
//    } else {
//        return find(q + 1, r, k - index_q);
//    }
//}
//
//
//
//
//void task_E() {
//    ifstream fin(R"(kth.in)");
//    ofstream fout(R"(kth.out)");
//    int n, k;
//    int A, B, C;
//    fin >> n >> k;
//    fin >> A >> B >> C;
//
//    a.resize(n);
//    fin >> a[0] >> a[1];
//    for (int i = 2; i < n; i++) {
//        a[i] = A * a[i - 2] + B * a[i - 1] + C;
//    }
//
//    fout << find(0, n - 1, k);
//
//    fout.close();
//    fin.close();
//}
