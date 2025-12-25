#include <bits/stdc++.h>
using namespace std;

void Display(vector<int> &vec){
    for(auto it: vec){
        cout<<it<<", ";
    }
    cout<<"\n";
}

vector<int> solve_lexico_smallest_perm(int n, vector<int> &data){
    using vi = vector<int>;
    priority_queue<vi, vector<vi>, greater<vi>> pq;
    for(int i=0;i<data.size();i++){
        pq.push({data[i], i+1});
    }
    vector<int> ans;
    while(!pq.empty()){
        ans.push_back(pq.top()[1]);
        pq.pop();
    }
    return ans;
}

int solve_beautiful_painting(int k, vector<vector<int>> &paint){
    
}

int main(){
    vector<int> data = {2,1,2};
    vector<int> ans = solve_lexico_smallest_perm(3, data);
    Display(ans);

    return 0;
}