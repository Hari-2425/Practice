#include <bits/stdc++.h>

using namespace std;

class Node{
    public:
    int val;
    Node* next;

    Node(int val){
        this->val = val;
        this->next = nullptr;
    }

    
    
};

void display(Node* root){
    Node* curr = root;

    while(curr != nullptr){
        cout<<curr->val<<"->";
        curr = curr->next;
    }
    cout<<"\n";
}

// 1->12->7->16->9
// 9->16->7->12->1->null

Node* reverse_list(Node* head){
    Node* curr = head;
    Node* prev = nullptr;

    while(curr != nullptr){
        Node* nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }

    return prev;
}

int main(){

    Node* head = new Node(35);

    head->next = new Node(46);
    head->next->next = new Node(28);
    head->next->next->next = new Node(13);

    head->next->next->next->next = new Node(100);

    head->next->next->next->next->next = new Node(154);



    display(head);
    
    Node* ans = reverse_list(head);
    display(ans);

    return 0;
}