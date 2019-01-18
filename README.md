
# uni_deque
C Deque Library


## The interface
Even if a Deque performs best only if you access the begin or the end of the list, this library also allows you to insert and access values at any position in the list, to enumerate a range of the list, to reverse the list, to sort the list, to insert sorted, to search for values, ...

In addition to the general functions which can be used for any kind of data, the library contains functions that are already specialized for basic types (characters, integers, floating points) and null-terminated strings (char* and wchar_t*).

Function names for data processing consist of key words that explain their purpose:
- Push
  - add a new element at the beginning or end of the list
- Insert
  - insert a new element at a certain position in the list
- Pop
  - delete an element at the beginning or end of the list
- Erase
  - delete an element at a certain position in the list
- Remove
  - delete an element that contains a certain value
- Front
  - access the begin of the list
- Back
  - access the end of the list
- At
  - access an element at a certain position in the list
- Sort
  - sort the list
- Asc
  - ascending order
- Desc
  - descending order
- Find
  - search the index of an element that contains a certain value

Specialized functions have an appendix that indicates the type that the function was made for:
- C    (for char)
- SC   (for signed char)
- UC   (for unsigned char)
- S    (for short)
- US   (for unsigned short)
- I    (for int)
- UI   (for unsigned int)
- L    (for long)
- UL   (for unsigned long)
- LL   (for long long)
- ULL  (for unsigned long long)
- F    (for float)
- D    (for double)
- LD   (for long double)
- Str  (for null-terminated string of char)
- WStr (for null-terminated string of wchar_t)

Examples:
The name of the function to add an int at the beginning of a Deque of int is
`PushFrontI`
The name of the function to insert a double into an ascending-sorted Deque of double is
`InsertAscD`


The comments in the first 250 lines of "uni_deque.h" should give you all the information you need to work with the library. The "main.c" file contains two examples of how to use the library. One for long int values and one for null-terminated strings.


## A little background information about the implementation
A Deque unites the functionality of a Stack and a Queue. That means a Deque holds the pointer to the first element `head` and a pointer to the last element `tail` of a container for the values to save. Aditionally this implementation maintains the number of saved values `size` and an error indicator `err`. Only a pointer of type `ud_t` is needed as interface referencing the Deque.
Schema:
![deque](images/deque.png)


The container for the values is a doubly-linked list. Besides of the pointer to the `previous` element and the `next` element it holds a pointer `data` to the actual value. This value can be of any type but should be the same for each element in a Deque because there will be no information about the memory size saved that `data` points to.
Schema of the linked list:
![list detail](images/list_detail.png)

