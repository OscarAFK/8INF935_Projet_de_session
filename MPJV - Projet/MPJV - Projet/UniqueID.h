#pragma once
#include <iostream>

//Taken from https://www.oreilly.com/library/view/c-cookbook/0596007612/ch08s09.html

class UniqueID {
protected:
    static int nextID;
public:
    int id;
    UniqueID();
    UniqueID(const UniqueID& orig);
    UniqueID& operator=(const UniqueID& orig);
};