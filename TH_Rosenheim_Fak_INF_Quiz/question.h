#ifndef QUESTION_H
#define QUESTION_H

#include <astring.h>

struct Question {
    AString question;

    AString rightAnswer;

    AString wrongAnswers[3];
};

#endif // QUESTION_H
