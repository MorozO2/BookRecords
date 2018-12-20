#include "pch.h"
#include "classes.h"
#include <string>
#include <iostream>
#include <vector>

//BOOK CLASS IMPLEMENTATIONS
Book::Book(std::string n, int num)
{
	name = n;
	idNum = num;
}

void Book::bookStatus()
{
	if (borrowed == false)
	{
		std::cout << "Available";
	}
	else
	{
		std::cout << "Not available";
	}
}
void Book::changeStatus(bool c)
{
	borrowed = c;
}
//BOOK CLASS IMPLEMENTATIONS



//RECORDS CLASS IMPLEMENTATIONS
bookRecords::bookRecords()
{
	lib = new std::vector<Book>;
}

bookRecords::~bookRecords()
{
	delete lib;
	std::cout << "rec dest done" << std::endl;
}

void bookRecords::addBook(Book b)
{
	lib->push_back(b);
}

void bookRecords::displayRecords()
{
	for (auto i = lib->begin(); i != lib->end(); i++)
	{
		i->bookStatus();
		std::cout <<"		"<< i->getBookName() <<"			"<<"Book No. "<< i->getBookNo() << std::endl;
	}
}
//RECORDS CLASS IMPLEMENTATIONS