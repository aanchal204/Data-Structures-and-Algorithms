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
typedef struct node{
    int index,rank,nextRank;
}node;
int compare(node a, node b){
    if(a.rank < b.rank)
        return 1;
    if(a.rank > b.rank)
        return 0;
    if(a.nextRank < b.nextRank)
        return 1;
    if(a.nextRank > b.nextRank)
        return 0;
    return 0;
}
vector<node> makeSuffixArray(string s){
    int len = s.length();
    vector<node> suffix;

    for (int i=0;i<len;i++){
        node temp;
        temp.index = i;
        temp.rank = s[i]-'a';
        temp.nextRank = i+1>=len ? -1 : s[i+1]-'a';
        suffix.push_back(temp);
    }
    sort(suffix.begin(),suffix.end(),compare);
    
    for(int k=4;k<2*len;k<<=1){
        
        for(int i=0;i<len;i++)
            cout<<suffix[i].index<<" "<<suffix[i].rank<<" "<<suffix[i].nextRank<<endl;
        cout<<endl;
        
        int previousRank = suffix[0].rank;
        int rank = 0;
        suffix[0].rank = rank;
        for(int i=1;i<len;i++){
            previousRank = suffix[i].rank;
            if(suffix[i].rank == previousRank && suffix[i].nextRank == suffix[i-1].nextRank)
                suffix[i].rank = rank;
            else
                suffix[i].rank = ++rank;
        }
        for(int i=0;i<len;i++){
            suffix[i].nextRank = suffix[i].index + k/2 >= len ? -1 : suffix[i+k/2].rank;
        }
        sort(suffix.begin(),suffix.end(),compare);
    }
    
    return suffix;
}
int main()
{
    string s;
    cin>>s;
    vector<node>suffixArray;
    suffixArray = makeSuffixArray(s);
    for(int i=0;i<s.length();i++)
        cout<<suffixArray[i].index<<" ";
    return 0;
}