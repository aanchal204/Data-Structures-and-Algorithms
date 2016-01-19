//https://www.hackerrank.com/contests/security-challenge/challenges/largest-palindromic-substring
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
#define INF 100005
typedef long long int ll;
#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))
#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define CONTEST 1
#define EPSILON 8.33e-3
#define LIMIT 5000000
#define MAXN 1000300
vector<char> a;
vector<ll> palLen;
void lpsManacher(string s,ll len){
    //preprocess the string to add # between the characters
    ll i;
    
    a.clear();
    a.push_back('$');
    a.push_back('#');
    for(i=0;i<len;i++){
        a.push_back(s[i]);
        a.push_back('#');
    }
    a.push_back('@');
    
    //manacher's algorithm
    ll centre, right;
    centre = right = 0;
    //palLen[i] = length of the longest palindrome with centre at i
    /*
     1. Copy the value from the mirror: only if i lies within the current boundary of centre i.e. i<right
     2. Expand at the current centre beyond the boundary - start expanding beyond i+palLen[i]
     from the mirror, we got that the length of palindrome at i is the value at mirror
     and hence we start comparing the characters beyond i+palLen[i]
     3. Update the centre and the boundary- once we have the length of the palindrome centred at i
     update the centre and boundary values, if this palindrome is of a longer length
     */
    ll max = -1;
    ll palCentre = 0;
    palLen.push_back(0);
    for(int i=1;i<(len+1)*2;i++){
        palLen.push_back(0);
        ll mirror = 2*centre - i;
        if(i < right)
            palLen[i] = min(palLen[mirror] , right-i);
        //expand at the current centre i
        while(a[i - (palLen[i] + 1)] == a[i + (palLen[i]+1)])
            palLen[i]++;
        if(i + palLen[i] > right){
            centre = i;
            right = i + palLen[i];
        }
        if(palLen[i] > max){
            max = palLen[i];
            palCentre = i;
        }
    }
    if(max&1){
        //cout<<palCentre<<" "<<max<<" "<<a[palCentre]<<endl;
        s = s.substr((palCentre-max)/2 , max);
    }else{
        s = s.substr((palCentre-max)/2,max);
    }
    cout<<s;
    //printf("%lld\n",max);
}
int main(void)
{
    string s;
    getline(cin, s);
    lpsManacher(s,strlen(s.c_str()));
    return 0;
}