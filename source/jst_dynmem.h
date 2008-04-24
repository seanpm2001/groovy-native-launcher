//  A simple library for creating a native launcher for a java app
//
//  Copyright (c) 2006 Antti Karanta (Antti dot Karanta (at) hornankuusi dot fi) 
//
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in
//  compliance with the License. You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software distributed under the License is
//  distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
//  implied. See the License for the specific language governing permissions and limitations under the
//  License.
//
//  Author:  Antti Karanta (Antti dot Karanta (at) hornankuusi dot fi) 


#if !defined( _JST_DYNMEM_H_ )
#  define _JST_DYNMEM_H_

/** Appends the given strings to target. size param tells the current size of target (target must have been
 * dynamically allocated, i.e. not from stack). If necessary, target is reallocated into a bigger space. 
 * Returns the possibly new location of target, and modifies the size inout parameter accordingly. 
 * If target is NULL, it is allocated w/ the given size (or bigger if given size does not fit all the given strings). 
 * In case target is NULL and you are not interested how big the buffer became, you can give NULL as size. */
char* jst_append( char* target, size_t* size, ... ) ; 

/** Concatenates the strings in the given null terminated str array to a single string, which must be freed by the caller. Returns null on error. */
char* jst_concatenateStrArray( char** nullTerminatedStringArray ) ;

/** If array is NULL, a new one will be created, size arlen. The given array will be reallocated if there is not enough space.
 * The newly allocated memory (in both cases) contains all 0s. If NULL is given as the item, zeroes are added at the given array position. */
void* jst_appendArrayItem( void* array, int index, size_t* arlen, void* item, int item_size_in_bytes ) ;

/** Appends the given pointer to the given null terminated pointer array.
 * given pointer to array may point to NULL, in which case a new array is created. 
 * Returns NULL on error. 
 * @param item if NULL, the given array is not modified and NULL is returned. */
void** jst_appendPointer( void*** pointerToNullTerminatedPointerArray, size_t* arrSize, void* item ) ;

int jst_pointerArrayLen( void** nullTerminatedPointerArray ) ;

/** Returns the given item, NULL if the item was not in the array. */
void* jst_removePointer( void** nullTerminatedPointerArray, void* itemToBeRemoved ) ;

/** returns 0 if the given item was not in the given array. pointer pointed to is set to NULL. */
int jst_removeAndFreePointer( void** nullTerminatedPointerArray, void** pointerToItemToBeRemoved ) ;


/** Given a null terminated string array, makes a dynamically allocated copy of it that can be freed using a single call to free. Useful for constructing
 * string arrays returned to caller who must free them. In technical detail, the returned mem block first contains all the char*, the termiting NULL and
 * then all the strings one after another. Note that whoever uses the char** does not need to know this mem layout. */
char** jst_packStringArray( char** nullTerminatedStringArray ) ;

typedef enum { PREFIX_SEARCH, SUFFIX_SEARCH, EXACT_SEARCH } SearchMode;

/** The first param may be NULL, it is considered an empty array. */
jboolean jst_arrayContainsString( char** nullTerminatedArray, const char* searchString, SearchMode mode ) ; 

/** These wrap the corresponding memory allocation routines. The only difference is that these print an error message if
 * the call fails. */
void* jst_malloc( size_t size ) ;
void* jst_calloc( size_t nelem, size_t elsize ) ;
void* jst_realloc( void* ptr, size_t size ) ;
char* jst_strdup( const char* s ) ;


#define jst_free( x ) free( x ) ; x = NULL

/** Frees all the pointers in the given array, the array itself and sets the reference to NULL */
void jst_freeAll( void*** pointerToNullTerminatedPointerArray ) ;



#endif
