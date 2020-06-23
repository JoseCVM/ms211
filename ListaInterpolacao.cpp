#include <bits/stdc++.h>
using namespace std;
/*
Jose Carlos Vasques Moreira
Este programa implementa algumas funcoes simples de interpolacao.
Basta entrar com os valores de x e f(x) desejados chamar a funcao correspondente para observar
os resultados. Há alguns exemplos de uso já listados na main, para resolucao da lista de ex. de MS211



compile me with
g++ FILENAME -O2 -std=c++17 -o PROGRAMNAME

https://github.com/JoseCVM/ms211
*/
double term(int i,double value,vector<double> x){
	double pro = 1;
	for(int j = 0;j<i;j++){
		pro *= (value-x[j]);
	}
	return pro;
}	

void makeDiffTable(vector<double> &x,vector<vector<double>> &y,int n){
	for(int i = 1;i<n;i++){
		for(int j = 0;j<n-i;j++){
			y[j][i] = ((y[j][i - 1] - y[j + 1][i - 1]) / (x[j] - x[i + j]));			
		}		
	}	
}

double newtonFormula(double value,vector<double> &x,vector<vector<double>> &y,int n){
	double sum = y[0][0];
	for(int i = 1;i<n;i++){
		sum += term(i,value,x)*y[0][i];		
	}
	return sum;
}
double absD(double x){
	return x < 0 ? x*-1 : x;	
}
double getMaxAbs(int j,vector<vector<double>> &y){
	double res = 0;
	for(int i = 0;i<y.size();i++){
		res = max(res,absD(y[i][j]));		
	}
	return res;	
}

double errorFormulaDo(double value,vector<double> &x,double maxY,int n){
	double err = 1;
	for(int j = 0;j<=n;j++){
		err *= (value - x[j]);
	}	
	err *= maxY;
	return err;	
}
double errorFormula(double value,vector<double> &x,vector<vector<double>> &y,int n){
	double maxY = getMaxAbs(n+1,y);
	double finError = INT_MAX;
	vector<double> chPoints;
	int lim = 1<<x.size();
	for(int i = 0;i<lim;i++){
		if(__builtin_popcount(i) != n+1) continue;
		vector<double> xx;
		for(int j = 0;j<x.size();j++){
			if(i&(1<<j)) xx.push_back(x[j]);			
		}
		double nerror = abs(errorFormulaDo(value,xx,maxY,n));	
		if(finError > nerror){
			finError = nerror;
			chPoints.clear();
			for(int j = 0;j<x.size();j++){
				if(i&(1<<j)) chPoints.push_back(x[j]);			
			}
		}
	}
	return finError;
}

void printDiff(vector<vector<double>> &y,int n){
	for(int i = 0;i<n;i++){
		for(int j = 0;j<n-i;j++){
			printf("%.4lf\t",y[i][j]);			
		}
		printf("\n");		
	}	
}

double linLagrange(double x, pair<double,double> p1, pair<double,double> p2){
	double l0 = (x-p2.first)/(p1.first - p2.first);
	double l1 = (x-p1.first)/(p2.first - p1.first);
	return p1.second * l0 + p2.second*l1;
}

double bestLinLagrange(double value, vector<double> &x, vector<double> &y){
	double truth = sqrt(value);
	double best = 10, ans;
	for(int i = 0;i<x.size();i++){
		for(int j = i+1;j<x.size();j++){
			double res = linLagrange(value,{x[i],y[i]},{x[j],y[j]});
			cout << res << '\n';
			if(abs(truth-res) < best){
				best = abs(truth-res);
				ans = res;				
			}
		}		
	}
	return ans;
}

int main(){
	
	printf("Digite o número de pontos que irá usar\n");
	int n;cin >> n;
	
	vector<double> x(n), yy(n);
	vector<vector<double>> y(n,vector<double>(n));
	printf("Digite os valores de x\n");
	for(int i = 0;i<n;i++){
		cin >> x[i];		
	}
	printf("Digite os valores de y\n");
	for(int i = 0;i<n;i++){
		cin >> y[i][0];	
		yy[i] = y[i][0];
	}
	makeDiffTable(x,y,n);
	printDiff(y,n);
	printf("Insira um valor para calcular e o grau do polinomio\n");
	double fx;cin >> fx;
	int grau;cin >> grau;
	
	printf("f(%lf) com grau %d: %.4lf\n",fx,grau,newtonFormula(fx,x,y,grau));
	printf("O erro foi de %.4lf\n",errorFormula(fx,x,y,grau));
	
	
	printf("Calculando ex. 2...\n");
	printf("O valor com o polinomio de lagrange linear foi %.5lf\n",bestLinLagrange(2.5,x,yy));
	return 0;
}