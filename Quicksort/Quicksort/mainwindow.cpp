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
    qDebug()<<ui->gridLayout->maximumSize().width();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Fill()
{
    for(int j=0;j<this->QuickSort->GetSize();j++)
    {
        switch (j) {
        case 0:
            ui->le_element1->setText(QString::number(QuickSort->Get(j)));
            break;
        case 1:
            ui->le_element2->setText(QString::number(QuickSort->Get(j)));
            break;
        case 2:
            ui->le_element3->setText(QString::number(QuickSort->Get(j)));
            break;
        case 3:
            ui->le_element4->setText(QString::number(QuickSort->Get(j)));
            break;
        case 4:
            ui->le_element5->setText(QString::number(QuickSort->Get(j)));
            break;
        case 5:
            ui->le_element6->setText(QString::number(QuickSort->Get(j)));
            break;
        case 6:
            ui->le_element7->setText(QString::number(QuickSort->Get(j)));
            break;
        case 7:
            ui->le_element8->setText(QString::number(QuickSort->Get(j)));
            break;
        case 8:
            ui->le_element9->setText(QString::number(QuickSort->Get(j)));
            break;
        case 9:
            ui->le_element10->setText(QString::number(QuickSort->Get(j)));
            break;
        }
    }
}

void MainWindow::on_OpenFile_triggered()
{

    QFile file(QFileDialog::getOpenFileName( this,tr("choose your file"),"","TextFile(*.txt)"));
    if(!file.open(QIODevice::ReadOnly)) {
        //QMessageBox::information(0,"error",file.errorString());
    }

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
