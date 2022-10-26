#include <iostream>
#include <vector>
#include <algorithm>

#define c_boost std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr)

using namespace std;

const int root = 0;
const int undefined = -1;
const int ALPHABET_SZ = 26;

inline void file_open(const string &name) {
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}

inline int getIdx(char c) {
    return (int) c - 'a';
}

struct borVertex {
    explicit borVertex(int parent, int charIdx = undefined) {
        this->parent = parent;
        this->charIdx = charIdx;
        this->sufLink = undefined;
        this->upLink = undefined;
        this->isChecked = false;
        this->go = vector<int>(ALPHABET_SZ, undefined);
        this->next = vector<int>(ALPHABET_SZ, undefined);
    }

    int parent, sufLink, upLink, charIdx, isChecked;
    vector<int> next, go, number;
};

class BorDka {
public:
    BorDka() : mbor({borVertex(root)}) {}

    void addString(const string &s) {
        int v = root;
        for (char c: s) {
            int idx = getIdx(c);
            if (mbor[v].next[idx] == undefined) {
                borVertex vertex = borVertex(v, idx);
                mbor.push_back(vertex);
                mbor[v].next[idx] = mbor.size() - 1;
            }
            v = mbor[v].next[idx];
        }
        mbor[v].number.push_back(count++);
    }

    int getLinkToTerminal(int v) {
        if (mbor[v].upLink == undefined) {
            int suf = getSufLink(v);
            if (suf == root) {
                mbor[v].upLink = root;
            } else if (mbor[suf].number.empty()) {
                mbor[v].upLink = getLinkToTerminal(suf);
            } else {
                mbor[v].upLink = suf;
            }
        }
        return mbor[v].upLink;
    }

    int go(int v, int charIdx) {
        if (mbor[v].go[charIdx] == undefined) {
            if (mbor[v].next[charIdx] != undefined)
                mbor[v].go[charIdx] = mbor[v].next[charIdx];
            else mbor[v].go[charIdx] = v == root ? root : go(getSufLink(v), charIdx);
        }
        return mbor[v].go[charIdx];
    }

    borVertex *getVertex(int v) {
        return &mbor[v];
    }

private:
    int count = 0;
    vector<borVertex> mbor;

    int getSufLink(int v) {
        if (mbor[v].sufLink == undefined) {
            if (v == root || mbor[v].parent == root)
                mbor[v].sufLink = root;
            else mbor[v].sufLink = go(getSufLink(mbor[v].parent), mbor[v].charIdx);
        }
        return mbor[v].sufLink;
    }
};


int main() {
    c_boost;
    file_open(R"(search4)");
    int n;
    cin >> n;
    vector<int> usedStrings(n, false);
    BorDka borDka = BorDka();
    string si, t;
    for (int i = 0; i < n; ++i) {
        cin >> si;
        borDka.addString(si);
    }
    cin >> t;
    int current = root;
    for (char c: t) {
        int idx = getIdx(c);
        current = borDka.go(current, idx);
        auto vertex = borDka.getVertex(current);
        int local = current;
        while (local != root) {
            if (!vertex->number.empty()) {
                for (int i : vertex->number)
                    usedStrings[i] = true;
                vertex->number.clear();
            }
            local = borDka.getLinkToTerminal(local);
            vertex = borDka.getVertex(local);
        }
    }

    for (int isUsed: usedStrings)
        cout << (isUsed ? "YES" : "NO") << '\n';
}