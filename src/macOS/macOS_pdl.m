#import "../pdl_api.h"
#import "Delegates.h"

void PDLShowWindow() {
}

void PDLHideWindow() {
}

void PDLResizeWindow(uint32_t width, uint32_t height) {
}

void PDLCloseWindow() {
	keepRunning = false;
	[application replyToApplicationShouldTerminate:YES];

	[pool release];
}


void PDLBlit(uint32_t *bitmap) {
}


uint8_t PDLGetKey(uint8_t key) {
	return keys[key];
}

bool PDLDoWindowMessages() {
	NSAutoreleasePool* inputPool = [[NSAutoreleasePool alloc] init];

	// NSEvent *keyDownEvent = [application nextEventMatchingMask:NSEventMaskKeyDown
	// 							  untilDate:[NSDate distantFuture]
	// 							  inMode:NSDefaultRunLoopMode
	// 							  dequeue:YES];

	// if(keyDownEvent != nil) {
	// 	mouseDown = true;
	// } else {
	// 	mouseDown = false;
	// }

	NSEvent *event = [application nextEventMatchingMask:NSEventMaskAny
								  untilDate:[NSDate distantFuture]
								  inMode:NSDefaultRunLoopMode
								  dequeue:YES];
	[application sendEvent:event];
	[application updateWindows];

	[inputPool release];

	return keepRunning;
}

bool PDLInit(const char *title, uint32_t title_len, uint32_t x, uint32_t y,
             uint32_t width, uint32_t height) 
{
	application = [NSApplication sharedApplication];

	if(application == nil) {
		return false;
	}

	pool = [[NSAutoreleasePool alloc] init];

	NSWindow *window;
	NSView *view;
	NSRect rect;
	NSString *nsTitle = [[NSString alloc] initWithBytes:(const void*)title 
							   length:(NSUInteger)title_len
							   encoding:NSASCIIStringEncoding];

	rect = NSMakeRect(x,y, width, height);

	window = [[Window alloc] initWithContentRect: rect
							  styleMask:NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskMiniaturizable
							  backing:NSBackingStoreBuffered
							  defer:NO];

	view = [[[PDLView alloc] initWithFrame:rect] autorelease];

	[window setTitle:nsTitle];
	[window setContentView:view];
	[window setDelegate:[[WindowDelegate alloc] init]];
	[window makeKeyAndOrderFront: nil];

	if(application.mainMenu == nil)
	{
		NSMenu* mainMenu = [[NSMenu alloc] initWithTitle:nsTitle];
		if(mainMenu == nil) {
			[pool release];
			return false;
		}
		application.mainMenu = mainMenu;
	}

	[application setDelegate:[[AppDelegate alloc] init]];
	[application setActivationPolicy:NSApplicationActivationPolicyRegular];
	[application setPresentationOptions:NSApplicationPresentationDefault];
	[application finishLaunching];


	return true;
}