#include "widget.h"
#include "treemodel.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
 ui->setupUi(this);

 //Получаем предустановленное "дерево" в file:
 QFile file(":/default.txt");
 file.open(QIODevice::ReadOnly);
 //Создаем заголовки столбцов:
 QStringList headers;
 headers << tr("Заголовок");
 //Загружаем данные в модель:
 TreeModel *model = new TreeModel(headers, file.readAll());
 file.close();
 ui->treeView->setModel(model);
 for (int column = 0; column < model->columnCount(); ++column) ui->treeView->resizeColumnToContents(column);

 //Осталось соединить сигналы со слотами:
 connect(ui->treeView->selectionModel(),SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
         this, SLOT(updateActions(const QItemSelection&,const QItemSelection&)));
 connect(ui->insertRowAction,SIGNAL(clicked()),this,SLOT(insertRow()));
 connect(ui->removeRowAction,SIGNAL(clicked()),this,SLOT(removeRow()));
 connect(ui->insertChildAction,SIGNAL(clicked()),this,SLOT(insertChild()));
 //и обновить состояние кнопок:
 updateActions();
}

void Widget::insertChild() {
 //Получаем модельный индекс и модель элемента:
 QModelIndex index = ui->treeView->selectionModel()->currentIndex();
 QAbstractItemModel *model = ui->treeView->model();
 //Вставляем данные:
 if (model->columnCount(index) == 0) {
  if (!model->insertColumn(0, index)) return;
 }
 if (!model->insertRow(0, index)) return;
 //Инициализируем их:
 for (int column = 0; column < model->columnCount(index); ++column) {
  QModelIndex child = model->index(0, column, index);
  model->setData(child, QVariant("Данные"), Qt::EditRole);
  if (!model->headerData(column, Qt::Horizontal).isValid())
   model->setHeaderData(column, Qt::Horizontal, QVariant("Столбец"), Qt::EditRole);
  }
 //Выбираем вставленный узел:
 ui->treeView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
  QItemSelectionModel::ClearAndSelect);
 //Меняем состояние кнопок:
 updateActions();
}

bool Widget::insertColumn() {
 QAbstractItemModel *model = ui->treeView->model();
 int column = ui->treeView->selectionModel()->currentIndex().column();
 bool changed = model->insertColumn(column + 1);
 if (changed)
  model->setHeaderData(column + 1, Qt::Horizontal, QVariant("Столбец"), Qt::EditRole);
 updateActions();
 return changed;
}

void Widget::insertRow() {
 QModelIndex index = ui->treeView->selectionModel()->currentIndex();
 QAbstractItemModel *model = ui->treeView->model();
 if (!model->insertRow(index.row()+1, index.parent())) return;
 updateActions();
 for (int column = 0; column < model->columnCount(index.parent()); ++column) {
  QModelIndex child = model->index(index.row()+1, column, index.parent());
  model->setData(child, QVariant("Данные"), Qt::EditRole);
 }
}

bool Widget::removeColumn() {
 QAbstractItemModel *model = ui->treeView->model();
 int column = ui->treeView->selectionModel()->currentIndex().column();
 bool changed = model->removeColumn(column); //Удалить столбец для каждого потомка
 if (changed) updateActions();
 return changed;
}

void Widget::removeRow() {
 QModelIndex index = ui->treeView->selectionModel()->currentIndex();
 QAbstractItemModel *model = ui->treeView->model();
 if (model->removeRow(index.row(), index.parent())) updateActions();
}

void Widget::updateActions(const QItemSelection &selected,const QItemSelection &deselected) {
 updateActions();
}

void Widget::updateActions() {
 //Обновим состояние кнопок:
 bool hasSelection = !ui->treeView->selectionModel()->selection().isEmpty();
 ui->removeRowAction->setEnabled(hasSelection);
 bool hasCurrent = ui->treeView->selectionModel()->currentIndex().isValid();
 ui->insertRowAction->setEnabled(hasCurrent);
}

void Widget::printTree(int level, const QModelIndex &index, QTextStream &stream)
{
    QString indent;
    for( int j = 0; j < level; ++j )
        indent.append( "   " );

   // print index itself
   if( index.isValid() )
   {
        stream << indent;
        for( int c = 0; c < index.model()->columnCount(index.parent()); ++c )
        {
                QModelIndex columnIndex = index.sibling(index.row(), c);
                stream << columnIndex.data().toString();
        }
        stream << "\n";
  }

  //print children
  for (int r = 0; r < index.model()->rowCount(index); r++)
   {
          const QModelIndex childIndex = index.child( r, 0 );
           this->printTree( level+1, childIndex, stream );
   }
}

void Widget::on_pushButton_2_clicked()
{
    //Получаем предустановленное "дерево" в file:
     file.setFileName(QFileDialog::getOpenFileName(nullptr,"","C:\\QT_EXAMPLE\\QT_labs\\5lab","*.txt"));

     if (file.open(QIODevice::ReadOnly))
     {
        //Создаем заголовки столбцов:
        QStringList headers;
        headers << tr("Заголовок") << tr("Описание");
        //Загружаем данные в модель:
        TreeModel *model = new TreeModel(headers, file.readAll());
        file.close();
        ui->treeView->setModel(model);
        for (int column = 0; column < model->columnCount(); ++column) ui->treeView->resizeColumnToContents(column);
     }
}

void Widget::on_pushButton_clicked()
{
    QString strFilter = "*.txt";
    QString fileName = QFileDialog::getSaveFileName( nullptr,"Сохранить файл", "C:\\QT_EXAMPLE\\QT_labs\\5lab", "*.txt", &strFilter);

    if (fileName != "") {
         QFile file(fileName);
         if (!file.open(QIODevice::WriteOnly)) {
             // error message
         } else {
             QTextStream stream(&file);
             stream.setCodec("UTF-8");
             for (int r = 0; r < ui->treeView->model()->rowCount(); r++)
                     this->printTree( 0, ui->treeView->model()->index(r,0), stream);
             file.close();
         }
     }
}
