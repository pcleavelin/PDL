#include "win32_pdl.h"

int main(int argc, char *argv[])
{
    bool running = true;

    PDLInit();

    while (running)
    {
        running = DoWindowMessages();
    }

    return 0;
}