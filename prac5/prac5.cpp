#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
const int L = 100;
const int G = 8;

struct student {
	string fullName;
	char sex[1];
	int group;
	int id;
	int grades[G];
	bool isEmpty() {
		return fullName.empty() && sex[0] == 0 && group == 0 && id == 0;
	}
} stud[L];

bool readFile() {
	ifstream dataStud("students.txt");
	if (dataStud.is_open()) {
		string data;
		int k = 0;
		if (dataStud.peek() == ifstream::traits_type::eof()) {
			cout << "the file is empty" << endl;
			dataStud.close();
			return true;
		}
		while (!dataStud.eof()) {
			if (!dataStud.eof()) {
				getline(dataStud, data);
				if (data == "") break;
				cout << "Full name: " << data << "; ";
			}
			if (!dataStud.eof()) {
				getline(dataStud, data);
				cout << "sex: " << data << "; ";
			}
			if (!dataStud.eof()) {
				getline(dataStud, data);
				cout << "group: " << data << "; ";
			}
			if (!dataStud.eof()) {
				getline(dataStud, data);
				cout << "id: " << data << "; ";
			}
			string disc[8]{ "grades: diff. tests: physics - ", "phylosophy - ", "PE - ", "informatics - ", "English - ", "exams: math. analysis - ", "programming - ", "alg. and geom. - " };
			for (int i = 0; i <= 7; i++) {
				if (!dataStud.eof())
					if (i != 7) {
						getline(dataStud, data);
						cout << disc[i] << data << ", ";
					}
					else {
						getline(dataStud, data);
						cout << disc[i] << data << ";\n";
					}
			}
		}
		dataStud.close();
		return true;
	}
	else {
		cout << "error opening the file" << endl;
		dataStud.close();
		return false;
	}
}

int addProfile(int k) {
	ofstream data("students.txt", ios::app);
	if (data.is_open()) {
		string profile;
		student* s = &stud[k];
		cout << "enter full name: ";
		cin.get();
		getline(cin, s->fullName);
		profile += s->fullName + "\n";
		cout << "enter sex(M or W): ";
		cin >> s->sex;
		if (s->sex[0] != 'W' && s->sex[0] != 'M') {
			cout << "incorrect data entered";
			data.close();
			return k;
		}
		cin.sync();
		profile += string(s->sex) + "\n";
		cout << "enter group: ";
		cin >> s->group;
		cin.sync();
		profile += to_string(s->group) + "\n";
		cout << "enter id: ";
		cin >> s->id;
		cin.sync();
		profile += to_string(s->id) + "\n";
		string subjects[8]{ "physics - ", "phylosophy - ", "PE - ", "informatics - ", "English - ", "math. analysis - ", "programming - ", "alg. and geom. - " };
		cout << "entering grades\n";
		for (int i = 0; i < 8; i++) {
			cout << subjects[i];
			cin >> s->grades[i];
			if (s->grades[i] == 2) {
				cout << "this student will be expelled, the profile will not be saved in the database";
				s = {};
				data.close();
				return k;
			}
		}
		for (int k = 0; k <= 7; k++) {
			profile += to_string(s->grades[k]) + "\n";
		}
		cout << "profile added\n";
		data << profile;
		data.close();
		return k++;
	}
	else {
		cout << "file not found" << endl;
		return k;
	}
}

bool dataGroup(int k, int group) {
	student* s = &stud[k];
	if (s->group == group) {
		cout << "Full name: " << s->fullName << "; " << "sex: " << s->sex << "; " << "group: " << s->group << "; " << "id: " << s->id << "; ";
		string disc[8]{ "grades: diff. tests: physics - ", "phylosophy - ", "PE - ", "informatics - ", "English - ", "exams: math. analysis - ", "programming - ", "alg. and geom. - " };
		for (int i = 0; i <= 7; i++) {
			if (i != 7) {
				cout << disc[i] << s->grades[i] << ", ";
			}
			else cout << disc[i] << s->grades[i] << ";\n";
		}
		return 1;
	}
}

void insertsort(float* arr, string* FN, int N) {
	for (int i = 1; i < N; i++) {
		for (int j = i - 1; j >= 0; j--) if (arr[i] > arr[j]) {
			swap(arr[i], arr[j]);
			i -= 1;
		}
	}
}

float avg(int k) {
	float avg = 0;
	student* s = &stud[k];
	for (int i = 0; i < G; i++) {
		avg += s->grades[i];
	}
	return avg / G;
}

void bestStudents() {
	float _avg[L] = {};
	string FN[L];
	int k = 0;
	for (; k < L; k++) {
		_avg[k] = avg(k);
		if (_avg[k] == 0) break;
	}
	for (int i = 0; i < k; i++) {
		student* s = &stud[i];
		FN[i] = s->fullName;
	}
	insertsort(_avg, FN, k);
	for (int i = 0; i < k; i++) {
		cout << i + 1 << ". " << FN[i] << " witn an average grade of " << _avg[i] << endl;
	}
}

int sameSexStud(char* sex) {
	int p = 0;
	for (int i = 0; !(stud[i].isEmpty() || i < L); i++) {
		student* s = &stud[i];
		if (s->sex[0] == *sex) p++;
	}
	return p;
}

bool divByGrades(int k, int g) {
	student* s = &stud[k];
	if (s->isEmpty()) return 0;
	int q = 0;
	switch (g) {
	case 1:
		for (int i = 0; i < G; i++) {
			if (s->grades[i] == 3) {
				cout << "Full name: " << s->fullName << "; " << "sex: " << s->sex << "; " << "group: " << s->group << "; " << "id: " << s->id << "; ";
				string disc[8]{ "grades: diff. tests: physics - ", "phylosophy - ", "PE - ", "informatics - ", "English - ", "exams: math. analysis - ", "programming - ", "alg. and geom. - " };
				for (int k = 0; k <= 7; k++) {
					if (k != 7) {
						cout << disc[k] << s->grades[k] << ", ";
					}
					else cout << disc[k] << s->grades[k] << ";\n";
				}
				break;
			}
		}
		break;
	case 2:
		for (int i = 0; i < G; i++) {
			if (s->grades[i] == 3) {
				q++;
			}
		}
		if (q == 0) {
			cout << "Full name: " << s->fullName << "; " << "sex: " << s->sex << "; " << "group: " << s->group << "; " << "id: " << s->id << "; ";
			string disc[8]{ "grades: diff. tests: physics - ", "phylosophy - ", "PE - ", "informatics - ", "English - ", "exams: math. analysis - ", "programming - ", "alg. and geom. - " };
			for (int k = 0; k <= 7; k++) {
				if (k != 7) {
					cout << disc[k] << s->grades[k] << ", ";
				}
				else cout << disc[k] << s->grades[k] << ";\n";
			}
		}
		break;
	case 3:
		for (int i = 0; i < G; i++) {
			if (s->grades[i] == 5) {
				q++;
			}
		}
		if (q == 8) {
			cout << "Full name: " << s->fullName << "; " << "sex: " << s->sex << "; " << "group: " << s->group << "; " << "id: " << s->id << "; ";
			string disc[8]{ "grades: diff. tests: physics - ", "phylosophy - ", "PE - ", "informatics - ", "English - ", "exams: math. analysis - ", "programming - ", "alg. and geom. - " };
			for (int k = 0; k <= 7; k++) {
				if (k != 7) {
					cout << disc[k] << s->grades[k] << ", ";
				}
				else cout << disc[k] << s->grades[k] << ";\n";
			}
		}
		break;
	}
	return 1;
}

void dataStudentById(int id, int k) {
	student* s = &stud[k];
	if (s->id == id) {
		cout << "Full name: " << s->fullName << "; " << "sex: " << s->sex << "; " << "group: " << s->group << "; " << "id: " << s->id << "; ";
		string disc[8]{ "grades: diff. tests: physics - ", "phylosophy - ", "PE - ", "informatics - ", "English - ", "exams: math. analysis - ", "programming - ", "alg. and geom. - " };
		for (int i = 0; i <= 7; i++) {
			if (i != 7) {
				cout << disc[i] << s->grades[k] << ", ";
			}
			else cout << disc[i] << s->grades[k] << ";\n";
		}
	}
}

void recordChanges() {
	int id_stud, k = -1;
	string buff;
	cout << "enter the student's id: ";
	cin >> id_stud;
	for (int i = 0; !(stud[i].isEmpty() || i < L); i++) {
		student* s = &stud[i];
		if (s->id == id_stud) {
			k = i;
			break;
		}
	}
	if (k == -1) {
		cout << "student is not found\n";
		return;
	}
	student* old = &stud[k];
	cout << "where do you want to make changes: ";
	cin.ignore();
	getline(cin, buff);
	if (buff == "name") {
		string full_name;
		cout << "enter a new value: ";
		cin.ignore();
		getline(cin, full_name);
		old->fullName = full_name;
	}
	else if (buff == "sex") {
		char new_sex[1]{};
		cout << "enter a new value: ";
		cin >> new_sex;
		old->sex[0] = new_sex[0];
	}
	else if (buff == "group") {
		int new_group;
		cout << "enter a new value: ";
		cin >> new_group;
		old->group = new_group;
	}
	else if (buff == "id") {
		int new_id;
		cout << "enter a new value: ";
		cin >> new_id;
		old->id = new_id;
	}
	else if (buff == "grade") {
		int new_grade, arr_value;
		string subject;
		cout << "enter the subject: ";
		cin.ignore();
		getline(cin, subject);
		cout << "subject = " << subject << endl;
		if (subject == "hysics") { arr_value = 0; }
		else if (subject == "hylosophy") { arr_value = 1; }
		else if (subject == "E") { arr_value = 2; }
		else if (subject == "nformatics") { arr_value = 3; }
		else if (subject == "nglish") { arr_value = 4; }
		else if (subject == "ath. analysis") { arr_value = 5; }
		else if (subject == "rogramming") { arr_value = 6; }
		else if (subject == "lg. and geom.") { arr_value = 7; }
		else {
			cout << "incorrect data\n";
			return;
		}
		cout << "enter a new value: ";
		cin >> new_grade;
		old->grades[arr_value] = new_grade;
	}
	else {
		cout << "incorrect data\n";
		return;
	}
	ofstream file_out("buffer.txt");
	if (file_out.is_open()) {
		for (int i = 0; !(stud[i].isEmpty() || i < L); i++) {
			file_out << stud[i].fullName << '\n' << stud[i].sex << '\n' << stud[i].group << '\n' << stud[i].id <<
				'\n' << stud[i].grades[0] << '\n' << stud[i].grades[1] << '\n' << stud[i].grades[2] << '\n' <<
				stud[i].grades[3] << '\n' << stud[i].grades[4] << '\n' << stud[i].grades[5] << '\n' << stud[i].grades[6] << '\n' << stud[i].grades[7] << '\n';
		}
	}
	else {
		cout << "could not open the file\n";
		return;
	}
	file_out.close();
	ofstream file;
	file.open("students.txt", ofstream::out | ofstream::trunc);
	file.close();
	ofstream new_file("students.txt");
	ifstream buffer("buffer.txt");
	if (new_file.is_open() && buffer.is_open()) {
		string line;
		while (getline(buffer, line)) {
			new_file << line << '\n';
		}
	}
	else {
		cout << "could not open the file\n";
		return;
	}
	ofstream file_clear;
	file_clear.open("buffer.txt", ofstream::out | ofstream::trunc);
	file_clear.close();
	new_file.close();
	cout << "changes applied\n";
}

int main() {
	int f = 0, inp;
	string str;
	ifstream data("students.txt");
	for (int i = 0; !data.eof(); i++, f++) {
		getline(data, str);
		stud[i].fullName = str;
		getline(data, str);
		stud[i].sex[0] = str[0];
		getline(data, str);
		int val = stoi(str);
		stud[i].group = val;
		getline(data, str);
		val = stoi(str);
		stud[i].id = val;
		for (int k = 0; k < G; k++) {
			getline(data, str);
			val = stoi(str);
			stud[i].grades[k] = val;
		}
		if (data.peek() == ifstream::traits_type::eof()) break;
	}
	data.close();
	cout << "\tMENU\n1.add a new student to the database\n2.make changes to the record\n3.output of all student data\n4.displaying information about all students of group N\n";
	cout << "5.displaying the top students by average grade\n6.Displaying the number of male and female students\n";
	cout << "7.output of data about students, depending on academic performance\n8.output of data about students by ip.\n0.exit program\n";
	cin >> inp;
	while (inp) {
		switch (inp) {
		case 1:
		{
			if (f == L) {
				cout << "the database is full\n";
				break;
			}
			else {
				f = addProfile(f);
			}
			break;
		}
		case 2:
		{
			recordChanges();
			break;
		}
		case 3:
		{
			readFile();
			break;
		}
		case 4:
		{
			int group;
			bool endCyc;
			cout << "enter the group number: ";
			cin >> group;
			for (int i = 0; !(stud[i].isEmpty() || i < L); i++) {
				endCyc = dataGroup(i, group);
				if (endCyc == 0) break;
			}
			break;
		}
		case 5:
		{
			cout << "top students:\n";
			bestStudents();
			break;
		}
		case 6:
		{
			char sex[1] = {};
			cout << "enter the gender(M or W)\n";
			cin >> sex[0];
			cout << "number of " << sex[0] << " students in a group = " << sameSexStud(sex) << endl;
			break;
		}
		case 7:
		{
			int g;
			bool endCyc;
			cout << "1. students without a scholaship\n2. students with a scholaship\n3. students study at <excellent>\n";
			cin >> g;
			for (int i = 0; !(stud[i].isEmpty() || i < L); i++) {
				endCyc = divByGrades(i, g);
				if (endCyc == 0) break;
			}
			break;
		}
		case 8:
			int id;
			cout << "enter id: ";
			cin >> id;
			for (int i = 0; !(stud[i].isEmpty() || i < L); i++) {
				dataStudentById(id, i);
			}
			break;
		}
		cin >> inp;
	}
	return 0;
}