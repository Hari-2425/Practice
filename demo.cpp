#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    unordered_map<string, int> dict;
    vector<int> par;

    int findPar(int node){
        if(par[node] == node){
            return node;
        }
        return par[node] = findPar(par[node]);
    }

    void unite(int a, int b){
        int pa = findPar(a);
        int pb = findPar(b);
        if(pa != pb){
            par[pb] = pa;
        }
    }

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        for(int i=0;i<accounts.size();i++){

            for(int j=1;j<accounts[i].size();j++){
                string email = accounts[i][j];
                
            }
        }
        unordered_map<int, set<string>> tmp_res;
        vector<vector<string>> res;
        for(auto pr: dict){
            string email = pr.first;
            int person = pr.second;

            tmp_res[person].insert(email);
        }

        for(auto pr: tmp_res){
            string person_name = accounts[pr.first][0];
            vector<string> tmp;
            tmp.push_back(person_name);
            for(string email: pr.second){
                tmp.push_back(email);
            }
            res.push_back(tmp);
        }
        return res;
    }
};

vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, 1);

    // Left Pass: ans[i] contains product of all elements to the left
    int leftProduct = 1;
    for (int i = 0; i < n; i++) {
        ans[i] = leftProduct;
        leftProduct *= nums[i];
    }

    // Right Pass: Multiply ans[i] by product of all elements to the right
    int rightProduct = 1;
    for (int i = n - 1; i >= 0; i--) {
        ans[i] *= rightProduct;
        rightProduct *= nums[i];
    }

    return ans;
}


int main(){
    vector<int> arr = {2, 4, 9, 1, 0, 10, 3};
    vector<int> ans = productExceptSelf(arr);
    for(int it: ans){
        cout<<it<<", "; 
    }
    return 0;
}