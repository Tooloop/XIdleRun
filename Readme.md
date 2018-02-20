# XIdleRun

XIdleRun is a small command line tool that waits for a certain time in seconds the user hasn't interacted with X11. After that it will run a command.


## Compiling

You need these packets installed

|    Packet   |                        Description                         |
|-------------|------------------------------------------------------------|
| libx11-dev  | X11 client-side library (development headers)              |
| libxext-dev | X11 miscellaneous extensions library (development headers) |
| libxss-dev  | X11 Screen Saver extension library (development headers)   |

On Ubuntu this line will do so:

    sudo apt install libx11-dev libxext-dev libxss-dev

Then compile it like so:

    make


## Usage

    xidlerun [-t seconds] [-c command]

**-t** Time in seconds, default is 60.
**-c** Command to run.

Examples:

    xidlerun 60 "echo One minute"
    xidlerun 3600 "/bin/bash ~/myscript.sh"


## Credits

The code is based on this [forum post](https://unix.stackexchange.com/a/128877)