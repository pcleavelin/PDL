#include "../pdl_api.h"

int main(int argc, char *argv[])
{
    bool running = true;

    PDLInit();

    while (running)
    {
        running = PDLDoWindowMessages();
    }

    return 0;
}