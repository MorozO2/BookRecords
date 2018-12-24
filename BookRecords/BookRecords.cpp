// BookRecords.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "classes.h"
#include <iostream>
#include <fstream>

int main()
{
	

	Book b("Moby Dick", 56);
	Book c("Playboy", 67);
	Book d("C++ for Morons", 89);
	d.changeStatus(true);
	bookRecords rec;
	rec.addBook(b);
	rec.addBook(c);
	rec.addBook(d);
	rec.displayRecords();
	rec.saveR();
	
	/*std::cout << "\n" << std::endl;

	
	std::cout << "Welcomes to LibraryRecords. Please select an option:" << std::endl;
	std::cout << "\n" << std::endl;
	std::cout << "Enter 1 to clear all library records." << std::endl;
	std::cout << "Enter 2 to save all current records to disc." << std::endl;
	std::cout << "Enter 3 to retrieve records from disc." << std::endl;
	std::cout << "Enter 4 to add new book to library." << std::endl;
	std::cout << "Enter 5 to borrow a book." << std::endl;
	std::cout << "Enter 6 to return a borrowed book." << std::endl;
	std::cout << "Enter 7 to see all books currently available." << std::endl;
	std::cout << "\n" << std::endl;*/
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
