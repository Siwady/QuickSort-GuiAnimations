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
    ui->cb_algorithm->addItem("3. Quicksort Dual Pivot Algorithm");
    play=false;
    this->timer=new QTimer(this);
    connect(this->timer,SIGNAL(timeout()),this,SLOT(Play()));
    this->timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
    play=false;
    delete QuickSort;

}

void MainWindow::Fill()
{
    QValidator *validator = new QIntValidator(0,999, this);
    for(int i=0;i<this->EditList.size();i++){
        ui->gridElements->removeWidget(this->EditList.at(i));
        delete this->EditList.at(i);
    }
    ui->gridElements->update();
    this->EditList.clear();
    //this->QuickSort->items.clear();
    for(int j=0;j<this->QuickSort->GetSize();j++)
    {
        EditList.push_back(new QLineEdit(QString::number(this->QuickSort->Get(j)),this));
        EditList.at(j)->setValidator(validator);
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
        ui->pb_generate->setEnabled(true);
    }


    file.close();


}


void MainWindow::on_bt_play_clicked()
{
    //this->QuickSort->QuickSort(0,this->QuickSort->items.size()-1);
    if(!play){
        ui->bt_play->setText("Pause");
        play=true;
        this->timer->start(50);
        ui->pb_nextStep->setEnabled(false);
        ui->pb_previousStep->setEnabled(false);
    }else
    {
        ui->bt_play->setText("Play");
        play=false;
        ui->pb_nextStep->setEnabled(true);
        ui->pb_previousStep->setEnabled(true);
    }
    //this->QuickSort->PlayQuickSort();
    this->QuickSort->renderArea->update();

}

void MainWindow::on_pb_generate_clicked()
{
    for(int i=0;i<this->QuickSort->steps.size();i++)
    {
        delete this->QuickSort->steps.at(i);
    }
    this->QuickSort->currentStep=0;
    this->QuickSort->steps.clear();
    this->QuickSort->GenerateSteps(ui->cb_algorithm->currentIndex());
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
    ui->bt_play->setText("Play");
    ui->pb_nextStep->setEnabled(false);
    ui->pb_previousStep->setEnabled(false);
    for(int i=0;i<this->EditList.size();i++)
    {
            this->QuickSort->Add(this->EditList.at(i)->text().toInt());
    }

    this->QuickSort->indexA=this->QuickSort->indexB=this->QuickSort->pivotIndex=this->QuickSort->End=
            this->QuickSort->Begin=-1;
    this->QuickSort->renderArea->update();
    ui->pb_generate->setEnabled(true);
}

void MainWindow::Play()
{
    if(play)
    {
        this->QuickSort->PlayAlgorithm();
        this->QuickSort->renderArea->update();
        if(this->QuickSort->currentStep==this->QuickSort->steps.size()-1){
            ui->bt_play->setText("Play");
            play=false;
        }
        timer->start(100);
    }
}

void MainWindow::on_SaveFile_triggered()
{
    QString text="[";
    for(int i=0;i<this->EditList.size();i++)
    {
        text.append(QString::number(this->EditList.at(i)->text().toInt()));
        if(i==this->EditList.size()-1)
            text.append("]");
        else
            text.append(",");
    }
    text.replace(" ","");
    QString filename = QFileDialog::getSaveFileName(
            this,
            tr("Save Document"),
            QDir::currentPath(),
            tr("TextFile(*.txt)") );
    if( !filename.isNull() )
    {
        QFile f(filename);
        f.open(QIODevice::WriteOnly);
        f.write(text.toLatin1());
        f.close();
    }
}

void MainWindow::on_pb_Add_clicked()
{
    this->EditList.push_back(new QLineEdit(""));
    ui->gridElements->addWidget(EditList.at(EditList.size()-1));
}

void MainWindow::on_pb_Delete_clicked()
{
    for(int i=0;i<this->EditList.size();i++){
        if(this->EditList.at(i)->text().isEmpty())
        {
               delete this->EditList.at(i);
               this->EditList.removeAt(i);
        }
    }
}
