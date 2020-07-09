#pragma once

#include <iostream>
namespace st = std;

namespace heaper {

class String {
    public:
        String (int capacity = 0);
        String (char const * const content);
        String (String &aString);
        String (String &&aString);
        String &operator = (String &aString);
        String &operator = (String &&aString);
        ~String ();
        int size ();

    protected:
        char *content;
        int aSize;
        
        friend String operator + (String &string0, String &string1);
        friend st::istream &operator >> (st::istream &inputStream, String &aString);
        friend st::ostream &operator << (st::ostream &outputStream, String &aString);
};
 
}
