// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <time.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

class predmet
{
protected:
	friend class student;
	string name;
	vector<int> ocenki;
	float srednee;
	float prohodnoi;
public:
	predmet(string a, int b)
	{
		name = a;
		prohodnoi = b;
		srednee = 0;
	}
	string getname() 
	{
		return name;
	}
	void addoc(int b)
	{
		ocenki.push_back(b);
	}
	void fsrednee()
	{
		int a=0;
		int n = 0;
		for (int i = 0;i < ocenki.size();i++)
		{
			a += ocenki[i];
			n += 1;
		}
		if(n!=0)
			srednee = a/n;
	}
	void printoc(ofstream& a)
	{
		a << name << ' ' << ocenki.size() << endl;
		for (int i = 0;i < ocenki.size();i++)
			a << ocenki[i] << ' ';
		a << endl;
	}
	friend ostream& operator<<(ostream& a, predmet b);
	friend ofstream& operator<<(ofstream& a, predmet b);
};

ostream& operator<<(ostream& a, predmet b)
{
	cout << b.name << endl;
	for (int i = 0;i < b.ocenki.size();i++)
		cout << b.ocenki[i] << ' ';
	cout << endl << "srednee: " << b.srednee << " prohodnpoi: " << b.prohodnoi << endl;
	return a;
}

ofstream& operator<<(ofstream& a, predmet b)
{
	a << b.name << ' ' << b.prohodnoi;
	return a;
}

class student
{
protected:
	string name;
	vector<predmet> kurs;
	string group;
public:
	student(string a, string b, vector<predmet> c)
	{
		name = a;
		group = b;
		kurs = c;
	}
	void addcourse(predmet a)
	{
		kurs.push_back(a);
	}
	void dellcourse(string a)
	{
		for (int i = 0;i < kurs.size();i++)
			if (kurs[i].getname() == a)
				kurs.erase(kurs.begin() + i);
	}
	void addoc(string a, int b)
	{
		for (int i = 0;i < kurs.size();i++)
			if (kurs[i].getname() == a)
				kurs[i].addoc(b);
	}
	void newgroup(string a)
	{
		group = a;
	}
	string getgroup()
	{
		return group;
	}
	string getname()
	{
		return name;
	}
	void srednee()
	{
		for (int i = 0;i < kurs.size();i++)
				kurs[i].fsrednee();
	}
	int proverka()
	{
		int z = 0;
		for (int i = 0;i < kurs.size();i++)
		{
			if (kurs[i].srednee >= kurs[i].prohodnoi)
				z = 1;
			else return 0;
		}
		return z;
	}
	friend ostream& operator<<(ostream& a, student b);
	friend ofstream& operator<<(ofstream& a, student b);
};

ostream& operator<<(ostream& a, student b)
{
	cout << '\t' << b.name << '-' << b.group << endl;
	for (int i = 0;i < b.kurs.size();i++)
		cout << b.kurs[i];
	return a;
}

ofstream& operator<<(ofstream& a, student b)
{
	a << b.name << ' ' << b.group << endl;
	for (int i = 0;i < b.kurs.size();i++)
		b.kurs[i].printoc(a);
	return a;
}

int main()
{
	vector<string> groups;
	vector<student> students;
	vector<predmet> predmets;
	string data, v1, v2, v3;
	int q = 0;
	
	while (data != "exit")
	{
		cin >> data;
		if (data == "add")
		{
			q = 1;
			cin >> v1;
			if (v1 == "group")
			{
				int z = 0;
				cin >> v2;
				for (int i = 0;i < groups.size();i++)
					if (groups[i] == v2) z = 1;//проверка на наличие такой группы
				if (z==0)
					groups.push_back(v2);
				else cout << "takoe est"<<endl;
			}
			if (v1 == "student")
			{
				int z = 1;
				cin >> v2;
				cin >> v3;
				for (int i = 0;i < groups.size();i++)
					if (groups[i] == v3) z = 0;//проверка на наличие такой группы
				for (int i = 0;i < students.size();i++)
					if (students[i].getname() == v2) z = 1;//проверка на наличие такого студента
				if (z == 0)
					students.emplace_back(v2, v3, predmets);
				else cout << "net taokoi gruppu ili takoi student est"<<endl;
			}
			if (v1 == "course")
			{
				cin >> v2;
				int z = 0;
				int w;
				if (!(cin >> w))
				{
					cin.clear();
					cout << "no int ";
				}//защита инт
				else
				{
					for (int i = 0;i < predmets.size();i++)
						if (predmets[i].getname() == v2) z = 1;//защита наличия предмета
					if (z == 0)
					{
						predmet a(v2, w);
						predmets.push_back(a);
						for (int i = 0;i < students.size();i++)
							students[i].addcourse(a);
					}
					else cout << "takoe est" << endl;
				}
				cin.clear();
				cout.clear();
			}
		}
		if (data == "dell")
		{
			q = 1;
			cin >> v1;
			if (v1 == "group")
			{
				cin >> v2;
				for (int i = 0;i < groups.size();i++)
					if (groups[i] == v2)
						groups.erase(groups.begin()+i);
				for (int i = 0;i < students.size();i++)
					if (students[i].getgroup() == v2)
					{
						students.erase(students.begin() + i);
						i--;
					}
			}
			if (v1 == "student")
			{
				cin >> v2;
				for (int i = 0;i < students.size();i++)
					if (students[i].getname() == v2)
						students.erase(students.begin()+i);
			}
			if (v1 == "course")
			{
				cin >> v2;
				for (int i = 0;i < predmets.size();i++)
					if (predmets[i].getname() == v2)
						predmets.erase(predmets.begin() + i);
				for (int i = 0;i < students.size();i++)
					students[i].dellcourse(v2);
			}
		}
		if (data == "ocenka")
		{
			q = 1;
			cin >> v1;
			cin >> v2;
			int w;
			if (!(cin >> w))
			{
				cin.clear();
				cout << "no int ";
			}//защита инт
			else
			{
				for (int i = 0;i < students.size();i++)
					if (students[i].getname() == v1)
					{
						students[i].addoc(v2, w);
					}
			}
			cin.clear();
			cout.clear();
		}
		if (data == "srednee")
		{
			q = 1;
			for (int i = 0;i < students.size();i++)
					students[i].srednee();
		}
		if (data == "list")
		{
			q = 1;
			for (int i = 0;i < students.size();i++)
				cout << students[i];
		}
		if (data == "exit")
		{
			q = 1;
		}
		if (data == "save")
		{
			q = 1;
			ofstream fout;
			fout.open("1.txt");
			fout << groups.size()<<endl;
			for (int i = 0;i < groups.size();i++)
				fout << groups[i]<<endl;
			fout << predmets.size()<<endl;
			for (int i = 0;i < predmets.size();i++)
				fout << predmets[i] << endl;
			fout << students.size() << endl;
			for (int i = 0;i < students.size();i++)
				fout << students[i];
			fout.close();
		}
		if (data == "load")
		{
			int a;
			q = 1;
			groups.clear();
			students.clear();
			predmets.clear();
			ifstream fin;
			fin.open("1.txt");
			fin >> a;
			for (int i = 0;i < a;i++)//groups
			{
				fin >> v1;
				groups.push_back(v1);
			}
			fin >> a;
			int w;
			for (int i = 0;i < a;i++)//predmets
			{
				fin >> v1;
				fin >> w;
				predmet a(v1, w);
				predmets.push_back(a);
			}
			fin >> a;
			for (int i = 0;i < a;i++)//students
			{
				fin >> v1;
				fin >> v2;
				students.emplace_back(v1, v2, predmets);
				int r,t;
				for (int i = 0;i < predmets.size();i++)
				{
					{
						fin >> v1;
						fin >> r;//количество оценок
						for (int i = 0;i < r;i++)
						{
							fin >> t;
							students.back().addoc(v1, t);
						}
					}
				}
			}
			fin.close();
		}
		if (data == "union")
		{
			q = 1;
			cin >> v1;//основная
			cin >> v2;//удаляется
			for (int i = 0;i < groups.size();i++)
				if (groups[i] == v2)
					groups.erase(groups.begin() + i);
			for (int i = 0;i < students.size();i++)
				if (students[i].getgroup() == v2)
				{
					students[i].newgroup(v1);
				}
		}
		if (data == "uspevaushie")
		{
			q = 1;
			for (int i = 0;i < students.size();i++)
				if (students[i].proverka())
					cout << students[i];
		}
		if (data == "otstaushie")
		{
			q = 1;
			for (int i = 0;i < students.size();i++)
				if (!students[i].proverka())
					cout << students[i];
		}
		if (q == 0) cout << "wrong command" << endl;
		q = 0;
	}

    return 0;
}

