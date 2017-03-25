#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

/**
 * Node_List Struct
 */
struct Node{
 char * value;
 struct Node * next;
 struct Node * last;
};

typedef struct Node Node;

/**
 * addClosingBracket
 * Adds a closing bracket to finish off struct.
 * @param  theList   The head
 * @param  theNode   Where the closing bracket goes
 * @return           if it completed succesfuly (yes = 1)
 */
int addClosingBracket(Node * theList, Node * theNode);

/**
 * addToBack
 * Adds a node to the end of the list.
 * @param  theList   The head
 * @param  toBeAdded The new node
 * @return           New head of list
 */
Node * addToBack(Node * theList, Node * toBeAdded);

/**
 * addToFront
 * Adds a node to the front of the list.
 * @param  theList   The head
 * @param  toBeAdded The new node
 * @return           New head of list
 */
Node * addToFront(Node * theList, Node * toBeAdded);

/**
 * changeValue
 * Changes the value of a certain node.
 * @param  node      The node you want the value changed
 * @param  newValue  The new value you want put there.
 * @param  size      Size you want allocated to the string value
 * @return int       If it succesfully changed or not. 1 for yes.
 */
int changeValue(Node * node, char * newValue, int size);

/**
 * containsFunction
 * Checks if a class contains a function or not
 * @param  node   The class
 * @return int    If it does or not. 1 for yes.
 */
int containsFunction(Node * node);

/**
 * createConstructors
 * Creates the constructors.
 * @param  head      The list
 */
void createConstructors(Node * head);

/**
 * createConstructorCalls
 * Creates the constructors calls
 * @param  head      The list
 */
int createConstructorCalls(Node * head);

/**
 * createFunctionPrototypes
 * Creates the function prototypes.
 * @param  head      The list
 */
void createFunctionPrototypes(Node * theList);

/**
 * createRecord
 * Creates a new node.
 * @param  value     The value you want it to have
 * @return           The node.
 */
Node * createRecord(char * value);


/**
 * constructorExists
 * Checks if a constructor exists by appending class
 * @param  head      The list
 * @param  class     The class you want to look for.
 * @return int       If the constuctor exists (1 for yes)
 */
int constructorExists(Node * head, char * class);

/**
 * Destroys the list, starting at the head freeing all memory.
 * @param theList the head of the list.
 */
void destroyList(Node * theList);

/**
 * destroyRecord
 * Frees the node value then the node
 * @param node The node you want destroyed.
 */
void destroyRecord(Node * node);

/**
 * editFunctionCall
 * Puts the usable variable in the function call.
 * @param  theList      The list
 * @param  searchKey    The function you are looking for
 * @param  class        The class you are looking for
 */
void editFunctionCall(Node * theList, char * searchKey, char * class);

/**
 * findBeforeFunction
 * Puts the variable reference in the function call.
 * @param  theList      The list
 * @param  searchKey    The function you are looking for
 * @param  class        The class you are looking for
 */
Node * findBeforeFunction(Node * list, Node * node);

/**
 * findFirstOccurence
 * Finds the first occurence of a string in the list from a node
 * @param  node         The node you want to start looking from
 * @param  str          The string you are looking for.
 * @return              Returns the node when it finds it.
 */
Node * findFirstOccurence(Node * node, char * str);

/**
 * findFunctionCalls
 * Looks for and finds any function calls then calls the construcor above them (for globals).
 * @param  theList      The list
 * @param  searchKey    The function you are looking for
 * @param  class        The class you are looking for
 */
void findFunctionCalls(Node * head, char * search, char * className);

/**
 * findLastOccurence
 * Finds the last occurence of a string in the list from a node.
 * @param  node         The node you want to start looking from
 * @param  str          The string you are looking for.
 * @return              Returns the node when it finds it.
 */
Node * findLastOccurence(Node * node, char * str);

/**
 * findLastBracket
 * Finds the end of a class
 * @param  node         The node you want to start looking from
 * @return              Returns the node when it finds it.
 */
Node * findLastBracket(Node * node);

/**
 * findMallocSpot
 * Finds the malloc if it is a ptr and not a regular class declaration.
 * @param  theList      The start of the list.
 * @param  search       What function you are searching for.
 * @param  class        The last class, search was found in.
 * @param  function     The last function, search was found in.
 * @param  className    The className.
 * @return              Returns the node when it finds it.
 */
Node * findMallocSpot(Node * theList, char * search, char * class, char * function, char * className);

/**
 * findUsableVar
 * Finds a usable var for a function call.
 * @param  theList                The start of the list.
 * @param  classLocation          The class location of the function call.
 * @param  functionLocation       The function location of the function call.
 * @param  class                  The class.
 * @return              Returns the usable var value.
 */
char * findUsableVar(Node * theList, char * classLocation, char * functionLocation, char * class);

/**
 * fixBrackets
 * Fixes the brackets, removes last bracket then adds in proper spot.
 * @param  theList         The start of the list.
 */
void fixBrackets(Node * theList);

/**
 * fixClassVariables
 * Finds variables that need editing in functions because they reference class variables.
 * Calls fixfunctionVariables.
 * @param  theList         The head of the list.
 */
void fixClassVariables(Node * theList);

/**
 * fixCalls
 * Fixes function calls that reference other classes for a given search term.
 * @param  theList      The start of the list.
 * @param  searchTerm   The function you are looking for.
 * @param  prefix       The prefix of the search term.
 */
void fixCalls(Node * theList, char * searchTerm, char * prefix);

/**
 * fixFunctionCalls
 * Finds Functions inside of structs then calls fix calls upon them.
 * @param  theList      The start of the list.
 */
void fixFunctionCalls(Node * theList);

/**
 * fixFunctionPtrs
 * Finds function ptrs then calls fixPtr upon them.
 * @param  theList      The start of the list.
 */
void fixFunctionPtrs(Node * theList);

/**
 * fixFunctionVariables
 * Fixes functionVariables dereferrencing them and creating the parameter.
 * @param  list         The node you want to start looking from
 * @param  class        The class you are looking for.
 * @param  var          The var you are searching for.
 * @return int          Returns if it was succesful in changing the function variables.
 */
int fixFunctionVariables(Node * list, Node * class, char * var);

/**
 * fixPtr
 * Adds the parameters to function ptrs to correct any potential mistakes.
 * @param  theList      The start of the list.
 * @param  search       The ptr you are looking for.
 * @param  start        The starting place of where to copy parameters.
 */
void fixPtr(Node * theList, char * search, Node * start);

/**
 * getLastItem
 * Gets the last item in the list.
 * @param  theList The start of the list.
 * @return         Last item in list.
 */
Node * getLastItem(Node * theList);

/**
 * getSuffix
 * Gets the suffix for renaming.
 * @param  node    The start of the list.
 * @param suffix   Suffix gets stored here.
 */
void getSuffix(Node * node, char * suffix);

/**
 * getVarType
 * Gets the var type of a variable for function calls.
 * @param  theList  The start of the list.
 * @param  var      The var
 * @param  class    The class the var is in.
 * @param  function The function the var is in.
 * @param  used     The used vriable.
 * @return char     The type.
 */
void getVarType(Node * theList, char * var, char * class, char * function, Node * used, char * type);

/**
 * getVariableTypeStart
 * Gets the variable type of a function
 * @param  theList The start of the list.
 * @param  theNode The function you are looking at (starting spot)
 * @return         The start of variable type.
 */
Node * getVariableTypeStart(Node * theList, Node * theNode);

/**
 * hasPrototype
 * Returns if there is already a prototype for that function created.
 * @param  theList The start of the list.
 * @param  search  The prototype you are searching for.
 * @return int     Has a prototype ( 1 = yes)
 */
int hasPrototype(Node * theList, char * search);

/**
 * insertAfter
 * Inserts after a given node
 * @param  node    The node you want to insert after.
 * @param  newNode The node you are inserting after it.
 * @return         Last item in list.
 */
int insertAfter(Node * node, Node * newNode);

/**
 * isClass
 * Determines if a node is a class
 * @param  theNode The node you want to check
 * @return         If item is class (yes = 1)
 */
int isClass(Node * theNode);

/**
 * isClassCall
 * Determines if a node is a class call.
 * @param  theList The start of the list
 * @param  theNode The node you want to check
 * @return         If item is class (yes = 1)
 */
int isClassCall(Node * theList, Node * theNode);

/**
 * isEmpty
 * Checks if list is empty
 * @param  theList The start of the list
 * @return        If its empty (yes = 1)
 */
int isEmpty(Node * theList);

/**
 * isFunction
 * Deterines if a node is a function
 * @param  theNode The node you want to check
 * @return         If item is class (yes = 1)
 */
int isFunction(Node * theNode);

/**
 * isFunctionCall
 * Determines if a node is a function call.
 * @param  theNode The node you want to check
 * @return         If item is class (yes = 1)
 */
int isFunctionCall(Node * theNode);

/**
 * isFunctionPtr
 * Determines if a node is a function ptr.
 * @param  theNode The node you want to check
 * @return         If item is class (yes = 1)
 */
int isFunctionPtr(Node * theNode);

/**
 * finishFunctionCalls
 * Finds function calls and calls edit function call.
 * @param  theNode The node you want to check
 * @return         If item is class (yes = 1)
 */
void finishFunctionCalls(Node * theList);

/**
 * fixAnyOtherCalls
 * Fixes any other function calls.
 * @param  theList The start of the list.
 * @param  search  The function you are searching for.
 * @param  rename  The thing you must rename it with.
 */
void fixAnyOtherCalls(Node * theList, char * search, char * prefix);

/**
  * fixCalls
  * Fixes function calls
  * @param theList  The start of the list.
  * @param searchTerm The function you are looking for
  * @param prefix     The prefix of the function.
  */
void fixCalls(Node * theList, char * searchTerm, char * prefix);

/**
  * fixFunctionCalls
  * Fixes the function calls
  * @param theList   The start of the list.
  */
void fixFunctionCalls(Node * theList);

/**
 * renameFunctions
 * Renames the functions in the list.
 * @param  theList The start of the list.
 */
void renameFunctions(Node * theList);

/**
 * printList
 * Prints each element of the list out to the screen.
 * @param theList   The head of the list
 * @param fileName  The filename
 */
void printList(Node * theList, char * fileName);

/**
 * moveClassesToTop
 * Moves all the classes(structs) to the top for the function ptr.
 * @param theList  The head of the list.
 */
void moveClassesToTop(Node * theList);

/**
 * printRecord
 * Prints out the current record's value
 * @param  node Node* (not NULL)
 * @return         none
 */
void printRecord(Node * node, int tabs, int inLoop, FILE * file);

/**
 * removeBetween
 * Removes node and assigns values appropriately
 * @param  node  The node you want to remove.
 * @return node  The next node.
 */
Node * removeBetween(Node * node);

/**
 * replaceRecord
 * Searches the list and replaces the record wherever it appears.
 * @param  theNode The node you want to check
 * @param  find    The string to look for
 * @param  replace The value to replace it with.
 * @param  int     Returns if it was repalced or not (1 = yes)
 */
int replaceRecord(Node * theList, char * find, char * replace);

/**
 * whichComesFirst
 * Tells you which comes first in the list.
 * @param  theList     The start of the list.
 * @param  firtNode    The firstNode for comparison
 * @param  secondNode  The secondNode for comparison.
 * @return  int        First node comes first (1), second node first (2)
 */
int whichComesFirst(Node * theList, Node * firstNode, Node * secondNode);

#endif
