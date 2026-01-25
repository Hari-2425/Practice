#include<bits/stdc++.h>
using namespace std;

class Node{
    unordered_map<char, Node*> mp;
    bool end;
public:
    Node(){
        end = false;
    }

    void insertFunc(string s) {
        int n = s.length();
        Node* curr = this;
        for (int i = 0; i < n; i++) {
            if (curr->mp.count(s[i])) {
                curr = curr->mp[s[i]];
            } else {
                curr->mp[s[i]] = new Node();
                curr = curr->mp[s[i]];
            }
            if (i == n - 1) {
                curr->end = true;  // mark the last node as end of word
            }
        }
    }

    bool searchWord(string s){
        int n = s.length();
        Node* curr = this;
        for (int i = 0; i < n; i++) {
            if (curr->mp.find(s[i]) == curr->mp.end()) {
                return false;  // character not found
            }
            curr = curr->mp[s[i]];
        }
        return curr->end;  // only true if it's a complete word
    }

};

int main(){
    Node* Trie = new Node();
    Trie->insertFunc("apple");
    Trie->insertFunc("apps");
    Trie->insertFunc("application");
    Trie->insertFunc("oppo");

    if(Trie->searchWord("app")){
        cout<<"Found\n";
    }
    else{
        cout<<"Not Found\n";
    }
    return 0;
}