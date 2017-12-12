
public interface IMyStack {

	
	/************************************
	 * 				isEmpty()			*
	 * Checks whether the stack is empty*
	 * and returns true if and only if	*
	 * it is empty.						*
	 * @param none						*
	 * @return boolean					*
	 * **********************************/
	public boolean isEmpty();
	
	
	/************************************
	 * 				isFull()			*
	 * Checks whether the stack is full *
	 * and returns true if and only if	*
	 * it is full.						*
	 * @param none						*
	 * @return boolean					*
	 * **********************************/
	public boolean isFull();
	
	
	/************************************
	 * 			  pushStack()			*
	 * Inserts an element at the top of *
	 * the stack 						*
	 * @param char						*
	 * @return none					    *
	 * **********************************/
	public void pushStack(char par);
	
	
	/************************************
	 * 			  popStack()			*
	 * Removes element from the top of	*
	 * the stack and returns the removed*
	 * element							*
	 * @param none						*
	 * @return char					    *
	 * **********************************/
	public void popStack();
	
	
	/************************************
	 * 			  peak()				*
	 * Returns the element at the top	*
	 * of the stack						*
	 * @param none						*
	 * @return char					    *
	 * **********************************/
	public char peak();
	
}
