#include <bits/stdc++.h>
#include <iostream>

using namespace std;

class Node{
    private:
        
        
    
    public:
        int data;
        Node *next;
        Node(int x){
            this->data = x;
            this->next = NULL;
        }
        int getValue(){
            return this->data;
        }

        Node* getNext(){
            return this->next;
        }
};

void Display(Node* head){
    Node* curr;
    curr = head;
    while (curr != NULL)
    {
        cout<<curr->getValue()<<"->";
        curr = curr->next;
    }
    cout<<"\n";
}
Node* InsertAtHead(Node* head, int x){
    if(head == nullptr){
        head = new Node(x);
        return head;
    }
    Node* newN = new Node(x);
    newN->next = head;
    head = newN;
    return head;
}
Node* InsertAtEnd(Node* head, int y){
    if(head == nullptr){
        head = new Node(y);
        return head;
    }
    Node* curr = head;
    while (curr->next != nullptr)
    {
        curr = curr->next;
    }
    curr->next = new Node(y);
    return head;
}

Node* InsertKth(Node* head, int k, int val){
    if(head == nullptr)
        return head;
    if(k == 1){
        head->data = val;
        return head;
    }
    int cnt = 1;
    Node *curr=head;
    while (curr != nullptr)
    {
        if(cnt == k){
            curr->data = val;
            break;
        }
        curr = curr->next;
        cnt++;
    }
    return head;
}

Node* InsertVal(Node* head, int x, int y){
    if(head == nullptr)
        return head;
    if(head->data == x){
        head->data = y;
        return head;
    }
    Node *curr=head;
    while (curr != nullptr)
    {
        if(curr->data == x){
            curr->data = y;
            break;
        }
        curr = curr->next;
    }
    return head;
}

Node* ArrayToLlst(vector<int> arr){
    if(arr.size()==0)
        return nullptr;
    Node* head = new Node(arr[0]);
    Node* curr = head;
    int i=1;
    while (i < (int)arr.size())
    {
        curr->next = new Node(arr[i]);
        curr = curr->next;
        i++;
    }
    return head;
}
Node* RemoveHead(Node* head){
    if(head == nullptr)
        return head;
    Node* tmp = head;
    head = head->next;
    delete tmp;
    return head;
}

Node* RemoveTail(Node* head){
    if(head == nullptr || head->next == nullptr)
        return head;
    Node* curr = head;
    while (curr->next->next != nullptr)
    {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
    return head;
}

Node* RemoveKth(Node* head, int k){
    if(head == nullptr){
        return head;
    }
    if(k == 1){
        Node* tmp = head;
        head = tmp->next;
        free(tmp);
        return head;
    }
    int cnt=1;
    Node *curr=head, *prev=nullptr;
    while (curr!=nullptr)
    {
        if(cnt == k){
            prev->next = prev->next->next;
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
        cnt++;
    }
    return head;
}

Node* RemoveEl(Node* head, int val){
    if(head == nullptr){
        return head;
    }
    if(head->getValue() == val){
        Node* tmp = head;
        head = tmp->next;
        free(tmp);
        return head;
    }
    Node *curr=head, *prev=nullptr;
    while (curr!=nullptr)
    {
        if(curr->getValue() == val){
            prev->next = prev->next->next;
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    return head;
}

Node* Reverse(Node* head){
    if(head==nullptr || head->next==nullptr)
        return head;
    Node *curr=head, *prev=nullptr;
    while (curr!=nullptr)
    {
        Node* front = curr->next;
        curr->next = prev;
        prev = curr;
        curr = front;
    }
    return prev;
}

bool isCycle(Node* head){
    if(head == nullptr)
        return 0;
    Node *slow, *fast;
    slow = fast = head;
    while (fast!=nullptr || fast->next!=nullptr)
    {
        if(slow == fast){
            return true;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return false;
}

int LoopLength(Node* head){
    if(head == nullptr)
        return 0;
    Node *slow, *fast;
    slow = fast = head;
    while (fast!=nullptr || fast->next!=nullptr)
    {
        if(slow == fast){
            break;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    if(fast==nullptr || fast->next==nullptr)
        return 0;
    int cnt=0;
    do
    {
        fast = fast->next;
        cnt++;
    } while (fast != slow);
    return cnt;
    
}

bool isPalindrome(Node* head){
    if(head==nullptr || head->next==nullptr)
        return true;

    Node *fast, *slow;
    fast = slow = head;
    while (fast->next!=nullptr && fast->next->next!=nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* newH = Reverse(slow->next);
    Display(newH);
    Node *first=head, *second=newH;

    while (second!=nullptr)
    {
        if(first->data != second->data){
            Reverse(newH);
            return false;
        }
        first = first->next;
        second = second->next;
    }
    Reverse(newH);
    return true;
}

// Node* Merge(Node* left, Node* right){
//     if(left == nullptr)
//         return right;
//     if(right == nullptr)
//         return left;
//     Node *head = nullptr;
//     if(left->data <= right->data){
//         head = left;
//         left = left->next;
//     }
//     else{
//         head = right;
//         right = right->next;
//     }
//     Node *curr = head;
//     while (left != nullptr && right != nullptr)
//     {
//         if(left->data <= right->data){
//             curr->next = left;
//             curr = curr->next;
//             left = left->next;
//         }
//         else{
//             curr->next = right;
//             curr = curr->next;
//             right = right->next;
//         }
//     }
//     if(left != nullptr){
//         curr->next = left;
//     }
//     else{
//         curr->next = right;
//     }
//     return head;
// }
// Node* MergeSort(Node* head){
//     if(head == nullptr || head->next == nullptr)
//         return head;
//     Node *slow, *fast;
//     slow = fast = head;
//     while (fast->next != nullptr && fast->next->next != nullptr)
//     {
//         slow = slow->next;
//         fast = fast->next->next;
//     }
//     Node* tmp = slow->next;
//     slow->next = nullptr;
//     Node* left = MergeSort(head);
//     Node* right = MergeSort(tmp);
//     return Merge(left, right);
// }

Node* merge(Node* left, Node* right){
    if(left == nullptr)
        return right;
    if(right == nullptr)
        return left;
    Node *curr, *res;
    res = nullptr;
    if(left->data <= right->data){
        res = left;
        left = left->next;
    }
    else{
        res = right;
        right = right->next;
    }
    curr = res;
    while (left!=nullptr && right!=nullptr)
    {
        if(left->data <= right->data){
            curr->next = left;
            left = left->next;
        }
        else{
            curr->next = right;
            right = right->next;
        }
        curr = curr->next;
    }
    
    if (left != nullptr)
    {
        curr->next = left;
    }
    if (right != nullptr)
    {
        curr->next = right;
    }
    return res;
}

Node* mergeSort(Node* head){
    if(head==nullptr || head->next==nullptr)
        return head;
    Node *slow, *fast;
    slow = fast = head;
    while (fast->next!=nullptr && fast->next->next!=nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* tmp = slow->next;
    slow->next = nullptr;
    Node* left = mergeSort(head);
    Node* right = mergeSort(tmp);
    return merge(left, right);
}

int main(){
    Node *head;
    vector<int> arr = {1, 2, 4, 4, 3, 2, 1};
    head = ArrayToLlst(arr);

    Node* sortedHead = mergeSort(head);
    Display(sortedHead);

    return 0;

}