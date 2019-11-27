#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

NSApplication *application;
NSAutoreleasePool *pool;

uint8_t keys[256] = {0};

bool keepRunning = true;

@interface PDLView : NSView

@end

@interface AppDelegate : NSObject<NSApplicationDelegate>

@end

@interface WindowDelegate : NSObject<NSWindowDelegate>

@end

@interface Window : NSWindow

@end