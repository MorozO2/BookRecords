#pragma once
#include "pch.h"
#include <memory>
#include "classes.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#pragma warning (disable:4996)
#define addBuffer 10 //Addition memory allocated for the records vector for adding books
#define bookID 5 //Length of ID numbers for books (5 digits) 
#define personID 6 //Length of library card numbers for person (6 digits)
#define ZERO 0
#define DUE_DATE 30
#define MONTHS 12
#define MONTH 1
#define WIDTH_1 30
#define WIDTH_2 50

const int limitedInput(unsigned int limit);
const std::string getMonth(int month);

//BOOK CLASS----------------------------------------------------------------------------------------------------------------------------
class Book
{
private:
	std::string title;
	int idNum;
	bool available;
	int cardBorrowed = 0;
	int dueD = 0;
	int dueM = 0;
public:
	Book(const std::string &n, int num, const bool& availability, int card, int dueDay, int dueMonth) :title(n), idNum(num), available(availability), cardBorrowed(card), dueD(dueDay),dueM(dueMonth)  {}; //CONSTRUCTOR 
	Book(const Book& b) : title(b.title), idNum(b.idNum), available(b.available), dueD(b.dueD), dueM(b.dueM) {}; // COPY CONSTRUCTOR 
	~Book() { } //DESTRUCTOR

	const std::string getBookName() { return title; } //FUNCTION FOR GETTING THE NAME OF THE BOOK
	const int getBookNo() { return idNum; } //FUNCTION FOR GETTING THE ID NUMBER OF THE BOOK
	const int getCardHolder() { return cardBorrowed; } //FUNCTION FOR GETTING THE LIBRARY CARD NO. ASSOCIATED WITH THE BOOK (IF THE BOOK IS BORROWED)
	const int getDueDay() { return dueD; }
	const int getDueMonth() { return dueM; }
	const bool bookStatus() { return available; } //FUNCTION THAT RETURN WHETHER THE BOOK IS AVAILABLE FOR BORROWING
	void changeStatus(bool c, int num, int dueDay, int dueMonth) { available = c; cardBorrowed = num; dueD = dueDay; dueM = dueMonth; } //FUNCTION FOR CHANGING THE BOOK'S STATUS FROM AVAILABLE TO UNAVAILABLE (AND VISE VERSA)
	
};
//BOOK CLASS----------------------------------------------------------------------------------------------------------------------------

//PERSON CLASS-----------------------------------------------------------------------------------------------------------
class Person
{
private:
	std::string nameP;
	int cardNum;
public:
	Person(const std::string &n, int num) : nameP(n), cardNum(num) {};
	Person(const Person &p) : nameP(p.nameP), cardNum(p.cardNum) {};
	const std::string getName() { return nameP; };//Function for getting the person's name
	const int getNum() { return cardNum; } //Function for getting the person's library card number
	~Person() {};
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
	void load(); //Loads all of the records from the txt file into a vector of objects "book"
	void displayAll(); //Display the records (vector bookRecs)
	void addBook(); //Adds a book to the records (vector bookRecs)
	void saveR(); // Saves all the records (book objects in vector bookRecs) to txt file, line by line. Clears the vector at the end.
	void clear(); //Clears the vector
	void find(); //Find a specific book object from bookRecs vector by book ID number
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
	void load();//Loads all of the records from the txt file into a vector of objects "person" (pRecs)
	void addPerson(); //Adds person object (by emplacing it) to the pRecs vector
	void displayAll();//Displays the contents of vector pRecs (person records)
	void saveR();//Saves all the records (person objects in vector pRecs) to txt file, line by line. Clears the vector at the end.
	void clear();//Clears records (pRecs vector)
	void find(); // Finds a specific person from the records (pRecs vector) by library card number
};
//PERSON RECORDS CLASS-------------------------------------------------------------

