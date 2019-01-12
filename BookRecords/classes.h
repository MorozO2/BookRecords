#pragma once
#include "pch.h"
#include <memory>
#include "classes.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#pragma warning (disable:4996)
#define addBuffer 10 //Addition memory allocated for the records vector for adding books
#define bookID 5 //Length of ID numbers for books (5 digits) 
#define personID 6 //Length of library card numbers for person (6 digits)
#define lineStart 0
#define DUE_DATE 30

const int input(unsigned int limit);

//BOOK CLASS----------------------------------------------------------------------------------------------------------------------------
class Book
{
private:
	std::string title;
	int idNum;
	bool available;
	int cardBorrowed = 0;
public:
	Book(const std::string &n, int num, const bool& availability, int card = 0) :title(n), idNum(num), available(availability), cardBorrowed(card) { /*std::cout << "Book" << std::endl;*/ }; //CONSTRUCTOR 
	Book(const Book& b) : title(b.title), idNum(b.idNum), available(b.available) {/* std::cout << "Book copy" << std::endl; */}; // COPY CONSTRUCTOR 
	~Book() { /*std::cout << /*"book dest done" << std::endl;*/ } //DESTRUCTOR

	const std::string getBookName() { return title; } //FUNCTION FOR GETTING THE NAME OF THE BOOK
	const int getBookNo() { return idNum; } //FUNCTION FOR GETTING THE ID NUMBER OF THE BOOK
	const int getCardHolder() { return cardBorrowed; } //FUNCTION FOR GETTING THE LIBRARY CARD NO. ASSOCIATED WITH THE BOOK (IF THE BOOK IS BORROWED)

	const bool bookStatus() { return available; } //FUNCTION THAT RETURN WHETHER THE BOOK IS AVAILABLE FOR BORROWING
	void changeStatus(bool c) { available = c; } //FUNCTION FOR CHANGING THE BOOK'S STATUS FROM AVAILABLE TO UNAVAILABLE (AND VISE VERSA)
	void changeHolder(int num) { cardBorrowed = num; } //FUNCTION FOR CHANGING THE LIBRARY CARDNUMBER ASSOCIATED WITH THE BOOK WHEN IT IS BORROWED
};
//BOOK CLASS----------------------------------------------------------------------------------------------------------------------------

//PERSON CLASS-----------------------------------------------------------------------------------------------------------
class Person
{
private:
	std::string nameP;
	int cardNum;
public:
	Person(const std::string &n, int num) : nameP(n), cardNum(num) { /*std::cout << "Person" << std::endl;*/ };
	Person(const Person &p) : nameP(p.nameP), cardNum(p.cardNum) { /*std::cout << "Person copy" << std::endl;*/ };
	const std::string getName() { return nameP; };
	const int getNum() { return cardNum; }
	~Person() { /*std::cout << "Person dest done" << std::endl;*/ };
};
//PERSON CLASS-----------------------------------------------------------------------------------------------------------






class personRecords;
//BOOK RECORDS CLASS------------------------------------------------------------------------------------------------------
class bookRecords
{
	friend void borrow_return(bookRecords& books, personRecords& people, bool borrow);

private: 
	std::vector<Book> bookRecs;
public:
	bookRecords(); //Constructor
	~bookRecords() {}; //destructor
	void load();
	void displayAll();
	void addBook();
	void saveR();

	
};
//BOOK RECORDS CLASS------------------------------------------------------------------------------------------------------




//PERSON RECORDS CLASS-------------------------------------------------------------
class personRecords
{
	friend void borrow_return(bookRecords& books, personRecords& people, bool borrow);

private:
	std::vector<Person> pRecs;
public:
	personRecords();
	~personRecords() {};
	void load();
	void addPerson();
	void displayAll();
	void saveR();

};
//PERSON RECORDS CLASS-------------------------------------------------------------

