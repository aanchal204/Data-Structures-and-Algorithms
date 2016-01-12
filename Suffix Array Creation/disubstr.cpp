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
typedef struct node{
    int index,rank,nextRank;
}node;
//http://www.spoj.com/problems/DISUBSTR/
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
    
    int k,step;
    // Let us sort suffixes according to first 1
    // character, then first 2, then first 4 and so on
    for(k = 1,step = 1;k<2*len;step++,k<<=1){
        suffix.clear();
        for(int i=0;i<len;i++){
            node temp;
            temp.index = i;
            temp.rank = pos[step-1][i];
            //for a suffix with index i, the nextRank will be the rank of the suffix with index i+k
            temp.nextRank = i+k < len ? pos[step-1][i+k] : -1;
            suffix.push_back(temp);
        }
        sort(suffix.begin(), suffix.end(), compare);
        //if the rank and nextRank of the current suffex and the previous suffix are the same, then the new rank of the current suffix will be same as that of the previous suffix
        for(int i=0;i<len;i++){
            pos[step][suffix[i].index] = (i>0 && suffix[i].rank == suffix[i-1].rank && suffix[i].nextRank == suffix[i-1].nextRank) ? (pos[step][suffix[i-1].index]) : (i);
        }
    }
    
    //finding the longest common prefix of the consecutive suffixes
    ll repeat = 0;
    for(int i=1;i<len;i++){
        int x,y;
        x = suffix[i].index;
        y=suffix[i-1].index;
        ll ans = 0;
        for(k=step-1;k>=0 && x<len && y<len;k--){
            // when the pos[k][x] == pos[k][y]
            //it means that the ranks of the suffixes beginning at index x and y and of length 2^k are equal
            //since the rank is equal, i.e. the suffixes are same
            //hence 2^k characters will be the same
            //we then look at the x+2^k and y+2^k characters onwards since 2^k chars have been found to be the same
            if(pos[k][x] == pos[k][y]){
                x += 1<<k;
                y += 1<<k;
                ans += 1<<k;
            }
        }
        repeat += ans;
    }
    cout<<len*(len+1)/2 - repeat<<endl;
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
        //for(int i=0;i<suffixArray.size();i++)
        //  printf("%d ",suffixArray[i].index);
    }
    return 0;
}