#ifndef QUIZ_H
#define QUIZ_H

#include <avector.h>
#include "question.h"

class Quiz {
public:
    Quiz();

    ~Quiz() = default;

    void startQuiz(AVector<SHARED_PTR(Question)> questions);

private:
    void askQuestions(AVector<SHARED_PTR(Question)> questions);

    void askQuestion(const AString& question, const StringVector& answers, byte rightAnswerIndex, byte& score);

};

#endif // QUIZ_H
