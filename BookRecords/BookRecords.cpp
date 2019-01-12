// BookRecords.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "classes.h"
#include <iostream>
#include <fstream>

int main()
{
	int select = 0;
	bookRecords books;
	personRecords people;
	people.load();
	books.load();
	int num = input(6);
	std::cout << input(6) << std::endl;
	for (;;)
	{
		std::cout << "Welcomes to LibraryRecords. Please select an option:" << std::endl;
		std::cout << "\n" << std::endl;
		std::cout << "Enter 1 to display current book records" << std::endl;
		std::cout << "Enter 2 to display current card holder records" << std::endl;
		std::cout << "Enter 3 to save current records" << std::endl;
		std::cout << "Enter 4 to add new book to library." << std::endl;
		std::cout << "Enter 5 to add new card holder" << std::endl;
		std::cout << "Enter 6 to borrow a book." << std::endl;
		std::cout << "Enter 7 to return a borrowed book." << std::endl;
		std::cout << "Enter 8 to see all books currently available." << std::endl;
		std::cout << "\n" << std::endl;

		std::cin >> select;
		switch (select)
		{
		case 1: books.displayAll(); break;
		case 2: people.displayAll();break;
		case 3: books.saveR(); people.saveR(); books.load(); people.load();break;
		case 4: books.addBook(); break;
		case 5: people.addPerson(); break;
		case 6: borrow_return(books, people, true);break;
		case 7: borrow_return(books, people, false);break;
		case 8: break;
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
