#include "mymodel.h"
#include "store.h"


MyModel::MyModel(QObject* parent)
	: QAbstractListModel(parent)
	, m_states(std::vector<State>(6, State::Unknown))
{
	Store::instance().registerCallback(std::bind(&MyModel::statesUpdateHandler, this, std::placeholders::_1));
}

int MyModel::rowCount(const QModelIndex &parent) const
{
	return m_states.size();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
	int i = index.row();
	if (role == StateRole && i < m_states.size())
	{
		return m_states[i];
	}
	return QVariant();
}

QHash<int, QByteArray> MyModel::roleNames() const
{
	QHash<int, QByteArray> roles;
	roles[StateRole] = "state";
	return roles;
}

bool MyModel::statesUpdateHandler(const std::vector<int>& received_states)
{
	std::size_t current_count{ m_states.size() };
	std::size_t received_count{ received_states.size() };

	// Remove
	if (current_count > received_count)
	{
		emit beginRemoveRows(QModelIndex(), received_count, current_count - 1);
		m_states.erase(m_states.begin() + received_count, m_states.end());
		emit endRemoveRows();
		current_count = received_count;
	}

	// Update
	auto received_state = received_states.begin();
	for (unsigned i = 0; i < current_count; ++i)
	{
		auto state = static_cast<State>(*received_state);
		if (m_states[i] != state)
		{
			m_states[i] = state;
			emit dataChanged(index(i), index(i), { Role::StateRole });
		}
		received_state++;
	}

	// Insert
	if (received_state != received_states.end())
	{
		emit beginInsertRows(QModelIndex(), current_count, received_count - 1);
		for (auto it = received_state; it != received_states.end(); ++it)
		{
			m_states.push_back(static_cast<State>(*it));
		}
		emit endInsertRows();
	}

	return true;
}