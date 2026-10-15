#include <iostream>
#include <vector>
#include <algorithm>
//#include <iterator>
#include <print>

using namespace std;

void print_vector(vector<int> v) {
	for(auto m : v) {
		cout << m << ", ";
	}
	cout << "\n";

}

vector<int> HighlanderN(vector<int> v) {
	// caso base
	if(v.size() < 2) return v;

	// caso inductivo
	vector<int> retorno = {};
	for(int i = 1; i < v.size(); i += 2) {
		retorno.push_back(v[i]);
	}
	reverse(retorno.begin(), retorno.end());
	return HighlanderN(retorno);
}

int main() {
	vector<int> v1 = {1,2,3,4,5,6,7,8,9};
	print_vector(v1);
	print_vector(HighlanderN(v1));

	vector<int> v2 = {1,2,3,4,5,6,7,8,9,10,1111,0,0,0,0,111,0,0,333};
	print_vector(v2);
	print_vector(HighlanderN(v2));

	vector<int> v3 = {1,2,3,4,5,6,7,8};
	print_vector(v3);
	print_vector(HighlanderN(v3));

	return 0;
}
