//http://www.spoj.com/problems/PLD/
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
#define MAXN 100030
void lpsManacher(char *s, ll len, ll k){
    //preprocess the string to add # between the characters
    ll i;
    char a[2*MAXN];
    a[0] = '$';     //start of string
    a[1] = '#';
    for(i=0;i<len;i++){
        ll index = (i+1)*2;
        a[index] = s[i];
        a[index+1] = '#';
    }
    a[(i+1)*2] = '@';       //end of string
    
    //manacher's algorithm
    ll centre, right;
    centre = right = 0;
    ll palLen[2*MAXN] = {0};
    //palLen[i] = length of the longest palindrome with centre at i
    /*
     1. Copy the value from the mirror: only if i lies within the current boundary of centre i.e. i<right
     2. Expand at the current centre beyond the boundary - start expanding beyond i+palLen[i]
     from the mirror, we got that the length of palindrome at i is the value at mirror
     and hence we start comparing the characters beyond i+palLen[i]
     3. Update the centre and the boundary- once we have the length of the palindrome centred at i
     update the centre and boundary values, if this palindrome is of a longer length
     */
    ll count = 0;
    for(int i=1;i<(len+1)*2;i++){
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
        /*
         Tricky part to count the number of palindromes of length k
         Hint: a palindrome of length 5 contains a palindrome of length 3 and 1
         eg: ababa
         the palLen value for b will be 3, but it contains a palindrome of length 1 as well: 'b'
         another: 2 abbaabbacaacfguiuoppo
         palLen for ab#ba.. is 4 (palindrome is abba)
         it contains a palindrome of length 2 also (bb) which is taken care by the following lines
         an even palindrome of length x, contains even palindromes of length 2,4,6...x
         an odd palindrome of length y, contains odd palindromes of length 1,3,5,...y
         */
        if(palLen[i] >= k){
            if(palLen[i]%2==0 && k%2==0)
                count++;
            if(palLen[i]%2!=0 && k%2!=0)
                count++;
        }
    }
    printf("%lld\n",count);
}
int main(void)
{
    ll n;
    scanf("%lld",&n);
    char s[MAXN];
    scanf("%s",s);
    lpsManacher(s, strlen(s),n);
    return 0;
}