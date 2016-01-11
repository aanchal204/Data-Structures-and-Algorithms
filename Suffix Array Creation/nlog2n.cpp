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

    //sort according to the first 2 characters of the suffixes
    for (int i=0;i<len;i++){
        node temp;
        temp.index = i;
        temp.rank = s[i]-'a';
        temp.nextRank = i+1>=len ? -1 : s[i+1]-'a';
        suffix.push_back(temp);
    }
    sort(suffix.begin(),suffix.end(),compare);
    
    // At his point, all suffixes are sorted according to first
    // 2 characters.  Let us sort suffixes according to first 4
    // characters, then first 8 and so on
    for(int k=4;k<2*len;k<<=1){
        
        int previousRank = suffix[0].rank;
        int rank = 0;
        suffix[0].rank = rank;
        //loop to update the ranks of the suffix
        for(int i=1;i<len;i++){
            previousRank = suffix[i].rank;
            //if the current rank and nextRank is same as those of the previous suffix,
            //the current rank will be same as the suffix
            //else it will be one greater than the previous suffix's rank
            if(suffix[i].rank == previousRank && suffix[i].nextRank == suffix[i-1].nextRank)
                suffix[i].rank = rank;
            else
                suffix[i].rank = ++rank;
        }
        //loop to update the nextRank of the suffixes
        //for a suffix with index i, the nextRank will be the rank of the suffex with index i+k/2
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