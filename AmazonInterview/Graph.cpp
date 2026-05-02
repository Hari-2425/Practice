#include <bits/stdc++.h>

using namespace std;

void WordBreak2_hlpr(int start, string inp, set<string> &dict, vector<string> &path,
    vector<vector<string>> &ans){
    if(start >= inp.length()){
        ans.push_back(path);
    }
    
    string tmp = "";
    for(int i=start;i<inp.size();i++){
        tmp += inp[i];
        if(dict.find(tmp) != dict.end()){
            path.push_back(tmp);
            WordBreak2_hlpr(i+1, inp, dict, path, ans);
            path.pop_back();
        }
    }
}

vector<string> wordBreak(string s, vector<string>& wordDict){
    vector<string> path;
    vector<vector<string>> ans;
    set<string> dict;
    for(int i=0;i<wordDict.size();i++){
        dict.insert(wordDict[i]);
    }

    WordBreak2_hlpr(0, s, dict, path, ans);
    vector<string> res;
    for(auto a: ans){
        string add = "";
        for(auto str: a){
            add += str;
            add += " ";
        }
        add.pop_back();
        res.push_back(add);
    }
    return res;
}

string reorganizeString(string s) {
    
}

int main(){
    string s = "catsandog";
    vector<string> wordDict = {"cats","dog","sand","and","cat"};

    vector<string> ans = wordBreak(s, wordDict);
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<"\n";
    }

    return 0;
}