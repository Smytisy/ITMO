////
//// Created by mailo on 05.12.2021.
////
//#include <iostream>
//#include <fstream>
//#include <vector>
//
//using namespace std;
//
//struct MultiMap {
//    struct Pair_List {
//        string key;
//        string values;
//
//        Pair_List *next;
//
//        explicit Pair_List(const string &key, const string &values) {
//            next = NULL;
//            this->key = key;
//            this->values = values;
//        };
//    };
//
//    vector<Pair_List *> map_table;
//    const int MOD = 110201;
//
//    const int random1 = 212011;
//    const int random2 = 123;
//
//    MultiMap() {
//        map_table.resize(MOD);
//    }
//
//    static int hash_function(const string &s) {
//        uint64_t hash = 0, pow = 1;
//        int p = 53;
//        for (char i : s) {
//            hash += (i - 'a' + 1) * pow;
//            pow *= p;
//        }
//        return (int) (hash % 10000000);
//    }
//
//    void put(const string &key, const string &values) {
//        Pair_List *tmp = get_pair(key);
//        if (tmp != NULL) {
//            tmp->values = values;
//            return;
//        }
//
//        int h = hash_function(key);
//        Pair_List *elem = new Pair_List(key, values);
//        elem->next = map_table[h % MOD];
//        map_table[h % MOD] = elem;
//    }
//
//    Pair_List *get_pair(const string &key) {
//        Pair_List *tmp = map_table[hash_function(key) % MOD];
//        while (tmp != NULL) {
//            if (tmp->key == key) {
//                return tmp;
//            }
//            tmp = tmp->next;
//        }
//        return NULL;
//    }
//
//    string get_value(const string &key) {
//        Pair_List *tmp = get_pair(key);
//        if (tmp == NULL) {
//            return "none";
//        }
//        return tmp->values;
//    }
//
//    void remove(const string &key) {
//        int h = hash_function(key);
//        Pair_List *current = map_table[h % MOD];
//        Pair_List *previous = NULL;
//        while (current != NULL) {
//            if (current->key == key) {
//                if (previous == NULL) {
//                    map_table[h % MOD] = current->next;
//                } else {
//                    previous->next = current->next;
//                    current->next = NULL;
//                }
//                free(current);
//                return;
//            }
//
//            previous = current;
//            current = current->next;
//        }
//    }
//
//};
//
//void task_B() {
//    ifstream fin(R"(map.in)");
//    ofstream fout(R"(map.out)");
//
//
//    string input;
//    MultiMap t;
//    while (fin >> input) {
//        string key;
//        string x;
//        if (input == "put") {
//            fin >> key;
//            fin >> x;
//            t.put(key, x);
//        } else if (input == "delete") {
//            fin >> x;
//            t.remove(x);
//        } else if (input == "get") {
//            fin >> x;
//            fout << t.get_value(x) << endl;
//        }
//    }
//
//    fin.close();
//    fout.close();
//}
//
//int main() {
//    task_B();
//    return 0;
//}