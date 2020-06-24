#include <bits/stdc++.h>
using namespace std;
/*
Jose Carlos Vasques Moreira
Este programa implementa integração aproximada pela regra do trapézio
Basta entrar com o intervalo desejado e o numero de intrevalos.
Há alguns exemplos de uso já listados na main, para resolucao da lista de ex. de MS211
Note que para trocar a funcao integrada, voce precisa editar a funcao f neste arquivo e recompilar


compile me with
g++ FILENAME -O2 -std=c++17 -o PROGRAMNAME

https://github.com/JoseCVM/ms211
*/
double f(double x){ 
	return exp(-(x*x));
} 
  
double trapezio(double a, double b, double n){
	double h = (b-a)/n; 
	double res = f(a)+f(b); 
  
	for (int i = 1; i < n; i++) res += 2*f(a+i*h); 
	res *= (h/2);
	return res; 
}

int main(){	
	double ini,fim; cin >> ini >> fim;
	int n;cin >> n;
  
	printf("Resultado: %.10lf\n", trapezio(ini, fim, n)); 
	return 0; 
} 