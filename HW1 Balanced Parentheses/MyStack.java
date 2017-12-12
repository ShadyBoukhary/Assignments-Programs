/* MyStack class that implements the IMyStack interface*/



public class MyStack implements IMyStack {

	// declaration of variables and constants in MyStack
		public final int MAXSIZE = 100;
		private int size, top;
		private char charArray [];		// array of chars to hold parenthesis
		
		/************************************
		 * 				MyStack()			*
		 * Default constructor, initializes *
		 * stack to MAXSIZE					*
		 * @param none						*
		 * @return none						*
		 * **********************************/
		public MyStack()
		{
			size = MAXSIZE;
			top = 0;
			charArray = new char [size];
		}
		
		/************************************
		 * 				MyStack(int)		*
		 * Parameterized constructor, 		*
		 * initializes stack to a given int	*
		 * @param none						*
		 * @return none						*
		 * **********************************/
		public MyStack(int a)
		{
			if (a > MAXSIZE)
				size = MAXSIZE;
			else
				size = a;
			top = 0;
			charArray = new char [size];
		}
		
		@Override
		/************************************
		 * 				isEmpty()			*
		 * Checks whether the stack is empty*
		 * and returns true if and only if	*
		 * it is empty.						*
		 * @param none						*
		 * @return boolean					*
		 * **********************************/
		public boolean isEmpty() {
			if (top == 0)
				return true;
			return false;
		}

		@Override
		/************************************
		 * 				isFull()			*
		 * Checks whether the stack is full *
		 * and returns true if and only if	*
		 * it is full.						*
		 * @param none						*
		 * @return boolean					*
		 * **********************************/
		public boolean isFull() {
			if (top == (MAXSIZE - 1))
				return true;
			return false;
		}

		@Override
		/************************************
		 * 			  pushStack()			*
		 * Inserts an element at the top of *
		 * the stack 						*
		 * @param char						*
		 * @return none					    *
		 * **********************************/
		public void pushStack(char par) {
			if (!isFull())
				charArray[top++] = par;
			else
				System.out.println("ERROR: Cannot insert something to a full stack");
		}

		@Override
		/************************************
		 * 			  popStack()			*
		 * Removes element from the top of	*
		 * the stack and returns the removed*
		 * element							*
		 * @param none						*
		 * @return char					    *
		 * **********************************/
		public void popStack() {
			if (!isEmpty())
				top--;
			else	
				System.out.println("ERROR: Cannot remove something from an empty stack. Returned character 0");
		}
		
		/************************************
		 * 			  peak()				*
		 * Returns the element at the top	*
		 * of the stack						*
		 * @param none						*
		 * @return char					    *
		 * **********************************/
		public char peak()
		{
			return charArray[top - 1];
		}

}
