/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*								 Shady Boukhary									*
*					 CMPS 2132 Object-Oriented Programming						*
*							   Dr. Stringfellow									*
*						HW4: SpaceFleet, due October 25th						*
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
#define MAX 100
using namespace std;

typedef SpaceCraft* Fleet[MAX];

// prototypes
void commence(int);
void openFiles(ifstream&, ifstream&, ofstream&);
int readFile(ifstream&, ifstream&, AsteroidList&, Fleet&, double&);
void printHeader(ofstream&);
void printAstHeader(ofstream&);
void printStatusReport(ofstream&, const Fleet&, int);
void turnOnShips(AsteroidList&, Fleet&, double, int, ofstream&);
void turnOnProbes(AsteroidList&, Fleet&, int);
int collectNearest(AsteroidList&, SpaceShip*, double, double&, int&, int&);
int visitNearest(AsteroidList&, SpaceProbe*, double&);
void printAstReport(int, int, const Fleet&, double, ofstream&);
void printTotals(const Fleet&, ofstream&);
void printList(const Fleet&, ofstream&);
void closeFiles(ifstream&, ifstream&, ofstream&);
void delay(int);

int main()
{

	// declare variables
	// prevDistance to add to distance if asteroid was broken up
	double maxSize = 0;
	bool isShip = true;
	int craftNum = 0;
	// declare objects
	Fleet fleet;
	AsteroidList astList;
	ifstream infile, infile1;
	ofstream outfile;

	// open files
	openFiles(infile, infile1, outfile);


	commence(2);
	// read the input file and insert asteroids 
	craftNum = readFile(infile, infile1, astList, fleet, maxSize);

	// print header 
	printHeader(outfile);

	printStatusReport(outfile, fleet, craftNum);

	turnOnProbes(astList, fleet, craftNum);
	printList(fleet, outfile);


	// collect and print report of each asteroid 
	printAstHeader(outfile);
	turnOnShips(astList, fleet, maxSize, craftNum, outfile);


	printStatusReport(outfile, fleet, craftNum);
	// print total distance, size, and number
	printTotals(fleet, outfile);

	// close all files
	closeFiles(infile, infile1, outfile);
	for (int x = 0; x < craftNum; x++)
		delete fleet[x];
	system("pause");
	return 0;
}
/****************************************
*			promptData()				*
* prompts user for general requirements	*
* param: int, double, Spaceship			*
* return: none							*
*****************************************/
void commence(int x)
{

	cout << "Intitializing System";
	delay(x);
	cout << "\r                        \r"
		<< "Commencing launch";
	delay(x);
	cout << "\r                        \r";
}

/****************************************
*				delay()					*
* delays program for few seconds		*
* param: int							*
* return: none							*
*****************************************/
void delay(int sec)
{
	for (int x = 0; x < sec; x++)
	{
		cout << ".";
		// batch command to delay 1 second
		system("timeout /t 1 /nobreak >nul");
	}

}

/****************************************
*				openFiles()				*
* asks user for file names, opens files	*
* param: ifstream, ofstream				*
* return: none							*
*****************************************/
void openFiles(ifstream& infile, ifstream& infile1, ofstream& outfile)
{
	// variables
	char choice;
	string input;
	string output;
	cout << "**********SHADY BOUKHARY**********\n\n";
	// prompt for input and output file names
	cout << "Would you like to enter the name of input and output files?: (Y/N) ";
	cin >> choice;
	// if users wants to enter names
	if (toupper(choice) == 'Y')
	{
		// get file names
		cout << "Name of space fleet file: ";
		cin.ignore();
		getline(cin, input);
		// convert string to cstring and open files
		infile1.open(input.c_str());
		cout << "Name of asteroid file: ";
		getline(cin, input);
		infile.open(input.c_str());
		cout << "Name of output file: ";
		getline(cin, output);
		outfile.open(output.c_str());
	}
	// use default names if user chooses not to
	else
	{
		infile.open("data.dat");
		infile.open("data2.dat");
	}
	if (!infile || !outfile)
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
int readFile(ifstream& infile, ifstream& infile1, AsteroidList& astList, Fleet& fleet, double& maxSize)
{
	int posX, posY, numAst = 0, craftNum, toCollect, toVisit;
	double size;
	char prec, type;
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
	infile1 >> craftNum;
	infile1 >> toVisit >> toCollect >> maxSize;
	SpaceCraft::setToVisitCollect(toVisit, toCollect);
	for (int x = 0; x < craftNum; x++)
	{
		infile1 >> type >> posX >> posY;
		if (type == 'S')
			fleet[x] = new SpaceShip(posX, posY);
		else
			fleet[x] = new SpaceProbe(posX, posY);
	}
	return craftNum;

}

/****************************************
*				printHeader()			*
* prints header to console and output	*
* file									*
* param: ofstream, SpaceShip			*
* return: none							*
*****************************************/
void printHeader(ofstream& outfile)
{
	cout << "\n\n\n**********WELCOME TO ASTEROID COLLECTOR**********\n\n\n";
	outfile << "\n\n\n**********WELCOME TO ASTEROID COLLECTOR**********\n\n\n";

}

void printStatusReport(ofstream& outfile, const Fleet& fleet, int craftNum)
{
	cout << endl << endl << "Status Reports:\n\n";
	outfile << endl << "Status Reports:\n\n";
	cout << "ID/Type" << setw(16) << "Position" << setw(21) << "Collected/Visited"
		<< setw(20) << "Size Collected\n" << "------------" << setw(11) << "--------"
		<< setw(21) << "-----------------" << setw(20) << "--------------\n";

	outfile << "   Type" << setw(16) << "Position" << setw(21) << "Collected/Visited"
		<< setw(20) << "Size Collected\n" << "------------" << setw(11) << "--------"
		<< setw(21) << "-----------------" << setw(20) << "--------------\n";

	for (int x = 0; x < craftNum; x++)
	{
		SpaceShip * ship = dynamic_cast <SpaceShip *>(fleet[x]);
		if (ship != 0)
		{
			cout << x << " " << ship->to_string();
			outfile << x << " " << ship->to_string();
		}
		else
		{
			SpaceProbe * probe = dynamic_cast<SpaceProbe *>(fleet[x]);
			if (probe != 0)
			{
				cout << x << " " << probe->to_string();
				outfile << x << " " << probe->to_string();
			}
		}
	}
	cout << endl;
	outfile << endl;
}

/****************************************
*				turnOnShips()			*
* turns ships on to collect asteroids	*
* param: AsteroidList, SpaceShip, double*
* return: none							*
*****************************************/
void turnOnShips(AsteroidList& list, Fleet& fleet, double msize, int numCrafts, ofstream& outfile)
{
	int collected = 0, totalCollected = 0;
	int astX = 0, astY = 0;
	double distance = 0;
	// turn spaceship on, collect asteroids,
	int x = 0;
	while (totalCollected < fleet[0]->getToCollect())
	{
		// downcast spaceCraft to spaceShip
		SpaceShip * ship = dynamic_cast <SpaceShip *>(fleet[x]);
		if (ship != 0)		// if it's a spaceship
		{
			// collect asteroid
			collected = collectNearest(list, ship, msize, distance, astX, astY);
			printAstReport(collected, x, fleet, distance, outfile);
			totalCollected++;
			distance = astX = astY = 0;
		}
		if (x == numCrafts - 1)
			x = 0;
		else
			x++;		// check next spaceCraft

	}
}

/****************************************
*				turnOnProbes()			*
* turns probes on to visit asteroids	*
* param: AsteroidList, SpaceProbe, double*
* return: none							*
*****************************************/
void turnOnProbes(AsteroidList & list, Fleet& fleet, int numCrafts)
{
	int visited = 0, totalVisited = 0;
	double distance = 0;
	// turn spaceprobe on and visit the closest asteroids
	int x = 0;
	while (totalVisited < fleet[0]->getToVisit() && totalVisited < list.getSize())
	{
		// downcast SpaceCraft to SpaceProbe
		SpaceProbe * probe = dynamic_cast<SpaceProbe *>(fleet[x]);
		if (probe != 0)		// if it's a SpaceProbe
		{
			// visit nearest asteroid
			visited = visitNearest(list, probe, distance);
			totalVisited++;
			distance = 0;
		}
		if (x == numCrafts - 1)
			x = 0;		// visit 1 asteroid per probe per cycle
		else
			x++;		// check next spaceCraft
	}
}

/****************************************
*				visitNearest()			*
* moves and visits closest asteroid		*
* param: AsteroidList, SpaceProbe, double*
* return: none							*
*****************************************/
int visitNearest(AsteroidList& list, SpaceProbe* probe, double& distance)
{
	// find the closest asteroid to the probe
	int i = probe->getClosest(0, distance, list);
	if (i != -1)	// if not all were visited
	{
		// move to asteroid's position
		probe->move(list.getAst(i).getX(), list.getAst(i).getY(), distance);
		// collect info about asteroid
		probe->collect(i, list);
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
int collectNearest(AsteroidList& astList, SpaceShip* spaceShip, double maxSize, double& distance, int& x, int& y)
{
	int i;
	bool blasted = false;	// if ast was blasted
	// find the nearest asteroid, if we blast it, find another one
	do {


		Asteroid ast;
		// get index of the closest asteroid
		i = spaceShip->getClosest(maxSize, distance, astList);
		// index = -1 means all have been collected
		// this is just in case user asks for more asteroids
		// than there is in space
		if (i != -1)
		{
			// get the asteroid
			ast = spaceShip->getPreciousAsts().getAst(i);
			if (ast.getSize() <= maxSize)
			{
				blasted = false;
				// get its position
				x = ast.getX();
				y = ast.getY();
				// move to the location of that asteroid
				spaceShip->move(x, y, distance);
				// collect the asteroid
				spaceShip->collect(i);
			}
			else
			{
				spaceShip->blast(i);
				blasted = true;
			}
		}
	} while (blasted);
	// return index to be passed to printAstReport
	return i;
}

// prints list of precious metal asteroids
void printList(const Fleet& fleet, ofstream& outfile)
{
	cout << "\n\nList of precious metal asteroids:\n\n"
		<< fleet[0]->getList();

	outfile << "\n\nList of precious metal asteroids:\n\n"
		<< fleet[0]->getList();
}

// prints header before printing collected asteroids
void printAstHeader(ofstream& outfile)
{
	string s = "Ship#" + string(5, ' ') + "Asteroid" + string(5, ' ') + "Position" + string(5, ' ')
		+ "Size" + string(5, ' ') + "Precious" + string(5, ' ')
		+ "Distance\n"
		+ "-----" + string(5, ' ') +"--------" + string(5, ' ') + "--------" + string(5, ' ')
		+ "----" + string(5, ' ') + "--------" + string(5, ' ')
		+ "--------\n";
	cout << endl << endl << "Asteroids Collected:\n\n" << s;
	outfile << endl << endl << "Asteroids Collected:\n\n" << s;
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
void printAstReport(int i, int x, const Fleet& fleet, double distance, ofstream& outfile)
{
	if (i != -1)
	{
		cout << setw(3) << x << setw(11) << i;
		string s = fleet[x]->getPreciousAsts().getAst(i).to_string();
		s.pop_back();
		cout << s << setw(16) << fixed << setprecision(2) << distance << endl;

		outfile << setw(3) << x << setw(11) << i;
		outfile << s << setw(16) << fixed << setprecision(2) << distance << endl;

	}
}

/****************************************
*			  printTotals()				*
* prints total # of collected asteroids,*
* their total size, and total distance	*
* param: ofstream, SpaceShip			*
* return: none							*
*****************************************/
void printTotals(const Fleet& fleet, ofstream& outfile)
{

	// print totals to console
	cout << endl << endl;
	outfile << endl << endl;

	cout << fleet[0]->SpaceCraft::to_string() << endl;

	outfile << fleet[0]->SpaceCraft::to_string() << endl;

}



/****************************************
*				closeFiles()			*
* closes input and output files			*
* param: ifstream, ofstream				*
* return: none							*
*****************************************/
void closeFiles(ifstream & infile, ifstream& infile1, ofstream& outfile)
{
	infile.close();
	infile1.close();
	outfile.close();
}

/*******end*******/