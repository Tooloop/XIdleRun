#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/scrnsaver.h>


float getIdleTime()
{
    Display *display;
    int event_base, error_base;
    XScreenSaverInfo info;

    display = XOpenDisplay("");

    if (XScreenSaverQueryExtension(display, &event_base, &error_base)) {
        XScreenSaverQueryInfo(display, DefaultRootWindow(display), &info);

        return (float)info.idle/1000.0f;
    }
    else {
        fprintf(stderr,"Error: XScreenSaver Extension not present\n");
        return -1;
    }
}

int main(int argc, char *argv[])
{
    unsigned int secondsToReset = 60;
    char *command = NULL;
    bool didReset = false;
    float idleTime = 0.0;

    // read options
    int c;
    int targ;
    while ((c = getopt (argc, argv, "t:c:")) != -1)

    switch (c)
    {
        case 't':
            targ = atoi(optarg);
            if (targ > 0) secondsToReset = targ;
            break;
        case 'c':
            command = optarg;
            break;
        case '?':
            return 1;
        default:
            abort ();
    }

    if (!command) {
        fprintf(stderr, "option -c is required\n");
        return 1;
    }

    // now observe idle time
    while(idleTime >= 0) {

        idleTime = getIdleTime();

        if (idleTime > secondsToReset && !didReset) {
            printf("Reached %f seconds of idle time. Executing command %s.\n", idleTime, command);
            system(command);
            didReset = true;
        }

        if (idleTime < secondsToReset && didReset) {
            printf("User interaction detectd, resetting time.\n");
            didReset = false;
        }

        sleep(1);
    }
}