// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <cstring>

#include "heaper.hpp"

namespace heaper {

// ====== Methods    

String::String (int capacity):
    aSize (0),
    content (new char (capacity + 1))
{
    st::cout << "Allocation construction" << '\n';
    content [0] = 0;
}
    
String::String (char const * const content):
    aSize (strlen (content)),
    content (new char (aSize + 1))
{
    st::cout << "Conversion construction" << '\n';
    strcpy (this->content, content);
}

String::String (String &aString):
    aSize (aString.aSize),
    content (new char (aSize + 1))
{
    st::cout << "Copy construction" << '\n';
    strcpy (content, aString.content);
}
        
String::String (String &&aString):
    aSize (aString.aSize),
    content (aString.content)
{
    aString.content = 0;
    st::cout << "Move construction" << '\n';
}

String &String::operator = (String &aString) {
    st::cout << "Copy assignment" << '\n';
    aSize = aString.aSize;
    content = new char (aSize + 1);
    strcpy (content, aString.content);
    return *this;
}

String &String::operator = (String &&aString) {
    st::cout << "Move assignment" << '\n';
    aSize = aString.aSize;
    content = aString.content;
    aString.content = 0;
    return *this;
}

String::~String () {
    delete [] content;
}

int String::size () {
    return aSize;
}

// ====== Friends
    
String operator + (String &string0, String &string1) {
    String result (string0.aSize + string1.aSize);
    strcat (strcat (result.content, string0.content), string1.content);
    return st::move (result);
}

st::istream &operator >> (st::istream &inputStream, String &aString) {
    int const bufferSize = 1024;
    auto buffer = String (bufferSize);
    inputStream.getline (buffer.content, bufferSize);
    aString = buffer;
    return inputStream;
}

st::ostream &operator << (st::ostream &outputStream, String &aString) {
    outputStream << aString.content;
    return outputStream;
}

}

