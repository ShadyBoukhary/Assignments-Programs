/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*								 Shady Boukhary									*
*					 CMPS 2132 Object-Oriented Programming						*
*							   Dr. Stringfellow									*
*						HW2: SpaceAst, due October 4th							*
*																				*
*		 This program reads data about the locations and sizes of				*
*		 asteroids in space, asks the user to input a starting position			*
*		 for a spaceship that collects these asteroids. The program				*
*		 makes the spaceship collect a user-specified number of asteroids		*
*		 in order of nearest to farthest, given that the asteroid is less		*
*		 than a user-specified maximum size. Then, the program prints to		*
*		 the console and an output file which asteroid were collected and		*
*		 in what order, their sizes, the distance the spaceship travelled		*
*		 to each asteroid, the asteroids original positions, the total			*
*		 distance travelled, the total size and the total number of				*
*								asteroids collected.							*
*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include "SpaceShip.h"

using namespace std;

// prototypes
void promptData(int&, double&, SpaceShip&);
void openFiles(ifstream&, ofstream&);
void readFile(ifstream&, AsteroidList&, SpaceShip&);
void printHeader(ofstream&, const SpaceShip&);
int collectNearest(AsteroidList&, SpaceShip&, double, double&, int&, int&);
void printAstReport(ofstream&, int, int, int, const AsteroidList&, double);
void printTotals(ofstream&, const SpaceShip&);
void closeFiles(ifstream&, ofstream&);

int main()
{
	// declare variables
	int collected, numRequired, astX = 0, astY = 0;
	// prevDistance to add to distance if asteroid was broken up
	double maxSize = 0, distance = 0;
	// declare objects
	AsteroidList astList;
	SpaceShip spaceShip;

	ifstream infile;
	ofstream outfile;
	// open files
	openFiles(infile, outfile);

	// request some data from the user
	promptData(numRequired, maxSize, spaceShip);

	// read the input file and insert asteroids 
	readFile(infile, astList, spaceShip);

	// print header 
	printHeader(outfile, spaceShip);

	// collect and print report of each asteroid 
	for (int x = 0; x < numRequired; x++)
	{
		collected = collectNearest(astList, spaceShip, maxSize, distance, astX, astY);
		printAstReport(outfile, collected, astX, astY, astList, distance);
		distance = astX = astY = 0;
	}
	// print total distance, size, and number
	printTotals(outfile, spaceShip);
	// close all files
	closeFiles(infile, outfile);
	system("pause");
	return 0;
}
/****************************************
*			promptData()				*
* prompts user for general requirements	*
* param: int, double, Spaceship			*
* return: none							*
*****************************************/
void promptData(int& numRequired, double & maxSize, SpaceShip & spaceShip)
{
	char choice;
	int x, y;
	// get required number of asteroids
	cout << "How many Asteroids would you like the spaceship to collect? ";
	cin >> numRequired;
	// get the maximum size the ship can collect
	cout << "What is the maximum size of asteroid the spaceship can collect? ";
	cin >> maxSize;
	// give the option of specifying a starting position for the ship
	cout << "Would you like to enter a custom starting position for the "
		<< "spaceship? (Y for yes): ";
	cin >> choice;


	// if hte user wants a custom starting position
	if (toupper(choice) == 'Y')
	{
		cout << "Please enter the x and y coordinates for the spaceship: ";
		cin >> x >> y;
		// set position for spaceship
		spaceShip.setPosition(x, y);
	}

}
/****************************************
*				openFiles()				*
* asks user for file names, opens files	*
* param: ifstream, ofstream				*
* return: none							*
*****************************************/
void openFiles(ifstream& infile, ofstream& outfile)
{
	// variables
	char choice;
	string input, output;
	cout << "**********SHADY BOUKHARY**********\n\n";
	// prompt for input and output file names
	cout << "Would you like to enter the names of input/output files?: (Y/N) ";
	cin >> choice;
	// if users wants to enter names
	if (toupper(choice) == 'Y')
	{
		// get file names
		cout << "Enter the name of the input file: ";
		cin.ignore();
		getline(cin, input);
		cout << "Enter the name of the output file: ";
		getline(cin, output);
		// convert string to cstring and open files
		infile.open(input.c_str());
		outfile.open(output.c_str());
		// if files have failed to open
		if (!(infile && outfile))
		{
			cout << "Failed to open files.\n"
				<< "Terminating...\n";
			system("pause");
			exit(1);
		}
	}
	// use default names if user chooses not to
	else
	{
		infile.open("data.dat");
		outfile.open("output.dat");
	}
}

/****************************************
*				readFile()				*
* reads positions and sizes of			*
* from input file and inserts them into *
* the AsteroidList object				*
* param: ifstream, AsteroidList,		*
* SpaceShip								*
* return: none							*
*****************************************/
void readFile(ifstream& infile, AsteroidList& astList, SpaceShip& spaceShip)
{
	int posX, posY, numAst = 0;
	double size;

	// read first number
	infile >> posX; \
		// check if end of file and asteroid number is less than 100
		while (!infile.eof() && numAst < 100)
		{
			// read the rest of the line
			infile >> posY >> size;
			// create temporary Asteroid object with data read
			Asteroid toInsert(posX, posY, size);
			// insert that object into the array of objects in AsteroidList
			astList.insert(toInsert);
			// update 
			numAst++;
			infile >> posX;
		}
}

/****************************************
*				printHeader()			*
* prints header to console and output	*
* file									*
* param: ofstream, SpaceShip			*
* return: none							*
*****************************************/
void printHeader(ofstream& outfile, const SpaceShip & ship)
{
	// clear console
	system("cls");
	// create a string that contains ship's position in a nice format
	string pos = "(" + to_string(ship.getX()) + ", " + to_string(ship.getY()) + ")";
	// print header to console
	cout << "**********WELCOME TO ASTEROID COLLECTOR**********\n\n";
	cout << "Asteroid Collected" << setw(13) << "Position" << setw(9)
		<< "Size" << setw(24) << "Distance (in miles)\n"
		<< "------------------" << setw(13) << "--------" << setw(9)
		<< "----" << setw(24) << "-------------------\n" << setw(9)
		<< "-" << setw(22) << pos << setw(9) << "-" << setw(24)
		<< "0.00\n";

	// print header to output file
	outfile << "**********WELCOME TO ASTEROID COLLECTOR**********\n\n";
	outfile << "Asteroid Collected" << setw(13) << "Position" << setw(9)
		<< "Size" << setw(24) << "Distance (in miles)\n"
		<< "------------------" << setw(13) << "--------" << setw(9)
		<< "----" << setw(24) << "-------------------\n" << setw(9)
		<< "-" << setw(22) << pos << setw(9) << "-" << setw(24)
		<< "0.00\n";

}

/****************************************
*			collectNearest()			*
* gets the index of the nearest asteroid*
* then calls spaceShip methods to		*
* to collect it then returns the index	*
* param: AsteroidList, SpaceShip,		*
* double, double, int, int				*
* return: int							*
*****************************************/
int collectNearest(AsteroidList& astList, SpaceShip& spaceShip, double maxSize, double& distance, int& x, int& y)
{
	int i;
	bool blasted = false;	// if ast was blasted
	// find the nearest asteroid, if we blast it, find another one
	do {
		

		Asteroid ast;
		// get index of the closest asteroid
		i = spaceShip.getClosest(maxSize, distance, astList);
		// index = -1 means all have been collected
		// this is just in case user asks for more asteroids
		// than there is in space
		if (i != -1)
		{
			// get the asteroid
			ast = astList.getAst(i);
			if (ast.getSize() <= maxSize)
			{
				blasted = false;
				// get its position
				x = ast.getX();
				y = ast.getY();
				// move to the location of that asteroid
				spaceShip.move(x, y, distance);
				// collect the asteroid
				spaceShip.collect(i, astList);
			}
			else
			{
				spaceShip.blast(i, astList);
				blasted = true;
			}
		}
	} while (blasted);
	// return index to be passed to printAstReport
	return i;
}

/****************************************
*				printAstReport()		*
* prints the # of asteroid collected,	*
* its initial position, size, and		*
* distance travelled to collect it		*
* param: ofstream, int, int, int		*
* AsteroidList, double					*
* return: none							*
*****************************************/
void printAstReport(ofstream& outfile, int i, int x, int y, const AsteroidList& list, double distance)
{
	if (i != -1)
	{
		// string to have position in a nice format
		string pos = "(" + to_string(x) + ", " + to_string(y) + ")";

		// print to console infor about the asteroid
		cout << setw(9) << i << setw(22) << pos << setw(9) << fixed << setprecision(2)
			<< list.getAst(i).getSize() << setw(23) << distance << endl;

		// print same information to the output file
		outfile << setw(9) << i << setw(22) << pos << setw(9) << fixed << setprecision(2)
			<< list.getAst(i).getSize() << setw(23) << distance << endl;
	}
}

/****************************************
*			  printTotals()				*
* prints total # of collected asteroids,*
* their total size, and total distance	*
* param: ofstream, SpaceShip			*
* return: none							*
*****************************************/
void printTotals(ofstream& outfile, const SpaceShip& spaceShip)
{
	// string of 100 '-' characters
	string tab = string(100, '-');

	// print totals to console
	cout << endl << tab << endl
		<< "Total Asteroids Collected: "
		<< spaceShip.getCollected() << setw(27) << "Total Distance Covered: "
		<< spaceShip.getTotalDistance() << setw(28)
		<< "Total Size of Asteroids: " << spaceShip.getTotalSize() << endl
		<< "\n\n **********THANK YOU**********\n";

	// print totals to output file
	outfile << endl << tab << endl
		<< "Total Asteroids Collected: " << setw(3)
		<< spaceShip.getCollected() << setw(27) << "Total Distance Covered: "
		<< spaceShip.getTotalDistance() << setw(28)
		<< "Total Size of Asteroids: " << spaceShip.getTotalSize() << endl
		<< "\n\n **********THANK YOU**********\n";
}
/****************************************
*				closeFiles()			*
* closes input and output files			*
* param: ifstream, ofstream				*
* return: none							*
*****************************************/
void closeFiles(ifstream& infile, ofstream& outfile)
{
	infile.close();
	outfile.close();
}

/*******end*******/