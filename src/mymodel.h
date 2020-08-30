#pragma once

#include <vector>

#include <QAbstractListModel>

class MyModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit MyModel(QObject* parent = nullptr);
    ~MyModel() = default;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    enum Role { StateRole = Qt::UserRole };
    Q_ENUM(Role)

    enum State { Unknown, Normal, Warning, Alarm, Ignored };
    Q_ENUM(State)

private:
    bool statesUpdateHandler(const std::vector<int>& states);
    std::vector<State> m_states;
};