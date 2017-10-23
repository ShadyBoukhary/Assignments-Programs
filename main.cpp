/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*								 Shady Boukhary									*
*					 CMPS 2132 Object-Oriented Programming						*
*							   Dr. Stringfellow									*
*						HW3: SpaceCrafts, due October 25th						*
*																				*
*		 This program reads data about the locations and sizes of				*
*		 asteroids in space, asks the user to input a starting position			*
*	for a spaceship and spaceprobe that collect these asteroids. The program	*
*		 makes the spaceship collect 3 asteroids and the probe visits 10		*
*		 in order of nearest to farthest, given that the asteroid is less		*
*		 than a user-specified maximum size. Then, the program prints to		*
*				 the console which asteroids were collected and					*
*		 in what order, their sizes, the distance the spaceship travelled		*
*		 to each asteroid, the asteroids original positions, the total			*
*		 distance travelled, the total size and the total number of				*
*								asteroids collected.							*
*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include "SpaceShip.h"
#include "SpaceProbe.h"

using namespace std;

// prototypes
void promptData(double&, SpaceShip&, SpaceProbe&);
void openFiles(ifstream&);
void readFile(ifstream&, AsteroidList&, SpaceShip&);
void printHeader(const SpaceCraft&, bool);
void turnOnShips(AsteroidList&, SpaceShip&, double);
void turnOnProbes(AsteroidList&, SpaceProbe&);
int collectNearest(AsteroidList&, SpaceShip&, double, double&, int&, int&);
int visitNearest(AsteroidList&, SpaceProbe&, double&);
void printAstReport(int, int, int, const AsteroidList&, double, bool);
void printTotals(const SpaceShip&, const SpaceProbe&, bool);
void printPrecious(const SpaceProbe&);
void closeFiles(ifstream&);
void delay(int);

int main()
{
	// declare variables
	// prevDistance to add to distance if asteroid was broken up
	double maxSize = 0;
	bool isShip = true;
	// declare objects
	AsteroidList astList;
	SpaceShip spaceShip;
	SpaceProbe spaceProbe;
	ifstream infile;

	// open files
	openFiles(infile);

	// request some data from the user
	promptData(maxSize, spaceShip, spaceProbe);

	// read the input file and insert asteroids 
	readFile(infile, astList, spaceShip);

	// print header 
	printHeader(spaceShip, isShip);

	// collect and print report of each asteroid 
	turnOnShips(astList, spaceShip, maxSize);
	// print total distance, size, and number
	printTotals(spaceShip, spaceProbe, isShip);
	// print header for probe
	printHeader(spaceProbe, !isShip);
	// collect and print reports
	turnOnProbes(astList, spaceProbe);
	// print totals for probe
	printTotals(spaceShip, spaceProbe, !isShip);

	printPrecious(spaceProbe);
	// close all files
	closeFiles(infile);
	system("pause");
	return 0;
}
/****************************************
*			promptData()				*
* prompts user for general requirements	*
* param: int, double, Spaceship			*
* return: none							*
*****************************************/
void promptData(double & maxSize, SpaceShip & spaceShip, SpaceProbe & spaceProbe)
{
	char choice;
	int x, y;
	// get the maximum size the ship can collect
	cout << "What is the maximum size of asteroid the spaceship can collect? ";
	cin >> maxSize;
	// give the option of specifying a starting position for the ship
	cout << "Would you like to enter a custom starting position for the "
		<< "spaceship and the spaceProbe? (Y for yes): ";
	cin >> choice;
	// if hte user wants a custom starting position
	if (toupper(choice) == 'Y')
	{
		cout << "Please enter the x and y coordinates for the spaceship: ";
		cin >> x >> y;
		// set position for spaceship
		spaceShip.setPosition(x, y);
		cout << "Please enter the x and y coordinates for the spaceprobe: ";
		cin >> x >> y;
		spaceProbe.setPosition(x, y);
	}
	// just for fun: delay program to launch crafts into space
	cout << "Intitializing System";
	delay(4);
	cout << "\r                        \r"
		<< "Commencing launch";
	delay(4);
	cout << "\r                        \r";
}

void delay(int sec)
{
	for (int x = 0; x < sec; x++)
	{
		cout << ".";
		system("timeout /t 1 /nobreak >nul");
	}

}

/****************************************
*				openFiles()				*
* asks user for file names, opens files	*
* param: ifstream, ofstream				*
* return: none							*
*****************************************/
void openFiles(ifstream& infile)
{
	// variables
	char choice;
	string input;
	cout << "**********SHADY BOUKHARY**********\n\n";
	// prompt for input and output file names
	cout << "Would you like to enter the name of input file?: (Y/N) ";
	cin >> choice;
	// if users wants to enter names
	if (toupper(choice) == 'Y')
	{
		// get file names
		cout << "Enter the name of the input file: ";
		cin.ignore();
		getline(cin, input);
		// convert string to cstring and open files
		infile.open(input.c_str());
		// if files have failed to open
	}
	// use default names if user chooses not to
	else
	{
		infile.open("data.dat");
	}
	if (!infile)
	{
		cout << "Failed to open file.\n"
			<< "Terminating...\n";
		system("pause");
		exit(1);
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
	char prec;
	bool isPrecious = false;
	// read first number
	infile >> posX; 
		// check if end of file and asteroid number is less than 100
		while (!infile.eof() && numAst < 100)
		{
			// read the rest of the line
			infile >> posY >> size >> prec;
			if (toupper(prec) == 'P')
				isPrecious = true;
			else
				isPrecious = false;
			// create temporary Asteroid object with data read
			Asteroid toInsert(posX, posY, size, isPrecious);
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
void printHeader(const SpaceCraft & craft, bool isShip)
{
	static int x = 0;
	// create a string that contains ship's position in a nice format
	string pos = "(" + to_string(craft.getX()) + ", " + to_string(craft.getY()) + ")";
	// to use the same function for probes and ships without printing welcome twice
	if (x < 1)
	{
		cout << "\n\n\n**********WELCOME TO ASTEROID COLLECTOR**********\n\n\n";
		x++;
	}
	// print header to console
	if (isShip)
	{
		cout << setw(35) << "SPACESHIP\n" << setw(36) << "---------\n\n";
		cout << "Asteroid Collected" << setw(13) << "Position" << setw(9)
			<< "Size" << setw(16) << "Distance\n"
			<< "------------------" << setw(13) << "--------" << setw(9)
			<< "----" << setw(16) << "--------\n" << setw(9)
			<< "-" << setw(22) << pos << setw(9) << "-" << setw(16)
			<< "0.00\n";
	}
	else
	{
		cout << "\n" << setw(41) << "SPACEPROBE\n" << setw(42) << "----------\n\n";
		cout << "Asteroid Visited" << setw(15) << "Position" << setw(9)
			<< "Size" << setw(15) << "Distance" <<  setw(14) << "Precious\n"
			<< "----------------" << setw(15) << "--------" << setw(9)
			<< "----" << setw(15) << "--------" << setw(14) <<  "--------\n" << setw(9)
			<< "-" << setw(22) << pos << setw(9) << "-" << setw(16)
			<< "0.00\n";
	}
}




void turnOnShips(AsteroidList& list, SpaceShip& ship, double msize)
{
	int collected = 0;
	int astX = 0, astY = 0;
	double distance = 0;
	// turn spaceship on, collect 3 asteroids, and print results
	for (int x = 0; x < 3; x++)
	{
		collected = collectNearest(list, ship, msize, distance, astX, astY);
		printAstReport(collected, astX, astY, list, distance, true);
		distance = astX = astY = 0;
	}
}

void turnOnProbes(AsteroidList & list, SpaceProbe & probe)
{
	int visited = 0;
	double distance = 0;
	// turn spaceprobe on and visit the closest 10 asteroids'
	for (int x = 0; x < 10; x++)
	{
		visited = visitNearest(list, probe, distance);
		printAstReport(visited, list.getAst(visited).getX(), list.getAst(visited).getY(), list, distance, false); 
		distance = 0;
	}
}

int visitNearest(AsteroidList& list, SpaceProbe& probe, double& distance)
{
	int i = probe.getClosest(0, distance, list);
	if (i != -1)
	{
		probe.move(list.getAst(i).getX(), list.getAst(i).getY(), distance);
		probe.collect(i, list);
	}
	return i;
	
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
void printAstReport(int i, int x, int y, const AsteroidList& list, double distance, bool isShip)
{
	if (i != -1)
	{
		// string to have position in a nice format
		string pos = "(" + to_string(x) + ", " + to_string(y) + ")";

		// print to console info about the asteroid
		cout << setw(9) << i << setw(22) << pos << setw(9) << fixed << setprecision(2)
			<< list.getAst(i).getSize() << setw(15) << distance;
		if (!isShip)
		{
			cout << setw(11);
			if (list.getAst(i).getPrecious())
				cout << "YES";
			else
				cout << "NO";
		}
		cout << endl;
	}
}

/****************************************
*			  printTotals()				*
* prints total # of collected asteroids,*
* their total size, and total distance	*
* param: ofstream, SpaceShip			*
* return: none							*
*****************************************/
void printTotals(const SpaceShip& spaceShip, const SpaceProbe& probe, bool isShip)
{
	// string of 100 '-' characters
	string tab = string(83, '-');

	// print totals to console
	cout << endl << tab << endl;
	if (isShip)
	{
		cout << "# Asteroids Collected: "
			<< spaceShip.getCollected() << setw(27) << "Total Distance Covered: "
			<< spaceShip.getTotalDistance() << setw(17)
			<< "Total Size: " << spaceShip.getTotalSize() << "\n\n\n";
	}
	else
	{
		cout << "# Asteroids Visited: "
			<< probe.getCollected() << setw(27) << "Total Distance Covered: "
			<< probe.getTotalDistance() << setw(25)
			<< "# Precious Asteroids: " << probe.getPreciousAsts().getSize() << endl << endl;
			
	}
}

void printPrecious(const SpaceProbe& probe)
{
	cout << "\n\nPrecious Asteroid #" << setw(15) << "Position\n"
		<< "------------------" << setw(16) << "--------\n";
	for (int x = 0; x < probe.getPreciousAsts().getSize(); x++)
	{
		string pos = "(" + to_string(probe.getPreciousAsts().getAst(x).getX()) 
			+ ", " + to_string(probe.getPreciousAsts().getAst(x).getY()) + ")";
		cout << setw(8) << x << setw(25) << pos << endl;
	}
	cout << endl;
}


/****************************************
*				closeFiles()			*
* closes input and output files			*
* param: ifstream, ofstream				*
* return: none							*
*****************************************/
void closeFiles(ifstream & infile)
{
	infile.close();
}

/*******end*******/