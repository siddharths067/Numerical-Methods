#include <bits/stdc++.h>
using namespace std;

long double power(long double x, long int y){
	long double ans = 1.0;
	while(y){
		if(y&1)ans*=x;
		x*=x;
		y>>=1;
	}
	return ans;
}
vector<long double> Solve(vector< vector<long double> >eq){
	long int n = eq.size();
	vector<long double> x(n);
	for(long long int i =0;i<n;i++)
		for(long long int j=0;j<n;j++)
			if(j>i){
				long double c = eq[j][i] / eq[i][i];
				for(long long int k=0;k<=n;k++)
					eq[j][k]-=(c*eq[i][k]);
			}
	x[n-1] = eq[n-1][n] / eq[n-1][n-1];
	for(long long int i = n-2;i>=0;i--){
		long double sum =0;
		for(long long int j=i+1;j<n;j++)
			sum+= (eq[i][j]*x[j]);
		x[i] = (eq[i][n]-sum)/eq[i][i];
	}

	for(auto z : x)
		cout<<z<<" ";
	return x;
}
vector<long double> Regression2D(vector<pair<long double,long double> > dat, long long int order){
	/*
		Some Properties of Normalized Equations Matrix
		the row size is always equal to the order of the Equations 0 -> order-1
		the column size is always order+1 for it to be stored
		the power of arguments will go from 0 to 2*order-2
		____________               _________
		| x^0 x^1 x^2 ...... x^(order-1)    |
		| x^1 x^2 x^3 ...... x^(order)      |
		| x^2 x^3 x^4 ...... x^(order+1)    |
		|............\\\\\\\...........     |
		|x^order x^order+1... x^(2*order-2) |
		|___________                ________|
	*/
	vector<vector<long double > > N_Mat;
	vector<long double> x_i,y_i;
	x_i.resize(order*2 + 1);
	y_i.resize(order);
	N_Mat.resize(order);
	for(long int i=0;i<order;i++)
		N_Mat[i].resize(order+1);
	for(long int i=0;i<dat.size();i++){
		for(long int j=0;j<2*order+1;j++){
			x_i[j] += power(dat[i].first,j);
			if(j<order)
				y_i[j] += (power(dat[i].first,j)*dat[i].second);
		}
	}
	for(long int i=0;i<order;i++)
		for(long int j=0;j<order;j++)
			N_Mat[i][j] = x_i[i+j];
	for(long int i=0;i<order;i++)
		N_Mat[i][order] = y_i[i];
		for(auto z : x_i)
			cout<<z<<" " ;
			cout<<endl;
		for(long int i=0;i<order;i++,cout<<endl)
			for(long int j=0;j<=order;j++)
				cout<<N_Mat[i][j]<<" ";
	return Solve(N_Mat);

}
int main() {
	// your code goes here
	return 0;
}
