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
#define MAXN 500003
typedef struct node{
    ll index,rank,nextRank;
}node;
vector<node> radix[MAXN];    //maxn : max rank possible
ll pos[20][MAXN];      //position matrix
//pos[i][j] = sorted index of the substring starting at the jth index and of length 2^i

ll modpow(ll a, ll b)
{
    ll x=1ll, y=a;
    while(b){
        if(b%2)
            x=(x*y);
        y=(y*y);
        b/=2;
    }
    return x;
}

/*
 To find the longest common substring between 2 strings
 concatenate the 2 strings together, and compute the LCP array
 LCP: longest common prefix
 as the name suggests, it gives the length of the longest commmon prefix between adjacent suffixes
 in the suffix array.
 We only need to check, that the start indices of the suffixes belong to different strings
 i.e. ith index of s1 and i-1th index of s2 or vice versa
 
 For ref: http://www.roman10.net/suffix-array-part-3-longest-common-substring-lcs/
 */

vector<node> countingSort(vector<node> suffix){
    //sort according to the nextRank
    
    ll max = -1;
    for(ll i=0;i<MAXN;i++)
        radix[i].clear();
    for(ll i=0;i<suffix.size();i++){
        radix[suffix[i].nextRank+1].push_back(suffix[i]);
        max = max(max,suffix[i].nextRank+1);
    }
    suffix.clear();
    for(ll i=0;i<=max;i++){
        for(int j=0;j<radix[i].size();j++){
            suffix.push_back(radix[i][j]);
        }
        radix[i].clear();
    }
    //sort according to the rank
    max = -1;
    //for(int i=0;i<MAXN;i++)
    //  radix[i].clear();
    for(ll i=0;i<suffix.size();i++){
        radix[suffix[i].rank+1].push_back(suffix[i]);
        max = max(max, suffix[i].rank+1);
    }
    suffix.clear();
    for(ll i=0;i<=max;i++){
        for(int j=0;j<radix[i].size();j++){
            suffix.push_back(radix[i][j]);
        }
    }
    return suffix;
}
void makeSuffixArray(string s,ll len1, ll len2){
    vector<node> suffix;
    ll len = len1+len2;
    for(ll i=0;i<len;i++){
        pos[0][i] = s[i]-'a';
    }
    
    ll k,step;
    // Let us sort suffixes according to first 1
    // character, then first 2, then first 4 and so on
    for(k = 1,step = 1;k<len;step++,k<<=1){
        suffix.clear();
        for(ll i=0;i<len;i++){
            node temp;
            temp.index = i;
            temp.rank = pos[step-1][i];
            //for a suffix with index i, the nextRank will be the rank of the suffix with index i+k
            temp.nextRank = i+k < len ? pos[step-1][i+k] : -1;
            suffix.push_back(temp);
        }
        //for(int i=0;i<len;i++)
        //  printf("%d %d %d\n",suffix[i].index,suffix[i].rank,suffix[i].nextRank);
        
        /*sort(suffix.begin(), suffix.end(), compare);
         only by changing the sort algo, the time complexity will vary
         instead of using quick sort (nlogn) the complexity becomes: nlogn*logn
         if counting sort is used, (n) the complexity becomes n*logn
         logn : number of times the sort function is called because we sort the suffixes according to the first char, first 2 chars, first 4 chars and so on
         */
        
        suffix = countingSort(suffix);
        
        //if the rank and nextRank of the current suffex and the previous suffix are the same, then the new rank of the current suffix will be same as that of the previous suffix
        for(ll i=0;i<len;i++){
            pos[step][suffix[i].index] = (i>0 && suffix[i].rank == suffix[i-1].rank && suffix[i].nextRank == suffix[i-1].nextRank) ? (pos[step][suffix[i-1].index]) : (i);
        }
    }
    ll max = 0;
    
    //finding the longest common prefix of the consecutive suffixes
    //ll repeat = 0;
    for(ll i=1;i<len;i++){
        ll x,y;
        x = suffix[i].index;
        y = suffix[i-1].index;
        ll ans = 0;
        for(k=step-1;k>=0;k--){
            // when the pos[k][x] == pos[k][y]
            //it means that the ranks of the suffixes beginning at index x and y and of length 2^k are equal
            //since the rank is equal, i.e. the suffixes are same
            //hence 2^k characters will be the same
            //we then look at the x+2^k and y+2^k characters onwards since 2^k chars have been found to be the same
            ll pow = modpow(2, k);
            if(x+pow<=len && y+pow<=len && pos[k][x] == pos[k][y]){
                x += pow;
                y += pow;
                ans += pow;     //ans is my current LCP between i and i-1 suffix
            }
        }
        //cout<<ans<<" ";
        if(ans > max){
            if((suffix[i].index<len1 && suffix[i-1].index>=len1)||(suffix[i].index>=len1&&suffix[i-1].index<len1)){
                max = ans;
            }
        }
    }
    printf("%lld\n",max);
}
int main(void)
{
    string a,b;
    char s1[MAXN],s2[MAXN];
    scanf("%s",s1);
    scanf("%s",s2);
    a = string(s1);
    b = string(s2);
    a = a + b;
    makeSuffixArray(a, strlen(s1), strlen(s2));
    return 0;
}