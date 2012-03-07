#include "ofAutoreleasePool.h"  

#if defined(TARGET_OSX) || defined(TARGET_OF_IPHONE)  

#include "GL/glew.h" // Due to a conflict between glew.h and Cocoa.h, glew.h must always be included _first_ whenever Cocoa.h is included  
#include <Cocoa/Cocoa.h>  

ofAutoreleasePool::ofAutoreleasePool() :  
pool(NULL)  
{  
    pool = [[NSAutoreleasePool alloc] init];  
}  

ofAutoreleasePool::~ofAutoreleasePool() {  
    [reinterpret_cast<NSAutoreleasePool*>(pool) drain];  
    pool = NULL;  
}  

#endif // defined(TARGET_OSX) || defined(TARGET_OF_IPHONE)  