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
}


void PDLBlit(uint32_t *bitmap) {
	if (view != NULL && view.bitmapMemory != NULL)
    {
        memcpy(view.bitmapMemory, bitmap, sizeof(uint32_t) * view.bitmapWidth * view.bitmapHeight);

        view.needsDisplay = YES;
    }
}

uint8_t PDLGetKey(uint8_t key) {
	return keys[key];
}

bool PDLDoWindowMessages() {
	// NSEvent *keyDownEvent = [application nextEventMatchingMask:NSEventMaskKeyDown
	// 							  untilDate:[NSDate distantFuture]
	// 							  inMode:NSDefaultRunLoopMode
	// 							  dequeue:YES];

	NSEvent *event = [application nextEventMatchingMask:NSEventMaskAny
								  untilDate:[NSDate distantPast]
								  inMode:NSDefaultRunLoopMode
								  dequeue:YES];
	[application sendEvent:event];
	[application updateWindows];

	return keepRunning;
}

bool PDLInit(const char *title, uint32_t title_len, uint32_t x, uint32_t y,
             uint32_t width, uint32_t height, uint32_t scale) 
{
	application = [NSApplication sharedApplication];

	if(application == nil) {
		return false;
	}

	NSRect rect;
	NSString *nsTitle = [[NSString alloc] initWithBytes:(const void*)title 
							   length:(NSUInteger)title_len
							   encoding:NSASCIIStringEncoding];

	rect = NSMakeRect(x,y, width*scale, height*scale);

	window = [[Window alloc] initWithContentRect: rect
							  styleMask:NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskMiniaturizable
							  backing:NSBackingStoreBuffered
							  defer:NO];

	view = [[PDLView alloc] initWithFrame:rect];

	[window setTitle:nsTitle];
	[window setContentView:view];
	[window setDelegate:[[WindowDelegate alloc] init]];
	[window makeKeyAndOrderFront: nil];

	if(application.mainMenu == nil)
	{
		NSMenu* mainMenu = [[NSMenu alloc] initWithTitle:nsTitle];
		if(mainMenu == nil) {
			return false;
		}
		application.mainMenu = mainMenu;
	}

	view.bitmapMemory = calloc(sizeof(uint32_t)*width*height, sizeof(uint8_t));
	if(view.bitmapMemory == NULL) {
		NSLog(@"Could not alloc bitmap");
		return false;
	}

	view.bitmapWidth = width;
	view.bitmapHeight = height;

	[application setDelegate:[[AppDelegate alloc] init]];
	[application setActivationPolicy:NSApplicationActivationPolicyRegular];
	[application setPresentationOptions:NSApplicationPresentationDefault];
	[application finishLaunching];

	return true;
}