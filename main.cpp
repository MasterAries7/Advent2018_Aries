#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <array>

using namespace std;

bool check2(string x);
bool check3(string x);
string findCommon(string x, string y);
void day3p1disect(string input, int& x_loc, int& y_loc, int& width, int& height);

void day1pt2() {
	ifstream input;
	input.open("input1.txt");
	set<int> freq;
	int inputchange;
	int current = 0;
	while (true) {
		if (freq.count(current))
			break;
		else {
			freq.insert(current);
			input >> inputchange;
			current += inputchange;
		}
		if (input.eof()) {
			input.close();
			input.open("input1.txt");
		}
	}
	cout << "Duplicate data is " << current;
}

void day2pt1() {
	ifstream input;
	input.open("input2-1.txt");
	int check3s = 0;
	int check2s = 0;
	string in;
	while (true) {
		if (input.eof()) {
			break;
		}
		getline(input, in);
		if (check3(in)) {
			check3s++;
		}
		if (check2(in)) {
			check2s++;
		}
	}
	cout << "Checksum is " << check3s*check2s << endl;
}

string day2pt2() {
	ifstream input;
	input.open("input2-1.txt");
	ifstream input2;
	string in, in2;
	while (true) {
		if (input.eof()) {
			break;
		}
		getline(input, in);
		input2.open("input2-1.txt");
		while (true) {
			if (input2.eof()) {
				break;
			}
			getline(input2, in2);
			if (in == in2) {
				getline(input2, in2);
			}
			string str = findCommon(in, in2);
			if (str != "0") {
				return str;
			}
		}
		input2.close();
	}
	return "0";
}

bool check3(string x) {
	int count;
	char ch;
	for (int j = 0; j < x.length(); j++) {
		count = 0;
		ch = x.at(j);
		for (int i = 0; i < x.length(); i++) {
			if (ch == x.at(i)) {
				count++;
			}
		}
		if (count == 3) {
			return true;
		}
	}
	return false;
}

bool check2(string x) {
	int count;
	char ch;
	for (int j = 0; j < x.length(); j++) {
		count = 0;
		ch = x.at(j);
		for (int i = 0; i < x.length(); i++) {
			if (ch == x.at(i)) {
				count++;
			}
		}
		if (count == 2) {
			return true;
		}
	}
	return false;
}

string findCommon(string x, string y) {
	int uncommon=0;
	int loc;
	for (int i = 0; i < x.length(); i++) {
		if(x.at(i) != y.at(i)) {
			uncommon++;
			loc = i;
		}
	}
	if (uncommon == 1) {
		x.erase(loc, 1);
		return x;
	}
	else {
		return "0";
	}
}

int day3pt1() {
	ifstream input;
	input.open("input3-1.txt");
	int** arr = new int*[1000];
	for (int i = 0; i < 1000; i++) {
		arr[i] = new int[1000];
	};
	
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			arr[i][j] = 0;
		}
	}

	while (true) {
		if (input.eof()) {
			break;
		}
		string in;
		getline(input, in);

		int x_loc, y_loc, width, height;
		day3p1disect(in, x_loc, y_loc, width, height);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				arr[x_loc + i][y_loc + j]++;
			}
		}
	}

	int count = 0;
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			if (arr[i][j] > 1) {
				count++;
			}
		}
	}

	for (int i = 0; i < 1000; i++) {
		delete [] arr[i];
	}
	delete [] arr;
	return count;
}

void day3p1disect(string input, int& x_loc, int& y_loc, int& width, int& height) {
	string x_locraw, y_locraw, widthraw, heightraw;
	x_locraw = input.substr(input.find('@') + 2, input.find(',') - (input.find('@') + 2));
	y_locraw = input.substr(input.find(',')+1, input.find(':') - (input.find(','+1)));
	widthraw = input.substr(input.find(':')+2, input.find('x') - (input.find(':')+2));
	heightraw = input.substr(input.find('x')+1);

	stringstream conv(x_locraw);
	conv >> x_loc;
	stringstream conv2(y_locraw);
	conv2 >> y_loc;
	stringstream conv3(widthraw);
	conv3 >> width;
	stringstream conv4(heightraw);
	conv4 >> height;
}

int day3pt2() {
	ifstream input;
	input.open("input3-1.txt");
	int** arr = new int*[1000];
	for (int i = 0; i < 1000; i++) {
		arr[i] = new int[1000];
	};

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			arr[i][j] = 0;
		}
	}

	while (true) {
		if (input.eof()) {
			break;
		}
		string in;
		getline(input, in);

		int x_loc, y_loc, width, height;
		day3p1disect(in, x_loc, y_loc, width, height);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				arr[x_loc + i][y_loc + j]++;
			}
		}
	}
	input.close();
	input.open("input3-1.txt");

	int count = 1;
	while (true) {
		if (input.eof()) {
			break;
		}
		string in;
		getline(input, in);
		bool break_cond;

		int x_loc, y_loc, width, height;
		day3p1disect(in, x_loc, y_loc, width, height);
		break_cond = true;
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (arr[x_loc + i][y_loc + j] != 1)
					break_cond = false;
			}
		}
		if (break_cond)
			break;
		count++;
	}

	for (int i = 0; i < 1000; i++) {
		delete[] arr[i];
	}
	delete[] arr;
	return count;
}

int main() {
	int x;
	cout << day3pt2();
	cin >> x;
	return 0;
}

