m(s,f,v,m)int*s;{for(v=0,m=1<<31;f-s;m=v>m?v:m,v=v>0?v:0)v+=*s++;return m;}
