#include "dialog.h"
#include "ui_dialog.h"
#include <QSettings>
#include <QFile>
#include <QXmlStreamReader>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QTextBrowser>
#include <QAction>

Dialog::Dialog(QWidget *parent)
    :QWidget(parent)
, ui(new Ui::Dialog)
    , duty()
{
    ui->setupUi(this);
    readFromFile("C:/Qt/QtWork/Tittled4/sht.ini");
}
void Dialog::readFromFile(const QString &fileName)
{
    QVector <QWidget*> mas;
    QSettings sett(fileName, QSettings::IniFormat);
    QFile file("C:/Qt/QtWork/Tittled4/dialog.xml");
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        reader.readNext();
        while(!reader.atEnd())
        {
            if(reader.isStartElement())
            {
                if(reader.name().toString() == "label")
                {
                    int x=0,y=0,h=0,w=0;
                    foreach (const QXmlStreamAttribute &attr,reader.attributes())
                    {
                        if(attr.name().toString()=="text")
                        {
                            mas << new QLabel(attr.value().toString(),this,Qt::Widget);
                        }
                        if(attr.name().toString() == "x")
                        {
                            x=attr.value().toInt();
                        }
                        if(attr.name().toString() == "y")
                        {
                            y=attr.value().toInt();
                        }
                        if(attr.name().toString() == "width")
                        {
                            w=attr.value().toInt();
                        }
                        if(attr.name().toString() == "height")
                        {
                            h=attr.value().toInt();
                        }
                    }
                    qobject_cast<QWidget*>(mas[mas.size()-1])->setGeometry(x,y,w,h);
                }
                if(reader.name().toString() == "button")
                {
                    int x=0,y=0,h=0,w=0;
                    foreach (const QXmlStreamAttribute &attr,reader.attributes())
                    {
                        if(attr.name().toString()=="text")
                        {
                            mas << new QPushButton(attr.value().toString(),this);
                        }
                        if(attr.name().toString() == "x")
                        {
                            x=attr.value().toInt();
                        }
                        if(attr.name().toString() == "y")
                        {
                            y=attr.value().toInt();
                        }
                        if(attr.name().toString() == "width")
                        {
                            w=attr.value().toInt();
                        }
                        if(attr.name().toString() == "height")
                        {
                            h=attr.value().toInt();
                        }
                    }
                    qobject_cast<QWidget*>(mas[mas.size()-1])->setGeometry(x,y,w,h);
                }
                if(reader.name().toString() == "textbrowser")
                {
                    int x=0,y=0,h=0,w=0;
                    foreach (const QXmlStreamAttribute &attr,reader.attributes())
                    {
                        if(attr.name().toString()=="name")
                        {
                            mas << new QTextBrowser(this);
                        }
                        if(attr.name().toString() == "x")
                        {
                            x=attr.value().toInt();
                        }
                        if(attr.name().toString() == "y")
                        {
                            y=attr.value().toInt();
                        }
                        if(attr.name().toString() == "width")
                        {
                            w=attr.value().toInt();
                        }
                        if(attr.name().toString() == "height")
                        {
                            h=attr.value().toInt();
                        }
                    }
                    qobject_cast<QTextBrowser*>(mas[mas.size()-1])->setGeometry(x,y,w,h);
                }
                if(reader.name().toString() == "textedit")
                {
                    int x=0,y=0,h=0,w=0;
                    foreach (const QXmlStreamAttribute &attr,reader.attributes())
                    {
                        if(attr.name().toString()=="name")
                        {
                            mas << new QTextEdit(this);
                        }
                        if(attr.name().toString() == "x")
                        {
                            x=attr.value().toInt();
                        }
                        if(attr.name().toString() == "y")
                        {
                            y=attr.value().toInt();
                        }
                        if(attr.name().toString() == "width")
                        {
                            w=attr.value().toInt();
                        }
                        if(attr.name().toString() == "height")
                        {
                            h=attr.value().toInt();
                        }
                    }
                    qobject_cast<QTextEdit*>(mas[mas.size()-1])->setGeometry(x,y,w,h);
                }
            }
            reader.readNext();
        }
    }
    file.close();
    sett.beginGroup("1");
    duty.name = sett.value("name", "anonymous").toString();
    duty.date = sett.value("date", "20.10.2019").toDateTime();
    duty.dolg = sett.value("dolg", 0).toInt();
    sett.endGroup();
    qobject_cast<QTextBrowser*>(mas[0])->setText(duty.name);
    qobject_cast<QTextBrowser*>(mas[1])->setText(duty.date.toString("dd.MM.yyyy"));
    connect(qobject_cast<QPushButton*>(mas[3]), &QPushButton::pressed, [&] ()
    {
        int paid = qobject_cast<QTextEdit*>(mas[2])->toPlainText().toInt();
        int dlg = this->duty.dolg - paid;
        sett.beginGroup("1");
        sett.setValue("dolg",dlg);
        sett.endGroup();
        close();
    });
}

Dialog::~Dialog()
{
    delete ui;
}
