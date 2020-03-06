#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

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

int main()
{
	add_member();
	return 0;
}