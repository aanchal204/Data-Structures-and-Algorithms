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
 
http://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/
 The naive approach has a high time complexity
 
 It can be reduced to n logn * logn
 
 We first sort all suffixes according to first character, 
 then according to first 2 characters, 
 then first characters and so on while the number of characters 
 to be considered is smaller than 2n. The important point is, 
 if we have sorted suffixes according to first 2i characters, 
 then we can sort suffixes according to first 2i+1 characters 
 in O(nLogn) time using a nLogn sorting algorithm like Merge Sort. 
 This is possible as two suffixes can be compared in O(1) time
 
 https://github.com/pulkit110/Algorithms/blob/master/Spoj/Complete/DISUBSTR.cpp
 
 */
typedef struct node{
    int index,rank,nextRank;
}node;
int compare(node a, node b){
    return (a.rank == b.rank) ? (a.nextRank < b.nextRank ? 1 : 0) : (a.rank < b.rank ? 1 : 0);
}
vector<node> makeSuffixArray(string s){
    ll len = s.length();
    vector<node> suffix;
    int min = 256;
    for(int i=0;i<len;i++)
        min = min(min , s[i]);
    
    int pos[20][len+1];      //position matrix
    //pos[i][j] = sorted index of the substring starting at the jth index and of length 2^i
    
    for(int i=0;i<len;i++)
        pos[0][i] = s[i]-min;
    
    // Let us sort suffixes according to first 1
    // character, then first 2, then first 4 and so on
    for(int k = 1,step = 1;k<2*len;step++,k<<=1){
        suffix.clear();
        for(int i=0;i<len;i++){
            node temp;
            temp.index = i;
            temp.rank = pos[step-1][i];
            //for a suffix with index i, the nextRank will be the rank of the suffix with index i+k
            temp.nextRank = i+k < len ? pos[step-1][i+k] : -1;
            suffix.push_back(temp);
        }
        //for(int i=0;i<len;i++)
        //  printf("%d %d %d\n",suffix[i].index,suffix[i].rank,suffix[i].nextRank);
        sort(suffix.begin(), suffix.end(), compare);
        //if the rank and nextRank of the current suffex and the previous suffix are the same, then the new rank of the current suffix will be same as that of the previous suffix
        for(int i=0;i<len;i++){
            pos[step][suffix[i].index] = (i>0 && suffix[i].rank == suffix[i-1].rank && suffix[i].nextRank == suffix[i-1].nextRank) ? (pos[step][suffix[i-1].index]) : (i);
        }
    }
    return suffix;
}
int main(void)
{
    int t;
    cin>>t;
    getchar();
    while(t--){
        string s;
        getline(cin, s);
        vector<node>suffixArray;
        suffixArray = makeSuffixArray(s);
        for(int i=0;i<suffixArray.size();i++)
            printf("%d ",suffixArray[i].index);
    }
    return 0;
}