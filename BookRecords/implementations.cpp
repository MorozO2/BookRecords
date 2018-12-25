#include "pch.h"
#include "classes.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

//BOOK CLASS IMPLEMENTATIONS
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
void Book::changeStatus(bool c) //Fucntions that changed the borrowed/not borrowed status of a book
{
	borrowed = c;
}
//BOOK CLASS IMPLEMENTATIONS



//BOOK RECORDS CLASS IMPLEMENTATIONS
bookRecords::bookRecords()
{
	lib.reserve(10);
}

bookRecords::~bookRecords()
{
	
	std::cout << "BookRecords destroyed" << std::endl;
}

void bookRecords::addBook(const Book& b)
{
	lib.emplace_back(b);
}

void bookRecords::displayRecords()
{
	for (auto i = lib.begin(); i != lib.end(); i++)
	{
		
		std::cout << i->bookStatus() <<"		"<< i->getBookName() <<"			"<<"Book No. "<< i->getBookNo() << std::endl;
	}
}

void bookRecords::saveR()
{
	std::ofstream bookRec;
	bookRec.open("bookRecords.txt", std::ios::app);
	for (auto i = lib.begin(); i != lib.end(); i++)
	{
		bookRec << i->getBookNo() << "	" << i->getBookName() << "	" << i->bookStatus() << "\n";
	} 
	bookRec.close();
}
//BOOK RECORDS CLASS IMPLEMENTATIONS


//PERSON CLASS IMPLEMENTATION

//PERSON CLASS IMPLEMENTATION



//PERSON RECORDS CLASS IMPLEMENTATION
personRecords::personRecords()
{
	//per = new std::vector<Person>;
	per.reserve(3);
}

personRecords::~personRecords()
{
	//delete per;
	std::cout << "PersonRecords destroyed" << std::endl;
}

void personRecords::addPerson(const Person &p)
{
	per.emplace_back(p);
}
void personRecords::displayRecords()
{
	for (auto i = per.begin(); i != per.end(); i++)
	{

		std::cout << i->getNum() << "		" << i->getName() << std::endl;
	}
}
void personRecords::saveR()
{
	std::ofstream personRec;
	personRec.open("personRecords.txt", std::ios::app);
	for (auto i = per.begin(); i != per.end(); i++)
	{
		personRec << i->getNum() << "	" << i->getName() << "	" << "\n";
	}
	personRec.close();
}
//PERSON RECORDS CLASS IMPLEMENTATION