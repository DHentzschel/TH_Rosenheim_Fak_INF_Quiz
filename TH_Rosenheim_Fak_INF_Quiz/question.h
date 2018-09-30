#ifndef QUESTION_H
#define QUESTION_H

#include <astring.h>
#include <stringvector.h>

struct Question {
    AString question;

    AString rightAnswer;

    AString wrongAnswers[3];

    byte lastRightAnswerIndex = 0xFF;

    StringVector getRandomizedAnswers()
    {
        StringVector result;
        result.reserve(4);

        bool isSet[4];
        memset(isSet, false, 4 * sizeof(bool));

        for (byte i = 0; i < 4; ++i) {
            const auto random = std::rand() % 4;

            if (isSet[random]) {
                --i;
                continue;
            }

            isSet[random] = true;
            if (random == 0) {
                lastRightAnswerIndex = i;
                result.append(rightAnswer);
            }
            else {
                result.append(wrongAnswers[random - 1]);
            }
        }

        return result;
    }

    byte getLastRightAnswerIndex() const
    {
        return lastRightAnswerIndex;
    }
};

#endif // QUESTION_H
