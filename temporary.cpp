#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

struct tm * timeinfo;
time_t tstamp;

struct profile // structure for a student's profile in the database
{
public:
	char name[20];
	char surname[20];
	char patronym[20];
	char sex;
	int group;
	int id;
	int grades[8];
	double gpa;
	bool scholarship;
	char depart[9];
	string edit;
};

void create_data()
{
	profile student;
	cout << "Surname:" << endl;
	cin >> student.surname;
	cin.clear();
	cout << "Name:" << endl;
	cin >> student.name;
	cin.clear();
	cout << "Patronym:" << endl;
	cin >> student.patronym;
	cin.clear();
	cout << "Group:" << endl;
	cin >> student.group;
	cin.clear();
	cout << "Index:" << endl;
	cin >> student.id;
	cin.clear();
	cout << "Sex (F/M):" << endl;
	cin >> student.sex;
	cin.clear();
	cout << "Department (day/evening/distance):" << endl;
	cin >> student.depart;
	cin.clear();
	cout << "Term grades (each of new line):" << endl;
	for (int i = 0; i < 8; i++)
	{
		cin >> student.grades[i];
		cin.clear();
	}
	time(&tstamp);
	timeinfo = localtime(&tstamp);
	student.edit = asctime(timeinfo);
	int temp = 0;
	for (int i = 0; i < 8; i++)
	{
		if (student.grades[i] == 2)
			temp++;
	}
	if (temp == 0)
	{
		ofstream database;
		database.open("students.txt", ios::app);
		if (!database.is_open())
			cout << endl << "Saving error! Access to the database was denied.";
		else
		{
			database << student.surname << " " << student.name << " " << student.patronym << endl;
			database << student.group << endl << student.id << endl << student.sex << endl;
			database << student.depart << endl;
			for (int i = 0; i < 8; i++)
				database << student.grades[i] << " ";
			database << endl << student.edit;
			database.close();
			cout << endl << "Profile is saved in the database.";
		}
	}
	else cout << endl << "This student will be expelled. The profile will not be saved in the database.";
};

int count_students()
{
	ifstream database("students.txt");
	if (database.is_open())
	{
		int temp = 0;
		string data;
		while (!database.eof())
		{
			getline(database, data);
			temp++;
		}
		database.close();
		int n;
		n = temp / 7;
		return n;
	}
	else return 0;
}

double gpa(int arr[8])
{
	double gpa = 0;
	for (int i = 0; i < 8; i++)
		gpa += arr[i];
	gpa = gpa / 8;
	return gpa;
}

bool grade_check(int arr[8])
{
	bool check = true;
	for (int i = 0; i < 8; i++)
	{
		if (arr[i] == 3)
		{
			check = false;
			break;
		}
	}
	return check;
}

void edit_data()
{
	ifstream database("students.txt");
	if (!database.is_open())
		cout << "Access to the database was denied.";
	else
	{
		int size;
		size = count_students();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			profile *student = new profile[size];
			for (int i = 0; i < size; i++)
			{
				database >> student[i].surname >> student[i].name >> student[i].patronym;
				database >> student[i].group >> student[i].id >> student[i].sex;
				database >> student[i].depart;
				for (int j = 0; j < 8; j++)
					database >> student[i].grades[j];
				getline(database, student[i].edit, '\n');
			}
			database.close();
			int answer_g, answer_i;
			cout << "Enter the group and index number of student whose profile needs to be edited." << endl;
			cout << "Group:" << endl;
			cin >> answer_g;
			cin.clear();
			cout << "Index:" << endl;
			cin >> answer_i;
			cin.clear();
			int edit = 2147483647;
			for (int i = 0; i < size; i++)
			{
				if ((student[i].group == answer_g) && (student[i].id == answer_i))
					edit = i;
			}
			if (edit == 2147483647)
			{
				cout << "Error! Can't find this student.";
				cout << endl << "Please try again." << endl << endl;
				edit_data();
			}
			else
			{
				cout << "The student's profile:" << endl;
				cout << student[edit].surname << " " << student[edit].name << " " << student[edit].patronym << endl;
				cout << student[edit].group << endl << student[edit].id << endl << student[edit].sex << endl;
				cout << student[edit].depart << endl;
				for (int j = 0; j < 8; j++)
					cout << student[edit].grades[j] << " ";
				cout << endl << endl << "Enter new info:" << endl;
				cout << "Surname:" << endl;
				cin >> student[edit].surname;
				cin.clear();
				cout << "Name:" << endl;
				cin >> student[edit].name;
				cin.clear();
				cout << "Patronym:" << endl;
				cin >> student[edit].patronym;
				cin.clear();
				cout << "Group:" << endl;
				cin >> student[edit].group;
				cin.clear();
				cout << "Index:" << endl;
				cin >> student[edit].id;
				cin.clear();
				cout << "Sex (F/M):" << endl;
				cin >> student[edit].sex;
				cin.clear();
				cout << "Department (day/evening/distance):" << endl;
				cin >> student[edit].depart;
				cin.clear();
				cout << "Term grades (each of new line):" << endl;
				for (int i = 0; i < 8; i++)
				{
					cin >> student[edit].grades[i];
					cin.clear();
				}
				time(&tstamp);
				timeinfo = localtime(&tstamp);
				student[edit].edit = asctime(timeinfo);
				int temp = 0;
				for (int i = 0; i < 8; i++)
				{
					if (student[edit].grades[i] == 2)
						temp++;
				}
				ofstream newdatabase;
				newdatabase.open("students.txt", ios::out);
				if (temp == 0)
				{
					if (!newdatabase.is_open())
						cout << endl << "Saving error! Access to the database was denied.";
					else
					{
						for (int i = 0; i < size; i++)
						{
							newdatabase << student[i].surname << " " << student[i].name << " " << student[i].patronym << endl;
							newdatabase << student[i].group << endl << student[i].id << endl << student[i].sex << endl;
							newdatabase << student[i].depart << endl;
							for (int j = 0; j < 8; j++)
								newdatabase << student[i].grades[j] << " ";
							newdatabase << endl << student[i].edit;
						}
						newdatabase.close();
						cout << endl << "The profile is updated.";
					}
				}
				else
				{
					cout << endl << "This student will be expelled. The profile will be deleted from the database.";
					for (int i = 0; i < edit; i++)
					{
						newdatabase << student[i].surname << " " << student[i].name << " " << student[i].patronym << endl;
						newdatabase << student[i].group << endl << student[i].id << endl << student[i].sex << endl;
						newdatabase << student[i].depart << endl;
						for (int j = 0; j < 8; j++)
							newdatabase << student[i].grades[j] << " ";
						newdatabase << endl << student[i].edit;
					}
					for (int i = (edit + 1); i < size; i++)
					{
						newdatabase << student[i].surname << " " << student[i].name << " " << student[i].patronym << endl;
						newdatabase << student[i].group << endl << student[i].id << endl << student[i].sex << endl;
						newdatabase << student[i].depart << endl;
						for (int j = 0; j < 8; j++)
							newdatabase << student[i].grades[j] << " ";
						newdatabase << endl << student[i].edit;
					}
					newdatabase.close();
				}
			}
			delete[] student;
		}
	}
}

void show_data()
{
	ifstream database("students.txt");
	if (!database.is_open())
		cout << "Access to the database was denied.";
	else
	{
		int temp;
		temp = count_students();
		if (temp == 0)
			cout << "The database is empty.";
		else
		{
			string data;
			while (!database.eof())
			{
				getline(database, data);
				cout << data << endl;
			}
		}
		database.close();
	}
}

void show_group()
{
	int n;
	cout << "Enter the group number:" << endl;
	cin >> n;
	cin.clear();
	ifstream database("students.txt");
	if (!database.is_open())
		cout << "Access to the database was denied.";
	else
	{
		int size;
		size = count_students();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			profile *student = new profile[size];
			char help;
			for (int i = 0; i < size; i++)
			{
				database >> student[i].surname >> student[i].name >> student[i].patronym;
				database >> student[i].group >> student[i].id >> student[i].sex;
				database >> student[i].depart;
				for (int j = 0; j < 8; j++)
					database >> student[i].grades[j];
				getline(database, student[i].edit, '\n');
				database >> help;
			}
			database.close();
			int temp = 0;
			for (int i = 0; i < size; i++)
			{
				if (student[i].group == n)
				{
					cout << student[i].id << " " << student[i].surname << " " << student[i].name << " " << student[i].patronym << endl;
					cout << student[i].sex << endl;
					cout << student[i].depart << endl << "Term grades: ";
					for (int j = 0; j < 8; j++)
						cout << student[i].grades[j] << " ";
					cout << endl << endl;
					temp++;
				}
			}
			if (temp == 0)
				cout << "There aren't such students in the database." << endl;
			delete[] student;
		}
	}
}

void show_id()
{
	int k;
	cout << "Enter the index:" << endl;
	cin >> k;
	cin.clear();
	ifstream database("students.txt");
	if (!database.is_open())
		cout << "Access to the database was denied.";
	else
	{
		int size;
		size = count_students();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			profile *student = new profile[size];
			for (int i = 0; i < size; i++)
			{
				database >> student[i].surname >> student[i].name >> student[i].patronym;
				database >> student[i].group >> student[i].id >> student[i].sex;
				database >> student[i].depart;
				for (int j = 0; j < 8; j++)
					database >> student[i].grades[j];
				getline(database, student[i].edit);
			}
			database.close();
			int temp = 0;
			for (int i = 0; i < size; i++)
			{
				if (student[i].id == k)
				{
					cout << student[i].group << " " << student[i].surname << " " << student[i].name << " " << student[i].patronym << endl;
					cout << student[i].sex << endl;
					cout << student[i].depart << endl << "Term grades: ";
					for (int j = 0; j < 8; j++)
						cout << student[i].grades[j] << " ";
					cout << endl << endl;
					temp++;
				}
			}
			if (temp == 0)
				cout << "There aren't such students in the database." << endl;
			delete[] student;
		}
	}
}

void smartest()
{
	ifstream database("students.txt");
	if (!database.is_open())
		cout << "Access to the database was denied.";
	else
	{
		int size;
		size = count_students();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			profile *student = new profile[size];
			for (int i = 0; i < size; i++)
			{
				database >> student[i].surname >> student[i].name >> student[i].patronym;
				database >> student[i].group >> student[i].id >> student[i].sex;
				database >> student[i].depart;
				for (int j = 0; j < 8; j++)
					database >> student[i].grades[j];
				getline(database, student[i].edit);
			}
			database.close();
			for (int i = 0; i < size; i++)
				student[i].gpa = gpa(student[i].grades);
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < (size - i); j++)
				{
					if (student[j + 1].gpa > student[j].gpa)
						swap(student[j], student[j + 1]);
				}
			}
			for (int i = 0; i < size; i++)
			{
				cout << student[i].group << " " << student[i].surname << " " << student[i].name;
				cout << " " << student[i].patronym << " GPA: " << student[i].gpa << endl;
			}
			delete[] student;
		}
	}
}

void scholarship()
{
	ifstream database("students.txt");
	if (!database.is_open())
		cout << "Access to the database was denied.";
	else
	{
		int size;
		size = count_students();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			profile *student = new profile[size];
			for (int i = 0; i < size; i++)
			{
				database >> student[i].surname >> student[i].name >> student[i].patronym;
				database >> student[i].group >> student[i].id >> student[i].sex;
				database >> student[i].depart;
				for (int j = 0; j < 8; j++)
					database >> student[i].grades[j];
				getline(database, student[i].edit);
			}
			database.close();
			for (int i = 0; i < size; i++)
				student[i].scholarship = grade_check(student[i].grades);
			int count = 0;
			char temp[9] = "day";
			for (int i = 0; i < size; i++)
			{
				if (student[i].scholarship == true)
				{
					if (strcmp(student[i].depart, temp) == 0)
						count++;
				}
			}
			cout << "Students recieving scholarships: " << count;
			delete[] student;
		}
	}
}

void stats()
{
	cout << "Show students, who:" << endl << "1. Don't recieve scholarship;" << endl << "2. Only got Bs last semester;";
	cout << endl << "3. Got Bs and As last semester;" << endl << "4. Only got As last semester;" << endl;
	int start;
	cin >> start;
	switch (start)
	{
	case 1:
	{
		ifstream database("students.txt");
		if (!database.is_open())
			cout << "Access to the database was denied.";
		else
		{
			int size;
			size = count_students();
			if (size == 0)
				cout << "The database is empty." << endl;
			else
			{
				profile *student = new profile[size];
				for (int i = 0; i < size; i++)
				{
					database >> student[i].surname >> student[i].name >> student[i].patronym;
					database >> student[i].group >> student[i].id >> student[i].sex;
					database >> student[i].depart;
					for (int j = 0; j < 8; j++)
						database >> student[i].grades[j];
					getline(database, student[i].edit);
				}
				database.close();
				for (int i = 0; i < size; i++)
					student[i].scholarship = grade_check(student[i].grades);
				char temp[9] = "day";
				int check = 0;
				for (int i = 0; i < size; i++)
				{
					if ((strcmp(student[i].depart, temp) != 0) || (student[i].scholarship == false))
					{
						cout << student[i].group << " " << student[i].surname << " " << student[i].name;
						cout << " " << student[i].patronym << endl;
						check++;
					}
				}
				if (check == 0)
					cout << "There aren't such students" << endl;
				delete[] student;
			}
		}
	}
	break;
	case 2:
	{
		ifstream database("students.txt");
		if (!database.is_open())
			cout << "Access to the database was denied.";
		else
		{
			int size;
			size = count_students();
			if (size == 0)
				cout << "The database is empty." << endl;
			else
			{
				profile *student = new profile[size];
				for (int i = 0; i < size; i++)
				{
					database >> student[i].surname >> student[i].name >> student[i].patronym;
					database >> student[i].group >> student[i].id >> student[i].sex;
					database >> student[i].depart;
					for (int j = 0; j < 8; j++)
						database >> student[i].grades[j];
					getline(database, student[i].edit);
				}
				database.close();
				for (int i = 0; i < size; i++)
					student[i].gpa = gpa(student[i].grades);
				int temp = 0;
				cout << endl;
				for (int i = 0; i < size; i++)
				{
					if (student[i].gpa == 4)
					{
						cout << student[i].group << " " << student[i].surname << " " << student[i].name;
						cout << " " << student[i].patronym << endl;
						temp++;
					}
				}
				if (temp == 0)
					cout << "There aren't such students." << endl;
				delete[] student;
			}
		}
	}
	break;
	case 3:
	{
		ifstream database("students.txt");
		if (!database.is_open())
			cout << "Access to the database was denied.";
		else
		{
			int size;
			size = count_students();
			if (size == 0)
				cout << "The database is empty." << endl;
			else
			{
				profile *student = new profile[size];
				for (int i = 0; i < size; i++)
				{
					database >> student[i].surname >> student[i].name >> student[i].patronym;
					database >> student[i].group >> student[i].id >> student[i].sex;
					database >> student[i].depart;
					for (int j = 0; j < 8; j++)
						database >> student[i].grades[j];
					getline(database, student[i].edit);
				}
				database.close();
				for (int i = 0; i < size; i++)
					student[i].scholarship = grade_check(student[i].grades);
				int temp = 0;
				cout << endl;
				for (int i = 0; i < size; i++)
				{
					if (student[i].scholarship == true)
					{
						cout << student[i].group << " " << student[i].surname << " " << student[i].name;
						cout << " " << student[i].patronym << endl;
						temp++;
					}
				}
				if (temp == 0)
					cout << "There aren't such students." << endl;
				delete[] student;
			}
		}
	}
	break;
	case 4:
	{
		ifstream database("students.txt");
		if (!database.is_open())
			cout << "Access to the database was denied.";
		else
		{
			int size;
			size = count_students();
			if (size == 0)
				cout << "The database is empty." << endl;
			else
			{
				profile *student = new profile[size];
				for (int i = 0; i < size; i++)
				{
					database >> student[i].surname >> student[i].name >> student[i].patronym;
					database >> student[i].group >> student[i].id >> student[i].sex;
					database >> student[i].depart;
					for (int j = 0; j < 8; j++)
						database >> student[i].grades[j];
					getline(database, student[i].edit);
				}
				database.close();
				for (int i = 0; i < size; i++)
					student[i].gpa = gpa(student[i].grades);
				int temp = 0;
				cout << endl;
				for (int i = 0; i < size; i++)
				{
					if (student[i].gpa == 5)
					{
						cout << student[i].group << " " << student[i].surname << " " << student[i].name;
						cout << " " << student[i].patronym << endl;
						temp++;
					}
				}
				if (temp == 0)
					cout << "There aren't such students." << endl;
				delete[] student;
			}
		}
	}
	break;
	default:
	{
		cout << "Error! Please try again." << endl << endl;
		stats();
	}
	break;
	}
}

void sex_check()
{
	ifstream database("students.txt");
	if (!database.is_open())
		cout << "Access to the database was denied.";
	else
	{
		int temp;
		temp = count_students();
		if (temp == 0)
			cout << "The database is empty.";
		else
		{
			string data;
			int m = 0, f = 0;
			while (!database.eof())
			{
				getline(database, data);
				if (data == "M")
					m++;
				else
				{
					if (data == "F")
						f++;
				}
			}
			cout << "Male students: " << m << endl;
			cout << "Female students: " << f << endl;
		}
		database.close();
	}
}

void db_menu()
{
	cout << "Welcome to the student database!" << endl << "1. Create a new profile;" << endl << "2. Edit an existing profile;";
	cout << endl << "3. Show all students;" << endl << "4. Show students by group;" << endl << "5. Show students by index;" << endl;
	cout << "6. Show the student rating;" << endl << "7. Show the sex ratio;" << endl;
	cout << "8. Calculate the number of scholarships;" << endl << "9. Show the grade statistics;" << endl;
	cout << "To choose an option please enter its number:" << endl;
	int start;
	cin >> start;
	cin.clear();
	switch (start)
	{
	case 1:
	{
		create_data();
		cout << endl << endl;
		db_menu();
	}
	break;
	case 2:
	{
		edit_data();
		cout << endl << endl;
		db_menu();
	}
	break;
	case 3:
	{
		show_data();
		cout << endl << endl;
		db_menu();
	}
	break;
	case 4:
	{
		show_group();
		cout << endl << endl;
		db_menu();
	}
	break;
	case 5:
	{
		show_id();
		cout << endl << endl;
		db_menu();
	}
	break;
	case 6:
	{
		smartest();
		cout << endl << endl;
		db_menu();
	}
	break;
	case 7:
	{
		sex_check();
		cout << endl << endl;
		db_menu();
	}
	break;
	case 8:
	{
		scholarship();
		cout << endl << endl;
		db_menu();
	}
	break;
	case 9:
	{
		stats();
		cout << endl << endl;
		db_menu();
	}
	break;

	default:
	{
		cout << "Error! Please try again" << endl << endl;
		db_menu();
	}
	break;
	}
}

int main()
{
	db_menu();
	return 0;
}
