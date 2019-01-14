#include "pch.h"
#include "classes.h"


//BOOK RECORDS CLASS IMPLEMENTATIONS
bookRecords::bookRecords()	//Constructor goes through txt file and, line by line, adds each book to the vector bookRecords
{	
	int count = 0;
	std::string line;
	std::fstream records;
	records.open("bookRecords.txt");
	if (records.is_open())
	{
		while (std::getline(records, line)) { count++; } //Counts how many line are in the file (1 book = 1 line) in order to determine how much memory to allocate for the vector
		bookRecs.reserve(count + addBuffer);	//reserves memory for vector in accordance with how many books (line in the txt file) are in the file
	}
	else { std::cout << "Error: could not open the file. Please check the source folder to see if bookRecords.txt is present." << std::endl; }
	records.close();
}


//FUNCTION FOR ADDING A NEW BOOK TO THE VECTOR
void bookRecords::addBook()
{
	std::string name;
	bool present = false;
	int num;
	std::cout << "Please enter the book's name: "; std::cin.ignore(); getline(std::cin, name); std::cout << "\n";
	std::cout << "Please enter a 5-digit number to identify the book: "; num = limitedInput(bookID);
	for (auto i = bookRecs.begin(); i != bookRecs.end(); i++)
	{
		if (i->getBookNo() == num) { present = true; } //Checks whether or not the book is present in the vector
	}

	if (present == true) { std::cout << "ERROR: A book with this number is already in the library. Please enter a different number." << std::endl; }
	else { bookRecs.emplace_back(name, num, true, ZERO, ZERO, ZERO); std::cout << "Book added" << std::endl; } //Emplaces (constructs) a book in the vector with the given parameters

	std::cout << "\n" << "Press any key to continue"; std::cin.ignore(); std::cin.get();
}

//FUNCTION FOR LOADING ALL THE BOOKS FROM THE TXT FILE TO THE VECTOR
void bookRecords::load()
{	
	std::string line;	//Sting for getting one line from the txt file
	std::string name;	//string for the name of the book
	int dueM = 0;
	int dueD = 0;
	int num = 0;			//Integer for the number of the book
	int card = 0;			//integer for the library card (if the book is borrowed by someone)
	bool available;
	std::fstream records; 
	records.open("bookRecords.txt");
	if (records.is_open())
	{
		while (std::getline(records, line))
		{
			available = true;
			num = std::stoi(line.substr(ZERO, bookID)); //Get the number of the book from the line
			name = line.substr(bookID, line.length() - bookID - (line.length() - line.find("¤"))); //get the name from the file
			card = std::stoi(line.substr(line.find("~") +1 , personID));	//Get the card number of the person who borrowed the book
			dueD = std::stoi(line.substr(line.find("*")+1, line.find("¨") - line.find("*")));//Get the return day from the txt file. Located between the * and ¨ indicators
			dueM = std::stoi(line.substr(line.find("¨")+1, 3)); //Get the return month from the txt file
			if (line.substr(line.find("¤") + 1, 1) == "N")
			{
				available = false;
			}
			bookRecs.emplace_back(name, num, available, card, dueD, dueM); //Constructs a "book" object inside bookRecs vector with the parameters received from the file line
		}
	}
	else {std::cout << "Error: could not open the file. Please check the source folder to see if bookRecords.txt is present." << std::endl;}
	std::cout << "BOOK RECORDS LOADED" << "\n" << std::endl;
	records.close();
}

//FUNCTION FOR DISPLAYING ALL THE BOOKS IN THE CURRENT RECORDS (VECTOR)
void bookRecords::displayAll()
{
	std::string status;
	std::cout << "**HERE IS A LIST OF BOOKS IN THE LIBRARY**"<< "\n" << std::endl;

	for (auto i = bookRecs.begin(); i != bookRecs.end(); i++)	//Loop that displays all the books that aren't available (loaned out). Also prints put the card that it was loaned out to
	{
		if (i->bookStatus() == false) 
		{
			status = "Not available";
			std::cout << status << std::setw(WIDTH_2) << i->getBookName() << std::setw(WIDTH_1)<< "ID: " << i->getBookNo() << std::setw(WIDTH_1) << "Borrowed by " << i->getCardHolder() << std::setw(WIDTH_1) << "Return due: " << i->getDueDay() << "th of " << getMonth(i->getDueMonth()) << std::endl;
		}
	}
	std::cout << "\n" << std::endl;
	for (auto i = bookRecs.begin(); i != bookRecs.end(); i++) //Second loop displays all the book that are available
	{
		if(i ->bookStatus() == true)
		{
		status = "Available";
		std::cout << status << std::setw(WIDTH_1) << i->getBookName() << std::setw(WIDTH_1) << "ID: " << i->getBookNo() << std::endl;
		}
	}
	
	std::cout <<"\n"<< "Press any key to continue"; std::cin.ignore(); std::cin.get();
}

//FUNCTION FOR SAVING THE CURRENT RECORDS(VECTOR) TO TXT FILE
void bookRecords::saveR()
{
	
	std::fstream records;
	records.open("bookRecords.txt", std::ios::out);
	if (records.is_open())
	{
		for (auto i = bookRecs.begin(); i != bookRecs.end(); i++) //Loop that checks whther the book is available or not, at saves with the appropriate indicator (for accurate loading)
		{
			if (i->bookStatus() == true) {records << i->getBookNo() << i->getBookName() << "¤A" << "~" << i->getCardHolder() << "*" << i-> getDueDay() << "¨" << i->getDueMonth()<< std::endl;}
			else if (i->bookStatus() == false) {records << i->getBookNo() << i->getBookName() << "¤N" << "~" << i->getCardHolder() << "*" << i->getDueDay() << "¨" << i->getDueMonth() << std::endl;
			}
		}
		bookRecs.clear();
	}
	else {std::cout << "ERROR: could not open the file. Please check the source folder to see if bookRecords.txt is present." << std::endl;}
	records.close();
	std::cout << "**CURRENT RECORDS HAVE BEEN SAVED TO DISC**" << std::endl;
	std::cout << "\n" << "Press any key to continue"; std::cin.ignore(); std::cin.get();
}

void bookRecords::find()	//FUNCTION FOR CHECKING WHETHER A BOOK WITH A GIVEN NUMBER IS IN THE LIBRARY
{
	int input;
	bool found = false;
	std::string status;
	std::cout << "Please enter the book ID number of the title you would like to check: "; 	input = limitedInput(bookID);
	for (auto i = bookRecs.begin(); i != bookRecs.end(); i++)
	{
		if (input == i->getBookNo())
		{ 
			if (i->bookStatus() == true) { status = "Available"; }
			else { status = "Not available"; }
			std::cout << "Book found: " << i->getBookName() << std::setw(WIDTH_1) << status << std::endl; found = true;
		}
	}
	
	if (found == false) { std::cout << "ERROR: Could not find book with the given number." << std::endl; }
	std::cout << "\n" << "Press any key to continue"; std::cin.ignore(); std::cin.get();
	
}


void bookRecords::clear()
{
	std::string input;
	std::cout << "WARNING: You are about to clear all currently loaded book records. Unsaved changes will be lost." << "\n" << "Are you sure you want to continue? y/n?" << std::endl;
	std::cin >> input;
	if (input == "y") { bookRecs.clear(); std::cout << "RECORDS CLEARED" << std::endl; }
	std::cout << "\n" << "Press any key to continue"; std::cin.ignore(); std::cin.get();
}
//BOOK RECORDS CLASS IMPLEMENTATIONS--------------------------------------------------------------------------------------------------------






//PERSON RECORDS CLASS IMPLEMENTATION------------------------------------------------------------------------------------------------------
personRecords::personRecords() //Constructor that count how many people are in the txt file and allocates memory accordingly
{
	int count = 0;
	std::string line;
	std::fstream records;
	records.open("personRecords.txt");
	if (records.is_open())
	{
		while (std::getline(records, line)) { count++; } //Counts how many line are in the file (1 person = 1 line) in order to determine how much memory to allocate for the vector
		pRecs.reserve(count + addBuffer); //Reserves memory + buffer (for adding more people after the vector is loaded)
	}
	else { std::cout << "ERROR: could not open the file. Please check the source folder to see if personRecords.txt is present." << std::endl; }
	records.close();
}


void personRecords::load()
{
	std::string line;	//Sting for getting one line from the txt file
	std::string name;	//string for the name of the book
	int num;			//Integer for the number of the book
	std::fstream records;
	records.open("personRecords.txt");
	if (records.is_open())
	{

		while (std::getline(records, line))
		{
			num = std::stoi(line.substr(ZERO, personID)); //Get the number of the book from the line
			name = line.substr(personID, line.length() - personID - (line.length() - line.find("¤"))); //get the name from the file
			
		
			pRecs.emplace_back(name, num); //Constructs a "book" object inside bookRecs vector with the parameters received from the file line
		}
		std::cout << "LIBRARY CARD HOLDER RECORDS LOADED" << "\n"<< std::endl;
	}
	else {std::cout << "ERROR: could not open the file. Please check the source folder to see if personRecords.txt is present." << std::endl;}
	
	records.close();
}

void personRecords::addPerson()
{
	std::string name;
	bool present = false;
	int num;
	std::cout << "Please enter the person's name: "; std::cin.ignore(); getline(std::cin, name); std::cout << "\n";
	std::cout << "please enter a 6-library card number: "; num = limitedInput(personID);
	for(auto i = pRecs.begin(); i != pRecs.end(); i++)
	{
		if (i->getNum() == num) {present = true;} //SET present BOOL TO TRUE (SINGNIFYING THAT LIBRARY CARD NUMBER IS ALREADY IN USE)
	}

	if (present == false) {pRecs.emplace_back(name, num);} //IF present BOOL IS FALSE, THAT MEANS THE LIBRARY CARD NUMBER IS NOT IN USE AND THE PERSON CAN BE ADDED TO THE RECORDS
	else {std::cout << "ERROR: This library card number is already in use" << std::endl;}
	std::cout << "\n" << "Press any key to continue"; std::cin.ignore(); std::cin.get();
}

void personRecords::displayAll()
{
	std::string status;
	std::cout << "**HERE IS A LIST OF LIBRARY CARD HOLDERS**"<< "\n" << std::endl;
	for (auto i = pRecs.begin(); i != pRecs.end(); i++)
	{
		std::cout << status << std::setw(WIDTH_1) << i->getName() << std::setw(WIDTH_1) << "ID:" << i->getNum() << std::endl;
	}

	std::cout << "\n" << "Press any key to continue"; std::cin.ignore(); std::cin.get();
}

void personRecords::saveR() 
{
	std::fstream records;
	records.open("personRecords.txt", std::ios::out);
	if (records.is_open())
	{
		for (auto i = pRecs.begin(); i != pRecs.end(); i++)
		{
			records << i->getNum() << i->getName() << std::endl;
		}
		pRecs.clear();
	}
	
	else { std::cout << "ERROR: could not open the file. Please check the source folder to see if personRecords.txt is present." << std::endl; }
	records.close();
	std::cout << "\n" << "Press any key to continue"; std::cin.ignore(); std::cin.get();
}

void personRecords::find() //Searches for person in pRecs by library card number
{
	int input;
	bool found = false;
	std::string status;
	std::cout << "Please enter the 6-digit library card number of the the person you would like to check: "; 	input = limitedInput(personID);
	for (auto i = pRecs.begin(); i != pRecs.end(); i++)
	{
		if (input == i->getNum())
		{
			std::cout << "Library card holder found: " << i->getNum() << std::setw(WIDTH_1) << i->getName()<< std::endl; found = true;
		}
	}

	if (found == false) { std::cout << "ERROR: Could not find person with the given number." << std::endl; }
	std::cout << "\n" << "Press any key to continue"; std::cin.ignore(); std::cin.get();
}

void personRecords::clear()
{
	std::string input;
	std::cout << "WARNING: You are about to clear all currently loaded library card holder records. Unsaved changes will be lost."<< "\n" << "Are you sure you want to continue? y/n?" << std::endl;
	std::cin >> input;
	if (input == "y") { pRecs.clear(); std::cout << "RECORDS CLEARED" << "\n" << std::endl; }
	std::cout << "\n" << "Press any key to continue"; std::cin.ignore(); std::cin.get();
}
//PERSON RECORDS CLASS IMPLEMENTATION-------------------------------------------------------------------------






//OTHER FUNCTIONS--------------------------------------------------------------
void borrow_return(bookRecords& books, personRecords& people, bool borrow) //FUNCTION FOR BORROWING AND RETURNING BOOKS. tAKES IN THE 2 RECORDS OBJECTS AND A BOOLEAN THAT DETERMINES WHETHER THE USER IS BORROWING OR RETURNING A BOOK
{
	int num;
	int cardNum;
	int message = 0;
	//Variables for getting the current time
	time_t now = time(0);
	tm *dt = localtime(&now);
	std::cout << "\n"<<"**BOOKS ARE BORROWED FOR A MONTH (30 DAYS) AT A TIME**" << "\n" << std::endl;
	std::cout << "Please the user's 6-digit library card number: "; cardNum = limitedInput(personID); std::cout << "\n";
	for (auto i = people.pRecs.begin(); i != people.pRecs.end(); i++) //Function first goes through the person records and check if the inputted library card number exists
	{
		if (cardNum == i->getNum()) //Executes if number is found
		{
			std::cout << "Please enter the ID number of the book: "; num = limitedInput(bookID);
			for (auto b = books.bookRecs.begin(); b != books.bookRecs.end(); b++) // Function the asks for book ID number and searches book records to check if the book is present
			{
				if (num == b->getBookNo() && borrow == true)
				{
					b->changeStatus(false, cardNum, dt->tm_mday, dt->tm_mon + 1); //When book is borrowed: set it unavailable, attach library card number, set return day, set return month
					std::cout << b->getBookName() << " was borrowed. Return on " << dt->tm_mday << "th of " << getMonth(dt->tm_mon + MONTH) << std::endl;
				}
				else if (b->bookStatus() == false && num == b->getBookNo() && borrow == false) //If the user is returning a book, the function changes it's status to available and resets all the data concerning the person who borrowed it
				{
					b->changeStatus(true, ZERO, ZERO, ZERO);
					std::cout << "Book successfully returned" << std::endl;
				}

			}
		}
	}
	
	std::cout << "\n" << "Press any key to continue"; std::cin.ignore(); std::cin.get();
}

//FUNCTION FOR INPUTING THE USER CARD NUMBER OR BOOK ID NUMBER. THE limit PARAMETER DEFINE HOW MANY DIGITS THE PERSON CAN INPUT. THIS IS TO AVOID ISSUES WITH DIFFERENT SIZES OF NUMBERS, BECAUSE IT MESSES WITH LOADING AND SAVING TO TXT FILE
const int limitedInput(unsigned int limit)
{
	bool valid = false;
	std::string check;
	
	do //Loop takes cin to a string and checks whether the length of the string goes below or above the limit, in which case it gives an error and asks the user to input the correct number of digits
	{
		std::cin >> check;
		if (check.length() != limit) 
		{ 
			if (check.length() > limit) { std::cout << "ERROR: number is too long. Please enter a "<< limit << "-digit number"<< std::endl;  }
			else if (check.length() < limit) { std::cout << "ERROR: number is too short. Please enter a "<< limit <<"-digit number." << std::endl; }
		}
		else { valid = true; }
	} while (valid == false);
	
	return std::stoi(check); //Returns a converted to int value
}

const std::string getMonth(int month)
{
	std::string months[MONTHS] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	return months[month];
}
//OTHER FUNCTIONS--------------------------------------------------------------