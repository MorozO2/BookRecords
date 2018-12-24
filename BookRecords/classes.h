#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

//BOOK CLASS
class Book
{
private:
	std::string nameB;
	int idNum;
	bool borrowed = false;
	int cardBorrowed = 45;
public:
	Book(std::string n, int num); //CONSTRUCTOR 
	~Book() { std::cout << "book dest done" << std::endl; }; //DESTRUCTOR
	const std::string getBookName() { return nameB; };
	int getBookNo() { return idNum; };
	const std::string bookStatus();
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
	void saveR();
	void clearSaved();
};
//BOOK RECORDS CLASS


//PERSON CLASS
class Person
{
private:
	std::string nameP;
	int cardNum;
public: 
	Person(std::string n, int num) { nameP = n; cardNum = num; };
	const std::string getName(){ return nameP; };
	const int getNum() { return cardNum; }
	~Person();
};
//PERSON CLASS


//PERSON RECORDS CLASS
class personRecords
{
private:
	std::vector<Person> *per;
public:
	void initialize();
	void addPerson();
	void deletePerson();
	void assignBook();
	void displayRecords();
	void saveR();
};
//PERSON RECORDS CLASS