#include <bits/stdc++.h>
using namespace std;

template<char MIN_CHAR = 'a', size_t ALPHABET = 26>
struct Trie {
    struct trie_node {
        int child[ALPHABET];

        int words = 0;

        trie_node() {
            memset(child, -1, ALPHABET*sizeof(int));
        }
    };

    const int root = 0;
    vector<trie_node> nodes = {trie_node()};

    int get_or_create_child(int node, int c) {
        if(nodes[node].child[c] < 0) {
            nodes[node].child[c] = int(nodes.size());
            nodes.emplace_back();
        }

        return nodes[node].child[c];
    }


    // adds word to trie and returns the ending node
    int add(const string &word) {
        int node = root;
        for(auto ch: word) 
            node = get_or_create_child(node, ch - MIN_CHAR);

        nodes[node].words++;

        return node;
    }

    // Given a string, how many words in the trie are prefixes of the string?
    int count_prefixes(const string &s, bool include_full = true) {
        int node = root, count = 0;
        for(auto ch: s) {
            count += nodes[node].words;
            node = nodes[node].child[ch - MIN_CHAR];

            if(node < 0) break;
        }

        if(include_full && node >= 0) count += nodes[node].words;

        return count;
    }

};

int main() {

    int N;
    cin >> N;
    Trie<> trie;

    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        cout << trie.count_prefixes(str, true) << (i < N - 1 ? ' ' : '\n');
        trie.add(str);
    }
}