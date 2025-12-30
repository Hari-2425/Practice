#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;


pii IsPalindrome(int i, int j, string s){
    int left=i, right=j;
    while(left>=0 && right<s.size() && s[left]==s[right]){
        left--;
        right++;
    }
    return {(right-left-1), left+1};
}

string longestPalindrome(string s){
    int n = s.length(), max_l=0;
    string ans;
    for(int i=0;i<n;i++){
        //Checking even length
        if(i>0){
            pii op = IsPalindrome(i-1, i, s);
            if(op.first > max_l){
                ans = s.substr(op.second, op.first);
                max_l = op.first;
            }
        }
        //Checking odd length
        pii op = IsPalindrome(i, i, s);
        if(op.first > max_l){
            ans = s.substr(op.second, op.first);
            max_l = op.first;
        }
    }
    return ans;
}

int countSubstrings_hlpr(int i, int j, string s){
    int left=i, right=j, res=0;
    while(left>=0 && right<s.size() && s[left]==s[right]){
        left--;
        right++;
    }
    return (right-j);
}

int countSubstrings(string s) {
    int n = s.length();
    int ans = 0;
    for(int i=0;i<n;i++){
        //Checking even length
        if(i>0){
            ans += countSubstrings_hlpr(i-1, i, s);
        }
        //Checking odd length
        ans += countSubstrings_hlpr(i, i, s);
    }
    return ans;
}

int main(){
    string s = "aaa";
    cout<<countSubstrings(s);

    return 0;
}