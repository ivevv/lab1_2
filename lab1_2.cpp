#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct tm * timeinfo;
time_t tstamp;

struct profile 
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

string convert_month(string date)
{
	string p_month;
	string temp;
	temp.push_back(date[4]);
	temp.push_back(date[5]);
	temp.push_back(date[6]);
	if (temp == "Jan")
		p_month = "01";
	if (temp == "Feb")
		p_month = "02";
	if (temp == "Mar")
		p_month = "03";
	if (temp == "Apr")
		p_month = "04";
	if (temp == "May")
		p_month = "05";
	if (temp == "Jun")
		p_month = "06";
	if (temp == "Jul")
		p_month = "07";
	if (temp == "Aug")
		p_month = "08";
	if (temp == "Sep")
		p_month = "09";
	if (temp == "Oct")
		p_month = "10";
	if (temp == "Nov")
		p_month = "11";
	if (temp == "Dec")
		p_month = "12";
	return p_month;
}

//появляется лишняя строка при перезаписи
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
			string fix;
			for (int i = 0; i < size; i++)
			{
				database >> student[i].surname >> student[i].name >> student[i].patronym;
				database >> student[i].group >> student[i].id >> student[i].sex;
				database >> student[i].depart;
				for (int j = 0; j < 8; j++)
					database >> student[i].grades[j];
				getline(database, fix, '\n');
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
				newdatabase.open("students.txt");
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
							newdatabase << endl << student[i].edit<< endl;
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
						newdatabase << endl << student[i].edit << endl;
					}
					for (int i = (edit +1); i < size; i++)
					{
						newdatabase << student[i].surname << " " << student[i].name << " " << student[i].patronym << endl;
						newdatabase << student[i].group << endl << student[i].id << endl << student[i].sex << endl;
						newdatabase << student[i].depart << endl;
						for (int j = 0; j < 8; j++)
							newdatabase << student[i].grades[j] << " ";
						newdatabase << endl << student[i].edit << endl;
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
			string fix;
			for (int i = 0; i < size; i++)
			{
				database >> student[i].surname >> student[i].name >> student[i].patronym;
				database >> student[i].group >> student[i].id >> student[i].sex;
				database >> student[i].depart;
				for (int j = 0; j < 8; j++)
					database >> student[i].grades[j];
				getline(database, fix, '\n');
				getline(database, student[i].edit, '\n');
			}
			database.close();
			int temp = 0;
			for (int i = 0; i < size; i++)
			{
				if (student[i].group == n)
				{
					cout << student[i].id << " " << student[i].surname << " " << student[i].name << " " << student[i].patronym << endl;
					cout << student[i].sex << endl;
					cout << "Term grades: ";
					for (int j = 0; j < 8; j++)
						cout << student[i].grades[j] << " ";
					cout << endl << endl;
					temp++;
				}
			}
			if (temp == 0)
				cout << "There aren't such students in the database." << endl;
			delete [] student;
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
			string fix;
			for (int i = 0; i < size; i++)
			{
				database >> student[i].surname >> student[i].name >> student[i].patronym;
				database >> student[i].group >> student[i].id >> student[i].sex;
				database >> student[i].depart;
				for (int j = 0; j < 8; j++)
					database >> student[i].grades[j];
				getline(database, fix, '\n');
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
			delete [] student;
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
			string fix;
			for (int i = 0; i < size; i++)
			{
				database >> student[i].surname >> student[i].name >> student[i].patronym;
				database >> student[i].group >> student[i].id >> student[i].sex;
				database >> student[i].depart;
				for (int j = 0; j < 8; j++)
					database >> student[i].grades[j];
				getline(database, fix, '\n');
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
				cout << student[i].group << " " << student[i].id << " " << student[i].surname << " " << student[i].name;
				cout << " " << student[i].patronym << " GPA: " << student[i].gpa << endl;
			}
			delete [] student;
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
			string fix;
			for (int i = 0; i < size; i++)
			{
				database >> student[i].surname >> student[i].name >> student[i].patronym;
				database >> student[i].group >> student[i].id >> student[i].sex;
				database >> student[i].depart;
				for (int j = 0; j < 8; j++)
					database >> student[i].grades[j];
				getline(database, fix, '\n');
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
				string fix;
				for (int i = 0; i < size; i++)
				{
					database >> student[i].surname >> student[i].name >> student[i].patronym;
					database >> student[i].group >> student[i].id >> student[i].sex;
					database >> student[i].depart;
					for (int j = 0; j < 8; j++)
						database >> student[i].grades[j];
					getline(database, fix, '\n');
					getline(database, student[i].edit);
				}
				database.close();
				for (int i = 0; i < size; i++)
					student[i].scholarship = grade_check(student[i].grades);
				char buff[9] = "day";
				int temp = 0;
				for (int i = 0; i < size; i++)
				{
					if ((strcmp(student[i].depart, buff) != 0) || (student[i].scholarship == false))
					{
						cout << student[i].group << " " << student[i].id << " " << student[i].surname << " " << student[i].name;
						cout << " " << student[i].patronym << " (" << student[i].depart << ")" << endl;
						temp++;
					}
				}
				if (temp == 0)
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
				string fix;
				for (int i = 0; i < size; i++)
				{
					database >> student[i].surname >> student[i].name >> student[i].patronym;
					database >> student[i].group >> student[i].id >> student[i].sex;
					database >> student[i].depart;
					for (int j = 0; j < 8; j++)
						database >> student[i].grades[j];
					getline(database, fix, '\n');
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
						cout << student[i].group << " " << student[i].id << " " << student[i].surname << " " << student[i].name;
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
				string fix;
				for (int i = 0; i < size; i++)
				{
					database >> student[i].surname >> student[i].name >> student[i].patronym;
					database >> student[i].group >> student[i].id >> student[i].sex;
					database >> student[i].depart;
					for (int j = 0; j < 8; j++)
						database >> student[i].grades[j];
					getline(database, fix, '\n');
					getline(database, student[i].edit);
				}
				database.close();
				for (int i = 0; i < size; i++)
				{
					student[i].scholarship = grade_check(student[i].grades);
					student[i].gpa = gpa(student[i].grades);
				}
				int temp = 0;
				cout << endl;
				for (int i = 0; i < size; i++)
				{
					if ((student[i].gpa != 5) && (student[i].scholarship == true))
					{
						if (student[i].gpa != 4)
						{
							cout << student[i].group << " " << student[i].id << " " << student[i].surname << " " << student[i].name;
							cout << " " << student[i].patronym << endl;
							for (int j = 0; j < 8; j++)
								cout << student[i].grades[j] << " ";
							cout << endl;
							temp++;
						}
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
				string fix;
				for (int i = 0; i < size; i++)
				{
					database >> student[i].surname >> student[i].name >> student[i].patronym;
					database >> student[i].group >> student[i].id >> student[i].sex;
					database >> student[i].depart;
					for (int j = 0; j < 8; j++)
						database >> student[i].grades[j];
					getline(database, fix, '\n');
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
						cout << student[i].group << " " << student[i].id << " " << student[i].surname << " " << student[i].name;
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

void time_check()
{
	cout << "Show profiles saved: " << endl << "1. on a certain date;" << endl << "2. before noon;" << endl << "3. after noon." << endl;
	int start;
	cin >> start;
	switch (start)
	{
	case 1: 
	{
		string date;
		cout << "Enter the date (dd.mm.yyyy.):" << endl;
		cin.ignore();
		getline(cin, date, '\n');
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
				string fix;
				for (int i = 0; i < size; i++)
				{
					database >> student[i].surname >> student[i].name >> student[i].patronym;
					database >> student[i].group >> student[i].id >> student[i].sex;
					database >> student[i].depart;
					for (int j = 0; j < 8; j++)
						database >> student[i].grades[j];
					getline(database, fix, '\n');
					getline(database, student[i].edit);
				}
				database.close();
				string f_day, p_day, f_month, p_month, f_year, p_year;
				f_day.push_back(date[0]);
				f_day.push_back(date[1]);
				f_month.push_back(date[3]);
				f_month.push_back(date[4]);
				f_year.push_back(date[6]);
				f_year.push_back(date[7]);
				f_year.push_back(date[8]);
				f_year.push_back(date[9]);
				int temp = 0;
				for (int i = 0; i < size; i++)
				{
					p_year.push_back(student[i].edit[20]);
					p_year.push_back(student[i].edit[21]);
					p_year.push_back(student[i].edit[22]);
					p_year.push_back(student[i].edit[23]);
					if (p_year == f_year)
					{
						p_day.push_back(student[i].edit[8]);
						p_day.push_back(student[i].edit[9]);
						if (p_day == f_day)
						{
							p_month = convert_month(student[i].edit);
							if (p_month == f_month)
							{
								cout << student[i].group << " " << student[i].id << " " << student[i].surname << " " << student[i].name << " " << student[i].patronym << endl;
								cout << student[i].sex << endl;
								cout << student[i].depart << endl << "Term grades: ";
								for (int j = 0; j < 8; j++)
									cout << student[i].grades[j] << " ";
								cout << endl << endl;
								temp++;
							}
						}
					}
					p_year.clear();
					p_day.clear();
					p_month.clear();
				}
				if (temp == 0)
					cout << "There aren't any student profiles created on this date." << endl;
				delete[] student;
			}
		}
	}
	break;
	case 2:
	{
		int noon = 12;
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
				string fix;
				for (int i = 0; i < size; i++)
				{
					database >> student[i].surname >> student[i].name >> student[i].patronym;
					database >> student[i].group >> student[i].id >> student[i].sex;
					database >> student[i].depart;
					for (int j = 0; j < 8; j++)
						database >> student[i].grades[j];
					getline(database, fix, '\n');
					getline(database, student[i].edit);
				}
				database.close();
				string buff;
				int hour, temp = 0;
				for (int i = 0; i < size; i++)
				{
					buff.push_back(student[i].edit[11]);
					buff.push_back(student[i].edit[12]);
					hour = atoi(buff.c_str());
					if (hour < 12)
					{
						cout << student[i].id << " " << student[i].surname << " " << student[i].name << " " << student[i].patronym << endl;
						cout << student[i].sex << endl;
						cout << student[i].depart << endl << "Term grades: ";
						for (int j = 0; j < 8; j++)
							cout << student[i].grades[j] << " ";
						cout << endl << endl;
						temp++;
					}
					buff.clear();
				}
				if (temp == 0)
					cout << "There aren't any student profiles created before noon." << endl;
				delete[] student;
			}
		}
	}
	break;
	case 3:
	{
		int noon = 12;
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
				string fix;
				for (int i = 0; i < size; i++)
				{
					database >> student[i].surname >> student[i].name >> student[i].patronym;
					database >> student[i].group >> student[i].id >> student[i].sex;
					database >> student[i].depart;
					for (int j = 0; j < 8; j++)
						database >> student[i].grades[j];
					getline(database, fix, '\n');
					getline(database, student[i].edit);
				}
				database.close();
				string buff;
				int hour, temp = 0;
				for (int i = 0; i < size; i++)
				{
					buff.push_back(student[i].edit[11]);
					buff.push_back(student[i].edit[12]);
					hour = atoi(buff.c_str());
					if (hour >= 12)
					{
						cout << student[i].id << " " << student[i].surname << " " << student[i].name << " " << student[i].patronym << endl;
						cout << student[i].sex << endl;
						cout << student[i].depart << endl << "Term grades: ";
						for (int j = 0; j < 8; j++)
							cout << student[i].grades[j] << " ";
						cout << endl << endl;
						temp++;
					}
					buff.clear();
				}
				if (temp == 0)
					cout << "There aren't any student profiles created after noon." << endl;
				delete[] student;
			}
		}
	}
	break;
	default:
	{
		cout << "Error! Please try again." << endl << endl;
		time_check();
	}
	break;
	}
}

void db_menu()
{
	cout << "Welcome to the student database!" << endl << "1. Create a new profile;" << endl << "2. Edit an existing profile;";
	cout << endl << "3. Show all students;" << endl << "4. Show students by group;" << endl << "5. Show students by index;" << endl;
	cout << "6. Show the student rating;" << endl << "7. Show the sex ratio;" << endl;
	cout << "8. Calculate the number of scholarships;" << endl << "9. Show the grade statistics;" << endl;
	cout << "10. Show profiles by date." << endl << endl;
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
	case 10:
	{
		time_check();
		cout << endl << endl;
		db_menu();
	}
	break;
	default:
	{
		cout << "Error! Please restart." << endl;
	}
	break;
	}
}

struct conference
{
public:
	char name[20];
	char surname[20];
	char patronym[20];
	bool status; //0 for attendee, 1 for speaker
	string topic;
	char degree[11];
	string uni;
	bool spb;
};

void add_member()
{
	conference member;
	int answer;
	cout << "Surname:" << endl;
	cin >> member.surname;
	cin.clear();
	cout << "Name:" << endl;
	cin >> member.name;
	cin.clear();
	cout << "Patronym:" << endl;
	cin >> member.patronym;
	cin.clear();
	cout << "Is the guest 1) an attendee or 2) a speaker?:" << endl;
	cin >> answer;
	if (answer == 2)
	{
		member.status = true;
		cin.ignore();
		cout << "Topic of the speech:" << endl;
		getline(cin, member.topic, '\n');
	}
	else
	{
		member.status = false;
		member.topic = "None";
	}
	cin.clear();
	cout << "Degree (student/bachelor/specialist/master/candidate/doctor):" << endl;
	cin >> member.degree;
	cin.clear();
	cout << "Is the guest: 1) a Saint-Petersburg resident 2) a nonresident?" << endl;
	cin >> answer;
	if (answer == 1)
		member.spb = true;
	else member.spb = false;
	cin.clear();
	cout << "Which university does the guest represent?" << endl;
	cin.ignore();
	getline(cin, member.uni, '\n');
	cin.clear();
	ofstream database;
	database.open("conference.txt", ios::app);
	if (!database.is_open())
		cout << endl << "Access to the database was denied.";
	else
	{
		database << member.surname << " " << member.name << " " << member.patronym << endl;
		database << member.status << endl << member.topic << endl << member.degree << endl;
		database << member.spb << endl << member.uni << endl;
		database.close();
		cout << endl << "Profile is saved in the database.";
	}
}

int count_members()
{
	ifstream database("conference.txt");
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
		n = temp / 6;
		return n;
	}
	else return 0;
}

void show_speakers()
{
	ifstream database("conference.txt");
	if (!database.is_open())
		cout << "Access to the database was denied.";
	else
	{
		int size;
		size = count_members();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			string fix;
			conference *member = new conference[size];
			for (int i = 0; i < size; i++)
			{
				database >> member[i].surname >> member[i].name >> member[i].patronym;
				database >> member[i].status;
				getline(database, fix, '\n');
				getline(database, member[i].topic, '\n');
				database >> member[i].degree;
				database >> member[i].spb;
				getline(database, fix, '\n');
				getline(database, member[i].uni, '\n');
			}
			database.close();
			int temp = 0;
			for (int i = 0; i < size; i++)
			{
				if (member[i].status == true)
				{
					cout << member[i].surname << " " << member[i].name << " " << member[i].patronym << " (";
					cout << member[i].degree<< ", " << member[i].uni << ")" << endl;
					cout << "Topic of speech: " << member[i].topic << endl << endl;
					temp++;
				}
			}
			if (temp == 0)
				cout << "There aren't any speakers in the database." << endl;
			delete[] member;
		}
	}
}

void show_guests()
{
	ifstream database("conference.txt");
	if (!database.is_open())
		cout << "Access to the database was denied.";
	else
	{
		int size;
		size = count_members();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			string fix;
			conference *member = new conference[size];
			for (int i = 0; i < size; i++)
			{
				database >> member[i].surname >> member[i].name >> member[i].patronym;
				database >> member[i].status;
				getline(database, fix, '\n');
				getline(database, member[i].topic, '\n');
				database >> member[i].degree;
				database >> member[i].spb;
				getline(database, fix, '\n');
				getline(database, member[i].uni, '\n');
			}
			database.close();
			int temp = 0;
			for (int i = 0; i < size; i++)
			{
				if (member[i].spb == false)
				{
					cout << member[i].surname << " " << member[i].name << " " << member[i].patronym << " (";
					cout << member[i].degree << ", " << member[i].uni << ")" << endl;
					temp++;
				}
			}
			if (temp == 0)
				cout << "There aren't any nonresident guests in the database yet." << endl;
			delete[] member;
		}
	}
}

void stud_speakers()
{
	ifstream database("conference.txt");
	if (!database.is_open())
		cout << "Access to the database was denied.";
	else
	{
		int size;
		size = count_members();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			string fix;
			conference *member = new conference[size];
			for (int i = 0; i < size; i++)
			{
				database >> member[i].surname >> member[i].name >> member[i].patronym;
				database >> member[i].status;
				getline(database, fix, '\n');
				getline(database, member[i].topic, '\n');
				database >> member[i].degree;
				database >> member[i].spb;
				getline(database, fix, '\n');
				getline(database, member[i].uni, '\n');
			}
			database.close();
			int temp = 0;
			for (int i = 0; i < size; i++)
			{
				if (member[i].status == true)
				{
					if (strcmp(member[i].degree, "student") == 0)
					{
						cout << member[i].surname << " " << member[i].name << " " << member[i].patronym << " (";
						cout << member[i].uni << ")" << endl;
						cout << "Topic of speech: " << member[i].topic << endl << endl;
						temp++;
					}
				}
			}
			if (temp == 0)
				cout << "There aren't any student speakers in the database yet." << endl;
			delete[] member;
		}
	}
}

void show_uni()
{
	ifstream database("conference.txt");
	if (!database.is_open())
		cout << "Access to the database was denied.";
	else
	{
		int size;
		size = count_members();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			string fix;
			conference *member = new conference[size];
			for (int i = 0; i < size; i++)
			{
				database >> member[i].surname >> member[i].name >> member[i].patronym;
				database >> member[i].status;
				getline(database, fix, '\n');
				getline(database, member[i].topic, '\n');
				database >> member[i].degree;
				database >> member[i].spb;
				getline(database, fix, '\n');
				getline(database, member[i].uni, '\n');
			}
			database.close();
			int temp = 0;
			string leti;
			leti = "LETI";
			for (int i = 0; i < size; i++)
			{
				if (strcmp(member[i].degree, "student") == 0)
				{
					if (member[i].uni == leti)
					{
						cout << member[i].surname << " " << member[i].name << " " << member[i].patronym << endl;
						temp++;
					}
				}
			}
			if (temp == 0)
				cout << "There aren't any students in the database yet." << endl;
			delete[] member;
		}
	}
}

void c_menu()
{
	cout << "Welcome to the conference database!" << endl << "1. Show all speakers;" << endl << "2. Show all nonresident guests;";
	cout << endl << "3. Show all student speakers;" << endl << "4. Show all students of the host university (LETI)." << endl << endl;
	cout << "To choose an option please enter its number:" << endl;
	int start;
	cin >> start;
	cin.clear();
	switch (start)
	{
	case 1:
	{
		show_speakers();
		cout << endl << endl;
		c_menu();
	}
	break;
	case 2:
	{
		show_guests();
		cout << endl << endl;
		c_menu();
	}
	break;
	case 3:
	{
		stud_speakers();
		cout << endl << endl;
		c_menu();
	}
	break;
	case 4:
	{
		show_uni();
		cout << endl << endl;
		c_menu();
	}
	break;
	default:
	{
		cout << "Error! Please restart" << endl;
	}
	break;
	}
}

void menu()
{
	cout << "Welcome to the database! What part of it you'd like to access?" << endl;
	cout << "1. Student database;" << endl << "2. Conference database." << endl << endl;
	cout << "To choose an option please enter its number:" << endl;
	int start;
	cin >> start;
	cin.clear();
	switch (start)
	{
	case 1:
		db_menu();
		break;
	case 2:
		c_menu();
		break;
	default:
	{
		cout << "Error! Please try again." << endl;
		menu();
	}
	break;
	}
}

int main()
{
	menu();
	return 0;
}