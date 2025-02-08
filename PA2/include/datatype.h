#ifndef DATATYPE_H
#define DATATYPE_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    BLACK,  // INT
    GREEN,  // FLOAT
    BLUE,   // DOUBLE
    RED,    // CHAR
} DataType;

#endif