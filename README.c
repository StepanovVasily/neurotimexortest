#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <ctime>
#include <vector>
#include <chrono>
#include <algorithm>
#include <windows.h>
#include <amp.h>
using namespace std;
using namespace std::chrono;

//2,25,1//320mc minError 0,065
//1050 mc
double d2[] = {
	0.3, 1, 0.6,
	0.35, 1, 0.65,
	0.4, 1, 0.7,
	0.45, 1, 0.75,
	0.5, 1, 0.8,
	0.55, 1, 0.85,
	0.6, 1, 0.9,
	0.65, 1, 0.85,
	0.7, 1, 0.8,
	0.75, 1, 0.75,
	0.8, 1, 0.7,
	0.85, 1, 0.65,
	0.9, 1, 0.6,
	0.95, 1, 0.55,


};
const int U = 14;
vector<double> d(3 * U);


const int I = 2;
vector<double> in(I);
const int N1 = 25;//нейроны на первом слое
const int N2 = 1;
const int N3 = 1;
const int N4 = 1;
//нейроны на втором слое
vector<double> n1(N1*(I + 1));
vector<double> n2(N2*(N1 + 1));
vector<double> n3(N3 *(N2 + 1));
vector<double> n4(N4 *(N3 + 1));
vector<double> actN(I + N1);
vector<double> actMass((I + N1)*U);

int currentD = 0;

double act2(int layer, int neuron) {
	int shag;
	if (layer <2){

		
		for (int i = 0; i != N1; i++) {
			shag = i*(I + 1);
			n1[shag] = 0;
			for (int j = 0; j != I; j++) {
				n1[shag] += in[j] * n1[shag + j + 1];
			}
			//if (n1[shag] < 0.0)n1[shag] = n1[shag] * 0.01;// (rand() % 100)*0.0001;

			//n1[shag] = n1[shag] / (1 + abs(-n1[shag]));

			if (n1[shag] < 0.0){
				n1[shag] -= 0.1;

			}
			else {

				n1[shag] += 0.1;
			}

		}
	}
	//cout << "act2 " << n1[0] << " " << n1[3] << ". ";
	if (layer<3){

		if (layer ==2)
		for (int i = 0; i != neuron; i++) {
			shag = i*(N1 + 1);
			n2[shag] = actMass[I + i + (I + N1)*currentD];
		}
		int NC = neuron;
		if (layer != 2)
			NC = 0;
		for (int i = NC; i != N2; i++) {
			shag = i*(N1 + 1);

			n2[shag] = 0;
			for (int j = 0; j != N1; j++) {
				n2[shag] += n1[j*(I + 1)] * n2[shag + j + 1];
			}
			if (n2[shag] < 0.0){ n2[shag] -= 0.1; }
			else{ n2[shag] += 0.1; }
		}
	}

 return n2[0];///1 выход
};



double act(int layer, int neiron) {

	int shag;
	for (int i = 0; i != N1; i++) {
		shag = i*(I + 1);
		n1[shag] = 0;
		for (int j = 0; j != I; j++) {
			n1[shag] += in[j] * n1[shag + j + 1];
		}
		//if (n1[shag] < 0.0)n1[shag] = n1[shag] * 0.01;// (rand() % 100)*0.0001;

		//n1[shag] = n1[shag] / (1 + abs(-n1[shag]));

		if (n1[shag] < 0.0){
			n1[shag] -= 0.1;

		}
		else {

			n1[shag] += 0.1;
		}

	}
	//cout << "act1 " << n1[0] << " " << n1[3] << ". ";

	for (int i = 0; i != N2; i++) {
		shag = i*(N1 + 1);
		n2[shag] = 0;
		for (int j = 0; j != N1; j++) {
			n2[shag] += n1[j*(I + 1)] * n2[shag + j + 1];
		}
		//if (n2[shag] < 0.0)n2[shag] = n2[shag] * 0.01;// (rand() % 100)*0.0001;
		//n2[shag] = n2[shag] / (1 + abs(-n2[shag]));

		if (n2[shag] < 0.0){
			n2[shag] -= 0.1;
		}
		else{

			n2[shag] += 0.1;
		}
		//n2[shag] += copysign(0.1, n2[shag]);

	}
	/*
	for (int i = 0; i != N3; i++) {
	int shag = i*(N2 + 1);
	n3[shag] = 0;
	for (int j = 0; j != N2; j++) {
	n3[shag] += n2[j*(N1 + 1)] * n3[shag + j + 1];
	}
	n3[shag] = n3[shag]  / (1 + abs(-n3[shag]));
	if (n3[shag]<0)
	n3[shag] -= 0.5;
	else	n3[shag] += 0.5;
	}*/
	/*
	for (int i = 0; i != N4; i++) {
	int shag = i*(N3 + 1);
	n4[shag] = 0;
	for (int j = 0; j != N3; j++) {
	n4[shag] += n2[j*(N2 + 1)] * n3[shag + j + 1];
	}
	n4[shag] = n4[shag] / (1 + abs(-n4[shag]));
	if (n4[shag]<0)
	n4[shag] -= 0.5;
	else	n4[shag] += 0.5;
	}
	*/
	return n2[0];///1 выход
};
#define PI 3.14
double error2(int layer, int neiron) {
	double err = 0;
	for (int i = 0; i != U; i++) {
		currentD = i;
		in[0] = d[i * 3];
		in[1] = d[i * 3 + 1];
		err += pow(abs(act(layer, neiron) - d[i * 3 + 2]), 2);
		//cout << "act1 " << pow(abs(act(layer, neiron) - d[i * 3 + 2]), 2) - pow(abs(act2(layer, neiron) - d[i * 3 + 2]), 2) << " l " << layer << endl;
	}
	return err;
};
double error(int layer, int neiron) {
	double err = 0;
	for (int i = 0; i != U; i++) {
		//cout<<"Error"<<d[i*3+2]<<" " << abs(act(d[i * 3], d[i * 3 + 1]) - d[i * 3 + 2]) <<" ";
		in[0] = d[i * 3];
		in[1] = d[i * 3 + 1];
		err += pow(abs(act(layer, neiron) - d[i * 3 + 2]), 2);

	}
	return err;
};
HWND myconsole1 = GetConsoleWindow();
HDC mydc1 = GetDC(myconsole1);
HDC src = CreateCompatibleDC(mydc1);
unsigned char mato[200 * 200 * 4];

double blackmat[200][200] = { 0 };
void drawImg(double *mat, int xp, int yp){

	//Get a handle to device context
	for (int i = 0; i != U; i++){
		d[i * 3] = d2[i * 3];
		d[i * 3 + 1] = d2[i * 3 + 1];
		d[i * 3 + 2] = d2[i * 3 + 2];
	}

	for (int x = 0; x != 200; x++)for (int y = 0; y != 200; y++){
		mato[x * 4 + y * 200 * 4] = (int)mat[x + y * 200];
		mato[x * 4 + y * 200 * 4 + 1] = (int)mat[x + y * 200];
		mato[x * 4 + y * 200 * 4 + 2] = (int)mat[x + y * 200];
		mato[x * 4 + y * 200 * 4 + 3] = 255;
	}
	HBITMAP map;
	map = CreateBitmap(200,
		200, // height
		1, // Color Planes, unfortanutelly don't know what is it actually. Let it be 1
		8 * 4, // Size of memory for one pixel in bits (in win32 4 bytes = 4*8 bits)
		(void*)mato);
	// hdc - Device context for window, I've got earlier with GetDC(hWnd) or GetDC(NULL);
	SelectObject(src, map);
	BitBlt(mydc1,
		xp,  // x and
		yp,  // y - upper-left corner of place, where we'd like to copy
		200, // width of the region
		200, // height
		src, // source
		0,   // x and
		0,   // y of upper left corner  of part of the source, from where we'd like to copy
		SRCCOPY);
	DeleteObject(map);
}
double first;
double endErr;
double change;
void drawpxl(int xp, int yp){

	//Get a handle to device context

	unsigned char pixl[4];

	pixl[0] = 0;
	pixl[1] = 0;
	pixl[2] = 255;
	pixl[3] = 255;

	HBITMAP map1;
	map1 = CreateBitmap(1,
		1, // height
		1, // Color Planes, unfortanutelly don't know what is it actually. Let it be 1
		8 * 4, // Size of memory for one pixel in bits (in win32 4 bytes = 4*8 bits)
		(void*)pixl);
	// hdc - Device context for window, I've got earlier with GetDC(hWnd) or GetDC(NULL);
	SelectObject(src, map1);

	BitBlt(mydc1,
		xp,  // x and
		yp,  // y - upper-left corner of place, where we'd like to copy
		1, // width of the region
		1, // height
		src, // source
		0,   // x and
		0,   // y of upper left corner  of part of the source, from where we'd like to copy
		SRCCOPY);

	DeleteObject(map1);
}
void seach(vector<double> &n, const int nSize, const int N){
	for (int i = 0; i != nSize; i++) {
		if ((i % (N + 1) == 0)) i++;
		first = error(2, i);
		change = n[i];
		n[i] = n[i] + 0.001*first;
		endErr = error(2, i);
		//cout << "r2+ " << first << " " << end << endl;
		if (endErr >= first)
			n[i] = change;
		first = error(2, i);
		change = n2[i];
		n[i] = n[i] - 0.001*first;
		endErr = error(2, i);
		//cout << "r2- "<< first <<" "<< end <<endl;
		if (endErr >= first)
			n[i] = change;
	}
};
int main()
{




	srand(time(0));
	for (int i = 0; i != n1.size(); i++)
		n1[i] = ((rand() % 10)*0.2 - 0.1);
	for (int i = 0; i != n2.size(); i++)
		n2[i] = ((rand() % 10)*0.2 - 0.1);
	for (int i = 0; i != n3.size(); i++)
		n3[i] = ((rand() % 10)*0.2 - 0.1);
	for (int i = 0; i != n4.size(); i++)
		n4[i] = ((rand() % 10)*0.2 - 0.1);

	for (int i = 0; i != U; i++){
		in[0] = d[i * 3];
		in[1] = d[i * 3 + 1];
		act(0, 0);
		
		for (int j = 0; j != I; j++){
			actMass[i*(I + N1) + j] = in[j];
		}
		for (int j = 0; j != N1; j++){
			//cout << j << " " << j*(I + 1) << " " << i*(I + N1) + j + I << endl;
			actMass[i*(I+N1)+j + I] = n1[j*(I + 1)];
		}
	};



	HWND myconsole = GetConsoleWindow();
	//Get a handle to device context
	HDC mydc = GetDC(myconsole);

	int pixel = 250;

	//Choose any color
	COLORREF COLOR = RGB(255, 255, 255);


	double m = 100;

	int r1;
	int r2;
	double che;
	double max;
	int n1Size = n1.size();
	int n2Size = n2.size();
	int n3Size = n3.size();
	int n4Size = n4.size();
	int posit = 0;
	//while (1) {
	for (int y1 = 0; y1 != 1000; y1++) {
		__int64 starttime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		che = 1.0;
		for (int y = 0; y != 1000; y++) {
			//seach(n1, n1Size, I);
			//seach(n2, n2Size, N1);
			first = error2(2, 0);
			posit = -1;
			for (int i = 0; i != n2Size; i++) {
				
				if ((i % (N1 + 1) == 0)) { i++; posit++; }
				

				//cout << "i " <<i << endl;

				change = n2[i];
				n2[i] = n2[i] + 0.001*first;
				endErr = error2(2, posit);
				if (endErr >= first)
					n2[i] = change;
				else
					first = error2(2, posit);
				change = n2[i];
				n2[i] = n2[i] - 0.001*first;
				endErr = error2(2, posit);
				if (endErr >= first)
					n2[i] = change;
				else
					first = error2(2, posit);
			}
			first = error2(1, 0);
			posit = -1;
			for (int i = 0; i != n1Size; i++) {
				if ((i % (I + 1) == 0)){ i++; posit++; }
				//cout << posit << " pos" << endl;
				change = n1[i];
				n1[i] = n1[i] + 0.001*first;
				endErr = error2(1, posit);
				//cout << "r1+ " << first << " " << end << endl;
				if (endErr >= first)
					n1[i] = change;
				else
					first = error2(1, posit);
				change = n1[i];
				n1[i] = n1[i] - 0.001*first;
				endErr = error2(1, posit);
				//cout << "r1- " << first << " " << end << endl;
				if (endErr >= first)
					n1[i] = change;
				else
					first = error2(1, posit);
			}
			/*
			for (int i = 0; i != n3Size; i++) {
			if ((i % (N2 + 1) == 0)) i++;
			first = error(3,i);
			change = n3[i];
			n3[i] = n3[i] + 0.001*first;
			end = error(3, i);
			//cout << "r1+ " << first << " " << end << endl;
			if (end >= first)
			n3[i] = change;
			first = error(3, i);
			change = n3[i];
			n3[i] = n3[i] - 0.001*first;
			end = error(3, i);
			//cout << "r1- " << first << " " << end << endl;
			if (end >= first)
			n3[i] = change;
			}
			for (int i = 0; i != n4Size; i++) {
			if ((i % (N3 + 1) == 0)) i++;
			first = error(4, i);
			change = n4[i];
			n4[i] = n4[i] + 0.001*first;
			end = error(4, i);
			//cout << "r1+ " << first << " " << end << endl;
			if (end >= first)
			n4[i] = change;
			first = error(4, i);
			change = n4[i];
			n3[i] = n4[i] - 0.001*first;
			end = error(4, i);
			//cout << "r1- " << first << " " << end << endl;
			if (end >= first)
			n4[i] = change;
			}
			*/
		}

		system("CLS");
		//int *b = (int *)&n1[1];
		//n1[1] = -n1[1];
		double temp = 5.0;
		bool t = false;
		//if (copysign(t, temp))
		//	cout << "p";

		//cout << " d " << temp << endl;
		//cout << "max " << max << endl;

		cout << "Error: " << error(0, 0) << "   " << endl;
		for (int i = 0; i != U; i++) {
			cout << "Out: " << d[i * 3 + 2] << " ";
			in[0] = d[i * 3];
			in[1] = d[i * 3 + 1];
			cout << "Activation: " << act(0, 0) << " ";
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



		if (GetAsyncKeyState('1') < 0)n2[1] -= 0.1;
		if (GetAsyncKeyState('2') < 0)n2[1] += 0.1;
		if (GetAsyncKeyState(81) < 0)n2[2] -= 0.1;
		if (GetAsyncKeyState(87) < 0)n2[2] += 0.1;

		if (GetAsyncKeyState('3') < 0)n1[1] -= 0.1;
		if (GetAsyncKeyState('4') < 0)n1[1] += 0.1;
		if (GetAsyncKeyState(69) < 0)n1[2] -= 0.1;
		if (GetAsyncKeyState(82) < 0)n1[2] += 0.1;

		///if (GetAsyncKeyState('r') < 0)
		for (int i = 0; i != 255; i++)
		if (GetAsyncKeyState(i) < 0)
			cout << "r" << i << endl;
		if (GetAsyncKeyState('5') < 0)n1[4] -= 0.1;
		if (GetAsyncKeyState('6') < 0)n1[4] += 0.1;
		if (GetAsyncKeyState(84) < 0)n1[5] -= 0.1;
		if (GetAsyncKeyState(89) < 0)n1[5] += 0.1;

		if (GetAsyncKeyState('7') < 0)m -= 10;
		if (GetAsyncKeyState('8') < 0)m += 10;


		/*
		float change1 = n2[1]; float change2 = n2[2];
		double max = 0;
		double min = 10000;
		double mat[200][200];
		for (int x = -100; x != 100; x++)for (int y = -100; y != 100; y++){
		n2[1] = x / m;
		n2[2] = y / m;
		mat[x + 100][y + 100] = error(0,0);
		if (mat[x + 100][y + 100] > max)max = mat[x + 100][y + 100];
		if (mat[x + 100][y + 100] < min)min = mat[x + 100][y + 100];
		}

		max = max - min;
		for (int x = -100; x != 100; x++)for (int y = -100; y != 100; y++){
		mat[x + 100][y + 100] -= min;
		mat[x + 100][y + 100] = mat[x + 100][y + 100] / max * 200;
		}
		drawImg(*mat, 50, 360);
		drawpxl(change2 * m + 100 + 50, change1 * m + 100 + 360);
		//SetPixel(mydc, change2 * m + 150, change1 * m + 510, RGB(255, 0, 0));
		n2[1] = change1; n2[2] = change2;

		/////////////////////////////////////////////////////
		max = 0;
		min = 10000;
		change1 = n1[1]; change2 = n1[2];
		for (int x = -100; x != 100; x++)for (int y = -100; y != 100; y++){
		n1[1] = x / m;
		n1[2] = y / m;
		mat[x + 100][y + 100] = error(0,0);
		if (mat[x + 100][y + 100] > max)max = mat[x + 100][y + 100];
		if (mat[x + 100][y + 100] < min)min = mat[x + 100][y + 100];
		}

		max = max - min;
		for (int x = -100; x != 100; x++)for (int y = -100; y != 100; y++){
		mat[x + 100][y + 100] -= min;
		mat[x + 100][y + 100] = (mat[x + 100][y + 100] / max) * 200;
		}
		drawImg(*mat, 50, 150);
		drawpxl(change2 * m + 100 + 50, change1 * m + 100 + 150);
		SetPixel(mydc, 1 * m + 150, 1 * m + 150, RGB(0, 255, 0));
		SetPixel(mydc, -1 * m + 150, -1 * m + 150, RGB(0, 0, 255));
		SetPixel(mydc, 0 * m + 150, 0 * m + 150, RGB(0, 50, 50));

		n1[1] = change1; n1[2] = change2;

		//////////////////////////////////////////
		max = 0;
		min = 10000;
		change1 = n1[4]; change2 = n1[5];
		for (int x = -100; x != 100; x++)for (int y = -100; y != 100; y++){

		n1[4] = x / m;
		n1[5] = y / m;
		mat[x + 100][y + 100] = error(0,0);
		if (mat[x + 100][y + 100] > max)max = mat[x + 100][y + 100];
		if (mat[x + 100][y + 100] < min)min = mat[x + 100][y + 100];
		}
		max = max - min;
		for (int x = -100; x != 100; x++)for (int y = -100; y != 100; y++){
		mat[x + 100][y + 100] -= min;
		mat[x + 100][y + 100] = (mat[x + 100][y + 100] / max) * 200;
		}
		drawImg(*mat, 260, 150);
		drawpxl(change2 * m + 100 + 260, change1 * m + 100 + 150);
		//SetPixel(mydc, change2 * m + 260, change1 * m + 150, RGB(255, 0, 0));
		n1[4] = change1; n1[5] = change2;
		////////////
		*/


		__int64 endtime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		std::cout << endl << "s" << endtime - starttime << std::endl;
		in[0] = 0.9;
		std::cout << endl << "test" << act(0, 0) << std::endl;
		int pos = 200;
		//drawImg(*blackmat, 500, 500);
		//drawImg(*blackmat, 500, 300);
		drawImg(*blackmat, 500, 100);
		//drawImg(*blackmat, 700, 500);
		//drawImg(*blackmat, 700, 300);
		//drawImg(*blackmat, 700, 100);

		for (int i = 0; i != 100; i++){
			SetPixel(mydc, 500, 100 + i, RGB(0, 30, 0));
			SetPixel(mydc, 500 + i, 100, RGB(0, 30, 0));
			SetPixel(mydc, 500 + 100, 100 + i, RGB(0, 30, 0));
			SetPixel(mydc, 500 + i, 100 + 100, RGB(0, 30, 0));

			SetPixel(mydc, 100 + i, 100 + i, RGB(0, 30, 0));
			in[0] = i*0.01;
			//if (i>0.6)
			//in[1] = 1;
			//else
			//in[1] = 0.3;
			SetPixel(mydc, 500 + i, 100 + act(0, 0) * 100, RGB(255, 255, 0));
		}

		for (int j = 0; j != U; j++){
			SetPixel(mydc, d[j * 3] * 100 + 500, d[j * 3 + 2] * 100 + 100, RGB(0, 0, 250));
		}
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
	//}


	return 0;
}
