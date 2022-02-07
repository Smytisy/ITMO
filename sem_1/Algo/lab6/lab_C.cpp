////
//// Created by mailo on 05.12.2021.
////
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
//        Pair_List *prev_pair;
//        Pair_List *next_pair;
//
//
//        Pair_List *next;
//
//        explicit Pair_List(const string &key, const string &values) {
//            next = NULL;
//            prev_pair = NULL;
//            next_pair = NULL;
//            this->key = key;
//            this->values = values;
//        };
//    };
//
//    Pair_List * last_pair = NULL;
//
//
//    vector<Pair_List *> map_table;
//    const int MOD = 1102010;
//
//    const int random1 = 212011;
//    const int random2 = 123;
//
//    MultiMap() {
//        map_table.resize(MOD);
//
//        last_pair = new Pair_List("", "none");
//        last_pair->next_pair = last_pair;
//        last_pair->prev_pair = last_pair;
//    }
//
//    static int hash_function(const string &s) {
//        uint64_t hash = 0, pow = 1;
//        int p = 53;
//        for (char i : s) {
//            hash += ((i - 'a' + 1) * pow) % 10000000000;
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
//        elem->next_pair = last_pair;
//        elem->prev_pair = last_pair->prev_pair;
//
//        last_pair->prev_pair->next_pair = elem;
//
//        elem->next = map_table[h % MOD];
//        map_table[h % MOD] = elem;
//
//        last_pair->prev_pair = elem;
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
//
//        int h = hash_function(key);
//        Pair_List *current = map_table[h % MOD];
//        Pair_List *previous = NULL;
//        while (current != NULL) {
//            if (current->key == key) {
//                //
//                current->next_pair->prev_pair = current->prev_pair;
//                current->prev_pair->next_pair = current->next_pair;
//                //
//                if (previous == NULL) {
//                    map_table[h % MOD] = current->next;
//                } else {
//
//                    previous->next = current->next;
//                    current->next = NULL;
//                }
//
//                return;
//            }
//
//            previous = current;
//            current = current->next;
//        }
//    }
//
//    string get_prev(const string& key) {
//        Pair_List *tmp = get_pair(key);
//        if (tmp != NULL) {
//            return tmp->prev_pair->values;
//        }
//        return "none";
//    }
//
//    string get_next(const string& key) {
//        Pair_List *tmp = get_pair(key);
//        if (tmp != NULL) {
//            return tmp->next_pair->values;
//        }
//        return "none";
//    }
//
//};
//
//void task_C() {
//    ifstream fin(R"(linkedmap.in)");
//    ofstream fout(R"(linkedmap.out)");
//
//
//    string input;
//    MultiMap t;
//
//    while (fin >> input) {
//        string key;
//        string x;
//        if (input == "put") {
//            //printf("put \n");
//            fin >> key;
//            fin >> x;
//            t.put(key, x);
//        } else if (input == "delete") {
//            fin >> x;
//            //printf("delete %s \n");
//            t.remove(x);
//        } else if (input == "get") {
//            //printf("get \n");
//            fin >> x;
//            fout << t.get_value(x) << endl;
//        } else if (input == "prev") {
//            //printf("prev \n");
//            fin >> x;
//            fout << t.get_prev(x) << endl;
//        } else if (input == "next") {
//            //printf("next \n");
//            fin >> x;
//            fout << t.get_next(x) << endl;
//        }
//    }
//
//    fin.close();
//    fout.close();
//}
//
//int main() {
//    task_C();
//    return 0;
//}
