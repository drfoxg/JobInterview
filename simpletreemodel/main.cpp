#include <QtGui>
#include <QTextCodec>

#include "treemodel.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(simpletreemodel);

    QApplication app(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    QFile file(":/data.txt");
    QTextStream utf_text(&file);
    file.open(QIODevice::ReadOnly);
    utf_text.setCodec("UTF-8");
    TreeModel model(utf_text.readAll());
    file.close();

    QTreeView view;
    view.setModel(&model);
    view.setWindowTitle(QObject::tr("Задание по C++"));
    view.show();

    return app.exec();
}
