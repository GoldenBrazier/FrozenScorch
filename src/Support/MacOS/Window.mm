#import <Support/MacOS/Window.h>
#import <Support/MacOS/KeyCodes.h>
#import <Cocoa/Cocoa.h>
#import <MetalKit/MetalKit.h>

@interface WindowViewController : NSViewController<MTKViewDelegate> {
    @public void (*m_event_callback)(void*);
    @public void (*m_render)();
    @public const Support::MacOS::Window* m_window;
}

@end

@interface MainView : MTKView { 
    @public void (*m_key_down_callback)(int, int);
    @public void (*m_mouse_down_callback)(int, int);
    @public void (*m_mouse_move_callback)(float, float);
}

@end

@implementation MainView

-(BOOL)acceptsFirstResponder
{
    return YES;
}

- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent 
{
    return YES;
}

- (void)mouseDown:(NSEvent*)theEvent
{
    if (m_mouse_down_callback) {
        (*m_mouse_down_callback)([NSEvent pressedMouseButtons], theEvent.buttonNumber);
    }
}

- (void)keyDown:(NSEvent*)theEvent
{
    if (m_key_down_callback) {
        (*m_key_down_callback)((int)[theEvent.characters characterAtIndex:0], theEvent.keyCode);
    }
}


- (void)flagsChanged:(NSEvent *)theEvent
{
    NSUInteger flags = [theEvent modifierFlags];
    if (flags & NSEventModifierFlagShift) {
        (*m_key_down_callback)((int)' ', (int)Support::MacOS::KeyCode::KEY_SHIFT);
    }

    if (flags & NSEventModifierFlagCommand) {
        (*m_key_down_callback)((int)' ', (int)Support::MacOS::KeyCode::KEY_COMMAND);
    }

    if (flags & NSEventModifierFlagControl) {
        (*m_key_down_callback)((int)' ', (int)Support::MacOS::KeyCode::KEY_CONTROL);
    }
    
    if (flags & NSEventModifierFlagOption) {
        (*m_key_down_callback)((int)' ', (int)Support::MacOS::KeyCode::KEY_OPTION);
    }
    
    if (flags & NSEventModifierFlagCapsLock) {
        (*m_key_down_callback)((int)' ', (int)Support::MacOS::KeyCode::KEY_CAPSLOCK);
    }
}

- (void)mouseMoved:(NSEvent*)theEvent
{
    NSPoint mouseDownPos = [theEvent locationInWindow];
    if (m_mouse_move_callback) {
        (*m_mouse_move_callback)(mouseDownPos.x, mouseDownPos.y);
    }
    // NSLog(@"mouseMoved %f %f", mouseDownPos.x, mouseDownPos.y);
    // CGDisplayHideCursor(CGMainDisplayID());
    // CGDisplayMoveCursorToPoint(CGMainDisplayID(), original);
}

- (void)updateTrackingAreas {
    NSTrackingAreaOptions options = (NSTrackingActiveAlways | NSTrackingInVisibleRect | NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved);
    NSTrackingArea *area = [[NSTrackingArea alloc] initWithRect:[self bounds] options:options owner:self userInfo:nil];
    [self addTrackingArea:area];
}

@end

@implementation WindowViewController

-(void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{

}

-(void)drawInMTKView:(nonnull MTKView *)view
{
    if (m_render) {
        (*m_render)();
    }
}
@end

namespace Support::MacOS {

Window::Window(const mtlpp::Device& device, size_t width, size_t height)
{
    NSRect frame = NSMakeRect(0, 0, width, height);
    NSWindow* window = [[NSWindow alloc] initWithContentRect:frame
#if MTLPP_IS_AVAILABLE_MAC(10_12)
        styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
#else
        styleMask:(NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask)
#endif
        backing:NSBackingStoreBuffered
        defer:NO];
    window.title = [[NSProcessInfo processInfo] processName];
    WindowViewController* viewController = [WindowViewController new];
    viewController->m_render = NULL;
    viewController->m_window = this;

    MainView* view = [[MainView alloc] initWithFrame:frame];
    view->m_mouse_down_callback = NULL;
    view.device = (__bridge id<MTLDevice>)device.GetPtr();
    view.delegate = viewController;
    view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;

    [window.contentView addSubview:view];
    [window center];
    [window orderFrontRegardless];
    [window makeFirstResponder:view];

    m_view = NS::Handle{ (__bridge void*)view };
    m_view_controller = NS::Handle{ (__bridge void*)viewController };
}

void Window::set_draw_callback(void (*drawcallback)()) 
{
    WindowViewController* view_controller = (__bridge WindowViewController*)m_view_controller.GetPtr();
    view_controller->m_render = drawcallback;
}

void Window::set_key_down_callback(void (*mouse_key_callback)(int, int))
{
    MainView* cur_view = (__bridge MainView*)m_view.GetPtr();
    cur_view->m_key_down_callback = mouse_key_callback;
}

void Window::set_mouse_down_callback(void (*mouse_down_callback)(int, int))
{
    MainView* cur_view = (__bridge MainView*)m_view.GetPtr();
    cur_view->m_mouse_down_callback = mouse_down_callback;
}

void Window::set_mouse_move_callback(void (*mouse_move_callback)(float, float))
{
    MainView* cur_view = (__bridge MainView*)m_view.GetPtr();
    cur_view->m_mouse_move_callback = mouse_move_callback;
}

size_t Window::width() const
{
    return size_t(((__bridge MTKView*)m_view.GetPtr()).frame.size.width);
}

size_t Window::height() const
{
    return size_t(((__bridge MTKView*)m_view.GetPtr()).frame.size.height);
}

mtlpp::Drawable Window::drawable() const
{
    return ns::Handle{ (__bridge void*)((__bridge MTKView*)m_view.GetPtr()).currentDrawable };
}

mtlpp::RenderPassDescriptor Window::renderpass_descriptor() const
{
    return ns::Handle{ (__bridge void*)((__bridge MTKView*)m_view.GetPtr()).currentRenderPassDescriptor };
}

void Window::Run()
{
    NSApplication* application = [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    NSMenu* menubar = [NSMenu new];
    NSMenuItem* appMenuItem = [NSMenuItem new];
    NSMenu* appMenu = [NSMenu new];
    NSMenuItem* quitMenuItem = [[NSMenuItem alloc] initWithTitle:@"Quit" action:@selector(stop:) keyEquivalent:@"q"];
    [menubar addItem:appMenuItem];
    [appMenu addItem:quitMenuItem];
    [appMenuItem setSubmenu:appMenu];
    [NSApp setMainMenu:menubar];

    [NSApp activateIgnoringOtherApps:YES];
    [NSApp run];
}

}