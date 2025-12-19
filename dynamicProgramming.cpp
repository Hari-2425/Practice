#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

struct PairHash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};
//KnapSack type
int recursive_func(int idx, vector<int> &weights, vector<int> &val, int W, unordered_map<pii, int, PairHash> &store){
    if(idx>=weights.size() || W<=0)
        return 0;
    if(store.count({idx, W})){
        return store[{idx, W}];
    }
    if(weights[idx] <= W){
        int ans1 = recursive_func(idx+1, weights, val, W, store); //not selected
        int ans2 = recursive_func(idx+1, weights, val, W-weights[idx], store) + val[idx]; //Selected
         
        return store[{idx, W}] = max(ans1, ans2);
    }
    
    return store[{idx, W}] = recursive_func(idx+1, weights, val, W, store);
}

int knapSack(vector<int> weights, vector<int> val, int W){
    int n = weights.size();
    
    unordered_map<pii, int, PairHash> store;
    return recursive_func(0, weights, val, W, store);
}

int main(){
    vector<int> wt = {1, 3, 4, 5};
    vector<int> val = {1, 4, 5, 7};
    int W = 7;

    cout<<"ANS: "<<knapSack(wt, val, W);

    return 0;
}