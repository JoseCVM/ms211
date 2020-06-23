#include <bits/stdc++.h>
using namespace std; 
/*
Jose Carlos Vasques Moreira
Este programa implementa integração aproximada pela regra de 1/3 de Simpson
Basta entrar com o intervalo desejado e o numero de intrevalos.
Há alguns exemplos de uso já listados na main, para resolucao da lista de ex. de MS211
Note que para trocar a funcao integrada, voce precisa editar a funcao f neste arquivo e recompilar


compile me with
g++ FILENAME -O2 -std=c++17 -o PROGRAMNAME

https://github.com/JoseCVM/ms211
*/
double f(double x){ 
    return sin(x); 
} 
double simpsons(double ini, double fim, int n){ 
    double h = (fim - ini) / n; 
    double x[n+3], fx[n+3]; 
    for (int i = 0; i <= n; i++){ 
        x[i] = ini + i * h; 
        fx[i] = f(x[i]); 
    } 
    double res = fx[0]+fx[n]; 
    for(int i = 1; i < n; i++){
		res += (i%2 != 0 ? 4 : 2)*fx[i];
    } 
    res = res * (h / 3); 
    return res; 
} 
  
int main(){    
    double ini,fim; cin >> ini >> fim;
	int n;cin >> n;
  
    printf("Resultado: %.10lf\n", simpsons(ini, fim, n)); 
    return 0; 
} 