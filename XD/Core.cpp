#include "Core.h"

long long nextId = 0;

long long Core::getNewId()
{
    nextId++;
    return nextId - 1;
}
