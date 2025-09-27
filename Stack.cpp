#include <bits/stdc++.h>
#include <iostream>

using namespace std;

vector<int> asteroidCollision(vector<int>& asteroids) {
    int n = asteroids.size();
    if(n <= 1){
        return asteroids;
    }
    stack<int> st;
    
    for(auto it: asteroids){
        if(!st.empty() && st.top()>0 && it<0){
            if(!st.empty() && st.top()>0 && st.top()<abs(it)){
                while(!st.empty() && st.top()>0 && st.top()<abs(it)){
                    st.pop();
                }
                if(st.empty() || st.top()<0) st.push(it);
                else if(!st.empty() && st.top()>0 && st.top()==abs(it)) st.pop();
            }
            else if(st.top()>0 && st.top()==abs(it)){
                st.pop();
            }
        }
        else{
            st.push(it);
        }
    }

    vector<int> ans;
    while(!st.empty()){
        ans.push_back(st.top());
        st.pop();
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
    sort(asteroids.begin(), asteroids.end());
    long long int w = mass;
    for(auto it: asteroids){
        if(w < it)
            return false;
        w += it;
    }
    return true;
}

int main(){
    vector<int> as = {10,2,-5};
    vector<int> ans = asteroidCollision(as);
    for(auto it: ans){
        cout<<it<<", ";
    }
    return 0;
}