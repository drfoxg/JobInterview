/*
    treeitem.cpp

    A container for items of data supplied by the simple tree model.
*/

#include <QStringList>

#include "treeitem.h"

TreeItem::TreeItem(const QList<QVariant> &data, int code, int parentcode, TreeItem *parent)
{
    parentItem = parent;
    itemData = data;
    codeData = code;
    parentcodeData = parentcode;
}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    return childItems.value(row);
}

TreeItem *TreeItem::childLast()
{
    return childItems.last();
}

int TreeItem::childCount() const
{
    return childItems.count();
}

int TreeItem::columnCount() const
{
    return itemData.count();
}

QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}

int TreeItem::code() const
{
    return codeData;
}

int TreeItem::parentCode() const
{
    return parentcodeData;
}

TreeItem *TreeItem::parent()
{
    return parentItem;
}

void TreeItem::setParent(TreeItem *parent)
{
    parentItem = parent;
}

int TreeItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
