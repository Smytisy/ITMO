//
// Created by mailo on 05.12.2021.
//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct HashSet {
    struct Value {
        int value;

        Value *next;

        explicit Value(int value) {
            next = NULL;
            this->value = value;
        };
    };

    vector<Value *> set_table;
    const int MOD = 110201;

    const int random1 = 212011;
    const int random2 = 123;

    HashSet() {
        set_table.resize(MOD);
    }

    int hash_function(int a) const {
        return abs(a + random2 * random1);
    }

    void add(int value) {
        if (!exists(value)) {
            int h = hash_function(value);
            Value *element = new Value(value);
            element->next = set_table[h % MOD];
            set_table[h % MOD] = element;
        }
    }

    Value *get(int value) {
        Value *tmp = set_table[hash_function(value) % MOD];
        while (tmp != NULL) {
            if (tmp->value == value) {
                return tmp;
            }
            tmp = tmp->next;
        }
        return NULL;
    }

    bool exists(int value) {
        Value *tmp = get(value);
        if (tmp != NULL) {
            return true;
        }
        return false;
    }

    void remove(int value) {
        if (!exists(value)) {
            return;
        }

        int h = hash_function(value);
        Value *current = set_table[h % MOD];
        Value *previous = NULL;
        while (current != NULL) {
            if (current->value == value) {
                if (previous == NULL) {
                    set_table[h % MOD] = current->next;
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


};

void task_A() {
    ifstream fin(R"(set.in)");
    ofstream fout(R"(set.out)");


    string input;
    HashSet t;
    while (fin >> input) {
        int x;
        if (input == "insert") {
            fin >> x;
            t.add(x);
        } else if (input == "delete") {
            fin >> x;
            t.remove(x);
        } else if (input == "exists") {
            fin >> x;
            fout << (t.exists(x) ? "true" : "false") << endl;
        }
    }

    fin.close();
    fout.close();
}
/*
int main() {
    task_A();
    return 0;
}
 */