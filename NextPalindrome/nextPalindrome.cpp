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
#include<map>
#define DEBUG 1
using namespace std;
#define MOD 1000000007
#define SIZE 1000003
#define dump(x) printf(#x" = %lld\n",x);
#define INF 1000005
typedef long long int ll;
#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))
#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define CONTEST 1
#define EPSILON 8.33e-3
#define LIMIT 5000000
#define MAXN 100004
//https://www.codechef.com/problems/PALIN
//http://www.geeksforgeeks.org/given-a-number-find-next-smallest-palindrome-larger-than-this-number/
int arr[SIZE];
bool stringToArray(string s){
    bool flag = false;
    for(int i=0;i<s.size();i++){
        arr[i] = s[i]-'0';
        if(arr[i]!=9)
            flag = true;
    }
    return flag;
}
void nextPalindrome(int len){
    int i,j;
    if(len&1){
        i = len/2 - 1;
        j = len/2 + 1;
    }else{
        i = len/2 -1;
        j = len/2;
    }
    /*
     We will start with two indices i and j. i pointing to the two middle elements 
     (or pointing to two elements around the middle element in case of n being odd). 
     We one by one move i and j away from each other.
     */
    while(i>=0 && j<len && arr[i] == arr[j]){
        i--;
        j++;
    }
    //case 1 : when it is already a palindrome
    //add 1 to the middle and propagate the carry
    if(i<0 || j>=len){
        if(len&1){
            i = len/2 - 1;
            j = len/2 + 1;
            int sum = arr[len/2]+1;
            int carry = sum/10;
            arr[len/2] = sum%10;
            while(carry){
                sum = carry + arr[i];
                carry = sum/10;
                arr[i] = arr[j] = sum%10;
                i--;
                j++;
            }
        }else{
            i = len/2 - 1;
            j = len/2;
            int sum = arr[len/2]+1;
            int carry = sum/10;
            arr[i] = arr[j] = sum%10;
            while(carry){
                i--;
                j++;
                sum = carry + arr[i];
                carry = sum/10;
                arr[i] = arr[j] = sum%10;
                
            }

        }
    }else{
        //we simply need to copy the digits on the left to the digits on the right
        //special case : when digit on left is less than the digit on right
        // in this case, increment the middle element(s) and propagate the carry
        bool isLeftSmall = false;
        if(arr[i] < arr[j])
            isLeftSmall = true;
        //copying the mirror of left to right
        while(i>=0 && j<len){
            arr[j] = arr[i];
            i--;
            j++;
        }
        if(isLeftSmall){
            //add 1 to the middle and propagate the carry
            int left,right;
            if(len&1){
                left = len/2 - 1;
                right = len/2 + 1;
                int sum = arr[len/2]+1;
                int carry = sum/10;
                arr[len/2] = sum%10;
                while(carry){
                    sum = carry + arr[left];
                    carry = sum/10;
                    arr[left] = arr[right] = sum%10;
                    left--;
                    right++;
                }
            }else{
                left = len/2 - 1;
                right = len/2;
                int sum = arr[len/2 - 1]+1;
                int carry = sum/10;
                arr[left] = arr[right] = sum%10;
                while(carry){
                    left--;
                    right++;
                    sum = carry + arr[left];
                    carry = sum/10;
                    arr[left] = arr[right] = sum%10;
                }
            }
        }
    }
}
int main(void)
{
    int t;
    scanf("%d",&t);
    while(t--){
        string s;
        cin>>s;
        bool flag = stringToArray(s);
        if(flag){
            nextPalindrome(s.size());
            for(int i=0;i<s.size();i++)
                cout<<arr[i];
            cout<<endl;
        }
        else{
            //special case when all digits are 9
            // ans will be 1000..001
            //number of 0s = number of 9s - 1
            //eg : 99 -> 101
            printf("1");
            for(int i=0;i<s.size()-1;i++)
                printf("0");
            printf("1\n");
        }
        
    }
    return 0;
}