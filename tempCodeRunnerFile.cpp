string minWindow(string s, string t){
//     if(t.size() == 0){
//         return "";
//     }
//     unordered_map<char, int> mps, mpt;
//     for(auto i: t){
//         mpt[i]++;
//     }
//     int start_index = -1;
//     int left=0, right=0, minLen=1e9, formed=0;

//     for(;right<s.length();++right){
//         char currChar = s[right];
//         mps[currChar]++;
//         if(mpt.count(currChar) && mpt[currChar]==mps[currChar]){
//             formed++;
//         }
//         while (left<=right && formed==mpt.size())
//         {
//             currChar = s[left];
//             if(right-left+1 < minLen){
//                 minLen = right-left+1;
//                 start_index = left;
//             }

//             mps[currChar]--;
//             if(mpt.count(currChar) && mps[currChar]<mpt[currChar]){
//                 formed--;
//             }

//             left++;
//         }
        
//     }
//     if(start_index == -1){
//         return "";
//     }
//     return s.substr(start_index, minLen);
// }