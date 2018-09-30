#include "consoleio.h"
#include "questions.h"

int main(int argc, char** argv)
{
    Questions questions;
    if (!questions.initialize()) {
        return EXIT_FAILURE;
    }

    ConsoleIO consoleIo;
    return EXIT_SUCCESS;
}