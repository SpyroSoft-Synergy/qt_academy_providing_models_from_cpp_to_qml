#include "todolist.h"

namespace {
    enum ToDoTaskRoles{
        TaskStateRole = Qt::UserRole // All values below Qt::UserRole are reserved.
    };
}

ToDoList::ToDoList(const std::vector<Task>& tasks, QObject* parent) : QAbstractListModel{parent}, m_tasks{tasks} {}

int	ToDoList::rowCount(const QModelIndex &parent) const {
    return m_tasks.size(); // rowCount is equal to a number of tasks.
}

QVariant ToDoList::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return {}; // If an index is invalid, we return invalid data.
    }

    const auto& task = m_tasks[index.row()];
    if (role == Qt::DisplayRole) {
        return task.description; // For Qt::DisplayRole, we return the description of a task.
    } else if (role == TaskStateRole) {
        return static_cast<int>(task.state); // For TaskStateRole, we return the current state of task.
    }
    return {}; // For all other roles, we return an invalid data.
}

QHash<int, QByteArray> ToDoList::roleNames() const {
    auto roles = QAbstractListModel::roleNames();
    roles.insert(TaskStateRole, "state"); // Append a custom role to the pre-defined list.
    return roles;
}
