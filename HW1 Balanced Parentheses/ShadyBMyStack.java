/* ******************************************************************************************* 										
 * 									Shady Boukhary											*
 * 						CMPS 2143 Object-Oriented Programming 								*
 * 					Programming Assignment 1 DUE September 13								*
 * 			This program asks the user to input a string to check whether or not it			*
 * 		has balanced parenthesis i.e. every right parenthesis has a corresponding left 		*
 *		one preceding it. After the users enters the string, the program displays to the 	*
 * 						console whether it is balanced or not.								
 * **************************************************************************************** */



import java.util.Scanner;

public class ShadyBMyStack {

	public static void main(String[] args) {
		// function calls
		printHeader();
		getThenCheck();
		goodbye();
	}
	
	/************************************
	 * 			  printHeader()			*
	 * prints a header on the top		*
	 * @param none						*
	 * @return none					    *
	 * **********************************/
	public static void printHeader() 
	{	
	System.out.println("**********WELCOME TO THE BALANCED PARENTHESES CHECKER**********");
	for (int x = 0; x < 3; x++)
		System.out.println();
	System.out.print("Please enter 10 strings to be analyzed:\n\n"
			+ "Input");
	setw("Result\n", 45);		// print using setw() function
	System.out.print("-----");
	setw("------\n", 45);
	
	}

	/************************************
	 * 			  getThenCheck()		*
	 * Calls getInput, analyzeInput,	*
	 * and printResult 10 times			*
	 * @param none						*
	 * @return none					    *
	 * **********************************/
	public static void getThenCheck()
	{
		String input;
		boolean isBalanced;
		
		for (int x = 0; x < 10; x++)
		{
			// gets input from the keyboard(
			input = getInput();
		
			// passes input to analyzeInput to determine if the input has balanced parenthesis
			isBalanced = analyzeInput(input);
		
			printResult(isBalanced);
		}
	}

	/************************************
	 * 			  getInput()			*
	 * Gets input from the keyboard		*
	 * @param none						*
	 * @return String				    *
	 * **********************************/
	@SuppressWarnings("resource")
	public static String getInput()
	{
		Scanner scanner = new Scanner(System.in);
		String s;
		
		// read line from the keyboard
		s = scanner.nextLine();
		return s;
	}
	
	
	/************************************
	 * 			  analyzeInput()		*
	 * Checks whether string has		*
	 * balanced parenthesis and returns	*
	 * true if it does and false if not *
	 * @param String					*
	 * @return boolean					*
	 * **********************************/
	public static boolean analyzeInput(String input)
	{	
		char character;
		MyStack stack1 = new MyStack(input.length());	// new stack of size = length of input
		
		/*a for loop that traverses the input character by character, pushes the character
		 * to the stack if it is a '(', and pops the last character if it encounters
		 * a ')' unless the ')' is not preceded by  a '(' when the stack is empty. At the end of this,
		 * if the stack is empty that means that the parenthesis are balanced in the input string */
		for (int x = 0; x < input.length(); x++)
		{
			character = input.charAt(x);
			if (character == '(' )
				stack1.pushStack(character);
			else if(character == ')')
			{
				if (stack1.isEmpty())
					return false;
				else
					stack1.popStack();
					
			}
		}
		return stack1.isEmpty();
		
	}
	
	/************************************
	 * 			  printResult()			*
	 * Prints "balanced" if the string 	*
	 * has balanced parenthesis or		*
	 * "not balanced" if does not		*
	 * Please note that the only way to *
	 * make the output look nice inside *
	 * the console - since the prompt   *
	 * had to stay there and the user	*
	 * input had to stay in the console *
	 * as well - was to make the input a*
	 * a part of the output by making	*
	 * the user print directly to the	*
	 * table. Since the program reads	*
	 * the input line by line, i was not*
	 * allowed to print to the same line*
	 * as the input. That's why they're *
	 * off by 1 line yet they still 	*
	 * look as neat as possible 		*
	 * @param boolean					*
	 * @return none					    *
	 * **********************************/
	public static void printResult(boolean isBalanced)
	{
		if (isBalanced)
			setw("Balanced!\n\n", 50);
		else 
			setw("Not Balanced!\n\n", 50);
		
	}
	/************************************
	 * 		  setw(string, int)			*
	 * Mimics the setw() function in	*
	 * C++ since Java doesn't have a	*
	 * convenient function like this	*
	 * Research was made to gather info *
	 * on how to work around that		*
	 * Java limitation. String.format()	*
	 * wasn't as easy to use or helpful *
	 * neither was print()				*
	 * @param String, integer			*
	 * @return none					    *
	 * **********************************/
	public static void setw(String s, int width)
	{
		for (int x = s.length(); x < width; x++)
			System.out.print(" ");
		System.out.print(s);
	}
	
	/************************************
	 * 			  Goodbye()				*
	 * prints Thank you after the 		*
	 * program is done executing		*
	 * @param none						*
	 * @return none					    *
	 * **********************************/
	public static void goodbye()
	{
		System.out.println("**********THANK YOU**********");
	}
	
}
	
