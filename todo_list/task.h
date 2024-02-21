#pragma once

#include <QString>

struct Task {
    enum class State {
        ToDo = 0,
        InProgress = 1,
        Done = 2
    };

    QString description;
    State state = State::ToDo;
};
