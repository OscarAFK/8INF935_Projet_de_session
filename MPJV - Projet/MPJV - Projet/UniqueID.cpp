#include "UniqueID.h"

int UniqueID::nextID = 0;

UniqueID::UniqueID() {
    id = ++nextID;
}

UniqueID::UniqueID(const UniqueID& orig) {
    id = orig.id;
}

UniqueID& UniqueID::operator=(const UniqueID& orig) {
    id = orig.id;
    return(*this);
}