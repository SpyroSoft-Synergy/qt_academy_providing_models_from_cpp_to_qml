#include "tree.h"

TreeNode::TreeNode(QVariant data, TreeNode *parent) : m_data(std::move(data)), m_parent(parent) {}

void TreeNode::appendChild(std::unique_ptr<TreeNode> &&child)
{
    m_children.push_back(std::move(child));
}

int TreeNode::index() const
{
    if (m_parent == nullptr) {
        return 0;
    }

    const auto it = std::find_if(m_parent->m_children.cbegin(), m_parent->m_children.cend(),
                                 [this](const std::unique_ptr<TreeNode> &node) {
                                     return node.get() == this;
                                 });
    if (it != m_parent->m_children.cend()) {
        return std::distance(m_parent->m_children.cbegin(), it);
    }
    return -1;
}

int TreeNode::childCount() const
{
    return m_children.size();
}

TreeNode *TreeNode::child(int index)
{
    return index >= 0 && index < childCount() ? m_children.at(index).get() : nullptr;
}

TreeNode *TreeNode::parent()
{
    return m_parent;
}

QVariant TreeNode::data() const
{
    return m_data;
}
