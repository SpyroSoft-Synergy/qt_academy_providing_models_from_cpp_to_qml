#include "spreadsheet.h"

Spreadsheet::Spreadsheet(const Array2D& array, QObject* parent) : QAbstractTableModel{parent}, m_array{array} {}

int Spreadsheet::rowCount(const QModelIndex& index) const {
    return rows;
}

int Spreadsheet::columnCount(const QModelIndex& index) const {
    return columns;
}

QVariant Spreadsheet::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return {}; // If index is invalid, return invalid data.
    }
    return m_array[index.row()][index.column()]; // Return the array data.
}

QVariant Spreadsheet::headerData(int section, Qt::Orientation orientation, int role) const {
    switch (orientation) {
    case Qt::Vertical:
        return section + 1; // Return numbers for rows.
    case Qt::Horizontal:
        return QChar('A' + section); // Return capital letters from A to Z for columns.
    default:
        return {};
    }
}
