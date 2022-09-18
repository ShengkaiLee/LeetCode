class Trie {
private:
    struct Node {
        unordered_map<char,Node*> next;
        bool isWord = false;
    };
    Node* root;
public:
    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        Node* curr = root;
        for (char c : word) {
            if (curr->next.find(c) == curr->next.end()) {
                curr->next[c] = new Node();
            }
            curr = curr->next[c];
        }
        curr->isWord = true;
    }
    
    bool search(string word) {
        Node* curr = root;
        for (char c : word) {
            if (curr->next.find(c) == curr->next.end()) return false;
            curr = curr->next[c];
        }
        return curr->isWord;
    }
    
    bool startsWith(string prefix) {
        Node* curr = root;
        for (char c : prefix) {
            if (curr->next.find(c) == curr->next.end()) return false;
            curr = curr->next[c];
        }
        return true;
    }
};
