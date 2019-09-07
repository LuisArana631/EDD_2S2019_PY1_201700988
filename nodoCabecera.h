#ifndef NODOCABECERA_H
#define NODOCABECERA_H

#include <stdlib.h>
#include "columna.h"

using namespace std;

class nodoCabecera{
public:
    int x;
    nodoCabecera* siguiente;
    nodoCabecera* anterior;
    columna* col;

    nodoCabecera(int);
};

#endif // NODOCABECERA_H
