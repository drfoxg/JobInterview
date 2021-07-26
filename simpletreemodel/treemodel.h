#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QMultiMap>

class TreeItem;

//! [0]
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(const QString &data, QObject *parent = 0);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
    void setupModelData(const QStringList &lines, TreeItem *parent);
    void *buildTree(QMultiMap<int, TreeItem*> cats, int parentcode, TreeItem *parent);

    TreeItem *rootItem;
};
//! [0]

#endif
