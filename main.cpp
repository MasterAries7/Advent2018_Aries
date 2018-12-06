#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct ShiftData {
	int month = -1, day = -1;
	int time[60] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int guard = -1;
};

struct GuardData {
	int guard = 0;
	int time_asleep;
	int time_sleep[60] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
};

bool check2(string x);
bool check3(string x);
string findCommon(string x, string y);
void day3p1disect(string input, int& x_loc, int& y_loc, int& width, int& height);
void day4p1disect(string input, int& month, int& day, int& hour, int& min, string& event, int& guard);
int FindGuardAndMin(vector<ShiftData> &vec);
int FindGuardAndMinPt2(vector<ShiftData> &vec);
void FillIn(vector<ShiftData> &vec);
void addSleepToShift(vector<ShiftData> &vec, int month, int day, int hour, int min, int guard);
void addGuardToShift(vector<ShiftData> &vec, int month, int day, int hour, int min, int guard);
void addWakeUpToShift(vector<ShiftData> &vec, int month, int day, int hour, int min, int guard);

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

int day4pt1() {
	ifstream input;
	input.open("input4-1.txt");
	ShiftData *gd;
	vector<ShiftData> vec;
	while (true) {
		if (input.eof()) {
			break;
		}
		string in;
		getline(input, in);
		int month, day, hour, min, guard;
		string event;
		day4p1disect(in, month, day, hour, min, event, guard);
		if (event == "guard") {
			addGuardToShift(vec, month, day, hour, min, guard);
		}
		if (event == "wakes") {
			addWakeUpToShift(vec, month, day, hour, min, guard);
		}
		if (event == "sleep") {
			addSleepToShift(vec, month, day, hour, min, guard);
		}
	}
	FillIn(vec);
	return FindGuardAndMin(vec);
}

int FindGuardAndMin(vector<ShiftData> &vec) {
	vector<GuardData> list;
	for (vector<ShiftData>::iterator it = vec.begin(); it != vec.end(); ++it) {
		if (it->guard == -1) {
			return 0;
		}
		if (list.empty()) {
			GuardData gd;
			gd.guard = it->guard;
			gd.time_asleep = 0;
			for (int i = 0; i < 60; i++) {
				if (it->time[i] == 1) {
					gd.time_asleep++;
				}
			}
			list.push_back(gd);
		}
		else {
			bool found = false;
			for (vector<GuardData>::iterator it2 = list.begin(); it2 != list.end(); ++it2) {
				if (it->guard == it2->guard) {
					found = true;
					for (int i = 0; i < 60; i++) {
						if (it->time[i] == 1) {
							it2->time_asleep++;
						}
					}
				}
			}
			if (!found) {
				GuardData gd;
				gd.guard = it->guard;
				gd.time_asleep = 0;
				for (int i = 0; i < 60; i++) {
					if (it->time[i] == 1) {
						gd.time_asleep++;
					}
				}
				list.push_back(gd);
			}
		}
	}
	int max_time_asleep = 0;
	int max_guard;
	for (vector<GuardData>::iterator it2 = list.begin(); it2 != list.end(); ++it2) {
		if (it2->time_asleep > max_time_asleep) {
			max_guard = it2->guard;
			max_time_asleep = it2->time_asleep;
		}
	}
	ShiftData sd;
	sd.guard = max_guard;
	for (vector<ShiftData>::iterator it = vec.begin(); it != vec.end(); ++it) {
		if (it->guard == sd.guard) {
			for (int i = 0; i < 60; i++) {
				if (it->time[i] == 1) {
					sd.time[i]++;
				}
			}
		}
	}
	int max_minute;
	int max_count = 0;
	for (int i = 0; i < 60; i++) {
		if (sd.time[i] > max_count) {
			max_count = sd.time[i];
			max_minute = i;
		}
	}
	return max_minute*sd.guard;
}

void FillIn(vector<ShiftData> &vec) {
	for (vector<ShiftData>::iterator it = vec.begin(); it != vec.end(); ++it) {
		int last = 0;
		for (int i = 0; i < 60; i++) {
			if ((it->time[i] == 1) && (last == 0)) {
				last = 1;
			}
			else if ((it->time[i] == 0) && (last == 1)) {
				last = 1;
				it->time[i] = 1;
			}
			else if ((it->time[i] == 2) && (last == 1)) {
				last = 2;
			}
			else if ((it->time[i] == 0) && (last == 2)) {
				last = 0;
			}
		}
	}
}

void addSleepToShift(vector<ShiftData> &vec, int month, int day, int hour, int min, int guard) {
	if (vec.empty()) {
		ShiftData gd;
		if (hour == 23) {
			gd.day = day + 1;
		}
		else {
			gd.day = day;
			gd.time[min] = 1;
		}
		gd.month = month;
		vec.push_back(gd);
		return;
	}
	for (vector<ShiftData>::iterator it = vec.begin(); it != vec.end(); ++it) {
		if ((((hour == 23) && (it->day == day + 1)) || ((it->day == day) && (hour == 0))) && (it->month == month)) {
			it->time[min] = 1;
			return;
		}
	}
	ShiftData gd;
	if (hour == 23) {
		gd.day = day + 1;
	}
	else {
		gd.day = day;
		gd.time[min] = 1;
	}
	gd.month = month;
	vec.push_back(gd);
	return;
}

void addWakeUpToShift(vector<ShiftData> &vec, int month, int day, int hour, int min, int guard) {
	if (vec.empty()) {
		ShiftData gd;
		if (hour == 23) {
			gd.day = day + 1;
		}
		else {
			gd.day = day;
			gd.time[min] = 2;
		}
		gd.month = month;
		vec.push_back(gd);
		return;
	}
	for (vector<ShiftData>::iterator it = vec.begin(); it != vec.end(); ++it) {
		if ((((hour == 23) && (it->day == day + 1)) || ((it->day == day) && (hour == 0))) && (it->month == month)) {
			it->time[min] = 2;
			return;
		}
	}
	ShiftData gd;
	if (hour == 23) {
		gd.day = day + 1;
	}
	else {
		gd.day = day;
		gd.time[min] = 2;
	}
	gd.month = month;
	vec.push_back(gd);
	return;
}

void addGuardToShift(vector<ShiftData> &vec, int month, int day, int hour, int min, int guard) {
	if (hour == 23) {
		hour = 0;
		day++;
		if (day > 28) {
			if (day == 29 && month == 2) {
				month = 3;
				day = 1;
			}
			else if (day == 31 && (month == 4 || month == 6 || month == 9 || month == 11)) {
				month++;
				day = 1;
			}
			else if (day == 32 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) {
				month++;
				day = 1;
			}
		}
	}
	if (vec.empty()) {
		ShiftData gd;
		if (hour == 23) {
			gd.day = day + 1;
		}
		else {
			gd.day = day;
		}
		gd.month = month;
		gd.guard = guard;
		vec.push_back(gd);
		return;
	}
	for (vector<ShiftData>::iterator it = vec.begin(); it != vec.end(); ++it) {
		if ((((hour == 23) && (it->day == day + 1)) || ((it->day == day)&&(hour == 0))) && (it->month == month)) {
			it->guard = guard;
			return;
		} 
	}
	ShiftData gd;
	if (hour == 23) {
		gd.day = day + 1;
	}
	else {
		gd.day = day;
	}
	gd.month = month;
	gd.guard = guard;
	vec.push_back(gd);
	return;
}

void day4p1disect(string input, int& month, int& day, int& hour, int& min, string& event, int& guard) {
	string monthraw, dayraw, hourraw, minraw, guardraw, temp;
	temp = input.substr(input.find('-') + 1);
	monthraw = temp.substr(0,temp.find('-'));
	temp = temp.substr(temp.find('-') + 1);
	dayraw = temp.substr(0, temp.find(' ') );
	temp = temp.substr(temp.find(' ') + 1);
	hourraw = temp.substr(0,temp.find(':') );
	temp = temp.substr(temp.find(':') + 1);
	minraw = temp.substr(0,temp.find(']') );
	temp = temp.substr(temp.find(']') + 2);

	if (temp.find("Guard") != string::npos) {
		event = "guard";
		temp = temp.substr(temp.find('#') + 1);
		guardraw = temp.substr(0,temp.find(' '));
		stringstream Gconv(guardraw);
		Gconv >> guard;
	}
	else if (temp.find("wakes") != string::npos) {
		event = "wakes";
	}
	else if (temp.find("falls") != string::npos) {
		event = "sleep";
	}
	else {
		event = "Tom fucked up";
	}

	stringstream conv(monthraw);
	conv >> month;
	stringstream conv2(dayraw);
	conv2 >> day;
	stringstream conv3(hourraw);
	conv3 >> hour;
	stringstream conv4(minraw);
	conv4 >> min;
}

int day4pt2() {
	ifstream input;
	input.open("input4-1.txt");
	ShiftData *gd;
	vector<ShiftData> vec;
	while (true) {
		if (input.eof()) {
			break;
		}
		string in;
		getline(input, in);
		int month, day, hour, min, guard;
		string event;
		day4p1disect(in, month, day, hour, min, event, guard);
		if (event == "guard") {
			addGuardToShift(vec, month, day, hour, min, guard);
		}
		if (event == "wakes") {
			addWakeUpToShift(vec, month, day, hour, min, guard);
		}
		if (event == "sleep") {
			addSleepToShift(vec, month, day, hour, min, guard);
		}
	}
	FillIn(vec);
	return FindGuardAndMinPt2(vec);
}

int FindGuardAndMinPt2(vector<ShiftData> &vec) {
	vector<GuardData> list;
	for (vector<ShiftData>::iterator it = vec.begin(); it != vec.end(); ++it) {
		if (it->guard == -1) {
			return 0;
		}
		if (list.empty()) {
			GuardData gd;
			gd.guard = it->guard;
			gd.time_asleep = 0;
			for (int i = 0; i < 60; i++) {
				if (it->time[i] == 1) {
					gd.time_asleep++;
					gd.time_sleep[i]++;
				}
			}
			list.push_back(gd);
		}
		else {
			bool found = false;
			for (vector<GuardData>::iterator it2 = list.begin(); it2 != list.end(); ++it2) {
				if (it->guard == it2->guard) {
					found = true;
					for (int i = 0; i < 60; i++) {
						if (it->time[i] == 1) {
							it2->time_asleep++;
							it2->time_sleep[i]++;
						}
					}
				}
			}
			if (!found) {
				GuardData gd;
				gd.guard = it->guard;
				gd.time_asleep = 0;
				for (int i = 0; i < 60; i++) {
					if (it->time[i] == 1) {
						gd.time_asleep++;
						gd.time_sleep[i]++;
					}
				}
				list.push_back(gd);
			}
		}
	}
	int max_time_sleep = 0;
	int max_minute = -1;
	int max_guard;
	for (vector<GuardData>::iterator it2 = list.begin(); it2 != list.end(); ++it2) {
		for (int i = 0; i < 60; i++) {
			if (max_time_sleep == 0) {
				max_time_sleep = it2->time_sleep[i];
				max_guard = it2->guard;
				max_minute = i;
			}
			else if (it2->time_sleep[i] > max_time_sleep) {
				max_time_sleep = it2->time_sleep[i];
				max_guard = it2->guard;
				max_minute = i;
			}
		}
	}
	return max_minute*max_guard;
}

int day5pt1() {
	ifstream input;
	input.open("input5.txt");
	string in;
	getline(input, in);
	int i = 0;
	while(i < in.length()-1){
		char ch = in.at(i);
		char ch_low = tolower(ch);
		char ch_upper = toupper(ch);
		char ch_next = in.at(i+1);
		if (ch_next != ch) {
			if ((ch_next == ch_low)||(ch_next == ch_upper)) {
				in.erase(i,2);
				i--;
			}
			else {
				i++;
			}
		}
		else {
			i++;
		}
	}
	return in.length();
}

int day5pt2() {
	ifstream input;
	input.open("input5.txt");
	string in;
	getline(input, in);
	int i = 0;
	int short_length = -1;
	string parsekey = "abcdefghijklmnopqrstuvwxyz";
	for (int j = 0; j < 26; j++) {
		string temp = in;
		if (short_length == -1) {
			short_length = temp.length();
		}
		while (true) {
			if (temp.find(parsekey[j]) != string::npos) {
				temp.erase(temp.find(parsekey[j]), 1);
			}
			else if (temp.find(toupper(parsekey[j])) != string::npos) {
				temp.erase(temp.find(toupper(parsekey[j])), 1);
			}
			else {
				if (short_length > temp.length()) {
					short_length = temp.length();
				}
				break;
			}
		}
		while (i < temp.length() - 1) {
			char ch = temp.at(i);
			char ch_low = tolower(ch);
			char ch_upper = toupper(ch);
			char ch_next = temp.at(i + 1);
			if (ch_next != ch) {
				if ((ch_next == ch_low) || (ch_next == ch_upper)) {
					temp.erase(i, 2);
					i--;
				}
				else {
					i++;
				}
			}
			else {
				i++;
			}
		}
		if (short_length > temp.length()) {
			short_length = temp.length();
		}
	}
	return short_length;
}

int main() {
	int x;
	cout << day5pt2();
	cin >> x;
	return 0;
}

