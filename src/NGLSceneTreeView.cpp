#include "NGLSceneTreeView.h"
#include <QGridLayout>
#include <QStringListModel>
#include <QModelIndexList>
#include <iostream>
#include <QVariant>
#include <QVector>
#include <QFile>
#include "SceneObject.h"
#include "SceneManager.h"

NGLSceneTreeView::NGLSceneTreeView(QWidget *_parent)
{
    //find object list placeholder in the UI and replace it with our class
    auto layout = _parent->findChild<QGridLayout*>("s_listGridLayout");
    auto list_widget = _parent->findChild<QWidget*>("m_objList");
    layout->replaceWidget(list_widget, this);
    
    QStringList headers;
    QString data;
    //list << "a" << "b";

    QFile file("default.txt");
    file.open(QIODevice::ReadOnly);
    m_treeModel = new SceneTreeModel(headers, file.readAll());
    file.close();
    //std::cout<<"Setting the model...\n";

    this->setModel(m_treeModel);

    // for (int column = 0; column < m_treeModel->columnCount(); ++column)
    //     this->resizeColumnToContents(column);
}

void NGLSceneTreeView::push_back(std::shared_ptr<SceneObject> obj)
{
    //std::cout<<"Pushing back..\n";
    auto numRows = m_treeModel->rowCount();

    //https://stackoverflow.com/questions/37412712/how-to-update-a-qstringlistmodel
    //std::cout<<"Finished checking row count...\n";
    if(m_treeModel->insertRows(numRows,1))
    {
        auto index = m_treeModel->index(numRows,0);
        //std::cout << "Got index!\n";
        m_treeModel->setData(index, QString(obj->getName().c_str()) );
        update();
    }
}

std::shared_ptr<SceneObject> NGLSceneTreeView::getSceneRoot() const
{
    return m_treeModel->getRootObject();
}

void NGLSceneTreeView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
    {
        std::cout << "DELETE\n";
        QModelIndexList indexes = this->selectionModel()->selectedIndexes();
        if (indexes.size() > 0)
        {
            QModelIndex selectedIndex = indexes.at(0);

        }
    }
}