#import <Support/MacOS/Window.h>
#import <Cocoa/Cocoa.h>
#import <MetalKit/MetalKit.h>

@interface WindowViewController : NSViewController<MTKViewDelegate> {
    @public void (*m_render)();
    @public const Support::MacOS::Window* m_window;
}

@end

@implementation WindowViewController
-(void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{

}

-(void)drawInMTKView:(nonnull MTKView *)view
{
    (*m_render)();
}
@end

namespace Support::MacOS {

Window::Window(const mtlpp::Device& device, void (*render)(), size_t width, size_t height)
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
    viewController->m_render = render;
    viewController->m_window = this;

    MTKView* view = [[MTKView alloc] initWithFrame:frame];
    view.device = (__bridge id<MTLDevice>)device.GetPtr();
    view.delegate = viewController;
    view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;

    [window.contentView addSubview:view];
    [window center];
    [window orderFrontRegardless];

    m_view = ns::Handle{ (__bridge void*)view };

}

// TODO: Implement functionality to set rendered after first init;
// void Window::set_renderer() const
// {
//     return ((__bridge MTKView*)m_view.GetPtr()).;
// }

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