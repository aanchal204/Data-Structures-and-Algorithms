#include<stdio.h>
#include<stdlib.h>      //malloc
#include<string.h>      //memset
#include<stdbool.h>
#include<math.h>
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>     //sort()
#include<cmath>         //abs()
#include<set>
#include<list>
#include<cstdio>
#define DEBUG 1
using namespace std;
#define MOD 1000000007
#define SIZE 100003
#define dump(x) printf(#x" = %lld\n",x);
#define INF 200005
typedef long long int ll;
#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))
#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define CONTEST 1
#define EPSILON 8.33e-3
#define LIMIT 5000000
/*
 A suffix array is a sorted array of all suffixes of a given string.
 
 http://www.geeksforgeeks.org/suffix-array-set-1-introduction/
 naive approach
 find all the suffixes of a string
 and then sort them in ascending order to get the suffix array
 
 The time complexity of above method to build suffix array is O(n2Logn)
 if we consider a O(nLogn) algorithm used for sorting.
 The sorting step itself takes O(n2Logn) time as every comparison
 is a comparison of two strings and the comparison takes O(n) time.
 
 Addition: finds the length of the longest common prefix between the consecutive suffixes
 it is used to calculate the number of distinct substrings in an array
 https://greasepalm.wordpress.com/2012/07/01/suffix-arrays-a-simple-tutorial/
 nC2 - sum of length of all LCP
 
 */
int compare(pair<string, int> a, pair<string, int> b){
    return a.first.compare(b.first) < 0?1:0;
}
vector<pair<string, int> > makeSuffixArray(string s){
    int len = s.length();
    vector<pair<string, int> > suffix;
    for(int i=len-1;i>=0;i--){
        suffix.push_back(make_pair(s.substr(i,len-i), i));
    }
    sort(suffix.begin(), suffix.end(), compare);
    for(int i=0;i<len;i++)
        cout<<suffix[i].first<<" "<<suffix[i].second<<endl;
    return suffix;
}
vector<int> createLongestCommonPrefix(vector<pair<string, int> >suffix){
    int len = suffix.size();
    vector<int> longestCommonPrefix;
    for(int i=0;i<len-1;i++){
        int count = 0;
        for(int j=0;j<suffix[i].first.length() && j<suffix[i+1].first.length();j++){
            if(suffix[i].first[j] == suffix[i+1].first[j])
                count++;
            else
                break;
        }
        longestCommonPrefix.push_back(count);
    }
    longestCommonPrefix.push_back(0);
    return longestCommonPrefix;
}
int main()
{
    string s;
    cin>>s;
    vector<pair<string, int> >suffixArray;
    suffixArray = makeSuffixArray(s);
    vector<int> longestCommonPrefix = createLongestCommonPrefix(suffixArray);
    for(int i=0;i<longestCommonPrefix.size();i++)
        cout<<longestCommonPrefix[i]<<" ";
    return 0;
}