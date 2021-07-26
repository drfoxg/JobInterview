#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>

//! [0]
class TreeItem
{
public:
    TreeItem(const QList<QVariant> &data, int code = 0, int parentcode = 0, TreeItem *parent = 0 );
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    TreeItem *childLast();
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    int code() const;
    int parentCode() const;
    TreeItem *parent();
    void setParent(TreeItem *parent);

private:
    int codeData;
    int parentcodeData;
    QList<TreeItem*> childItems;
    QList<QVariant> itemData;
    TreeItem *parentItem;
};
//! [0]

#endif
