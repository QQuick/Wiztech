#include <iostream>
namespace st = std;

#include "heaper.hpp"

namespace heaper {

// ====== Methods    

String::String (int capacity):
    aSize (0),
    content (new char (capacity + 1))
{
    content [0] = 0;
}
    
String::String (char const * const content):
    size (strlen (content),
    content (new char (aSize + 1))
{}

String::String (String &aString):
    aSize (astring.aSize),
    content (new char (aSize + 1))
{
    st::cout << "Copy construction" << '\n';
    strcpy (content, aString.content);
}
        
String::String (String &&aString):
    aSize (aString.aSize),
    content (aString.content)
{
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
    return *this;
}

~String::String () {
    delete [] content;
}

int size () {
    return aSize;
}

// ====== Friends
    
String &&operator + (String &string0, String &string1) {
    String result (string0.aSize + string1.aSize);
    strcat (strcat (result.content, string0), string1));
    return st::move (result);
}

istream &operator >> (st::istream &inputStream, String &aString) {
    int const bufferSize = 1024;
    auto buffer = String (bufferSize);
    inputStream.getline (buffer.content, bufferSize, 0);
    aString = st::move (buffer);
}

ostream &operator << (st::ostream &outputStream, String &aString) {
    return outputStream << aString.content;
}
