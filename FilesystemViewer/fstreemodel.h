#pragma once

#include <QAbstractItemModel>

#include <tree.h>

class FSTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit FSTreeModel(std::unique_ptr<TreeNode> root, QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = {}) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = {}) const override;
    int columnCount(const QModelIndex &parent = {}) const override;

private:
    std::unique_ptr<TreeNode> m_root;
};
