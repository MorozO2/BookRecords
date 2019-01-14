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
	for (;;)
	{
		std::cout << "\n" <<"Welcomes to LibraryRecords. Please select an option:" << "\n" << "\n" << std::endl;
		std::cout << "\n" << std::endl;

		std::cout << "||DISPLAY RECORDS||" << std::endl;
		std::cout << "Enter 1 to display current book records" << std::endl;
		std::cout << "Enter 2 to display current card holder records" << "\n" << "\n" <<std::endl;

		std::cout << "||ADD TO RECORDS||" << std::endl;
		std::cout << "Enter 3 to add new book to library." << std::endl;
		std::cout << "Enter 4 to add new card holder" << std::endl;
		std::cout << "Enter 5 to save current records" << "\n" << "\n" << std::endl;

		std::cout << "||BORROW/RETURN BOOKS||" << std::endl;
		std::cout << "Enter 6 to borrow a book." << std::endl;
		std::cout << "Enter 7 to return a borrowed book." << "\n" << "\n" << std::endl;

		std::cout << "||CHECK RECORDS||" << std::endl;
		std::cout << "Enter 8 to search for a book by ID number." << std::endl;
		std::cout << "Enter 9 to search for a person by library card number." << "\n" << "\n" << std::endl;

		std::cout << "||CLEAR/RELOAD RECORDS||" << std::endl;
		std::cout << "Enter 10 to clear all current book records" << std::endl;
		std::cout << "Enter 11 to clear all current person records" << std::endl;
		std::cout << "Enter 12 to load book records" << std::endl;
		std::cout << "Enter 13 to load person records" << "\n" << "\n" << std::endl;

		std::cout << "||TO EXIT PROGRAM ENTER 0. PLEASE REMEMBER TO SAVE RECORDS BEFORE EXITING.||" << "\n" << "\n" << std::endl;
	
		std::cin >> select;
		if (select == 1) { books.displayAll(); }
		else if (select == 2) { people.displayAll(); }
		else if (select == 3) { books.addBook(); }
		else if (select == 4) { people.addPerson(); }
		else if (select == 5) { books.saveR(); people.saveR(); books.load(); people.load(); }
		else if (select == 6) { borrow_return(books, people, true); }
		else if (select == 7) { borrow_return(books, people, false); }
		else if (select == 8) { books.find(); }
		else if (select == 9) { people.find(); }
		else if (select == 10) { books.clear(); }
		else if (select == 11) { people.clear(); }
		else if (select == 12) { books.load(); }
		else if (select ==13) { people.load(); }
		else if (select == 0) { exit(0); }
		else { std::cout << "ERROR: Please enter one of the given numbers" << std::endl; }
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
