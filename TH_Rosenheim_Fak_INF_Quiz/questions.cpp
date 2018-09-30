#include "questions.h"

#include <logger.h>
#include <file.h>

Questions::Questions()
{
    questions_.reserve(8);
}

Questions::~Questions()
{
}

bool Questions::initialize()
{
    if (!serializeQuestions()) {
        return false;
    }
}

bool Questions::serializeQuestions()
{
    File file(filename_);
    if (!file.exists()) {
        Logger::error("Could not find file '" + filename_ + "'!", true, ConsoleColor::Red);
        return false;
    }

    if (!file.open(ReadOnly)) {
        Logger::error("Could not open file '" + filename_ + "' with flag OpenMode::ReadOnly!", true, ConsoleColor::Red);
        return false;
    }

    auto serializeQuestion = [this](const AString& line) {
        SHARED_PTR(Question) question;
        question.reset(new Question());

        const auto splittedLine = line.split(':');

        /* Serialize question*/
        if (splittedLine.size() != 2) {
            return false;
        }
        question->question = splittedLine[0];

        /* Serialize answers */
        const auto splittedAnswers = splittedLine[1].split(';');

        /* Serialize right answer */
        if (splittedAnswers.size() != 4) {
            return false;
        }
        question->rightAnswer = splittedAnswers[0];

        /* Serialize wrong answers */
        for (byte i = 0; i < 3; ++i) {
            question->wrongAnswers[i] = splittedAnswers[i + 1];
        }

        questions_.append(question);
        return true;
    };

    while (!file.atEnd()) {
        const auto line = file.readLine();

        /* Skip if line is comment */
        if (line.startsWith(";")) {
            return false;
        }

        serializeQuestion(line);
    }

    return questions_.size() > 0;
}
