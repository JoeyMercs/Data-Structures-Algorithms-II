// Joseph Mercedes
// Data Structures and Algorithms II
// Programming Assignment #4

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

#define len 1001
int mtx[len][len] = {0};

int main(){

	string inputFile, outputFile;
	
	cout << "Enter name of input file: ";
	cin >> inputFile;
	cout << "Enter name of output file: ";
	cin >> outputFile;

	ifstream input(inputFile.c_str());
	ofstream output(outputFile.c_str());

	string a,b,c;

	while (getline(input,a) && getline(input,b) && getline(input,c)){

		// Setup Matrix
		for(int i=0; i<len; i++){
			for(int j=0; j<len; j++){
				mtx[i][j] = 0;
			}
		}

		mtx[0][0] = 1;

		int lenA = a.length();
		int lenB = b.length();
		int lenC = c.length();

		// If the sum of the Lengths don't match, it can't be a merge
		if (lenC != lenA + lenB){
			output << "*** NOT A MERGE ***" << endl;
			continue;
		}

		// Fill up matrix mtx in order to merge the paths
		for(int k=0; k<=lenA; k++){

			for(int l=0; l<=lenB; l++){

				if(mtx[k][l] == 1){

					if(c[k+l] == a[k])
						mtx[k+1][l] = 1;

					if(c[k+l] == b[l])
						mtx[k][l+1] = 1;

				}
			}
		}

		// Determines whether or not c has satisfied the merge condition
		if(mtx[lenA][lenB] == 1){

			int x = lenA;
			int y = lenB;

			while(x>0 && y>=0){

				if(mtx[x][y] == 1 && (y == 0 || mtx[x][y-1] == 0)) {

					c[x+y-1] = toupper(c[x+y-1]);
					x--;

				}else{
					y--;
				}
			}
			
			output << c << endl;

		}else{
			output << "*** NOT A MERGE ***" << endl;
		}
	}
	
	input.close();
	output.close();

	return 0;
}