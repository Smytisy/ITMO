//
// Created by mailo on 05.12.2021.
//
//
// Created by mailo on 05.12.2021.
//


#include <iostream>
#include <fstream>
#include <vector>

using namespace std;






struct MultiMap {
    struct Pair_List {
        string key;
        vector<string> values;

        Pair_List *next;

        explicit Pair_List(const string &key, const string &value) {
            next = NULL;
            this->key = key;
            this->values.push_back(value);
        };
    };

    vector<Pair_List *> map_table;
    const int MOD = 1102010;

    const int random1 = 212011;
    const int random2 = 123;

    MultiMap() {
        map_table.resize(MOD);
    }

    static int hash_function(const string &s) {
        uint64_t hash = 0, pow = 1;
        int p = 53;
        for (char i : s) {
            hash += (i - 'a' + 1) * pow;
            pow *= p;
        }
        return (int) (hash % 10000000);
    }

    void put(const string &key, const string &value) {
        Pair_List *tmp = get_pair(key);
        if (tmp != NULL) {
            if (!contains(key, value)) {
                tmp->values.push_back(value);
            }
            return;
        }

        int h = hash_function(key);
        Pair_List *elem = new Pair_List(key, value);
        elem->next = map_table[h % MOD];
        map_table[h % MOD] = elem;
    }

    Pair_List *get_pair(const string &key) {
        Pair_List *tmp = map_table[hash_function(key) % MOD];
        while (tmp != NULL) {
            if (tmp->key == key) {
                return tmp;
            }
            tmp = tmp->next;
        }
        return NULL;
    }
    bool contains(const string &key, const string &value) {
        int h = hash_function(key);
        Pair_List *current = map_table[h % MOD];
        for(auto & i : current->values) {
            if (value == i) {
                return true;
            }
        }
        return false;
    }

    vector<string> return_vector(const string &key) {
        printf("reret \n");
        Pair_List *tmp = map_table[hash_function(key) % MOD];
        printf("reret2 \n");
        return tmp->values;
    }

    void delete_vector_element(const string &key, const string &value) {
        int h = hash_function(key);
        Pair_List *current = map_table[h % MOD];
        for(int i = 0; i < current->values.size(); i++) {
            if (value == current->values[i]) {
                auto iter = current->values.cbegin();
                current->values.erase(iter + i);
                break;
            }
        }
    }

    void remove(const string &key, const string &value) {
        int h = hash_function(key);
        Pair_List *current = map_table[h % MOD];
        Pair_List *previous = NULL;
        while (current != NULL) {
            if (current->key == key) {
                delete_vector_element(key, value);
                if (previous == NULL) {
                    map_table[h % MOD] = current->next;
                } else {
                    previous->next = current->next;
                    current->next = NULL;
                }
                free(current);
                return;
            }

            previous = current;
            current = current->next;
        }
    }


    void remove_all(const string &key) {

        int h = hash_function(key);
        Pair_List *current = map_table[h % MOD];
        Pair_List *previous = NULL;
        while (current != NULL) {
            if (current->key == key) {

                if (previous == NULL) {
                    map_table[h % MOD] = current->next;
                } else {
                    previous->next = current->next;
                    current->values.clear();
                    current->next = NULL;
                }
                free(current);
                return;
            }

            previous = current;
            current = current->next;
        }
    }

};


void task_D() {
    ifstream fin(R"(C:\Users\mailo\CLionProjects\algoLab6\files\multimap.in)");
    ofstream fout(R"(C:\Users\mailo\CLionProjects\algoLab6\files\multimap.out)");


    string input;
    MultiMap t;

    while (fin >> input) {
        string key;
        string x;
        if (input == "put") {
            printf("put \n");
            fin >> key;
            fin >> x;
            t.put(key, x);
        } else if (input == "delete") {
            fin >> key;
            fin >> x;

            printf("delete \n");
            t.remove(key, x);
        } else if (input == "get") {
            printf("get1 \n");
            fin >> x;
            vector<string> tmp = t.return_vector(x);
            fout << tmp.size() << ' ';
            printf("get2 \n");
            printf("return\n");
            for(const string& e: tmp) {
                fout << e << ' ';
            }
            fout << endl;
            printf("get3 \n");
        } else if (input == "deleteall") {
            fin >> x;
            printf("deleteall \n");
            t.remove_all(x);
        }
    }

    fin.close();
    fout.close();
}

int main() {
    task_D();
    return 0;
}
