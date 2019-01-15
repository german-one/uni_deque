/*
Copyright (c) 2019 Steffen Illhardt

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef UNI_DEQUE_H_INCLUDED__
#define UNI_DEQUE_H_INCLUDED__

#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif


// Begin with opening a deque by calling UDOpen(). Assign the returned value to a variable of type ud_t.
//  Pass it as first argument to all of the other functions of this library.

// Create new elements using the UDPush... or UDInsert... functions.
//  Passed values are copied to an allocated memory space. The pointer to this memory space will be returned.
//  The UDInsert... functions insert the element before the element with the defined index. Thus, UDInsert... functions can't be used to create
//  the first element in an empty deque.

// Get the value of elements using the UDFront..., UDBack... and UDAt... funktions. The belonging elements are not removed and still in the deque.

// Remove elements using the UDPop... or UDErase... functions. They return the value of the removed element.

// Pointer values returned by certain UDPop... or UDErase... functions have to be released using UDDeleteData() if they are not used anymore.
// +++ NOTE +++ The application shall release pointers returned by functions that are marked with "/// (!)" using UDDeleteData().

// The number of elements in the deque is returned by the UDSize() function.

// Functions that fail return a zero or NULL value, except of the UDSearch... functions which return UD_INVALID_IDX in this case.
//  To distinguish between zero values saved in the elements and zero values returned due to the failing of the function, an error flag is set.
//  UDOpen() does not set the error flag. It returns a NULL pointer if it failed.
//  Unless the functions UDSize(), UDEmpty(), UDFailed(), and UDDeleteData() that always set the error flag to 0,
//  all other functions of this library set it to 1 if the functions failed and to 0 if they succeeded.
//  The UDFailed() function returns the value of this error flag and shall be called directly after a function returns to find out if it failed.
//  It is illegal to call UDFailed() after UDClose() as it is illegal to use the value returned by UDOpen() after UDClose() was called.

// Always pass the variable assigned by UDOpen() to the UDClose() function if the deque isn't used anymore.
//  It releases all allocated memory used in the deque.
// +++ NOTE +++ The application shall release the pointer returned by UDOpen() using UDClose().


/* fprintf and fscanf macros for format conversion of library-specific integer types */
#define PRI_UD_SIZE(spec) PRI##spec##64
#define SCN_UD_SIZE(spec) SCN##spec##64
// Valid specifiers are i, d, u, and x (additionally X for PRI_UD_SIZE) to be passed to the macros.

/* macro representing the return value of UDFind() if the function failed  */
#define UD_INVALID_IDX UINT64_MAX


/* Library-specific integer types. */
typedef  int64_t   ud_ssize_t; // signed type
typedef  uint64_t  ud_size_t;  // unsigned type


/* Type of a pointer to an object containig information to control the deque. */
typedef  struct ud_detail  * ud_t;


/* Type of a callback function passed to UDForEach(). */
typedef  int(*ud_for_each_proc_t)(void *element_data, void *user_parameter);
// Declaration of a callback function:
/*
  int ForEachCallback(void *p_data, void *user_parameter);
*/
// ForEachCallback is a placeholder for the application-defined function name.
// The first parameter is the pointer to the data saved in the deque element.
// The second parameter gets the pointer passed to the last parameter of UDForEach().
// Return a non-zero value to continue the enumeration or zero otherwise.
// +++ NOTE +++ The behavior is undefined if the callback function alters the number of elements or their order in the deque.


/* Type of a callback function passed to UDSort(), UDInsertSorted(), UDFind(), and UDRemove(). */
typedef  int(*ud_cmp_t)(const void *element_data_1, const void *element_data_2);
// Declaration of a callback function:
/*
  int CmpCallback(const void *p_data_1, const void *p_data_2);
*/
// CmpCallback is a placeholder for the application-defined function name.
// Return a value less than zero if the first value comes before the second.
// Return a zero value if both values are equal.
// Return a value greater than zero if the first value comes after the second.



// Overview of functions and groups of functions:
//  function                                      wrapper macro                 complexity
//  --------------------------------------------------------------------------------------
//  UDOpen                                        OPEN                          O(1)
//  UDSize                                        SIZE                          O(1)
//  UDEmpty                                       EMPTY                         O(1)
//  UDFailed                                      FAILED                        O(1)
//  UDDeleteData                                  DELETE_DATA                   O(1)
//  UDClose                                       CLOSE                         O(n)
//  UDPushFront...                                PUSH_FRONT                    O(1)
//  UDPushBack...                                 PUSH_BACK                     O(1)
//  UDInsert...                                   INSERT                        O(n)
//  UDFront...                                    FRONT                         O(1)
//  UDBack...                                     BACK                          O(1)
//  UDAt...                                       AT                            O(n)
//  UDPopFront...                                 POP_FRONT                     O(1)
//  UDPopBack...                                  POP_BACK                      O(1)
//  UDErase...                                    ERASE                         O(n)
//  UDRemove...                                   REMOVE                        O(n)
//  UDReverse                                     REVERSE                       O(n)
//  UDForEach                                     FOR_EACH                      O(n)
//  UDSort...                                     SORT_ASC / SORT_DESC          O(n log n)
//  UDInsertSorted/UDInsertAsc.../UDInsertDesc... INSERT_ASC / INSERT_DESC      O(n)
//  UDFind...                                     FIND                          O(n)

/* macros that wrap the functions of this library, specialized for a specific type */
#ifndef UD_NO_WRAPPER_MACROS
# define CONCAT_TYPE_(f,t) f##t
# define FUNCTION_TYPE_(f,t) CONCAT_TYPE_(f,t)
# ifndef UD_TYPE
#   define UD_TYPE I
# endif
# define OPEN         UDOpen
# define SIZE         UDSize
# define EMPTY        UDEmpty
# define FAILED       UDFailed
# define DELETE_DATA  UDDeleteData
# define CLOSE        UDClose
# define PUSH_FRONT   FUNCTION_TYPE_(UDPushFront,UD_TYPE)
# define PUSH_BACK    FUNCTION_TYPE_(UDPushBack,UD_TYPE)
# define INSERT       FUNCTION_TYPE_(UDInsert,UD_TYPE)
# define FRONT        FUNCTION_TYPE_(UDFront,UD_TYPE)
# define BACK         FUNCTION_TYPE_(UDBack,UD_TYPE)
# define AT           FUNCTION_TYPE_(UDAt,UD_TYPE)
# define POP_FRONT    FUNCTION_TYPE_(UDPopFront,UD_TYPE)
# define POP_BACK     FUNCTION_TYPE_(UDPopBack,UD_TYPE)
# define ERASE        FUNCTION_TYPE_(UDErase,UD_TYPE)
# define REMOVE       FUNCTION_TYPE_(UDRemove,UD_TYPE)
# define REVERSE      UDReverse
# define FOR_EACH     UDForEach
# define SORT_ASC     FUNCTION_TYPE_(UDSortAsc,UD_TYPE)
# define SORT_DESC    FUNCTION_TYPE_(UDSortDesc,UD_TYPE)
# define INSERT_ASC   FUNCTION_TYPE_(UDInsertAsc,UD_TYPE)
# define INSERT_DESC  FUNCTION_TYPE_(UDInsertDesc,UD_TYPE)
# define FIND         FUNCTION_TYPE_(UDFind,UD_TYPE)
// To use these macros, define UD_TYPE to either of these values before including "uni_deque.h":
//   C    (for char)
//   SC   (for signed char)
//   UC   (for unsigned char)
//   S    (for short)
//   US   (for unsigned short)
//   I    (for int)
//   UI   (for unsigned int)
//   L    (for long)
//   UL   (for unsigned long)
//   LL   (for long long)
//   ULL  (for unsigned long long)
//   F    (for float)
//   D    (for double)
//   LD   (for long double)
//   Str  (for null-terminated string of char)
//   WStr (for null-terminated string of wchar_t)
// If UD_TYPE was not defined explicitely then it defaults to I.
// These values equal the name appendix of the specialized functions.
// The definition of UD_TYPE does not avoid the usage of any of the functions of this library.
// If these macros conflict with macros of other libraries, define UD_NO_WRAPPER_MACROS before including
//  "uni_deque.h" in order to bypass the definition of the wrapper macros.
#endif


/* Frame functions. */
ud_t       UDOpen(void);
ud_size_t  UDSize(const ud_t deq);
int        UDEmpty(const ud_t deq);
int        UDFailed(const ud_t deq);
void       UDDeleteData(const ud_t deq, void *p_data);
void       UDClose(ud_t deq);


/* Generalized functions for pointers to values of any type. */
void  * UDPushFront(const ud_t deq, const void *const p_data, const size_t data_size);

void  * UDPushBack(const ud_t deq, const void *const p_data, const size_t data_size);

void  * UDInsert(const ud_t deq, const ud_size_t index, const void *const p_data, const size_t data_size);


void  * UDFront(const ud_t deq);

void  * UDBack(const ud_t deq);

void  * UDAt(const ud_t deq, const ud_size_t index);


void  * UDPopFront(const ud_t deq);                     /// (!)

void  * UDPopBack(const ud_t deq);                      /// (!)

void  * UDErase(const ud_t deq, const ud_size_t index); /// (!)



/* Function that removes the first element found that contains the value pointed to by p_data. */
void  * UDRemove(const ud_t deq, const void *const p_data, ud_cmp_t cmp_callback_func); /// (!)



/* Function to reverse the order of elements in the deque. */
int  UDReverse(const ud_t deq);



/* Function to enumerate the values of a range of elements. */
// The range is defined by the index where to start and the number of elements to process.
//  If a negative value is passed to the number parameter then the function will iterate towards the front of the deque.
// Pass a pointer of an application-defined function to the callback_func parameter which will be called for each value pointed to in the elements.
// The user_parameter will be passed as second argument to the callback function. This parameter can be NULL.
int  UDForEach(const ud_t deq, const ud_size_t start_idx, const ud_ssize_t number, ud_for_each_proc_t callback_func, void *user_parameter);



/* Function to sort the elements in the deque by their values. */
int  UDSort(const ud_t deq, ud_cmp_t cmp_callback_func);



/* Function that inserts a value into a sorted deque. */
void  * UDInsertSorted(const ud_t deq, const void *const p_data, const size_t data_size, ud_cmp_t cmp_callback_func);



/* Function that returns the index of the related element if the value pointed to by p_data was found in the deque or UD_INVALID_IDX otherwise. */
ud_size_t  UDFind(const ud_t deq, const void *const p_data, ud_cmp_t cmp_callback_func);



/* Specialized functions for integral values. */
char                * UDPushFrontC  (const ud_t deq, const char               value);
signed char         * UDPushFrontSC (const ud_t deq, const signed char        value);
unsigned char       * UDPushFrontUC (const ud_t deq, const unsigned char      value);
short               * UDPushFrontS  (const ud_t deq, const short              value);
unsigned short      * UDPushFrontUS (const ud_t deq, const unsigned short     value);
int                 * UDPushFrontI  (const ud_t deq, const int                value);
unsigned int        * UDPushFrontUI (const ud_t deq, const unsigned int       value);
long                * UDPushFrontL  (const ud_t deq, const long               value);
unsigned long       * UDPushFrontUL (const ud_t deq, const unsigned long      value);
long long           * UDPushFrontLL (const ud_t deq, const long long          value);
unsigned long long  * UDPushFrontULL(const ud_t deq, const unsigned long long value);

char                * UDPushBackC  (const ud_t deq, const char               value);
signed char         * UDPushBackSC (const ud_t deq, const signed char        value);
unsigned char       * UDPushBackUC (const ud_t deq, const unsigned char      value);
short               * UDPushBackS  (const ud_t deq, const short              value);
unsigned short      * UDPushBackUS (const ud_t deq, const unsigned short     value);
int                 * UDPushBackI  (const ud_t deq, const int                value);
unsigned int        * UDPushBackUI (const ud_t deq, const unsigned int       value);
long                * UDPushBackL  (const ud_t deq, const long               value);
unsigned long       * UDPushBackUL (const ud_t deq, const unsigned long      value);
long long           * UDPushBackLL (const ud_t deq, const long long          value);
unsigned long long  * UDPushBackULL(const ud_t deq, const unsigned long long value);

char                * UDInsertC  (const ud_t deq, const ud_size_t index, const char               value);
signed char         * UDInsertSC (const ud_t deq, const ud_size_t index, const signed char        value);
unsigned char       * UDInsertUC (const ud_t deq, const ud_size_t index, const unsigned char      value);
short               * UDInsertS  (const ud_t deq, const ud_size_t index, const short              value);
unsigned short      * UDInsertUS (const ud_t deq, const ud_size_t index, const unsigned short     value);
int                 * UDInsertI  (const ud_t deq, const ud_size_t index, const int                value);
unsigned int        * UDInsertUI (const ud_t deq, const ud_size_t index, const unsigned int       value);
long                * UDInsertL  (const ud_t deq, const ud_size_t index, const long               value);
unsigned long       * UDInsertUL (const ud_t deq, const ud_size_t index, const unsigned long      value);
long long           * UDInsertLL (const ud_t deq, const ud_size_t index, const long long          value);
unsigned long long  * UDInsertULL(const ud_t deq, const ud_size_t index, const unsigned long long value);


char                UDFrontC  (const ud_t deq);
signed char         UDFrontSC (const ud_t deq);
unsigned char       UDFrontUC (const ud_t deq);
short               UDFrontS  (const ud_t deq);
unsigned short      UDFrontUS (const ud_t deq);
int                 UDFrontI  (const ud_t deq);
unsigned int        UDFrontUI (const ud_t deq);
long                UDFrontL  (const ud_t deq);
unsigned long       UDFrontUL (const ud_t deq);
long long           UDFrontLL (const ud_t deq);
unsigned long long  UDFrontULL(const ud_t deq);

char                UDBackC  (const ud_t deq);
signed char         UDBackSC (const ud_t deq);
unsigned char       UDBackUC (const ud_t deq);
short               UDBackS  (const ud_t deq);
unsigned short      UDBackUS (const ud_t deq);
int                 UDBackI  (const ud_t deq);
unsigned int        UDBackUI (const ud_t deq);
long                UDBackL  (const ud_t deq);
unsigned long       UDBackUL (const ud_t deq);
long long           UDBackLL (const ud_t deq);
unsigned long long  UDBackULL(const ud_t deq);

char                UDAtC  (const ud_t deq, const ud_size_t index);
signed char         UDAtSC (const ud_t deq, const ud_size_t index);
unsigned char       UDAtUC (const ud_t deq, const ud_size_t index);
short               UDAtS  (const ud_t deq, const ud_size_t index);
unsigned short      UDAtUS (const ud_t deq, const ud_size_t index);
int                 UDAtI  (const ud_t deq, const ud_size_t index);
unsigned int        UDAtUI (const ud_t deq, const ud_size_t index);
long                UDAtL  (const ud_t deq, const ud_size_t index);
unsigned long       UDAtUL (const ud_t deq, const ud_size_t index);
long long           UDAtLL (const ud_t deq, const ud_size_t index);
unsigned long long  UDAtULL(const ud_t deq, const ud_size_t index);


char                UDPopFrontC  (const ud_t deq);
signed char         UDPopFrontSC (const ud_t deq);
unsigned char       UDPopFrontUC (const ud_t deq);
short               UDPopFrontS  (const ud_t deq);
unsigned short      UDPopFrontUS (const ud_t deq);
int                 UDPopFrontI  (const ud_t deq);
unsigned int        UDPopFrontUI (const ud_t deq);
long                UDPopFrontL  (const ud_t deq);
unsigned long       UDPopFrontUL (const ud_t deq);
long long           UDPopFrontLL (const ud_t deq);
unsigned long long  UDPopFrontULL(const ud_t deq);

char                UDPopBackC  (const ud_t deq);
signed char         UDPopBackSC (const ud_t deq);
unsigned char       UDPopBackUC (const ud_t deq);
short               UDPopBackS  (const ud_t deq);
unsigned short      UDPopBackUS (const ud_t deq);
int                 UDPopBackI  (const ud_t deq);
unsigned int        UDPopBackUI (const ud_t deq);
long                UDPopBackL  (const ud_t deq);
unsigned long       UDPopBackUL (const ud_t deq);
long long           UDPopBackLL (const ud_t deq);
unsigned long long  UDPopBackULL(const ud_t deq);

char                UDEraseC  (const ud_t deq, const ud_size_t index);
signed char         UDEraseSC (const ud_t deq, const ud_size_t index);
unsigned char       UDEraseUC (const ud_t deq, const ud_size_t index);
short               UDEraseS  (const ud_t deq, const ud_size_t index);
unsigned short      UDEraseUS (const ud_t deq, const ud_size_t index);
int                 UDEraseI  (const ud_t deq, const ud_size_t index);
unsigned int        UDEraseUI (const ud_t deq, const ud_size_t index);
long                UDEraseL  (const ud_t deq, const ud_size_t index);
unsigned long       UDEraseUL (const ud_t deq, const ud_size_t index);
long long           UDEraseLL (const ud_t deq, const ud_size_t index);
unsigned long long  UDEraseULL(const ud_t deq, const ud_size_t index);

char                UDRemoveC  (const ud_t deq, const char               value);
signed char         UDRemoveSC (const ud_t deq, const signed char        value);
unsigned char       UDRemoveUC (const ud_t deq, const unsigned char      value);
short               UDRemoveS  (const ud_t deq, const short              value);
unsigned short      UDRemoveUS (const ud_t deq, const unsigned short     value);
int                 UDRemoveI  (const ud_t deq, const int                value);
unsigned int        UDRemoveUI (const ud_t deq, const unsigned int       value);
long                UDRemoveL  (const ud_t deq, const long               value);
unsigned long       UDRemoveUL (const ud_t deq, const unsigned long      value);
long long           UDRemoveLL (const ud_t deq, const long long          value);
unsigned long long  UDRemoveULL(const ud_t deq, const unsigned long long value);


int  UDSortAscC   (const ud_t deq);
int  UDSortDescC  (const ud_t deq);
int  UDSortAscSC  (const ud_t deq);
int  UDSortDescSC (const ud_t deq);
int  UDSortAscUC  (const ud_t deq);
int  UDSortDescUC (const ud_t deq);
int  UDSortAscS   (const ud_t deq);
int  UDSortDescS  (const ud_t deq);
int  UDSortAscUS  (const ud_t deq);
int  UDSortDescUS (const ud_t deq);
int  UDSortAscI   (const ud_t deq);
int  UDSortDescI  (const ud_t deq);
int  UDSortAscUI  (const ud_t deq);
int  UDSortDescUI (const ud_t deq);
int  UDSortAscL   (const ud_t deq);
int  UDSortDescL  (const ud_t deq);
int  UDSortAscUL  (const ud_t deq);
int  UDSortDescUL (const ud_t deq);
int  UDSortAscLL  (const ud_t deq);
int  UDSortDescLL (const ud_t deq);
int  UDSortAscULL (const ud_t deq);
int  UDSortDescULL(const ud_t deq);


char                * UDInsertAscC   (const ud_t deq, const char               value);
char                * UDInsertDescC  (const ud_t deq, const char               value);
signed char         * UDInsertAscSC  (const ud_t deq, const signed char        value);
signed char         * UDInsertDescSC (const ud_t deq, const signed char        value);
unsigned char       * UDInsertAscUC  (const ud_t deq, const unsigned char      value);
unsigned char       * UDInsertDescUC (const ud_t deq, const unsigned char      value);
short               * UDInsertAscS   (const ud_t deq, const short              value);
short               * UDInsertDescS  (const ud_t deq, const short              value);
unsigned short      * UDInsertAscUS  (const ud_t deq, const unsigned short     value);
unsigned short      * UDInsertDescUS (const ud_t deq, const unsigned short     value);
int                 * UDInsertAscI   (const ud_t deq, const int                value);
int                 * UDInsertDescI  (const ud_t deq, const int                value);
unsigned int        * UDInsertAscUI  (const ud_t deq, const unsigned int       value);
unsigned int        * UDInsertDescUI (const ud_t deq, const unsigned int       value);
long                * UDInsertAscL   (const ud_t deq, const long               value);
long                * UDInsertDescL  (const ud_t deq, const long               value);
unsigned long       * UDInsertAscUL  (const ud_t deq, const unsigned long      value);
unsigned long       * UDInsertDescUL (const ud_t deq, const unsigned long      value);
long long           * UDInsertAscLL  (const ud_t deq, const long long          value);
long long           * UDInsertDescLL (const ud_t deq, const long long          value);
unsigned long long  * UDInsertAscULL (const ud_t deq, const unsigned long long value);
unsigned long long  * UDInsertDescULL(const ud_t deq, const unsigned long long value);


ud_size_t  UDFindC  (const ud_t deq, const char               value);
ud_size_t  UDFindSC (const ud_t deq, const signed char        value);
ud_size_t  UDFindUC (const ud_t deq, const unsigned char      value);
ud_size_t  UDFindS  (const ud_t deq, const short              value);
ud_size_t  UDFindUS (const ud_t deq, const unsigned short     value);
ud_size_t  UDFindI  (const ud_t deq, const int                value);
ud_size_t  UDFindUI (const ud_t deq, const unsigned int       value);
ud_size_t  UDFindL  (const ud_t deq, const long               value);
ud_size_t  UDFindUL (const ud_t deq, const unsigned long      value);
ud_size_t  UDFindLL (const ud_t deq, const long long          value);
ud_size_t  UDFindULL(const ud_t deq, const unsigned long long value);



/* Specialized functions for floating point values. */
float        * UDPushFrontF (const ud_t deq, const float       value);
double       * UDPushFrontD (const ud_t deq, const double      value);
long double  * UDPushFrontLD(const ud_t deq, const long double value);

float        * UDPushBackF (const ud_t deq, const float       value);
double       * UDPushBackD (const ud_t deq, const double      value);
long double  * UDPushBackLD(const ud_t deq, const long double value);

float        * UDInsertF (const ud_t deq, const ud_size_t index, const float       value);
double       * UDInsertD (const ud_t deq, const ud_size_t index, const double      value);
long double  * UDInsertLD(const ud_t deq, const ud_size_t index, const long double value);


float        UDFrontF (const ud_t deq);
double       UDFrontD (const ud_t deq);
long double  UDFrontLD(const ud_t deq);

float        UDBackF (const ud_t deq);
double       UDBackD (const ud_t deq);
long double  UDBackLD(const ud_t deq);

float        UDAtF (const ud_t deq, const ud_size_t index);
double       UDAtD (const ud_t deq, const ud_size_t index);
long double  UDAtLD(const ud_t deq, const ud_size_t index);


float        UDPopFrontF (const ud_t deq);
double       UDPopFrontD (const ud_t deq);
long double  UDPopFrontLD(const ud_t deq);

float        UDPopBackF (const ud_t deq);
double       UDPopBackD (const ud_t deq);
long double  UDPopBackLD(const ud_t deq);

float        UDEraseF (const ud_t deq, const ud_size_t index);
double       UDEraseD (const ud_t deq, const ud_size_t index);
long double  UDEraseLD(const ud_t deq, const ud_size_t index);

float        UDRemoveF (const ud_t deq, const float       value);
double       UDRemoveD (const ud_t deq, const double      value);
long double  UDRemoveLD(const ud_t deq, const long double value);


int  UDSortAscF  (const ud_t deq);
int  UDSortDescF (const ud_t deq);
int  UDSortAscD  (const ud_t deq);
int  UDSortDescD (const ud_t deq);
int  UDSortAscLD (const ud_t deq);
int  UDSortDescLD(const ud_t deq);


float        * UDInsertAscF  (const ud_t deq, const float       value);
float        * UDInsertDescF (const ud_t deq, const float       value);
double       * UDInsertAscD  (const ud_t deq, const double      value);
double       * UDInsertDescD (const ud_t deq, const double      value);
long double  * UDInsertAscLD (const ud_t deq, const long double value);
long double  * UDInsertDescLD(const ud_t deq, const long double value);


ud_size_t  UDFindF (const ud_t deq, const float       value);
ud_size_t  UDFindD (const ud_t deq, const double      value);
ud_size_t  UDFindLD(const ud_t deq, const long double value);



/* Specialized functions for null-terminated strings. */
char     * UDPushFrontStr (const ud_t deq, const char    *str);
wchar_t  * UDPushFrontWStr(const ud_t deq, const wchar_t *str);

char     * UDPushBackStr (const ud_t deq, const char    *str);
wchar_t  * UDPushBackWStr(const ud_t deq, const wchar_t *str);

char     * UDInsertStr (const ud_t deq, const ud_size_t index, const char    *str);
wchar_t  * UDInsertWStr(const ud_t deq, const ud_size_t index, const wchar_t *str);


char     * UDFrontStr (const ud_t deq);
wchar_t  * UDFrontWStr(const ud_t deq);

char     * UDBackStr (const ud_t deq);
wchar_t  * UDBackWStr(const ud_t deq);

char     * UDAtStr (const ud_t deq, const ud_size_t index);
wchar_t  * UDAtWStr(const ud_t deq, const ud_size_t index);


char     * UDPopFrontStr (const ud_t deq);                     /// (!)
wchar_t  * UDPopFrontWStr(const ud_t deq);                     /// (!)

char     * UDPopBackStr (const ud_t deq);                      /// (!)
wchar_t  * UDPopBackWStr(const ud_t deq);                      /// (!)

char     * UDEraseStr (const ud_t deq, const ud_size_t index); /// (!)
wchar_t  * UDEraseWStr(const ud_t deq, const ud_size_t index); /// (!)

char     * UDRemoveStr (const ud_t deq, const char    *str);   /// (!)
wchar_t  * UDRemoveWStr(const ud_t deq, const wchar_t *str);   /// (!)


int  UDSortAscStr  (const ud_t deq);
int  UDSortDescStr (const ud_t deq);
int  UDSortAscWStr (const ud_t deq);
int  UDSortDescWStr(const ud_t deq);


char     * UDInsertAscStr  (const ud_t deq, const char    *str);
char     * UDInsertDescStr (const ud_t deq, const char    *str);
wchar_t  * UDInsertAscWStr (const ud_t deq, const wchar_t *str);
wchar_t  * UDInsertDescWStr(const ud_t deq, const wchar_t *str);


ud_size_t  UDFindStr (const ud_t deq, const char    *str);
ud_size_t  UDFindWStr(const ud_t deq, const wchar_t *str);


#ifdef __cplusplus
}
#endif

#endif // UNI_DEQUE_H_INCLUDED__
