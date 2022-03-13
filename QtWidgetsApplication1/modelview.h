#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qlistview.h>
#include <QtWidgets/qtreeview.h>
#include <QtWidgets/qboxlayout.h>
#include <qfilesystemmodel.h>
#include <qdebug.h>


class MyTableModel :public QAbstractTableModel
{
	std::vector<Activity> activities;
public:
	MyTableModel(const std::vector<Activity>& activities) :activities{ activities }
	{}
	int rowCount(const QModelIndex& ) const override
	{
		int d = static_cast<int>(activities.size());
		return  d;
		
	}
	int columnCount(const QModelIndex& ) const override
	{
		return 4;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override 
	{
		if (role == Qt::DisplayRole) {
			Activity ac = activities[index.row()];
			qDebug() << "row:" << index.row() << " col:" << index.column();
			if (index.column() == 0)
				return QString::fromStdString(ac.getname());
			if (index.column() == 1)
				return QString::fromStdString(ac.getdescription());
			if (index.column() == 2)
				return QString::fromStdString(ac.gettype());
			if (index.column() == 3)
				return QString::number(ac.getduration());
			
		}
		return QVariant();
	}
};
