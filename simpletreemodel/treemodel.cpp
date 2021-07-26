/*
    treemodel.cpp

    Provides a simple tree model to show how to create and use hierarchical
    models.
*/

#include <QtGui>

#include "treeitem.h"
#include "treemodel.h"
#include "strparser.h"

using namespace strparser;

TreeModel::TreeModel(const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << tr("Заголовок");
    rootItem = new TreeItem(rootData);
    setupModelData(data.split(QString("\n")), rootItem);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return rootItem->data(section);
    }
    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(child.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
    StrParser parser;
    QMultiMap<int, TreeItem*> cats;

    int number = lines.count();
    while (number > 0) {
        number--;
        QString lineData = lines[number];
        parser.Parse(lineData);

        if (!lineData.isEmpty()) {
            QList<QVariant> columnData;
            columnData << parser.getData();
            cats.insertMulti(parser.getParentCode(), new TreeItem(columnData, parser.getCode(), parser.getParentCode()));
        }
    }
    buildTree(cats, 0, parent);
}

void *TreeModel::buildTree(QMultiMap<int, TreeItem*> cats, int parentcode, TreeItem *parent)
{
    int code = 0;

    QList <TreeItem*> items;
    items = cats.values(parentcode);
    if (items.size()){
        for (int i = 0; i < items.size(); i++) {
            code = items.at(i)->code();
            if (buildTree(cats, code, items.at(i)) == NULL){
                items.at(i)->setParent(parent);
                parent->appendChild(items.at(i));
            }
        }
    } else
        return NULL;

    return NULL;
}











































