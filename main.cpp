#include "quadtree.h"
#include <iostream>

using namespace std;


int main (void)
{

	if (qtCompress("img.png", 80.0) == true) {
		cout << "comprimi bien" << endl;
		if (qtDecompress("hola.eda", 256))
			cout << "descomprimi bien" << endl;
		else
			cout << "no se pudo descomprimir" << endl;
	}
	else
		cout << "no se pudo comprimir" << endl;

	system("pause");

	return 0;
}