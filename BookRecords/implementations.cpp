#include "pch.h"
#include "classes.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#define addBuffer 10 //Addition memory allocated for the records vector for adding books
#define bookID 5 //Length of ID numbers for books (5 digits) 
#define personID 6 //Length of library card numbers for person (6 digits)
#define lineStart 0

//BOOK RECORDS CLASS IMPLEMENTATIONS
bookRecords::bookRecords()
{	
	int count = 0;
	std::string line;
	std::fstream records;
	records.open("bookRecords.txt");
	if (records.is_open())
	{
		while (std::getline(records, line)) { count++; } //Counts how many line are in the file (1 book = 1 line) in order to determine how much memory to allocate for the vector
		bookRecs.reserve(count + addBuffer);
		std::cout << "Book records loaded." << std::endl;
	}
	else { std::cout << "Error: could not open the file. Please check the source folder to see if bookRecords.txt is present." << std::endl; }
	records.close();
}

bookRecords::~bookRecords()
{
	
	std::cout << "BookRecords destroyed" << std::endl;
}

void bookRecords::addBook(/*const Book& b*/)
{
	std::string name;
	int num;
	std::cout << "Please enter the book's name: "; std::cin.ignore(); getline(std::cin, name); std::cout << "\n";
	std::cout << "Please enter a 5-digit number to identify the book: "; std::cin >> std::setw(bookID)>> num; std::cout << "\n";
	
	bookRecs.emplace_back(name, num, true);
}

void bookRecords::load()
{	
	std::string line;	//Sting for getting one line from the txt file
	std::string name;	//string for the name of the book
	int num;			//Integer for the number of the book
	int card = 0;			//integer for the library card (if the book is borrowed by someone)
	bool available;
	std::fstream records; 
	records.open("bookRecords.txt");
	if (records.is_open())
	{
		
		while (std::getline(records, line))
		{
			available = true;
			num = std::stoi(line.substr(lineStart, bookID)); //Get the number of the book from the line
			name = line.substr(bookID, line.length() - bookID - (line.length() - line.find("¤"))); //get the name from the file
			card = std::stoi(line.substr(line.find("~") +1 , personID));	//Get the card number of the person who borrowed the book
			std::cout << line.substr(line.find("¤")+1, 1);
			if (line.substr(line.find("¤") + 1, 1) == "N")
			{
				available = false;
			}
			bookRecs.emplace_back(name, num, available, card); //Constructs a "book" object inside bookRecs vector with the parameters received from the file line
		}
	}
	else 
	{
		std::cout << "Error: could not open the file. Please check the source folder to see if bookRecords.txt is present." << std::endl;
	}
	records.close();
}
void bookRecords::displayAll()
{
	std::string status;
	std::cout << "**HERE IS A LIST OF BOOKS IN THE LIBRARY**"<< "\n" << std::endl;
	for (auto i = bookRecs.begin(); i != bookRecs.end(); i++)
	{
		if (i->bookStatus() == false) 
		{
			status = "Not available";
			std::cout << status << "  " << i->getBookName() << "  " << "ID " << i->getBookNo() << "	" << "Borrowed by card No. " << i->getCardHolder() << "\n" << std::endl;
		}
	}
	for (auto i = bookRecs.begin(); i != bookRecs.end(); i++)
	{
		if(i ->bookStatus() == true)
		{
		status = "Available";
		std::cout << status << "  " << i->getBookName() << "  " << "ID " << i->getBookNo() << "\n" << std::endl;
		}

	}
}

void bookRecords::saveR()
{
	
	std::fstream records;
	records.open("bookRecords.txt", std::ios::out);
	if (records.is_open())
	{
		for (auto i = bookRecs.begin(); i != bookRecs.end(); i++)
		{
			if (i->bookStatus() == true)
			{
				records << i->getBookNo() << i->getBookName() << "¤A" << "~" << i->getCardHolder()<< std::endl;
			}
			else if (i->bookStatus() == false)
			{
				records << i->getBookNo() << i->getBookName() << "¤N" << "~" << i->getCardHolder() << std::endl;
			}

		}
	}
	else
	{
		std::cout << "Error: could not open the file. Please check the source folder to see if bookRecords.txt is present." << std::endl;
	}
	records.close();
	bookRecs.clear();
	std::cout << "**CURRENT RECORDS HAVE BEEN SAVED TO DISC**" << std::endl;
}
//BOOK RECORDS CLASS IMPLEMENTATIONS


//PERSON CLASS IMPLEMENTATION

//PERSON CLASS IMPLEMENTATION



//PERSON RECORDS CLASS IMPLEMENTATION------------------------------------------------------------------------------------------------------
personRecords::personRecords()
{
	int count = 0;
	std::string line;
	std::fstream records;
	records.open("personRecords.txt");
	if (records.is_open())
	{
		while (std::getline(records, line)) { count++; } //Counts how many line are in the file (1 person = 1 line) in order to determine how much memory to allocate for the vector
		pRecs.reserve(count + addBuffer);
		std::cout << "Cardholder records loaded." << std::endl;
	}
	else { std::cout << "Error: could not open the file. Please check the source folder to see if personRecords.txt is present." << std::endl; }
	records.close();
}

personRecords::~personRecords()
{
	std::cout << "PersonRecords destroyed" << std::endl;
}
void personRecords::load()
{
	std::string line;	//Sting for getting one line from the txt file
	std::string name;	//string for the name of the book
	int num;			//Integer for the number of the book
	bool available;
	std::fstream records;
	records.open("personRecords.txt");
	if (records.is_open())
	{

		while (std::getline(records, line))
		{
			num = std::stoi(line.substr(lineStart, personID)); //Get the number of the book from the line
			name = line.substr(personID, line.length() - bookID - (line.length() - line.find("¤"))); //get the name from the file
			if (line.substr(line.find("¤") + 1, 2) == "N")
			{
				available = false;
			}
			pRecs.emplace_back(name, num); //Constructs a "book" object inside bookRecs vector with the parameters received from the file line
		}
	}
	else
	{
		std::cout << "Error: could not open the file. Please check the source folder to see if bookRecords.txt is present." << std::endl;
	}
	records.close();
}
void personRecords::addPerson()
{
	std::string name;
	bool present = false;
	int num;
	std::cout << "Please enter the person's name: "; std::cin.ignore(); getline(std::cin, name); std::cout << "\n";
	std::cout << "please enter a 6-library card number: "; std::cin >> num;
	for(auto i = pRecs.begin(); i != pRecs.end(); i++)
	{
		if (i->getNum() == num)
		{
			present = true;
		}
	}
	if (present == false)
	{
		pRecs.emplace_back(name, num);
	}

	else
	{
		std::cout << "This library card number is already in use" << std::endl;
	}
}
void personRecords::displayAll()
{
	std::string status;
	std::cout << "**HERE IS A LIST OF LIBRARY VARD HOLDERS**"<< "\n" << std::endl;
	for (auto i = pRecs.begin(); i != pRecs.end(); i++)
	{
		std::cout << status << "  " << i->getName() << "  " << "Card No. " << i->getNum() << std::endl;
	}
}
void personRecords::saveR()
{
	std::fstream records;
	records.open("personRecords.txt", std::ios::out);
	for (auto i = pRecs.begin(); i != pRecs.end(); i++)
	{
		records << i->getNum() << i->getName() << std::endl;
	}
	pRecs.clear();
	records.close();
}
//PERSON RECORDS CLASS IMPLEMENTATION-------------------------------------------------------------------------

//OTHER FUNCTIONS--------------------------------------------------------------
void borrow_return(bookRecords& books, personRecords& people, bool borrow )
{
	int num;
	int cardNum;
	
	std::cout << "Please the user's 6-digit library card number: "; std::cin >> std::setw(personID) >> cardNum; std::cout << "\n";
	for (auto i = people.pRecs.begin(); i != people.pRecs.end(); i++)
	{
		if (cardNum == i->getNum())
		{
			std::cout << "Please enter the ID number of the book: "; std::cin >> std::setw(bookID) >> num;
			for (auto b = books.bookRecs.begin(); b != books.bookRecs.end(); b++)
			{

				if (b->bookStatus() == false && num == b->getBookNo() && borrow == true)
				{
					std::cout << "This book is currently not available" << std::endl;
				}
				else if (num == b->getBookNo() && borrow == true)
				{
					b->changeStatus(false);
					b->changeHolder(cardNum);
				}
				else if (b->bookStatus() == false && num == b->getBookNo() && borrow == false)
				{
					b->changeStatus(true);
					b->changeHolder(0);
				}
				else if (b->bookStatus() == true && num == b->getBookNo() && borrow == true)
				{
					std::cout << "The book with said number has not been borrowed" << std::endl;
				}

				else
				{
					std::cout << "No such book in the library" << std::endl;
				}
			}
		}

		else
		{
			std::cout << "No cardholder with that number exists. Please register the card holder." << std::endl;
		}
	}
}

const int input(int limit)
{
	int input;
	int count = 0;
	while ((input = getchar()) != && count < limit);
	{
		count++;
	}

	return input;
}
//OTHER FUNCTIONS--------------------------------------------------------------