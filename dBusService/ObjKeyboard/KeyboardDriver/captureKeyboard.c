

#include <X11/XKBlib.h>

//#define XKB_CTRL_DEBUG

Bool xcbCtrlSwitchLayout(const char *displayName)
{
    int grpIdx = -1;
    XkbStateRec xkbState;
    Bool ret = False;
    int checkXkbExt[5];

    Display *_display = XOpenDisplay(displayName);
    if (_display == NULL)
        return ret;

    //Check keyboard extension
    if (XkbQueryExtension(_display,
                          &checkXkbExt[0],
                          &checkXkbExt[1],
                          &checkXkbExt[2],
                          &checkXkbExt[3],
                          &checkXkbExt[4]) == False)
    {
        XCloseDisplay(_display);
        return ret;
    }

#ifdef XKB_CTRL_DEBUG
    printf("-display: %d\n", _display);
#endif

    //Get current state of layout group
    if (XkbGetState(_display, XkbUseCoreKbd, &xkbState) == Success)
    {
        grpIdx = xkbState.group;
    }
    
    if (grpIdx == -1)
    {
        XCloseDisplay(_display);
        return ret;
    }

    //max group count: 4 (XkbExtension)
    if (grpIdx++ == 3)
        grpIdx = 0;

    //switch group
    ret = XkbLockGroup(_display, XkbUseCoreKbd, grpIdx);

    XCloseDisplay(_display);
    return ret;
}