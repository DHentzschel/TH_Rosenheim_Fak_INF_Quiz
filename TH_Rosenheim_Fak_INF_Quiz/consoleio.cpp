#include "consoleio.h"

#include <cstdlib>
#include <ctime>

ConsoleIO::ConsoleIO()
{
    std::srand(std::time(nullptr));
}

ConsoleIO::~ConsoleIO()
{
}
