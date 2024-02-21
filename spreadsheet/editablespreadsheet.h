#pragma once

#include <spreadsheet.h>

class EditableSpreadsheet : public Spreadsheet
{
    Q_OBJECT
public:
    using Spreadsheet::Spreadsheet;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool removeRows(int row, int count, const QModelIndex &parent = {}) override;
    bool insertRows(int row, int count, const QModelIndex &parent = {}) override;
};
