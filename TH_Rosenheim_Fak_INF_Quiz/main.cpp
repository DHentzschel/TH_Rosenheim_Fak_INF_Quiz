#include "quiz.h"
#include "questions.h"

#include <Windows.h>
int main(int argc, char** argv)
{
    std::locale::global(std::locale("German_germany"));

    Questions questions;
    if (!questions.initialize()) {
        return EXIT_FAILURE;
    }

    Quiz quiz;
    quiz.startQuiz(questions.getQuestions());

    return EXIT_SUCCESS;
}