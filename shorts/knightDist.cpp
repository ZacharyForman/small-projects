#include<iostream>
#include<queue>
#define P n.push(a),m.push(b)
#define M(X,Y)if((a=R+X)<8&(b=S+Y)<8)P,C[a*8+b]=C[R*8+S]+1;
main(){char s[6],t[6];std::cin>>s;for(;std::cin>>s>>t;){unsigned R=97,S=49,a=*t-R,b=t[1]-S,c=*s-R,d=s[1]-S,C[64];for(S=64;S--;)C[S]=9;C[a*8+b]=0;std::queue<int>n,m;P;while(C[c*8+d]&8){R=n.front();S=m.front();M(1,2)M(2,1)M(1,-2)M(-2,1)M(-2,-1)M(-1,-2)M(-1,2)M(2,-1)n.pop();m.pop();}std::cout<<C[c*8+d]<<'\n';}}