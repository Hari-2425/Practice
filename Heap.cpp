#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class dataStruct{
    public:
    priority_queue<int> right;
    priority_queue<int, vector<int>, greater<int>> left;

    dataStruct(){

    }

    void AddNumber(int num){
        // by default add num into left pq.
        left.push(num);
        // size difference is <= 1
        if(abs(left.size()-right.size()) <= 1){
            return;
        }
        if(left.size() > right.size()){
            right.push(left.top());
            left.pop();
        }
        else{
            left.push(right.top());
            right.pop();
        }
    }

    double FindMedian(){
        if(right.size() == left.size()){
            int a = right.top();
            int b = left.top();
            return (double)(a+b)/2;
        }
        else{
            if(left.size() > right.size())
                return (double)left.top();
            else
                return (double)right.top();
        }
    }
};




int main(){

    // priority_queue<int, vector<int>, greater<int>> pq;
    // pq.push(4);
    // pq.push(2);
    // pq.push(1);
    // pq.push(10);
    // pq.push(7);
    // pq.push(9);
    // pq.push(3);
    // pq.push(5);
    // pq.push(6);
    // pq.push(8);

    // while (!pq.empty())
    // {
    //     /* code */
    //     cout<<pq.top()<<" ";
    //     pq.pop();
    // }
    dataStruct ds;
    for(int i=0;i<6;i++){
        ds.AddNumber(i);
    }
    // 0 1 2 3 4 5
    cout<<ds.FindMedian()<<"\n";
    for(int i=10;i<17;i++){
        ds.AddNumber(i);
    }
    // 0 1 2 3 4 5 10 11 12 13 14 15 16
    cout<<ds.FindMedian()<<"\n";
    return 0;
}