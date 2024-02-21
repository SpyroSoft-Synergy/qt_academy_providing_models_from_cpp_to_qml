#pragma once

#include <QAbstractTableModel>

#include <array>

class Spreadsheet : public QAbstractTableModel
{
    Q_OBJECT
public:
    static inline constexpr int MaxArraySize = 9;

    using value_type = double;
    using Array2D = std::array<std::array<value_type, MaxArraySize>, MaxArraySize>;

    explicit Spreadsheet(const Array2D& array, QObject* parent = nullptr);

    int rowCount(const QModelIndex& index = {}) const override;
    int columnCount(const QModelIndex& index = {}) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

protected:
    Array2D m_array;
    int rows = MaxArraySize;
    int columns = MaxArraySize;
};
