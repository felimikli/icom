#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
const int MAX_SIZE = 20;
const int MAX_VALUE = 100;

void ordenarVector(vector<int> &b)
{

  if (b.size() <= 1)
    return;

  vector<int> menores;
  vector<int> mayores;
  int pivot = b[0];

  for (int i = 1; i < b.size(); i++)
    if (b[i] > pivot)
      mayores.push_back(b[i]);
    else
      menores.push_back(b[i]);

  ordenarVector(menores);
  ordenarVector(mayores);

  int j = 0;
  for (int &elem : menores)
    b[j++] = elem;

  b[j++] = pivot;

  for (int &elem : mayores)
    b[j++] = elem;
}

int main()
{
  srand(time(0));

  int SIZE = rand() % MAX_SIZE;
  vector<int> v(SIZE);

  for (int i = 0; i < SIZE; i++)
    v[i] = rand() % MAX_VALUE;

  cout << "Vector original:" << endl;
  for (int &elem : v)
    cout << elem << "\t";
  cout << endl;

  ordenarVector(v);

  cout << "Vector ordenado:" << endl;
  for (int &elem : v)
    cout << elem << "\t";
  cout << endl;
  return 0;
}
