// laba_number1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
int tabs = 0;
const int M = 50;

using namespace std;

struct BOOK {
	int id;
	string title;
	string author;
	int book_year;
	string publishing_house;
	double price;
	int writting_year;

};
struct Branch
{
	int ID;
	Branch *LeftBr;
	Branch *RightBr;
};
void Add(int aID, Branch *&aBranch)
{

	if (!aBranch)
	{
		aBranch = new Branch;
		aBranch->ID = aID;
		aBranch->LeftBr = 0;
		aBranch->RightBr = 0;
		return;
	}
	if (aBranch->ID > aID)
	{
		Add(aID, aBranch->LeftBr);
	}
	else
	{
		Add(aID, aBranch->RightBr);
	}
}
int minimum(BOOK *books)
{
	int min = books[0].id;
	for (int i = 1; i < M; i++)
	{
		if (min > books[i].id)min = books[i].id;
	}
	return min;

}
int min_without_one(int firstMin, BOOK *books)
{
	int min = INT_MAX;
	for (int i = 0; i < M; i++)
	{
		if (min > books[i].id&&books[i].id > firstMin)min = books[i].id;
	}
	return min;
}
BOOK* Sorting(BOOK *books)
{
	BOOK *sortBooks = new BOOK[M];
	sortBooks[0].id = minimum(books);
	for (int i = 1; i < M; i++)
	{
		sortBooks[i].id = min_without_one(sortBooks[i - 1].id, books);
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (sortBooks[i].id == books[j].id) {
				sortBooks[i].title = books[j].title;
				sortBooks[i].author = books[j].author;
				sortBooks[i].book_year = books[j].book_year;
				sortBooks[i].publishing_house = books[j].publishing_house;
				sortBooks[i].price = books[j].price;
				sortBooks[i].writting_year = books[j].writting_year;
			}
		}
	}
	return sortBooks;
}
void print(Branch *aBranch)
{
	if (!aBranch) return;
	tabs++;

	print(aBranch->LeftBr);

	for (int i = 0; i < tabs; i++) cout << "  ";
	cout << aBranch->ID << endl;


	print(aBranch->RightBr);

	tabs--;
	return;
}
void printData(BOOK *books, int i)
{

	if (i == 0) {
		cout << "ID: " << "Title:             " << "Author :     " << "Book year:    " << "Publishing hous:    " << "Price:     " << "Writting year: " << endl;
	}
	cout << books[i].id << "   " << books[i].title << "   " << books[i].author << "        " << books[i].book_year << "          " << books[i].publishing_house << "       " << books[i].price << "        " << books[i].writting_year << endl;

}
Branch* newBranch(BOOK *books)
{
	Branch *ROOT = 0;
	for (int i = 0; i < M; i++)
	{
		Add(books[i].id, ROOT);
	}
	print(ROOT);
	return ROOT;
}
int LineSearch(BOOK *books, int searchID)
{
	int stepId = -1;
	do {
		stepId++;
	} while (books[stepId].id != searchID);
	printData(books, stepId);
	return stepId + 1;
}
int BranchSearch(Branch *&ROOT, int searchID, int stepId)
{
	if (ROOT->ID != searchID)
	{
		if (ROOT->ID > searchID)
		{
			BranchSearch(ROOT->LeftBr, searchID, ++stepId);
		}
		else
		{
			BranchSearch(ROOT->RightBr, searchID, ++stepId);
		}
	}
	else {
		return ++stepId;
	}
}
int BinarySearch(BOOK *sortBooks, int searchID, int first_id, int last_id, int step)
{
	int medium, stepId;
	if (searchID == sortBooks[first_id].id)
	{
		medium = first_id;

	}
	if (searchID == sortBooks[last_id].id)
	{
		medium = last_id;
	}
	if (searchID != sortBooks[last_id].id&&searchID != sortBooks[first_id].id) {
		medium = first_id + (last_id - first_id) / 2;
		if (searchID > sortBooks[medium].id) {
			first_id = medium;
			step++;
			stepId = BinarySearch(sortBooks, searchID, first_id, last_id, step);
		}
		if (searchID < sortBooks[medium].id && (medium != first_id || medium != last_id)) {
			last_id = medium;
			step++;
			stepId = BinarySearch(sortBooks, searchID, first_id, last_id, step);
		}
	}
	if (searchID == sortBooks[medium].id) {
		cout << endl << endl;
		printData(sortBooks, medium);
		step++;
		stepId = step;
	}
	return stepId;
}
int main()
{

	BOOK books[M];
	ifstream file("input.txt");
	if (file.is_open())
	{
		string line;

		for (int i = 0; getline(file, line); i++)
		{
			istringstream iss(line);
			iss >> books[i].id >> books[i].title >> books[i].author >> books[i].book_year >> books[i].publishing_house >> books[i].price >> books[i].writting_year;
			printData(books, i);

		}

	}
	else {
		cout << "The file doesn't open" << endl;

	}
	multimap<int, int> my_map;
	int id, id1;
	BOOK *sort;
	sort = Sorting(books);
	for (int i = 0; i < M; i++)
	{
		id = sort[i].id;
		while ((id / 10) != 0) {
			id = id / 10;
		}
		my_map.insert(pair<int, int>(id, sort[i].id));
	}
	int c, i;
	do {
		do {
			cout << "Menu:\n" << "1)Line search\n" << "2)Branch Search\n" << "3)Binary search\n" << "4)Hash search\n" << "0)Exit" << endl;
			cin >> c;
		} while (c > 4 || c < 0);
		int searchid, step;
		Branch *ROOT = 0;

		int first_id = 0, last_id = M - 1, id;
		multimap<int, int>::iterator it;
		multimap<int, int>::iterator end;
		switch (c)
		{
		case 1: cout << "Enter id: "; cin >> searchid; step = LineSearch(books, searchid);
			cout << "Steps count:" << step << endl;
			cout << "The worst case : N = 50 => the averege is 25" << endl;
			break;
		case 2:  cout << "Enter id: "; cin >> searchid;
			ROOT = newBranch(books);
			step = BranchSearch(ROOT, searchid, 0);
			cout << "Steps count:" << step << endl;
			cout << "The worst case : N = 50 => the averege is" << log10(50) << endl;
			break;
		case 3: cout << "Enter id: "; cin >> searchid;
			//sort = Sorting(books);
			for (int i = 0; i < M; i++)
			{
				printData(sort, i);
			}
			step = BinarySearch(sort, searchid, first_id, last_id, 0);
			cout << "Steps count:" << step << endl;
			cout << "The worst case : N = 50 => the averege is" << log10(50) << endl;
			break;
		case 4:
			cout << "Enter id: "; cin >> searchid;
			id = searchid;
			while ((id / 10) != 0) {
				id = id / 10;
			}

			it = my_map.find(id);
			step = 1;
			/* for (it; it->first ==id ; it++)
			 {
				 cout <<"Key: "<< it->first << endl;
				 cout <<"Second: "<< it->second << endl;
			 }*/
			 //end = my_map.end(id);
			if (it->first == id)
			{
				while (it->second != searchid)
				{
					it++;
					step++;
					if (step > my_map.count(id))
					{
						cout << "doesn't exist" << endl;
						it = my_map.end();
						break;
					}
				}
				if (it != my_map.end()) {
					//cout << it->first << endl;
					cout << "Steps count:" << step << endl;
					cout << it->second << endl;
					step = LineSearch(books, it->second);
					//printData(sort,);
				}

				// cout << "exist" << endl;
			}


			//cout << it->second;
			break;
		case 0:break;
		}
	} while (c);
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
