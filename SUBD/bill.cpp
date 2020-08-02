#include "bill.h"
#include "ui_bill.h"
#include <QSqlError>
#include <QMessageBox>

SqlTableModel::SqlTableModel(QObject *parent): QSqlTableModel(parent)
{
}

QVariant SqlTableModel::data(const QModelIndex &index, int role) const
{
    if ((role == Qt::DisplayRole) && (index.column() == columnCount(QModelIndex())-1)) {
        return data(index.sibling(index.row(),1),role).toInt() * (1.0 - data(index.sibling(index.row(),2),role).toDouble());
    }
    else {
        return QSqlTableModel::data(index, role);
    }
}

int SqlTableModel::columnCount(const QModelIndex &parent) const
{
    const int count = QSqlTableModel::columnCount(parent) + 1;
    return count;
}

bill::bill(QWidget *parent,QSqlDatabase *db, bool d) : QWidget(parent)
  ,ui(new Ui::bill)
{
    ui->setupUi(this);
    mdl = new SqlTableModel(this);
    mdl->setTable("bill");
    mdl->select();
    mdl->setHeaderData(0,Qt::Horizontal,"№");
    mdl->setHeaderData(1,Qt::Horizontal,"Сумма");
    mdl->setHeaderData(2,Qt::Horizontal,"Скидка");
    mdl->setHeaderData(3,Qt::Horizontal,"Сумма со скидкой");
    ui->tableView->setModel(mdl);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    mdl->setEditStrategy(QSqlTableModel::OnFieldChange);
    QRect rect = ui->tableView->geometry();
    rect.setWidth(2 + ui->tableView->verticalHeader()->width() + ui->tableView->columnWidth(0) + ui->tableView->columnWidth(1) + ui->tableView->columnWidth(2) + ui->tableView->columnWidth(3) + ui->tableView->columnWidth(4));
    ui->tableView->setGeometry(rect);
    if(d)
    {
        ui->pushButton_Del->setEnabled(false);
    }
    else
    {
        ui->pushButton_Cho->setEnabled(false);
    }
}

void bill::on_pushButton_Del_clicked()
{
    if(mdl->rowCount()!=0)
    {
        int selRow = ui->tableView->currentIndex().row();
        if(selRow >= 0)
        {
            mdl->removeRow(selRow);
            if(!mdl->submitAll())
                QMessageBox::critical(NULL,QObject::tr("Ошибка"),mdl->lastError().text());
            mdl->select();
        }
    }
}

void bill::on_pushButton_Cho_clicked()
{
    if(mdl->rowCount()!=0)
    {
        int selRow = ui->tableView->currentIndex().row();
        if(selRow >= 0)
        {
            emit ret_id(mdl->record(selRow).value(0).toInt());
            close();
        }
    }
}
