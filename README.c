// NeuroTimeXorTest.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <ctime>
#include <vector>
#include <chrono>
#include <algorithm>
#include <windows.h>
using namespace std;
using namespace std::chrono;

float d[] = {
	0, 0, 0,
	0, 1, 1,
	1, 0, 1,
	1, 1, 0
}; 



float o;

const int I = 2;
vector<float> in(I);
const int N1 = 80;//нейроны на первом слое
const int N2 = 1;
const int N3 = 1;
//нейроны на втором слое
vector<double> n1(N1*(I+1));
vector<double> n2(N2*(N1+1));
vector<double> n3(N3 *(N2 + 1));

float act() {
	for (int i = 0; i != I; i++) {
		if (in[i] < 0.0)
			in[i] = in[i] * (rand() % 100)*0.001;
			in[i] += 0.1;
		//in[i] = max(0.0f, in[i]);
		// 1 / (1 + abs(-in[i]));
	}
	for (int i = 0; i != N1; i++) {
		int shag = i*(I + 1);
		n1[shag] = 0;
		for (int j = 0; j != I; j++) {
			n1[shag] += in[j] * n1[shag +j + 1];
		}
		if (n1[shag] < 0.0)
			n1[shag] = n1[shag] * (rand() % 100)*0.001;
		n1[shag] += 0.1;
		//n1[shag]= max(0.0, n1[shag]);
	}

	for (int i = 0; i != N2; i++) {
		int shag = i*(N1 + 1);
		n2[shag] = 0;
		for (int j = 0; j != N1 ; j++) {
			n2[shag] += n1[j*(I+1)] * n2[shag+j+1];
		}
		if (n2[shag] < 0.0)
			n2[shag] = n2[shag] * (rand() % 100)*0.001;
		n2[shag] += 0.1;
		//n2[shag] = max(0.0, n2[shag]);
	}
	/*
	for (int i = 0; i != N3; i++) {
		int shag = i*(N2 + 1);
		n3[shag] = 0;
		for (int j = 0; j != N2; j++) {
			n3[shag] += n2[j*(N1 + 1)] * n3[shag + j + 1];
		}
		if (n3[shag] < 0.0)
			n3[shag] = n3[shag] * (rand() % 100)*0.0001;
		n3[shag] += 0.1;
		//n2[shag] = max(0.0, n2[shag]);
	}*/
	return n2[0];///1 выход
};

float error() {
	double err = 0;
	for (int i = 0; i != 4; i++) {
		//cout<<"Error"<<d[i*3+2]<<" " << abs(act(d[i * 3], d[i * 3 + 1]) - d[i * 3 + 2]) <<" ";
		in[0] = d[i * 3];
		in[1] = d[i * 3 + 1];
		err+= abs(act() - d[i * 3+2]);

	}
	return (float)err;
};

int main()
{

	srand(time(0));
	for (int i = 0; i != n1.size(); i++)
		n1[i] = ((rand()%10)*0.2-0.1);
	for (int i = 0; i != n2.size(); i++)
		n2[i] =  ((rand() % 10)*0.2 - 0.1);
	for (int i = 0; i != n3.size(); i++)
		n3[i] =  ((rand() % 10)*0.2 - 0.1);

	float first;
	float end;
	float change;
	int r1;
	int r2;
	double che;
	double max;
	int n1Size= n1.size();
	int n2Size = n2.size();
	int n3Size = n3.size();
	while (1) {
		for (int y1 = 0; y1 != 1; y1++) {
			__int64 starttime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			
		che = 1.0;
		for (int y = 0; y != 1; y++) {




			for (int i = 0; i != n2Size; i++) {
				if ((i % (N1 + 1) == 0)) i++;
				first = error();
				change = n2[i];
				n2[i] = n2[i]+ 0.01*first;
				end = error();
				//cout << "r2+ " << first << " " << end << endl;
				if (end >= first)
					n2[i] = change;
				first = error();
				change = n2[i];
				n2[i] = n2[i]-0.01*first;
				end = error();
				//cout << "r2- "<< first <<" "<< end <<endl;
				if (end >= first)
					n2[i] = change;
			}
	
			for (int i = 0; i != n1Size; i++) {
				if ((i % (I + 1) == 0)) i++;
				first = error();
				change = n1[i];
				n1[i] = n1[i]+  0.01*first;
				end = error();
				//cout << "r1+ " << first << " " << end << endl;
				if (end >= first)
					n1[i] = change;
				first = error();
				change = n1[i];
				n1[i] = n1[i]-  0.01*first;
				end = error();
				//cout << "r1- " << first << " " << end << endl;
				if (end >= first)
					n1[i] = change;
			}
			/*
			for (int i = 0; i != n3Size; i++) {
				if ((i % (N2 + 1) == 0)) i++;
				first = error();
				change = n3[i];
				n3[i] = n3[i] + 0.01*first;
				end = error();
				//cout << "r1+ " << first << " " << end << endl;
				if (end >= first)
					n3[i] = change;
				first = error();
				change = n3[i];
				n3[i] = n3[i] - 0.01*first;
				end = error();
				//cout << "r1- " << first << " " << end << endl;
				if (end >= first)
					n3[i] = change;
			}
			*/

			/*
			first = error();
			if (rand() % 2) {
				r1 = rand() % I;
				r2 = rand() % N1;
				change = n1[r2*I + (r1 + 1)];

				n1[r2*I + (r1 + 1)] += ((rand() % 100) * 0.02 - 0.01)*first;
				end = error();
				if (end > first)
					n1[r2*I + (r1 + 1)] = change;

			}
			else {
				r1 = rand() % N1;
				r2 = rand() % N2;
				change = n2[r2*N1 + (r1 + 1)];
				n2[r2*N1 + (r1 + 1)] += ((rand() % 100) * 0.02 - 0.01)*first;
				end = error();
				if (end > first)
					n2[r2*N1 + (r1 + 1)] = change;


			}
		*/





		}

		system("CLS");



		//cout << "max " << max << endl;
		
		cout << "Error: " << error() << "   " << endl;
		for (int i = 0; i != 4; i++) {
			cout << "Out: " << d[i * 3 + 2] << " ";
			in[0] = d[i * 3];
			in[1] = d[i * 3 + 1];
			cout << "Activation: " << act() << " ";
			cout << endl;
		}
		cout << "c " << che << endl;
		/*
		cout << "n1: ";
		for (int i = 0; i != n1.size(); i++)
			cout << n1[i] << " ";
		cout << endl;
		

		cout << "n2: ";
		for (int i = 0; i != n2.size(); i++)
			cout << n2[i] << " ";
		cout << endl;
		*/
		__int64 endtime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		std::cout << endtime- starttime << std::endl;

	}
		/*
	max = 0;
	for (int i = 0; i != n1.size(); i++) {
		if ((i % (I + 1) != 0)) {
			if (abs(-n1[i]) > max) {

				max = abs(n1[i]);
			}
		}
	}
	for (int i = 0; i != n2.size(); i++) {
		if ((i % (N1 + 1) != 0)) {
			if (abs(-n2[i]) > max)
				max = abs(n2[i]);
		}
	}
	cout << "max" << max << endl;
	for (int i = 0; i != n1.size(); i++) {
		if ((i % (I + 1) != 0)) {
			n1[i] = n1[i] / max;
		}
	}
	for (int i = 0; i != n2.size(); i++) {
		if ((i % (N1 + 1) != 0)) {
			n2[i] = n2[i] / max;
		}
	}
	*/
}


	return 0;
}

