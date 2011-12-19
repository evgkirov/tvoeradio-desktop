#include "application.h"
#include <objc/runtime.h>

void dockClickHandler(id self, SEL _cmd)
{
    Q_UNUSED(self)
    Q_UNUSED(_cmd)
    qApp->mainWindow->show();
}

void Application::setupMacHandlers()
{
    Class cls = [[[NSApplication sharedApplication] delegate] class];
    if (!class_addMethod(cls, @selector(applicationShouldHandleReopen:hasVisibleWindows:), (IMP) dockClickHandler, "v@:"))
        NSLog(@"Application::setupMacHandlers() : class_addMethod failed!");

}
