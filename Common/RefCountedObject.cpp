#include "Config.h"

#include "RefCountedObject.h"



RefCountedObject::RefCountedObject(): _counter(1)
{
}


RefCountedObject::~RefCountedObject()
{
}

