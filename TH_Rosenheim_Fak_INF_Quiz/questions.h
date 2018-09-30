#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <avector.h>

#include "question.h"

class Questions {
public:
    Questions();

    ~Questions() = default;

    bool initialize();

    AVector<SHARED_PTR(Question)> getQuestions();

private:
    const AString filename_ = "data.list";

    AVector<SHARED_PTR(Question)> questions_;

    bool deserializeQuestions();

};

#endif // QUESTIONS_H
