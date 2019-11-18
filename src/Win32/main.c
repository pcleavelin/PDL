#include "win32_pdl.h"

int main(int argc, char *argv[])
{
    bool running = true;

    PDLResizeWindow(1024, 768);

    while (running)
    {
        running = DoWindowMessages();
    }

    return 0;
}