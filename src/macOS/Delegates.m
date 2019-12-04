#import "Delegates.h"
#import <Carbon/Carbon.h>

@implementation AppDelegate
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
	keepRunning = false;

	return NSTerminateCancel;
}
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
	keepRunning = false;

	return NO;
}
@end

@implementation WindowDelegate
- (BOOL)windowShouldClose:(NSWindow *)sender
{
	keepRunning = false;

	return YES;
}
@end

@implementation Window
- (void)keyDown:(NSEvent *)event
{
	switch(event.keyCode)
	{
		case kVK_LeftArrow:  { keys[0x7b] = 1; } break;
		case kVK_RightArrow: { keys[0x7c] = 1; } break;
		case kVK_UpArrow:    { keys[0x7e] = 1; } break;
		case kVK_DownArrow:  { keys[0x7d] = 1; } break;

		case kVK_ANSI_0: { keys[0x1d] = 1; } break;
		case kVK_ANSI_1: { keys[0x12] = 1; } break;
		case kVK_ANSI_2: { keys[0x13] = 1; } break;
		case kVK_ANSI_3: { keys[0x14] = 1; } break;
		case kVK_ANSI_4: { keys[0x15] = 1; } break;
		case kVK_ANSI_5: { keys[0x17] = 1; } break;
		case kVK_ANSI_6: { keys[0x16] = 1; } break;
		case kVK_ANSI_7: { keys[0x1a] = 1; } break;
		case kVK_ANSI_8: { keys[0x1c] = 1; } break;
		case kVK_ANSI_9: { keys[0x19] = 1; } break;

		case kVK_ANSI_A: { keys[0x41] = 1; } break;
		case kVK_ANSI_B: { keys[0x42] = 1; } break;
		case kVK_ANSI_C: { keys[0x43] = 1; } break;
		case kVK_ANSI_D: { keys[0x44] = 1; } break;
		case kVK_ANSI_E: { keys[0x45] = 1; } break;
		case kVK_ANSI_F: { keys[0x46] = 1; } break;
		case kVK_ANSI_G: { keys[0x47] = 1; } break;
		case kVK_ANSI_H: { keys[0x48] = 1; } break;
		case kVK_ANSI_I: { keys[0x49] = 1; } break;
		case kVK_ANSI_J: { keys[0x4a] = 1; } break;
		case kVK_ANSI_K: { keys[0x4b] = 1; } break;
		case kVK_ANSI_L: { keys[0x4c] = 1; } break;
		case kVK_ANSI_M: { keys[0x4d] = 1; } break;
		case kVK_ANSI_N: { keys[0x4e] = 1; } break;
		case kVK_ANSI_O: { keys[0x4f] = 1; } break;
		case kVK_ANSI_P: { keys[0x50] = 1; } break;
		case kVK_ANSI_Q: { keys[0x51] = 1; } break;
		case kVK_ANSI_R: { keys[0x52] = 1; } break;
		case kVK_ANSI_S: { keys[0x53] = 1; } break;
		case kVK_ANSI_T: { keys[0x54] = 1; } break;
		case kVK_ANSI_U: { keys[0x55] = 1; } break;
		case kVK_ANSI_V: { keys[0x56] = 1; } break;
		case kVK_ANSI_W: { keys[0x57] = 1; } break;
		case kVK_ANSI_X: { keys[0x58] = 1; } break;
		case kVK_ANSI_Y: { keys[0x59] = 1; } break;
		case kVK_ANSI_Z: { keys[0x5a] = 1; } break;

		case kVK_Escape: { keys[0x1b] = 1; } break;

		default: break;
	}
}
- (void)keyUp:(NSEvent *)event
{
	switch(event.keyCode)
	{
		case kVK_LeftArrow:  { keys[0x7b] = 0; } break;
		case kVK_RightArrow: { keys[0x7c] = 0; } break;
		case kVK_UpArrow:    { keys[0x7e] = 0; } break;
		case kVK_DownArrow:  { keys[0x7d] = 0; } break;

		case kVK_ANSI_0: { keys[0x1d] = 0; } break;
		case kVK_ANSI_1: { keys[0x12] = 0; } break;
		case kVK_ANSI_2: { keys[0x13] = 0; } break;
		case kVK_ANSI_3: { keys[0x14] = 0; } break;
		case kVK_ANSI_4: { keys[0x15] = 0; } break;
		case kVK_ANSI_5: { keys[0x17] = 0; } break;
		case kVK_ANSI_6: { keys[0x16] = 0; } break;
		case kVK_ANSI_7: { keys[0x1a] = 0; } break;
		case kVK_ANSI_8: { keys[0x1c] = 0; } break;
		case kVK_ANSI_9: { keys[0x19] = 0; } break;

		case kVK_ANSI_A: { keys[0x41] = 0; } break;
		case kVK_ANSI_B: { keys[0x42] = 0; } break;
		case kVK_ANSI_C: { keys[0x43] = 0; } break;
		case kVK_ANSI_D: { keys[0x44] = 0; } break;
		case kVK_ANSI_E: { keys[0x45] = 0; } break;
		case kVK_ANSI_F: { keys[0x46] = 0; } break;
		case kVK_ANSI_G: { keys[0x47] = 0; } break;
		case kVK_ANSI_H: { keys[0x48] = 0; } break;
		case kVK_ANSI_I: { keys[0x49] = 0; } break;
		case kVK_ANSI_J: { keys[0x4a] = 0; } break;
		case kVK_ANSI_K: { keys[0x4b] = 0; } break;
		case kVK_ANSI_L: { keys[0x4c] = 0; } break;
		case kVK_ANSI_M: { keys[0x4d] = 0; } break;
		case kVK_ANSI_N: { keys[0x4e] = 0; } break;
		case kVK_ANSI_O: { keys[0x4f] = 0; } break;
		case kVK_ANSI_P: { keys[0x50] = 0; } break;
		case kVK_ANSI_Q: { keys[0x51] = 0; } break;
		case kVK_ANSI_R: { keys[0x52] = 0; } break;
		case kVK_ANSI_S: { keys[0x53] = 0; } break;
		case kVK_ANSI_T: { keys[0x54] = 0; } break;
		case kVK_ANSI_U: { keys[0x55] = 0; } break;
		case kVK_ANSI_V: { keys[0x56] = 0; } break;
		case kVK_ANSI_W: { keys[0x57] = 0; } break;
		case kVK_ANSI_X: { keys[0x58] = 0; } break;
		case kVK_ANSI_Y: { keys[0x59] = 0; } break;
		case kVK_ANSI_Z: { keys[0x5a] = 0; } break;

		case kVK_Escape: { keys[0x1b] = 0; } break;

		default: break;
	}
}
@end

@implementation PDLView
@synthesize bitmapMemory;
@synthesize bitmapWidth;
@synthesize bitmapHeight;

- (void)drawRect:(NSRect)rect {	
	CGContextRef graphicsContext = [NSGraphicsContext currentContext].CGContext;
	CGContextSetInterpolationQuality(graphicsContext, kCGInterpolationNone);

	CGColorSpaceRef colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);

	self.provider = CGDataProviderCreateWithData(NULL, self.bitmapMemory, sizeof(uint32_t)*self.bitmapWidth*self.bitmapHeight, NULL);
	self.image = CGImageCreate(self.bitmapWidth,
									 self.bitmapHeight,
									 8,
									 32,
									 sizeof(uint32_t)*self.bitmapWidth,
									 colorSpace,
									 kCGBitmapByteOrder32Little|kCGImageAlphaNoneSkipFirst,
									 self.provider,
									 NULL,
									 NO,
									 kCGRenderingIntentDefault);
	CGColorSpaceRelease(colorSpace);

	CGContextDrawImage(graphicsContext, rect, self.image);

	CGImageRelease(self.image);
	CGDataProviderRelease(self.provider);
}

- (void)dealloc {
	free(view.bitmapMemory);
}
@end