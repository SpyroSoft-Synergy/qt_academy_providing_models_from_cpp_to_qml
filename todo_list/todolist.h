#pragma once

#include <QObject>
#include <QAbstractListModel>

#include <vector>

#include "task.h"

class ToDoList : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ToDoList(const std::vector<Task>& tasks, QObject* parent = nullptr);

    int	rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    std::vector<Task> m_tasks;
};
