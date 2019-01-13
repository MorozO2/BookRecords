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
		std::cout << "Book records loaded." << std::endl;
	}
	else { std::cout << "Error: could not open the file. Please check the source folder to see if bookRecords.txt is present." << std::endl; }
	records.close();
}


//FUNCTION FOR ADDING A NEW BOOK TO THE VECTOR
void bookRecords::addBook()
{
	std::string name;
	bool present;
	int num;
	std::cout << "Please enter the book's name: "; std::cin.ignore(); getline(std::cin, name); std::cout << "\n";
	std::cout << "Please enter a 5-digit number to identify the book: "; num = input(bookID);
	for (auto i = bookRecs.begin(); i != bookRecs.end(); i++)
	{
		if (i->getBookNo() == num) { present = true; } //Checks whether or not the book is present in the vector
	}

	if (present == true) { std::cout << "A book with this number is already in the library. Please enter a different number." << std::endl; }
	else { bookRecs.emplace_back(name, num, true); std::cout << "Book added" << std::endl; } //Emplaces (constructs) a book in the vector with the given parameters

	std::cout << "Press any key to continue: "; std::cin.ignore(); std::cin.get();
}

//FUNCTION FOR LOADING ALL THE BOOKS FROM THE TXT FILE TO THE VECTOR
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
			if (line.substr(line.find("¤") + 1, 1) == "N")
			{
				available = false;
			}
			bookRecs.emplace_back(name, num, available, card); //Constructs a "book" object inside bookRecs vector with the parameters received from the file line
		}
	}
	else {std::cout << "Error: could not open the file. Please check the source folder to see if bookRecords.txt is present." << std::endl;}
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
			std::cout << status << "  " << i->getBookName() << "  " << "ID " << i->getBookNo() << "	" << "Borrowed by card No. " << i->getCardHolder() << "\n" << std::endl;
		}
	}
	for (auto i = bookRecs.begin(); i != bookRecs.end(); i++) //Second loop displays all the book that are available
	{
		if(i ->bookStatus() == true)
		{
		status = "Available";
		std::cout << status << "  " << i->getBookName() << "  " << "ID " << i->getBookNo() << "\n" << std::endl;
		}
	}
	std::cout << "Press any key to continue: "; std::cin.ignore(); std::cin.get();
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
			if (i->bookStatus() == true) {records << i->getBookNo() << i->getBookName() << "¤A" << "~" << i->getCardHolder()<< std::endl;}
			else if (i->bookStatus() == false) {records << i->getBookNo() << i->getBookName() << "¤N" << "~" << i->getCardHolder() << std::endl;}
		}
	}
	else {std::cout << "Error: could not open the file. Please check the source folder to see if bookRecords.txt is present." << std::endl;}
	records.close();
	bookRecs.clear();
	std::cout << "**CURRENT RECORDS HAVE BEEN SAVED TO DISC**" << std::endl;
	std::cout << "Press any key to continue"; std::cin.ignore(); std::cin.get();
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
		std::cout << "Cardholder records loaded." << std::endl;
	}
	else { std::cout << "Error: could not open the file. Please check the source folder to see if personRecords.txt is present." << std::endl; }
	records.close();
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
	std::cout << "please enter a 6-library card number: "; num = input(personID);
	for(auto i = pRecs.begin(); i != pRecs.end(); i++)
	{
		if (i->getNum() == num) {present = true;} //SET present BOOL TO TRUE (SINGNIFYING THAT LIBRARY CARD NUMBER IS ALREADY IN USE)
	}

	if (present == false) {pRecs.emplace_back(name, num);} //IF present BOOL IS FALSE, THAT MEANS THE LIBRARY CARD NUMBER IS NOT IN USE AND THE PERSON CAN BE ADDED TO THE RECORDS
	else {std::cout << "This library card number is already in use" << std::endl;}
	std::cout << "Press any key to continue"; std::cin.ignore(); std::cin.get();
}

void personRecords::displayAll()
{
	std::string status;
	std::cout << "**HERE IS A LIST OF LIBRARY VARD HOLDERS**"<< "\n" << std::endl;
	for (auto i = pRecs.begin(); i != pRecs.end(); i++)
	{
		std::cout << status << "  " << i->getName() << "  " << "Card No. " << i->getNum() << std::endl;
	}

	std::cout << "Press any key to continue"; std::cin.ignore(); std::cin.get();
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
	std::cout << "Press any key to continue"; std::cin.ignore(); std::cin.get();
}
//PERSON RECORDS CLASS IMPLEMENTATION-------------------------------------------------------------------------

//OTHER FUNCTIONS--------------------------------------------------------------
void borrow_return(bookRecords& books, personRecords& people, bool borrow) //FUNCTION FOR BORROWING AND RETURNING BOOKS. tAKES IN THE 2 RECORDS OBJECTS AND A BOOLEAN THAT DETERMINES WHETHER THE USER IS BORROWING OR RETURNING A BOOK
{
	int num;
	int cardNum;
	int message = 0;
	
	std::cout << "Please the user's 6-digit library card number: "; cardNum = input(personID); std::cout << "\n";
	for (auto i = people.pRecs.begin(); i != people.pRecs.end(); i++)
	{

		if (cardNum == i->getNum())
		{
			std::cout << "Please enter the ID number of the book: "; num = input(bookID);
			for (auto b = books.bookRecs.begin(); b != books.bookRecs.end(); b++)
			{

				if (b->bookStatus() == false && num == b->getBookNo() && borrow == true)
				{
					message = 2; goto error_message;
				}
				else if (num == b->getBookNo() && borrow == true)
				{
					b->changeStatus(false);
					b->changeHolder(cardNum);
					std::cout << b->getBookName() << " was borrowed. Return in " << DUE_DATE << " days." << std::endl;
				}
				else if (b->bookStatus() == false && num == b->getBookNo() && borrow == false)
				{
					b->changeStatus(true);
					b->changeHolder(0);
					std::cout << "Book successfully returned" << std::endl;
				}
				else if (b->bookStatus() == true && num == b->getBookNo() && borrow == true)
				{
					message = 3; goto error_message;
				}

				else { message = 4; goto error_message; }
			}
		}
		
		else { message = 1; goto error_message; }
	}
	error_message:
	if(message == 1) { no_card:  std::cout << "No cardholder with that number exists. Please register the card holder." << std::endl; }
	else if(message == 2) {not_available:  std::cout << "This book is currently not available" << std::endl; }
	else if(message == 3) {not_borrowed: std::cout << "The book with said number has not been borrowed" << std::endl; }
	else if(message == 4) {not_present: std::cout << "This book is not in the library" << std::endl; }
	
	std::cout << "Press any key to continue"; std::cin.ignore(); std::cin.get();
}

//FUNCTION FOR INPUTING THE USER CARD NUMBER OR BOOK ID NUMBER. THE limit PARAMETER DEFINE HOW MANY DIGITS THE PERSON CAN INPUT. THIS IS TO AVOID ISSUES WITH DIFFERENT SIZES OF NUMBERS, BECAUSE IT MESSES WITH LOADING AND SAVING TO TXT FILE
const int input(unsigned int limit)
{
	bool valid = false;
	std::string check;
	
	do //Loop takes cin to a string and checks whether the length of the string goes below or above the limit, in which case it gives an error and asks the user to input the correct number of digits
	{
		std::cin >> check;
		if (check.length() != limit) 
		{ 
			if (check.length() > limit) { std::cout << "Error: number is too long. Please enter a "<< limit << "-digit number"<< std::endl; valid = false; }
			else if (check.length() < limit) { std::cout << "Error: number is too short. Please enter a "<< limit <<"-digit number." << std::endl; valid = false; }
		}
		else { valid = true; }
	} while (valid == false);
	
	return std::stoi(check); //Returns a converted to int value
}
//OTHER FUNCTIONS--------------------------------------------------------------