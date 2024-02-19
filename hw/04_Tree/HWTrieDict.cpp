#include <iostream>
#include <fstream>
using namespace std;

class TrieNode {
public:
    bool isEndOfWord;
    TrieNode* children[26]{};

    TrieNode() : isEndOfWord(false) {}
    ~TrieNode() {
        for (auto t: children)
            delete t;
    }
};

class Trie {
private:
    TrieNode* root;

    void insert(const char* word) {
        TrieNode* node = root;
        for (int i = 0; word[i] != '\0'; ++i) {
            int index = word[i] - 'a';
            if (!node->children[index])
                node->children[index] = new TrieNode();
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }
public:
    explicit Trie(const char dict[]) {
        root = new TrieNode();
        char word[256];
        ifstream f(dict);
        while (f.getline(word, sizeof(word))) {
            if (strncmp(word, "cat", 3) == 0) {
                cout << "";
            }
            insert(word);
        }
    }

    ~Trie() {
        delete root;
    }

    bool is_word(const char* word) {
        TrieNode* node = root;
        for (int i = 0; word[i] != '\0'; ++i) {
            int index = word[i] - 'a';
            if (!node->children[index])
                return false;
            node = node->children[index];
        }
        return node != nullptr && node->isEndOfWord;
    }

    bool is_prefix(const char* prefix) {
        TrieNode* node = root;
        for (int i = 0; prefix[i] != '\0'; ++i) {
            int index = prefix[i] - 'a';
            if (!node->children[index])
                return false;
            node = node->children[index];
        }
        return true;
    }
};

int main() {
	Trie t("../data/en213k.txt"); // load dict.txt from the current directory
	
	ifstream f("triespellcheck.txt");
	char word[256];
	int count = 0;
	while (f.getline(word, sizeof(word))) {
        size_t length = strlen(word);
        if (length > 0 && word[length - 1] == '\r')
            word[length - 1] = '\0';

		if (!t.is_word(word))
			cout << word << '\n';
		if (t.is_prefix(word))
			cout << "startswith: " << word << '\n';
	}

    cout << flush;
	return 0;
}
