#include "editablespreadsheet.h"

Qt::ItemFlags EditableSpreadsheet::flags(const QModelIndex &index) const {
    return QAbstractTableModel::flags(index) | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable; // Enable items selecting and editing.
}

bool EditableSpreadsheet::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid()) {
        return false; // If index is invalid, don't change the data and return false immediately.
    }

    bool isOk = false;
    if (double newValue = value.toDouble(&isOk); isOk) { // Validate if the data is of double type.
        m_array[index.row()][index.column()] = newValue; // Change the data in the internal storage.

        QModelIndex topLeft = Spreadsheet::index(index.row(), index.column());
        QModelIndex bottomRight = Spreadsheet::index(index.row(), index.column());
        emit dataChanged(topLeft, bottomRight, {role}); // Signal the data change. topLeft and bottomRight indexes refer to the same element, because only one element has changed.
    }
    return isOk; // Return the information whether a data was changed successfully, or not.
}

bool EditableSpreadsheet::removeRows(int row, int count, const QModelIndex &parent) {
    if (rows <= 1) {
        return false; // Don't remove any more rows if there's only one remaining.
    }

    beginRemoveRows(parent, row, row + count); // Signal the start of row manipulation.
    rows -= count; // Decrement the number of rows.
    endRemoveRows(); // Signal the end of row manipulation.
    return true;
}

bool EditableSpreadsheet::insertRows(int row, int count, const QModelIndex &parent) {
    if (rows >= MaxArraySize) {
        return false; // Don't insert any more rows if there are already 9.
    }

    beginInsertRows(parent, row, row + count); // Signal the start of row manipulation.
    rows += count; // Increment the number of rows.
    endInsertRows(); // Signal the end of row manipulation.
    return true;
}
