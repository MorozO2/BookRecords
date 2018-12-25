#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

//BOOK CLASS----------------------------------------------------------------------------------------------------------------------------
class Book
{
private:
	std::string nameB;
	int idNum;
	bool borrowed = false;
	int cardBorrowed = 45;
public:
	Book(const std::string &n, int num) :nameB(n), idNum(num) { std::cout << "Book" << std::endl; }; //CONSTRUCTOR 
	Book(const Book& b) : nameB(b.nameB), idNum(b.idNum) { std::cout << "Book copy" << std::endl; }; //CONSTRUCTOR 
	~Book() { std::cout << "book dest done" << std::endl; }; //DESTRUCTOR
	const std::string getBookName() { return nameB; };
	int getBookNo() { return idNum; };
	const std::string bookStatus();
	void changeStatus(bool c);
};
//BOOK CLASS----------------------------------------------------------------------------------------------------------------------------

//PERSON CLASS-----------------------------------------------------------------------------------------------------------
class Person
{
private:
	std::string nameP;
	int cardNum;
public:
	Person(const std::string &n, int num) : nameP(n), cardNum(num) { std::cout << "Person" << std::endl; };
	Person(const Person &p) : nameP(p.nameP), cardNum(p.cardNum) { std::cout << "Person copy" << std::endl; };
	const std::string getName() { return nameP; };
	const int getNum() { return cardNum; }
	~Person() {};
};
//PERSON CLASS-----------------------------------------------------------------------------------------------------------

//BOOK RECORDS CLASS------------------------------------------------------------------------------------------------------
class bookRecords
{
private:
	std::vector<Book> lib;
public:
	bookRecords(); //Constructor
	~bookRecords(); //destructor
	void initialize();
	void addBook(const Book& b);
	void borrowBook();
	void returnBook();
	void displayRecords();
	void saveR();
	void clearSaved();
};
//BOOK RECORDS CLASS------------------------------------------------------------------------------------------------------




//PERSON RECORDS CLASS-------------------------------------------------------------
class personRecords
{
private:
	std::vector<Person> per;
public:
	personRecords();
	~personRecords();
	void initialize();
	void addPerson(const Person &p);
	void deletePerson();
	void assignBook();
	void displayRecords();
	void saveR();
};
//PERSON RECORDS CLASS-------------------------------------------------------------