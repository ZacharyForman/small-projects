m(int*s,int*f){int v=0,m=1<<31;for(;f-s;m=v>m?v:m,v=v>0?v:0)v+=*s++;return m;}