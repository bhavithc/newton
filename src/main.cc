#define RELEASE
#include "app.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        return CLI::showHelp();
    }

    return CLI::createApp(argc, (const char **)argv);
};
