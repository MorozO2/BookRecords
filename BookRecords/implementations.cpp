#include "pch.h"
#include "classes.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

//BOOK CLASS IMPLEMENTATIONS
Book::Book(std::string n, int num)
{
	nameB = n;
	idNum = num;
}

const std::string Book::bookStatus()
{
	if (borrowed == false)
	{
		return std::string("Available");
	}
	else
	{
		return std::string("Not available");
	}
}
void Book::changeStatus(bool c)
{
	borrowed = c;
}
//BOOK CLASS IMPLEMENTATIONS



//BOOK RECORDS CLASS IMPLEMENTATIONS
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
		
		std::cout << i->bookStatus() <<"		"<< i->getBookName() <<"			"<<"Book No. "<< i->getBookNo() << std::endl;
	}
}

void bookRecords::saveR()
{
	std::ofstream bookRec;
	bookRec.open("bookRecords.txt", std::ios::app);
	for (auto i = lib->begin(); i != lib->end(); i++)
	{
		bookRec << i->getBookNo() << "	" << i->getBookName() << "	" << i->bookStatus() << "\n";
	} 
	bookRec.close();
}
//BOOK RECORDS CLASS IMPLEMENTATIONS


//PERSON CLASS IMPLEMENTATION

//PERSON CLASS IMPLEMENTATION



//PERSON RECORDS CLASS IMPLEMENTATION
void personRecords::saveR()
{
	std::ofstream personRec;
	personRec.open("personRecords.txt", std::ios::app);
	for (auto i = per->begin(); i != per->end(); i++)
	{
		personRec << i->getNum() << "	" << i->getName() << "	" << "\n";
	}
	personRec.close();
}
//PERSON RECORDS CLASS IMPLEMENTATION