#pragma once  

#include "ofConstants.h"  

#if defined(TARGET_OSX) || defined(TARGET_OF_IPHONE)  

/// \class ofAutoreleasePool  
/// \brief a Mac/iOS-specific class that creates a scoped NSAutoreleasePool which will handle any Cocoa objects that are autoreleased  
///  
/// While the normal Cocoa event loop is running, there is always a Cocoa-supplied NSAutoreleasePool in place,  
/// but if for some reason Cocoa code will be called  in some other context (another thread, or before the event loop has started),  
/// ofAutoreleasePool can be used to manually create a NSAutoreleasePool  
/// Just place an instance of this class as a local variable on the stack. While the variable is alive, it will take ownership of any autoreleased objects,  
/// and when the ofAutoreleasePool instance is deleted, it will delete any autoreleased objects that it still owns.  

class ofAutoreleasePool {  
public:  
	ofAutoreleasePool();  
	~ofAutoreleasePool();  
	
private:  
	// copying is not supported  
	ofAutoreleasePool(const ofAutoreleasePool&);  
	ofAutoreleasePool& operator=(const ofAutoreleasePool&);  
	
	void* pool;  
};  

#endif // defined(TARGET_OSX) || defined(TARGET_OF_IPHONE)  