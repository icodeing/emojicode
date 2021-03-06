//
//  String.h
//  Emojicode
//
//  Created by Theo Weidmann on 02.02.15.
//  Copyright (c) 2015 Theo Weidmann. All rights reserved.
//

#ifndef EmojicodeString_h
#define EmojicodeString_h

#include "EmojicodeAPI.hpp"
#include "List.h"

namespace Emojicode {

struct String {
    /// The number of characters. Strings are not null terminated.
    EmojicodeInteger length;
    /// The characters (Unicode Codepoints, @c EmojicodeChar) of this string.
    Object *charactersObject;

    EmojicodeChar* characters() { return charactersObject->val<EmojicodeChar>(); }
};

extern Object **stringPool;
#define emptyString (stringPool[0])

/** Compares if the value of @c a is equal to @c b. */
bool stringEqual(String *a, String *b);

/// Converts the string to a UTF8 char array and returns it.
/// @warning The returned pointer points into an object allocated by the Emojicode memory manager. It must not be free’d
/// and will not survive the imminent garbage collector cycle.
const char* stringToCString(Object *str);

/** Creates a string from a UTF8 C string. The string must be null terminated! */
Object* stringFromChar(const char *cstring);

/** 
 * Tries to parse the string in the this-slot on the stack as JSON.
 */
void parseJSON(Thread *thread, Box *destination);

void stringMark(Object *self);

void initStringFromSymbolList(String *string, List *list);

void stringPrintStdoutBrigde(Thread *thread, Value *destination);
void stringEqualBridge(Thread *thread, Value *destination);
void stringSubstringBridge(Thread *thread, Value *destination);
void stringIndexOf(Thread *thread, Value *destination);
void stringTrimBridge(Thread *thread, Value *destination);
void stringGetInput(Thread *thread, Value *destination);
void stringSplitByStringBridge(Thread *thread, Value *destination);
void stringLengthBridge(Thread *thread, Value *destination);
void stringUTF8LengthBridge(Thread *thread, Value *destination);
void stringByAppendingSymbolBridge(Thread *thread, Value *destination);
void stringSymbolAtBridge(Thread *thread, Value *destination);
void stringBeginsWithBridge(Thread *thread, Value *destination);
void stringEndsWithBridge(Thread *thread, Value *destination);
void stringSplitBySymbolBridge(Thread *thread, Value *destination);
void stringToData(Thread *thread, Value *destination);
void stringToCharacterList(Thread *thread, Value *destination);
void stringJSON(Thread *thread, Value *destination);
void stringFromSymbolListBridge(Thread *thread, Value *destination);
void stringFromStringList(Thread *thread, Value *destination);
void stringToInteger(Thread *thread, Value *destination);
void stringToDouble(Thread *thread, Value *destination);
void stringToUppercase(Thread *thread, Value *destination);
void stringToLowercase(Thread *thread, Value *destination);
void stringCompareBridge(Thread *thread, Value *destination);

}

#endif /* EmojicodeString_h */
