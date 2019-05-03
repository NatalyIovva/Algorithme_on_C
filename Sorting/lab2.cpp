// lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

void printData(BOOK *books, int i)
{

	if (i == 0) {
		cout << "ID: " << "Title:             " << "Author :     " << "Book year:    " << "Publishing hous:    " << "Price:     " << "Writting year: " << endl;
	}
	cout << books[i].id << "   " << books[i].title << "   " << books[i].author << "        " << books[i].book_year << "          " << books[i].publishing_house << "       " << books[i].price << "        " << books[i].writting_year << endl;

}
void swap(int *xp, int *yp, int &swap_count)
{
	swap_count++;
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(BOOK arr[], int low, int high, int &compar_count, int &swap_count)
{
	int pivot = arr[high].id;    // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or 
		// equal to pivot 
		if (arr[j].id <= pivot)
		{
			compar_count++;
			i++;    // increment index of smaller element 
			swap(&arr[i].id, &arr[j].id, swap_count);
		}
	}
	swap(&arr[i + 1].id, &arr[high].id, swap_count);
	return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(BOOK arr[], int low, int high, int &compar_count, int &swap_count)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		   at right place */
		int pi = partition(arr, low, high, compar_count, swap_count);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1, compar_count, swap_count);
		quickSort(arr, pi + 1, high,compar_count, swap_count);
	}
}
/* function to sort arr using shellSort */
int shellSort(BOOK arr[], int n, int &compar_count, int &swap_count)
{
	// Start with a big gap, then reduce the gap 
	for (int gap = n / 2; gap > 0; gap /= 2)
	{	
		// Do a gapped insertion sort for this gap size. 
		// The first gap elements a[0..gap-1] are already in gapped order 
		// keep adding one more element until the entire array is 
		// gap sorted  
		for (int i = gap; i < n; i += 1,compar_count++)
		{
			// add a[i] to the elements that have been gap sorted 
			// save a[i] in temp and make a hole at position i 
			int temp = arr[i].id;

			// shift earlier gap-sorted elements up until the correct  
			// location for a[i] is found 
			int j;
			for (j = i; j >= gap && arr[j - gap].id > temp; j -= gap,compar_count++)
				arr[j] = arr[j - gap];
				

			//  put temp (the original a[i]) in its correct location 
			arr[j].id = temp;
			swap_count++;
		}
	}
	
	return 0;
}

// To heapify a subtree rooted with node i which is 
// an index in arr[]. n is size of heap 
void heapify(BOOK arr[], int n, int i, int &compar_count, int &swap_count)
{
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

	// If left child is larger than root 
	if (l < n && arr[l].id > arr[largest].id)
	{
		compar_count++;
		largest = l;
	}
		

	// If right child is larger than largest so far 
		if (r < n && arr[r].id > arr[largest].id) {
			compar_count++;
			largest = r;
	}
		

	// If largest is not root 
	if (largest != i)
	{
		swap(arr[i].id, arr[largest].id);
		swap_count++;

		// Recursively heapify the affected sub-tree 
		heapify(arr, n, largest,compar_count,swap_count);
	}
}

// main function to do heap sort 
void heapSort(BOOK arr[], int n,int &compar_count, int &swap_count)
{
	// Build heap (rearrange array) 
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i,compar_count, swap_count);

	// One by one extract an element from heap 
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end 
		swap(arr[0].id, arr[i].id);
		swap_count++;

		// call max heapify on the reduced heap 
		heapify(arr, i, 0,compar_count, swap_count);
	}
}



void selectionSort(BOOK arr[], int n, int &compar_count, int &swap_count)
{
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray 
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array 
		min_idx = i;
		for (j = i + 1; j < n; j++,compar_count++)
			if (arr[j].id < arr[min_idx].id){
				min_idx = j;
				
			}
				

		// Swap the found minimum element with the first element 
		swap(&arr[min_idx].id, &arr[i].id,swap_count);
	}
}

void insertionSort(BOOK arr[], int n, int &compar_count, int &swap_count)
{
	int i, key, j;
	for (i = 1; i < n; i++) {
		key = arr[i].id;
		j = i - 1;
		/* Move elements of arr[0..i-1], that are
		  greater than key, to one position ahead
		  of their current position */
		while (j >= 0&&arr[j].id > key) {
				compar_count++;
				swap_count++;
				arr[j + 1].id = arr[j].id;
				j = j - 1;
			
		}
		swap_count++;
		arr[j + 1].id = key;
	}
}

// A function to implement bubble sort 
void bubbleSort(BOOK arr[], int n, int &compar_count, int &swap_count)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place    
		for (j = 0; j < n - i - 1; j++)
			if (arr[j].id > arr[j + 1].id){
				compar_count++;
				swap(&arr[j].id, &arr[j + 1].id, swap_count);
			}
				
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
	int c,i, compar_count=0, swap_count=0;
	do {
		do {
			cout << "Menu:\n" << "1)Quick sort\n" << "2)Shellsort\n" << "3)Insertion sort \n" << "4)Selection sort \n" <<"5)Bubble sort\n"<<"6)Heapsort "<< "0)Exit" << endl;
			cin >> c;
		} while (c > 6 || c < 0);
		
		switch (c)
		{
		case 1: quickSort(books, 0, M-1,compar_count,swap_count);
			for (i = 0; i < M; i++) {
				printData(books, i);
			}
			cout << "\nSwaps:" << swap_count;
			cout << "\n Comparations:" << compar_count << "\n";
			swap_count = 0;
			compar_count = 0;	
			break;
		case 2: shellSort(books, M,compar_count,swap_count);
			for (i = 0; i < M; i++) {
				printData(books, i);
			}
			cout << "\nSwaps:" << swap_count;
			cout << "\n Comparations:" << compar_count << "\n";
			swap_count = 0;
			compar_count = 0;
			break;
		case 3:insertionSort(books, M, compar_count, swap_count);
			for (i = 0; i < M; i++) {
				printData(books, i);
			}
			cout << "\nSwaps:" << swap_count;
			cout << "\n Comparations:" << compar_count << "\n";
			swap_count = 0;
			compar_count = 0;
			break;
			break;
		case 4:selectionSort(books, M,compar_count,swap_count);
			for (i = 0; i < M; i++) {
			printData(books, i);
		}
			cout << "\nSwaps:" << swap_count;
			cout << "\n Comparations:" << compar_count<<"\n";
			swap_count = 0;
			compar_count = 0;
			break;
		case 5:bubbleSort(books, M,compar_count, swap_count);
			for (i = 0; i < M; i++) {
			printData(books, i);
		}
			cout << "\nSwaps:" << swap_count;
			cout << "\n Comparations:" << compar_count<<"\n";
			swap_count = 0;
			compar_count = 0;
			break;
		case 6:heapSort(books, M, compar_count, swap_count);
			for (i = 0; i < M; i++) {
				printData(books, i);
			}cout << "\nSwaps:" << swap_count;
			cout << "\n Comparations:" << compar_count << "\n";
			swap_count = 0;
			compar_count = 0;
			break;
		case 0:break;
		}
	} while (c);


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
