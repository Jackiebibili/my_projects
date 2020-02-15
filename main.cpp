/*
******************************************
***The Theatre Ticket Reservation System**
*Author    : Jingxi Li (NetID: jxl180095)*
*Instructor: Mr. Jason Smith			 *
*Course    : CS 1337.008				 *
*Date      : 12 February 2020			 *
******************************************
*/
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<fstream>
#include<string>
#include<cmath>
#include<cctype>
using namespace std;

//global constants for different admission prices
const double priceAdult = 10.0;
const double priceChild = 5.0;
const double priceSenior = 7.5;
const string filename = "A1.txt";  //the copied file to read and edit for ticket reservations

//function prototypes
int promptMainMenu();
void colsRowsReadIn(fstream&, int&, int&);
void displaySimpSeatingChart(fstream&, int);
int seatSelectionUser(int, int, int&, int&, int&, int&, int&);
bool sequentialRegisterCheck(fstream&, int, int, int, int);
void registerSeats(fstream&, int, int, int, int, int, int);
bool alternativeSeats(fstream&, int, int, int, int&, int&);
bool insideFor(fstream&, int, int, int, int&, int&, int, bool);
void displayRecommendedSeats(int, int, int);
double totalSalesCalculate(fstream&, int&, int&, int&, int&);
void displayReport(int, int, int, int, int, double);
int filePtrPos(int, int, int);
int offsetPos(int, int);
void modify(int&, int);
void displayReal(fstream&, int);
bool digit(string);
bool alpha(string);


int main()
{
	//replicate the original text file

	/////////////////////////////////////////////////////////////////////////////////////////
	////////////////////          DO  NOT CHANGE CODE BELOW THIS               //////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	string temp, line;

	cout << "Enter File Name: ";
	cin >> temp;
	ifstream infile(temp);
	ofstream outfile(filename);
	if (infile)
		while (getline(infile, line))
			outfile << line << "\n";

	infile.close();
	outfile.close();

	/////////////////////////////////////////////////////////////////////////////////////////
	////////////////////          DO  NOT CHANGE CODE ABOVE THIS               //////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	cin.ignore(); //ignore a newline character in the buffer

	//declaration of variables
	char entry;
	int rows = 1, cols = 1, rowSelect = 1, colSelect = 1;
	int adults = 0, children = 0, seniors = 0, sumSeats = 0;
	int start = 1, end = 1;
	int totalAdults = 0, totalChidren = 0, totalSeniors = 0;
	int totalSeats = 0, totalSeatSold = 0;
	double totalSale = 0.0;
	fstream seatFile(filename, ios::in | ios::binary); //define a file stream and open it
	seatFile.close(); //file is always close in main 
	colsRowsReadIn(seatFile, rows, cols); //read in the number of cols and rows

	while (promptMainMenu() == 1) //display the menu and prompt the user to choose, 1 is to reserve and 2 is to exit
	{
		displayReal(seatFile, cols); //display the real seating chart to choose from

		//prompt the user to enter the details about the reservation and return -1 for invalid reservation (total #seats = 0)
		sumSeats = seatSelectionUser(rows, cols, rowSelect, colSelect, adults, children, seniors);
		if (sumSeats == -1)
		{
			cout << "total ticket number cannot be 0 or larger than available column\n";
			continue;
		}

		//check if the seat(s) can be sequentially register
		if (sequentialRegisterCheck(seatFile, cols, rowSelect, colSelect, sumSeats))
		{
			registerSeats(seatFile, cols, rowSelect, colSelect, adults, children, seniors); //if so, register for it
			cout << "seats are available and reserved\n";
		}
		else
		{
			cout << "seats not available\n";
			//check do we have alternative seating option along the designated row
			if (alternativeSeats(seatFile, rowSelect, cols, sumSeats, start, end))
			{
				displayRecommendedSeats(rowSelect, start, end); //if so, display the recommended seats
				cout << "Would you like to reserve the recommended seats\n";
				cout << "Y for yes and N for no\n";
				cin.get(entry);
				cin.ignore();
				if (entry == 'Y') //if yes, register for it
				{
					registerSeats(seatFile, cols, rowSelect, start, adults, children, seniors);
					cout << "seats confirmed\n";
				}
				else
				{
					cout << "no\n";
				}
			}
			else //if no recommended seats available, display an message
			{
				cout << "best seats - no seats available\n";
				continue;
			}
		}
	}

	//calculate the total sales
	totalSale = totalSalesCalculate(seatFile, totalAdults, totalChidren, totalSeniors, totalSeatSold); 

	//calculates the total seats in the auditorium
	totalSeats = rows * cols; 

	cout << "Report\n";
	//display the report about the details of sale
	displayReport(totalSeats, totalSeatSold, totalAdults, totalChidren, totalSeniors, totalSale);

	return 0;

}


/*
The promptMainMenu function prompts the user to enter the path he/she would like to go,
whether 1 for reservation or 2 for exit; and checks the validation of the user's input
*/
int promptMainMenu()
{
	string num;
	cout << "1. Reserve\n2. Exit\n";
	getline(cin, num);
	//ask to re-enter the choice when the length or property of the anwer is not valid
	while (!isdigit(num[0]) || num.length() != 1 || (num[0] != '1' && num[0] != '2'))
	{
		cout << "Incorrect input\n";
		cout << "Please enter a number either 1 or 2\n";
		getline(cin, num);
	}
	if (num[0] == '1')
		return 1;
	else
		return 2;
}


/*
The colsRowsReadIn function reads in the #cols and #rows in the file, assuming
each newline in the text file does not contains a carriage return '\r'
*/
void colsRowsReadIn(fstream& file, int& rows, int& cols)
{
	rows = 0;
	cols = 0;
	string l;
	string firstLine;
	file.open(filename, ios::in | ios::binary);
	file.seekg(0L, ios::beg);
	while (getline(file, l))
	{
		if (l == "")
			break;

		rows++;
	}
	file.clear();	
	file.seekg(0L, ios::beg); //direct to the beginning of the file
	getline(file, firstLine);
	cols = static_cast<int>(firstLine.length()); // if contains '\r', -1 to adjust
	file.close(); //always end with a close file in function
}


/*
This function displays the real arrangement of the seating chart in the
format of A, C, S, . in order for user to identify the location of seat
*/
void displayReal(fstream& file, int cols)
{
	char ch;
	int curCol = 1, curRow = 0;
	file.clear();
	file.open(filename, ios::in | ios::binary);
	file.seekg(0L, ios::beg);

	while (file.get(ch))
	{
		if (curCol > cols) //when reaching a new row, add a newline
		{
			curRow++;
			curCol = 1;
			cout << endl;
		}
		if (ch == 'A' || ch == 'C' || ch == 'S') //when encountering occupied seats, display its status
		{
			cout << ch;
			curCol++;
		}
		else if (ch == '.') //when reaching vacant seats, display dots
		{
			cout << ".";
			curCol++;
		}
	}
	file.close(); //always end with a close file in function
	cout << endl;
}


/*
This function displays the simplified form of the seating chart in
the combination of pound keys and dots 
*/
void displaySimpSeatingChart(fstream& file, int cols)
{
	char ch;
	int i;
	int curCol = cols + 1, curRow = 0;
	file.open(filename, ios::in | ios::binary);
	file.seekg(0L, ios::beg);

	//display the alphabets of the column number
	cout << "  ";
	for (i = 0; i < cols; i++)
		cout << static_cast <char>('A' + i);

	while (file.get(ch))
	{
		if (curCol > cols)
		{
			curRow++;
			curCol = 1;
			cout << endl; //when reaching a new row, add a newline
			cout << curRow << " "; //each row starts with the row # and spaces 
		}
		//if encountering reserved seats, display in terms of '#'
		if (ch == 'A' || ch == 'C' || ch == 'S')
		{
			cout << "#";
			curCol++;
		}
		//if encountering vacant seats, display in terms of '.'
		else if (ch == '.')
		{
			cout << ".";
			curCol++;
		}

	}
	file.close(); //always end with a close file in function
	cout << endl;
}


/*
This function is the input validation of integer with at least 2 digits long
It accepts the number in string as an argument and return true for valid
and false for invalid
*/
bool digit(string number)
{
	if (number == "")
		return false;
	for (int i = 0; i < number.length(); i++)
	{
		if (!isdigit(number[i]))
			return false;
	}
	return true;
}


/*
This function is the input valiation of all-uppercase alphabet with at least
2 digit long and accepts the string of alphabet as an argument and return
true for valid and false for invalid
*/
bool alpha(string str)
{
	if (str == "")
		return false;
	for (int i = 0; i < str.length(); i++)
	{
		if (!isupper(str[i]))
			return false;
	}
	return true;
}


/*
This function prompts the user to enter the details of the reservation,
validate them and returns the number of total tickets the user wanted 
to reserved or -1 for ticket number of 0
*/
int seatSelectionUser(int rows, int cols, int& rowSelect,
	int& colSelect, int& adults, int& children, int& seniors)
{
	int totalTickets;
	char seatLetter;
	string row_s, a, c, s;

	//prompt reserved row number 
	cout << "Enter the reserved row number: ";
	getline(cin, row_s);
	while (!digit(row_s) || rowSelect < 1 || rowSelect > rows)
	{
		cout << "Enter a valid row number since 1: ";
		getline(cin, row_s);
	}
	rowSelect = stoi(row_s);

	//prompt the column letter
	cout << "Enter the starting seat letter: ";
	cin.get(seatLetter);
	cin.ignore();
	while (!isupper(seatLetter) || seatLetter < 'A' || seatLetter >('A' + cols - 1))
	{
		cout << "Enter a valid starting seat letter since A: ";
		cin.get(seatLetter);
		cin.ignore();
	}
	colSelect = seatLetter - 'A' + 1;

	//prompt the number of adult tickets
	cout << "Enter the number of adult tickets: ";
	getline(cin, a);
	while (!digit(a) || adults < 0)
	{
		cout << "Enter a valid number of adult tickets since 0: ";
		getline(cin, a);
	}
	adults = stoi(a);

	//prompt the number of child tickets
	cout << "Enter the number of child tickets: ";
	getline(cin, c);
	while (!digit(c) || children < 0)
	{
		cout << "Enter a valid number of child tickets since 0: ";
		getline(cin, c);
	}
	children = stoi(c);

	//prompt the number of senior tickets
	cout << "Enter the number of senior tickets: ";
	getline(cin, s);
	while (!digit(s) || seniors < 0)
	{
		cout << "Enter a valid number of senior tickets since 0: ";
		getline(cin, s);
	}
	seniors = stoi(s);

	//if the #total seats is valid
	if (adults + children + seniors > 0 && adults + children + seniors <= cols)
		return adults + children + seniors;
	else//if invalid
		return -1;
}


/*
This function checks if the sequential reservation of all tickets is
possible and returns true for the ability to reserve and otherwise,
false.
*/
bool sequentialRegisterCheck(fstream& file, int cols,
	int startRow, int startCol, int numSeats)
{
	int i;
	char ch;
	file.open(filename, ios::in | ios::binary);
	for (i = startCol; i < startCol + numSeats; i++)
	{
		file.seekg(filePtrPos(startRow, cols, i), ios::beg);
		file.get(ch);
		if (ch != '.') //if at least one of the seats is not vacant, cannot have instant reservation performed
			return false;
	}
	file.close(); //always end with a close file in function
	return true; //successfully passing through the for loop means the ability to perform instant reservation
}


/*
This function modifies the content in the text file and reserve
the seats that the user chose
*/
void registerSeats(fstream& file, int cols, int startRow,
	int startCol, int numAdults, int numChildren, int numSeniors)
{
	int i;
	file.open(filename, ios::in | ios::out | ios::binary); //retain the content of the file

	file.seekp(filePtrPos(startRow, cols, startCol), ios::beg); //direct to the starting position of the first seat to reserve

	//priority: adults, children, and then senior, from left to to right
	for (i = 0; i < numAdults; i++)
	{
		file.put('A');
	}
	for (i = 0; i < numChildren; i++)
	{
		file << 'C';
	}
	for (i = 0; i < numSeniors; i++)
	{
		file << 'S';
	}
	file.close(); //always end with a close file in function
}


/*
This function performs the calculation of start and end position of
the alternative seats and return false for not found and true for found
Notice: parameter: rows is reserved #row and sr is the #total seats reserved 
*/
bool alternativeSeats(fstream& file, int rows, int cols, int sr, int& start, int& end)
{
	int i;
	for (i = 0; i <= (cols / (2 * sr)); i++)
	{
		if (insideFor(file, rows, cols, sr, start, end, i, true)) //jump the the right first from the center of the row
			return true;
		if (insideFor(file, rows, cols, sr, start, end, i, false)) //then jump to the left from the center of the row
			return true;
	}
	file.clear();
	return false;
}


/*
This function is the part inside the for loop of the function 
alternativeSeats and calculates the possible alternative seats
within the range of (2 * #total seats) each time

*/
bool insideFor(fstream& file, int rows, int cols, int sr, int& start, int& end, int i, bool change)
{
	int middle;
	//find the middle number in that row
	if (cols / 2 == 1)//if #row is odd, 
		middle = cols / 2 + 1;
	else
		middle = cols / 2; //if even #row, middle = the left one of the middle numbers
	int j, maxLength = 0, accum = 0;
	char ch;
	int upFlag = 0, lowFlag = 0; //lower bound and upper bound
	file.open(filename, ios::in | ios::binary);

	if (change) //if true, set the file pointer (jump to the right)
	{
		file.clear();
		file.seekg(filePtrPos(rows, cols, middle) + offsetPos(i, sr), ios::beg);
	}
	else //if false, set the file pointer (jump to the left)
	{
		file.clear();
		file.seekg(filePtrPos(rows, cols, middle) - offsetPos(i, sr), ios::beg);
	}

	file.get(ch);
	//if found a vacant seats means the possibility of seats in a row within the range of (2 * #total seats)
	if (ch == '.')
	{
		//set the upper bound
		if (change)
			upFlag = offsetPos(i, sr);
		else
			upFlag = (-1) * offsetPos(i, sr);
		//set the lower bound
		if (i != cols / (2 * sr))
		{
			lowFlag = upFlag - sr;
			upFlag += sr;
		}
		else if (upFlag > 0)
		{
			lowFlag = upFlag - sr;
			upFlag = cols - middle;
			if (cols % 2 == 0)
				upFlag++;
		}
		else//upFlag < 0
		{
			lowFlag = middle - cols;
			upFlag += sr;
			if (cols % 2 == 0)
				lowFlag++;
		}
		accum = 0;
		//search through the range to see if a possible row of seats are vacant
		for (j = lowFlag; j <= upFlag; j++)
		{
			file.seekg((filePtrPos(rows, cols, middle) + j), ios::beg);
			file.get(ch);
			if (ch == '.')
			{
				accum++; //if found one vacant seat, increment it
				//find the maximum number of seats that are vacant
				if (maxLength < accum)
				{
					maxLength = accum;
					end = j;
				}
			}
			else //if the vacant seats are not consequtive, start again the increment from 0
			{
				accum = 0;
			}
		}
		//if the vacant seats in a row is not less than the #total seats reserved, alternative seats are available
		if (maxLength >= sr)
		{
			//if the alternative seats somewhat overlap with the middle number
			if (lowFlag < 0 && lowFlag >= -sr && upFlag > 0 && upFlag <= sr)
			{
				start = end - maxLength + 1;
				if (abs(start) == sr && end == sr) //if all spaces in the range are available, choose the centeral part in a row

				{
					end = sr / 2;
					start = end - sr + 1;
					modify(start, middle);
					modify(end, middle);
					file.close();
					return true;
				}
				else if (abs(start) <= 0.5 * sr) //left side of center is shorter than the right part--lean right
				{
					end = sr + start - 1; //start part is justified
					modify(start, middle);
					modify(end, middle);
					file.close();
					return true;
				}
				else if(abs(start) > 0.5 * sr) //left side of center is longer than the right part--lean left
				{
					start = end - sr + 1; //end part is justified
					modify(start, middle);
					modify(end, middle);
					file.close();
					return true;
				}
				/*
				else
				{
					start = start + (abs(start) + end) - sr;
					end = start + sr - 1;
					modify(start, middle);
					modify(end, middle);
					file.close();
					return true;
				}*/
			}
			else //alternative seats are either fully lean left or right
			{
				if (end > 0)//lean to the right
				{
					start = end - maxLength + 1; //start part justified
					end = start + sr - 1;
					modify(start, middle);
					modify(end, middle);
					file.close();
					return true;
				}
				else//lean to the left
				{
					start = end - sr + 1; //end part justified
					modify(start, middle);
					modify(end, middle);
					file.close();
					return true;
				}
			}
		}

	}
	file.close(); //always end with a close file in function
	return false; //means seats in this range are not available
}

/*
This function displays the recommended seats in the format of An - Am
*/
void displayRecommendedSeats(int rowSelect, int start, int end)
{
	cout << "best available is ";
	if (start == end)
	{
		cout << rowSelect << static_cast<char>('A' + start - 1) << endl;
	}
	else
	{
		cout << rowSelect << static_cast <char>('A' + start - 1) << " - " << rowSelect << static_cast <char>('A' + end - 1) << endl;
	}
}


/*
This function calculates the total sales from the tickets sold and returns it
*/
double totalSalesCalculate(fstream& file, int& sumAdults, int& sumChildren,
	int& sumSeniors, int& seatSold)
{
	char ch;
	file.open(filename, ios::in | ios::binary);
	file.seekg(0L, ios::beg);
	while (file.get(ch))
	{
		if (ch == 'A')
			sumAdults++;
		else if (ch == 'C')
			sumChildren++;
		else if (ch == 'S')
			sumSeniors++;
	}
	file.close();
	seatSold = sumAdults + sumChildren + sumSeniors;
	return sumAdults * priceAdult + sumChildren * priceChild + sumSeniors * priceSenior;
}


/*
This function displays the report of the sales of ticket for
a particulat auditorium
*/
void displayReport(int sumSeats, int sumSold, int sumAdult, int sumChildren,
	int sumSeniors, double totalSale)
{
	cout << "Total Seats\t" << sumSeats << endl;
	cout << "Total Tickets\t" << sumSold << endl;
	cout << "Adult Tickets\t" << sumAdult << endl;
	cout << "Child Tickets\t" << sumChildren << endl;
	cout << "Senior Tickets\t" << sumSeniors << endl;
	cout << fixed << showpoint << setprecision(2);
	cout << "Total Sales\t" << "$" << totalSale << endl;
}


/*
This function calculate the file pointer position from the beginning
of file by using #row, #column, and #current column in the designated row
*/
int filePtrPos(int r, int c, int curCol)
{
	return ((r - 1) * (c + 1) + curCol - 1);
}


/*
This function calculates the length of jump from the center of the row, 
which is the offset number originated from the center and returns it
*/
int offsetPos(int counter, int numSeatReserved)
{
	return (numSeatReserved * counter);
}


/*
This function modifies the number of current column in a designated row
by applying a offset from the center of the row
*/
void modify(int& x, int center)
{
	x = center + x;
}

