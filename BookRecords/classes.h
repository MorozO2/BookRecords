#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

//BOOK CLASS
class Book
{
private:
	std::string name;
	int idNum;
	bool borrowed = false;
	int cardBorrowed = 45;
public:
	Book(std::string n, int num); //CONSTRUCTOR 
	~Book() { std::cout << "book dest done" << std::endl; }; //DESTRUCTOR
	std::string getBookName() { return name; };
	int getBookNo() { return idNum; };
	void bookStatus();
	void changeStatus(bool c);
};
//BOOK CLASS


//BOOK RECORDS CLASS
class bookRecords
{
private:
	std::vector<Book> *lib;
public:
	bookRecords(); //Constructor
	~bookRecords(); //destructor
	void initialize();
	void addBook(Book b);
	void borrowBook();
	void returnBook();
	void displayRecords();

};
//BOOK RECORDS CLASS


//PERSON CLASS
class Person
{
private:
	std::string name;
	int cardNum;
public: 
	Person(std::string n, int num) { name = n; cardNum = num; };
	~Person();
};
//PERSON CLASS


//PERSON RECORDS CLASS
//PERSON RECORDS CLASS