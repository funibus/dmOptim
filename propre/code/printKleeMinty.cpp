#include <iostream>
#include <utility>
#include <stdlib.h>

using namespace std;


int main(int argc,char *argv[])
{
	if (argc != 2)
	{
		cerr << endl << "attention, le programme prend 1 argument : le nombre de variables de Klee-Minty" << endl << endl;
		exit(1);
	}
	int n = atoi(argv[1]);
	
	cout << "max: ";
	for (int i = 0; i < n; i++)
	{
		if (i != 0)
			cout << " +";
		cout << "1";
		for (int j = 1; j< n-i; j++)
			cout << "0";
		cout << "x" << i+1 << " ";
	}
	
	for (int k = 0; k < n; k++)
	{
		cout << endl;
		for (int i = 0; i < k; i++)
		{
			if (i != 0)
				cout << " +";
			cout << "2";
			for (int j = 0; j< k-i; j++)
				cout << "0";
			cout << "x" << i+1 << " ";
		}
		cout << "+1x" <<k+1 << " <= 1";
		for (int j = 0; j < k; j++)
			cout << "00";
	}

    return 0;

}
