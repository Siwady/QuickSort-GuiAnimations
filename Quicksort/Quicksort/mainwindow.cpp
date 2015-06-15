#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QFile>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    qApp->setStyle("fusion");

    this->QuickSort=new QuickSortArray();
    ui->gridLayout->addWidget(this->QuickSort->renderArea,0,0);

    ui->cb_algorithm->addItem("1. Quicksort 2 Ways Algorithm");
    ui->cb_algorithm->addItem("2. Quicksort 3 Ways Algorithm");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Fill()
{
    for(int i=0;i<this->EditList.size();i++){
        ui->gridElements->removeWidget(this->EditList.at(i));
        delete this->EditList.at(i);
    }
    ui->gridElements->update();
    this->EditList.clear();
    //this->QuickSort->items.clear();
    for(int j=0;j<this->QuickSort->GetSize();j++)
    {
        EditList.push_back(new QTextEdit(QString::number(this->QuickSort->Get(j)),this));
        //ui->gridElements->addWidget(EditList.at(j));
    }
    for(int j=0;j<this->EditList.size();j++)
    {
        EditList.at(j)->setAlignment(Qt::AlignCenter);
        ui->gridElements->addWidget(EditList.at(j));
    }
}

void MainWindow::on_OpenFile_triggered()
{

    QFile file(QFileDialog::getOpenFileName( this,tr("choose your file"),"","TextFile(*.txt)"));
    if(file.open(QIODevice::ReadOnly)) {
        this->QuickSort->items.clear();
        QTextStream in(&file);
        while(!in.atEnd()) {
            QString line = in.readLine();
            fields = line.split(",").replaceInStrings("[","").replaceInStrings("]","");

            for(int i=0;i<fields.size();i++)
            {
                this->QuickSort->Add(fields.at(i).toInt());
            }
            qDebug()<<this->QuickSort->GetSize();
            qDebug()<<this->QuickSort->Get(1);
        }
       // this->QuickSort->renderArea->setArray(this->QuickSort);
        this->QuickSort->renderArea->setFocus();
        Fill();
    }


    file.close();


}


void MainWindow::on_bt_play_clicked()
{
    //this->QuickSort->QuickSort(0,this->QuickSort->items.size()-1);
    this->QuickSort->PlayQuickSort();
}

void MainWindow::on_pb_generate_clicked()
{
    this->QuickSort->GenerateSteps();
    qDebug()<<this->QuickSort->steps.size();
    ui->bt_play->setEnabled(true);
    ui->pb_nextStep->setEnabled(true);
    ui->pb_previousStep->setEnabled(true);
}

void MainWindow::on_pb_nextStep_clicked()
{
    this->QuickSort->NextStep();
}

void MainWindow::on_pb_previousStep_clicked()
{
    this->QuickSort->PreviousStep();
}

void MainWindow::on_pb_update_clicked()
{
    this->QuickSort->items.clear();
    ui->bt_play->setEnabled(false);
    ui->pb_nextStep->setEnabled(false);
    ui->pb_previousStep->setEnabled(false);
    for(int i=0;i<this->EditList.size();i++)
    {
            this->QuickSort->Add(this->EditList.at(i)->toPlainText().toInt());
    }

    this->QuickSort->indexA=this->QuickSort->indexB=this->QuickSort->pivotIndex=this->QuickSort->End=
            this->QuickSort->Begin=-1;
    this->QuickSort->renderArea->repaint();
}
