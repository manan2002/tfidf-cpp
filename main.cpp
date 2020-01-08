#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include "summarizer.h"

using namespace std;

class data{
	string paragraph;
	vector<pair<int, double>> summary;

	vector<string> returnSentences();

	void assignSummary()
	{
		summary = getSummary(paragraph);
	}

public:
	static string dataFName;
	//Constructors
	data(string para)
	{
		paragraph = para;
		assignSummary();
	}
	data()
	{
		paragraph = "Not yet set";
	}

	//Public functions.
	vector<pair<int, double>> returnSummary();

	string returnParagraph();

	void displaySummary()
	{
		vector<string> sentences = returnSentences();
		assignSummary();
		int numlines = 4, count = 0;
		cout << "Summary:\n";
		for (auto x : summary)
		{
			cout << "--> " << sentences[x.first] << "\n";
			if (count >= numlines)
				break;
			count++;
		}
		cout << "-------------------------------------------\n\n";
	}

	void displayParagraph()
	{
		cout << "Paragraph read from file: \n\n";
		cout << paragraph << "\n";
		cout << "-------------------------------------------\n\n";
	}
};

string data::dataFName = "data.dat";

vector<string> data::returnSentences()
{
	return getSentences(paragraph);
}

vector<pair<int, double>> data::returnSummary()
{
	return summary;
}

string data::returnParagraph()
{
	return paragraph;
}

int getNewSummary();
void saveToFile(data d);
void displayLogs();
void deleteAllLogs();

int main()
{
	remove("data.dat");
	int choice = -1;
	while (true)
	{
		do
		{
			system("clear");
			cout << "\t\t Paragraph Summarizer \t\t\n\n";
			cout << "1. Get new summary.\n";
			cout << "2. View logs.\n";
			cout << "3. Delete all logs.\n";
			cout << "4. Exit.\n";
			cout << "Enter choice : ";
			cin >> choice;

		} while (choice < 1 || choice > 4);
		switch (choice)
		{
		case 1:
			getNewSummary();
			break;

		case 2:
			displayLogs();
			break;
	
    case 3:
        deleteAllLogs();
        break;
    case 4:
        exit(0);
        break;
    
		}
	}
	exit(0);
}

int getNewSummary()
{
	string Fname, textInput;
	int choice;
	cout << "Enter File(txt) : ";
	cin >> Fname;
	ifstream fin(Fname, ios::in);
	if (!fin)
	{
		cout << "File doesn't exist";
	}
	else
	{
		fin.seekg(ios::beg);
		while (fin.good())
		{
			getline(fin, textInput);
		}

		system("clear");
		data d(textInput);
		d.displayParagraph();
		d.displaySummary();
		cout << "1. Save summary.\n";
		cout << "2. Cancel.\n";
		cout << "Enter choice(1-2): ";
		cin >> choice;
		if (choice == 1)
		{
			saveToFile(d);
		}
	}
	return 0;
}

void saveToFile(data d)
{
	ofstream fout("data.dat", ios::app | ios::binary);
	if (fout)
	{
		fout.write((char *)&d, sizeof(d));
		cout << "Written to file.\n";
		fout.close();
	}
}

void displayLogs()
{
	vector<data> logs;
	data d;
	ifstream fin("data.dat", ios::in | ios::binary);
	while (fin.read((char *)&d, sizeof(d)))
	{
		logs.insert(logs.end(), d);
	}
	fin.close();
	for (int i = 0; i < logs.size(); i++){
		cout << i + 1 << ") \n";
		logs[i].displayParagraph();
		logs[i].displaySummary();
	}
	int n;
	cout<<"Enter 0 when ready to go back to menu. ";
	cin >> n;

}

void deleteAllLogs(){
	remove("data.dat");
	cout<<"All logs deleted.\n\n";
	cout<<"Enter 0 to go back to menu. ";
	int n;
	cin>>n;
}
