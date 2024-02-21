#include "fstreemodel.h"

#include <filesystem>

FSTreeModel::FSTreeModel(std::unique_ptr<TreeNode> root, QObject *parent) : QAbstractItemModel(parent), m_root(std::move(root)) {}

QVariant FSTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {}; // If index is invalid, return an invalid data.
    }

    const auto *item = static_cast<const TreeNode*>(index.internalPointer()); // Retrieve the full TreeNode instance using internalPointer() function.
    std::filesystem::path path = item->data().toString().toStdString();
    return QString::fromStdString(path.filename().string()); // Return a filename only, instead of a full path.
}

QModelIndex FSTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return {}; // If there's no such index, we return an invalid position indicator.
    }

    TreeNode *parentItem = parent.isValid() ? static_cast<TreeNode*>(parent.internalPointer()) : m_root.get(); // If the parent is not valid, we assume it's root item.
    if (auto *childItem = parentItem->child(row); childItem) {
        return createIndex(row, column, childItem);
    }
    return {};
}

QModelIndex FSTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return {}; // If the index is invalid, we return an invalid position indicator.
    }

    auto *childItem = static_cast<TreeNode*>(index.internalPointer());
    TreeNode *parentItem = childItem->parent(); // We retrieve the parent from the TreeNode instance.
    return parentItem != m_root.get() ? createIndex(parentItem->index(), 0, parentItem) : QModelIndex{};
}

int FSTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0) {
        return 0; // We ignore other columns. We assume there's only one.
    }

    const TreeNode *parentItem = parent.isValid() ? static_cast<const TreeNode*>(parent.internalPointer()) : m_root.get();
    return parentItem->childCount(); // Return a number of children of the parent.
}

int FSTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1; // We assume there's only one column in this model.
}
