#pragma once

#include <QVariant>

#include <vector>
#include <memory>

/*
 * The data is stored internally in the model using TreeNode objects that are linked together in a pointer-based tree structure.
 * Generally, each TreeNode has a parent item, and can have a number of children.
 * However, the root item in the tree structure has no parent item and it is never referenced outside the model.
 */
class TreeNode {
public:
    explicit TreeNode(QVariant data, TreeNode* parent = nullptr);

    void appendChild(std::unique_ptr<TreeNode> &&child);

    int index() const;
    int childCount() const;

    TreeNode *child(int index);
    TreeNode *parent();

    QVariant data() const;

private:
    std::vector<std::unique_ptr<TreeNode>> m_children;
    QVariant m_data;
    TreeNode *m_parent;
};
