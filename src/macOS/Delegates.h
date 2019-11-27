#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

@interface PDLView : NSView
	@property void *bitmapMemory;
	@property int bitmapWidth;
	@property int bitmapHeight;

	@property CGImageRef image;
	@property CGDataProviderRef provider;
@end

@interface AppDelegate : NSObject<NSApplicationDelegate>

@end

@interface WindowDelegate : NSObject<NSWindowDelegate>

@end

@interface Window : NSWindow

@end

NSApplication *application;
NSWindow *window;
PDLView *view;

uint8_t keys[256] = {0};

bool keepRunning = true;