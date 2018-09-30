#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <avector.h>

#include "question.h"

class Questions {
public:
    Questions();

    ~Questions();

    bool initialize();

private:
    const AString filename_ = "data.list";

    AVector<SHARED_PTR(Question)> questions_;

    bool serializeQuestions();

};

#endif // QUESTIONS_H
