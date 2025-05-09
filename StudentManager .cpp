#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;


void menu();
void clear();
void logOut();


class Student {
	private:
		string name;
		string surname;
		int age;
		bool active;
	public:
		void SetName(string value) {
			name=value;
		}
		string GetName() {
			return name;
		}
		void SetSurname(string value) {
			surname=value;
		}
		string GetSurname() {
			return surname;
		}
		void SetAge(int value) {
			age=value;
		}
		int GetAge() {
			return age;
		}
		void addStudent(vector<Student>&data) {
			clear();
			Student s1;
			cout << "Enter Name: ";
			getline(cin, s1.name);
			cout << "Enter Surname: ";
			getline(cin, s1.surname);
			cout << "Enter Age: ";
			cin >> s1.age;
			s1.active=true;
			data.push_back(s1);
			cin.get();
			cout << "Added succecfully!" <<endl<<"Press enter to continue." << endl;
			clear();
		}
		int findIndex(vector<Student>data,string search) {
			for (int i = 0; i < data.size(); i++) {
				if (data[i].surname == search) {
					return i;
				}
			}
			return -1;
		}
		void editStudent(vector<Student>&data) {
			clear();
			string search;
			cout << "Enter surname for search: ";
			getline(cin, search);
			int index = findIndex(data, search);
			if (index != -1) {
				bool flag = true;
				while (flag == true) {
					cout << "Found " << data[index].surname << "!" << endl;
					cout << endl;
					cout << "1) Edit name" << endl;
					cout << "2) Edit surname" << endl;
					cout << "3) Edit age" << endl;
					cout << "4) Exit edit menu" << endl;
					int select;
					cin >> select;
					switch (select) {
						case 1: {
							cin.get();
							cout << "Enter new value for name: " << endl;
							getline(cin, data[index].name);
							cout << "Succecfully Updated values!"<<endl<<"Press enter to continue." << endl;
							clear();
							break;
						}
						case 2: {
							cin.get();
							cout << "Enter new value for surname: " << endl;
							getline(cin, data[index].surname);
							cout << "Succecfully Updated values!"<<endl<<"Press enter to continue." << endl;
							clear();
							break;
						}
						case 3: {
							cout << "Enter new value for age: " << endl;
							int age;
							cin >>data[index].age;
							cin.get();
							cout << "Succecfully Updated values!"<<endl<<"Press enter to continue." << endl;
							clear();
							break;
						}
						case 4:
							flag = false;
							system("cls");
							break;
						default:
							cin.get();
							system("color 04");
							cout << "invalid input!"<<endl<<"Press enter to continue." << endl;
							clear();
							break;
					}
				}
			} else {
				cout << endl;
				cout << "Not found!"<<endl<<"Press enter to continue." << endl;
				clear();
			}
		}

		void deleteStudent(vector<Student>&data) {
			clear();
			string search;
			cout << "Enter surname to delete: " << endl;
			getline(cin, search);
			int index = findIndex(data, search);
			if (index != -1) {
				char check;
				cout << "Found!"<<endl<<"Are you sure you want to delete " <<
				     data[index].surname << " ? Enter 'y' for yes and 'n' for no!" << endl;
				cin>>check;
				if (check == 'y') {
					cin.get();
					data[index].active = false;
					cout << "Deleted succecfully!"<<endl<<"Press enter to continue." << endl;
					clear();
				} else if (check == 'n') {
					cin.get();
					cout << "Deleting canceled."<<endl<<"Press enter to continue." << endl;
					clear();
				} else {
					cin.get();
					system("color 04");
					cout << "invalid input!"<<endl<<"Press enter to continue." << endl;
					clear();
				}
			} else {
				cout << endl;
				system("color 04");
				cout << "Not found!"<<endl<<"Press enter to continue." << endl;
				clear();
			}
		}


		void printStudent(vector<Student>&data) {
			clear();
			for (int i = 0; i < data.size(); i++) {
				if (data[i].active) {
					cout << "Name:" << data[i].name << endl;
					cout << "Surname:" << data[i].surname << endl;
					cout << "Age:" << data[i].age << endl;
					cout << "*******************************************" << endl;
				}
			}
			cout << "Press enter to continue." << endl;
			clear();
		}
};


int main() {
	Student s;
	vector<Student>data;
	string username, password;
	ifstream inputs;
	inputs.open("student.txt");
	int line=1;
	char c;
	while(inputs.peek() != -1) {
		Student input;
		string name;
		string surname;
		int age;
		switch (line%4)
		{
		case 1: {
			//name
			for(int i=0; i<6; i++)
				inputs.get(c);
			getline(inputs,name);
			input.SetName(name);
			line ++ ;
		} case 2: {
			//surname
			for(int i=0; i<9; i++)
				inputs.get(c);
			getline(inputs,surname);
			input.SetSurname(surname);
			line ++;
		} case 3: {
			//age
			for(int i=0; i<5; i++)
				inputs.get(c);
			inputs>>age;
			input.SetAge(age);
			line ++;
		} case 0: {
			data.push_back(input);
			for(int i=0; i<44; i++)
				inputs.get(c);
			line ++;
		}
	}
	}
	inputs.close();
	
	while (true) {
		system("color 05");
		cout << "********* Welcome *********" << endl;
		cout << "Please enter your username: ";
		getline(cin, username);

		if (username == "admin") {
			cout << "Please enter your password: ";
			getline(cin, password);
			if (password == "admin") {
				system("cls");
				cout << "Succefully logged in as admin." << endl;
				cout << endl;
				bool a = true;
				while (a == true) {
					menu();
					Student s1;
					int select;
					cin >> select;
					switch (select) {
						case 1:
							s1.addStudent(data);
							break;
						case 2:
							s1.editStudent(data);
							break;
						case 3:
							s1.deleteStudent(data);
							break;
						case 4:
							s1.printStudent(data);
							break;

						case 5:
							a=false;
							logOut();
							break;

						case 6: {
							ofstream ofs("student.txt",ios::out);
							for(int i=0; i<data.size(); i++) {
								ofs<<"Name: "<< data[i].GetName()<<"\nSurname: "<< data[i].GetSurname()<< "\nAge: "<< data[i].GetAge()<<endl;
								ofs << "*******************************************"<< endl;
							}
							ofs.flush();
							ofs.close();
							return 0;
						}
						default: {
							cin.get();
							system("color 04");
							cout << "invalid input!"<<endl<<"Press enter to continue." << endl;
							clear();
							break;
						}
					}
				}
				clear();
			} else {
				system("color 04");
				cout << "Wrong password!"<<endl<<"Press enter to try again." << endl;
				clear();
			}
		}

		else if (username == "guest") {
			cout << "Please enter your password: ";
			getline(cin, password);
			if (password == "guest") {
				system("cls");
				cout << "Succefully logged in as guest!" << endl;
				cout << endl;
				bool b = true;
				while (b == true) {
					Student s1;
					cout << "1) Print student infotmation" << endl;
					cout << "2) Logout" << endl;
					int selecet;
					cin >> selecet;
					switch (selecet) {
						case 1:
							s1.printStudent(data);
							break;

						case 2: {
							b = false;
							logOut();
						}
					}
				}
			} else {
				system("color 04");
				cout << "Wrong password!"<<endl<<"Press enter to try again." << endl;
				clear();
			}

		} else {
			system("color 04");
			cout << "Wrong username!"<<endl<<"Press enter to try again..." << endl;
			clear();
		}
	}
	return 0;
}

void clear() {
	cin.get();
	system("cls");
};

void menu() {
	cout << "1) Add student" << endl;
	cout << "2) Edit student" << endl;
	cout << "3) Delete student" << endl;
	cout << "4) print student" << endl;
	cout << "5) Logout" << endl;
	cout << "6) Save and Exit" << endl;
};

void logOut() {
	system("cls");
	cout << "Succecfully logged out!" << endl;
	cin.get();
	cout << "Press enter to continue." << endl;
	cin.get();
	system("cls");
};