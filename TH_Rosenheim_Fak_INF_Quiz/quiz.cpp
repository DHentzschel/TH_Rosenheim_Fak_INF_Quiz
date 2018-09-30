#include "quiz.h"

#include <cstdlib>
#include <ctime>

#include <iostream>

#include <console.h>

Quiz::Quiz()
{
    std::srand(STATIC_CAST(uint, std::time(nullptr)));
    Console::setConsoleTitle("Hochschule Rosenheim - Fak. Informatik Quiz");
}

void Quiz::startQuiz(AVector<SHARED_PTR(Question)> questions)
{
    AString command;

    auto shouldQuit = [](const AString& command) {
        return !command.equals("j", CaseInsensitive)
            && !command.equals("y", CaseInsensitive);
    };

    do {
        askQuestions(questions);
        Console::print("Nochmal? (j, n)");
        Console::print("> ", false);
        std::cin >> command;
        system("cls");
    } while (!shouldQuit(command));

}

void Quiz::askQuestions(AVector<SHARED_PTR(Question)> questions)
{
    Console::print("Willkommen beim Quiz der Fakultät Informatik!", true, Blue);
    Console::print("Dir werden Fragen gestellt und du musst diese mit den Antwortmöglichkeiten 1-4 beantworten.");
    Console::print("Je nachdem, wie viele Fragen du richtig beantwortest, gewinnst du etwas. (Nur solange der Vorrat reicht!)");
    Console::print("");

    byte score = 0;
    for (uint i = 0; i < questions.size(); ++i) {
        /* Idk why tf this was the only spontaneous
        way to convert char to string */
        AString string;
        string.resize(1);
        string[0] = 'A' + i;
        Console::print(string + ". ", false, Green);

        const auto randomizedAnswers = questions[i]->getRandomizedAnswers();
        const auto rightAnswerIndex = questions[i]->getLastRightAnswerIndex();

        askQuestion(questions[i]->question, randomizedAnswers, rightAnswerIndex, score);
    }

    Console::print("Quiz beendet! Du hast ", false, Black, White);
    Console::print((score == 0 ? "keine" : (score == 8 ? "alle" : TO_STRING(score))),
        false, (score == 0 ? ConsoleColor::Red : ConsoleColor::Green), White);
    Console::print(" Fragen richtig beantwortet.", true, Black, White);

    byte voucherAmount = (score >= 3 ? (score >= 6 ? 2 : 1) : 0);
    Console::print("Das bedeutet, du bekommst: ");
    Console::print(" - " + TO_STRING(voucherAmount) + " Freigetränk" + (voucherAmount == 1 ? "" : "e"), true, ConsoleColor::Yellow);
    if (score == 8) {
        Console::print(" - ein Premium-Geschenk ;)", true, ConsoleColor::Purple);
    }
    Console::printLine();
}

void Quiz::askQuestion(const AString& question, const StringVector& answers, byte rightAnswerIndex, byte& score)
{
    Console::print(question, true, Green);

    for (byte i = 0; i < 4; ++i) {
        Console::print("  " + TO_STRING(i + 1) + ". " + answers[i], true, Yellow);
    }

    AString input;
    auto isInputValid = [](const AString& input) {
        if (!input.isNumber()) {
            return false;
        }
        const auto number = input.toByte();
        return number <= 4 && number > 0;
    };

    do {
        Console::print("Antwort: ", false);
        std::cin >> input;
    } while (!isInputValid(input));

    const auto answer = input.toByte();
    if (answer - 1 == rightAnswerIndex) {
        ++score;
        Console::print("Richtige Antwort!\n", true, Green);
    }
    else {
        Console::print("Falsche Antwort!\n", true, Red);
    }
}
