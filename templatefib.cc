#include <cstdio>

//Silly O(1) (runtime) fibonacci calculator :) 

template<int i> unsigned long long int fib(){
	return fib<i-1>() + fib<i-2>();
}

template<> unsigned long long int fib<0>(){
	return 0;
}

template<> unsigned long long int fib<1>(){
	return 1;
}

#define f(x) printf("Fibb(" "%d" ") = %llu\n", x, fib<x>())

template<int i> void loop(){
	f(80-i);
	loop<i-1>();
}

template<> void loop<-1>(){}

int main(){
	loop<80>();
}
