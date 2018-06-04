#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QFileDialog>
//#include <QMouseEvent>
#include "Cell.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(200,270);

    beginLabel = new QLabel(this);
    widthLabel = new QLabel(this);
    heightLabel = new QLabel(this);
    fieldHeightEdit = new QLineEdit(this);
    fieldWidthEdit = new QLineEdit(this);
    fieldBtn = new QPushButton(this);
    loadBtn = new QPushButton(this);

    beginLabel->setText("Введите размеры поля\n(в количестве ячеек)");
    beginLabel->setGeometry(20,30,160,30);
    beginLabel->setAlignment(Qt::AlignCenter);

    widthLabel->setText("Ширина:");
    widthLabel->setGeometry(20,100,60,20);
    widthLabel->setAlignment(Qt::AlignRight);
    fieldWidthEdit->setGeometry(90,100,100,20);

    heightLabel->setText("Высота:");
    heightLabel->setGeometry(20,140,60,20);
    heightLabel->setAlignment(Qt::AlignRight);
    fieldHeightEdit->setGeometry(90,140,100,20);

    fieldBtn->setGeometry(50,180,100,30);
    fieldBtn->setText("Создать");
    loadBtn->setGeometry(50,210,100,30);
    loadBtn->setText("Загрузить...");

    connect(fieldBtn, SIGNAL(clicked(bool)), this, SLOT(createFieldSlot()));
    connect(loadBtn, SIGNAL(clicked(bool)), this, SLOT(loadSlot()));

}

void MainWindow::nullCheck()
{
    QMessageBox::information(this,"Good", "yep");
//    bool key = true;
//    QString *p = &first;        //--установились на начало списка параметров
//    while (*p != NULL)         //--пока аргумент не равен нулю
//    {
//        if (p == NULL or p == QString::number(0))
//        {
//            QMessageBox::warning(this,"Check","Error");
//            key = false;
//            break;
//        }
//        p++;
//    }

//    if(key)
//    {
//        QMessageBox::information(this,"Good","All right!");
//    }
}



void MainWindow::createFieldSlot()
{

    int width = fieldWidthEdit->text().toInt();
    int height = fieldHeightEdit->text().toInt();
    gField = new Field(width, height);
    game = new Game(width, height);

    startNewGame(height, width);
}

void MainWindow::clickCellSlot(int row, int col){
//    QMessageBox::information(this,"",QString::number(row) + '|' + QString::number(col));
    if (pencilRBtn->isChecked()){
        fieldTable->item(row, col)->setBackgroundColor(Qt::green);
//    fieldTable->setItem(row, col, QTableWidgetItem.setBackgroundColor(Qt::blue));
        gField->makeAlive(col,row);
//    QMessageBox::warning(this,"",QString::number(info.value()));
    }
    if (eraserRBtn->isChecked()){
        gField->returnField()[row][col].bIsAlive = false;
        if (!gField->returnField()[row][col].bIsAlive)
            fieldTable->item(row, col)->setBackgroundColor(Qt::white);
    }
}

void MainWindow::clickCellStateSlot(int row, int col){
    if (!tmr->isActive()){
        if(row==2){
            states[0][col] = false;
            bornCount->item(1,col)->setBackground(Qt::white);
            states[2][col] = false;
            bornCount->item(3,col)->setBackground(Qt::white);
        }
        else{
            states[1][col] = false;
            bornCount->item(2,col)->setBackground(Qt::white);
        }
        states[row-1][col] = true;
        bornCount->item(row,col)->setBackground(Qt::green);
    }
    else
    {
        QMessageBox::warning(this,"","Нажмите стоп прежде чем настраивать условия жизни!");
    }
}

void MainWindow::startNewGame(int height, int width){
    this->resize(800,600);
//    QIcon icon("gol_ic.icns");
//    this->setWindowIcon(icon);

        beginLabel->hide();
        widthLabel->hide();
        heightLabel->hide();
        fieldHeightEdit->hide();
        fieldWidthEdit->hide();
        fieldBtn->hide();


        fieldTable = new QTableWidget(height,width,this);
    //    tablesList = new QList<QTableWidget>;
    //    tablesList << fieldTable;

        saveBtn = new QPushButton(this);
        freqTimer = new QLineEdit(this);
        setTimer = new QPushButton(this);
        epochLabel = new QLabel(this);
        pencilRBtn = new QRadioButton(this);
        eraserRBtn = new QRadioButton(this);
    //    epochSlider = new QSlider(this);
        bornLabel = new QLabel(this);
        bornCount = new QTableWidget(4,9,this);
        setBornCountBtn = new QPushButton(this);
        startBtn = new QPushButton(this);
        stopBtn = new QPushButton(this);
        freqLabel = new QLabel(this);
        int cellSize;
//        bool states;

    epoch = 0;
    bornNum = 3;

    bornCount->horizontalHeader()->setDefaultSectionSize(20);
    bornCount->verticalHeader()->setDefaultSectionSize(20);
    bornCount->setGeometry(600,445,182,82);
    bornCount->horizontalHeader()->setVisible(false);
    bornCount->verticalHeader()->setVisible(false);
    bornCount->setEditTriggers(0);
    for (int h=0; h<4; h++)
            for(int w=0;w<9;w++)
           {
                QTableWidgetItem *t = new QTableWidgetItem("");
                if (h==0)
                    t->setText(QString::number(w));
                t->setFlags(t->flags() &= ~Qt::ItemIsSelectable );
                bornCount->setItem(h,w,t);
           }
    for (int s=0; s<3; s++)
        for (int num=0; num<9; num++){
            if (s==0){
                if (num==3)
                    states[s][num] = true;
                else
                    states[s][num] = false;
            }
            if (s==1){
                if (num!=3 && num!=2)
                    states[s][num] = true;
                else
                    states[s][num] = false;
            }
            if (s==2){
                if (num==3 || num==2)
                    states[s][num] = true;
                else
                    states[s][num] = false;
            }
        }
    for (int s=0; s<3; s++){
        for (int num=0; num<9; num++){
            if(states[s][num])
                bornCount->item(s+1,num)->setBackground(Qt::green);
            else
                bornCount->item(s+1,num)->setBackground(Qt::white);
        }
    }

//    for (int s=0; s<2; s++){
//        for (int num=0; num<9; num++){
//            std::cout<<states[s][num]<<' ';
//        }
//        std::cout<<"\n";
//    }
//    std::cout<<"---------------";

    fieldTable->setGeometry(20,30,530,530);
    if (width>height) cellSize = 530 / width;
    else cellSize = 530 / height;

    fieldTable->horizontalHeader()->setVisible(false);
    fieldTable->horizontalHeader()->setDefaultSectionSize(cellSize);
    fieldTable->verticalHeader()->setVisible(false);
    fieldTable->verticalHeader()->setDefaultSectionSize(cellSize);
    fieldTable->setEditTriggers(0);
    for (int h=0; h<height; h++)
            for(int w=0;w<width;w++)
           {
               QTableWidgetItem *t = new QTableWidgetItem("");
               t->setFlags(t->flags() &= ~Qt::ItemIsSelectable );
               fieldTable->setItem(h,w,t);
           }


    freqLabel->setGeometry(580,120,200,24);
    freqLabel->setText("Скорость анимации в мс.");
    freqLabel->setAlignment(Qt::AlignCenter);
    freqTimer->setGeometry(580,160,200,24);
    setTimer->setGeometry(630,200,100,24);
    setTimer->setText("Принять");
    startBtn->setGeometry(580,260,90,24);
    startBtn->setText("Старт");
    stopBtn->setGeometry(690,260,90,24);
    stopBtn->setText("Стоп");


    epochLabel->setGeometry(580,340,80,16);
    epochLabel->setText(QString("Эпоха: 0"));

    pencilRBtn->setText("Добавить");
    pencilRBtn->setChecked(true);
    pencilRBtn->setGeometry(680,324,100,18);
    eraserRBtn->setText("Убрать");
    eraserRBtn->setGeometry(680,356,100,18);


    bornLabel->setText("Количество клеток \nдля рождения новой");
    bornLabel->setGeometry(580,400,200,32);
    bornLabel->setAlignment(Qt::AlignHCenter);
//    bornCount->setText("3");
    setBornCountBtn->setText("Установить");
    setBornCountBtn->setGeometry(630,540,100,24);

    saveBtn->setGeometry(625,30,110,24);
    saveBtn->setText("Сохранить...");

//    epochSlider->setGeometry(580,380,200,22);
//    epochSlider->setOrientation(Qt::Horizontal);
//    epochSlider->setMaximum(0);

    saveBtn->show();
    freqLabel->show();
    freqTimer->show();
    setTimer->show();
    fieldTable->show();
    bornLabel->show();
    bornCount->show();
    setBornCountBtn->show();
    startBtn->show();
    stopBtn->show();
    epochLabel->show();
    pencilRBtn->show();
    eraserRBtn->show();
//    epochSlider->show();

    tmr = new QTimer(this);
    tmr->setInterval(250);

    drawField();

    connect(saveBtn, SIGNAL(clicked(bool)), this, SLOT(saveSlot()));
    connect(setTimer, SIGNAL(clicked(bool)), this, SLOT(setFreqSlot()));
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateStateSlot()));
//    connect(epochSlider, SIGNAL(sliderMoved(int)), this, SLOT(epochSlot(int)));
    connect(fieldTable, SIGNAL(cellClicked(int,int)), this, SLOT(clickCellSlot(int, int)));
    connect(bornCount, SIGNAL(cellClicked(int,int)), this, SLOT(clickCellStateSlot(int, int)));
    connect(startBtn, SIGNAL(clicked(bool)),this,SLOT(startGameSlot()));
    connect(stopBtn, SIGNAL(clicked(bool)),this,SLOT(stopGameSlot()));
    connect(setBornCountBtn, SIGNAL(clicked(bool)),this,SLOT(setBornNumSlot()));
}

void MainWindow::drawField(){
    Cell **f = gField->returnField();
    for(int h = 0; h < gField->iFieldHeight; h++)
    {
        for(int w = 0; w < gField->iFieldWidth; w++)
        {
            if(f[h][w].bIsAlive == 1) fieldTable->item(h,w)->setBackground(Qt::green);
            if(f[h][w].bIsAlive == 0 && fieldTable->item(h,w)->backgroundColor() == Qt::green) fieldTable->item(h,w)->setBackground(Qt::white);
//            else fieldTable->item(h,w)->setBackground(Qt::white);
//            fieldTable->setItem(h, w, item);
//            QMessageBox::warning(this,"",QString::number(gField->returnField()[h][w].bIsAlive));


        }
    }
}

void MainWindow::setBornNumSlot(){
//    try{
//        if (!tmr->isActive())
//            if (bornCount->text().toInt()<9 && bornCount->text().toInt()>=0)
//                bornNum = bornCount->text().toInt();
//            else
//                QMessageBox::warning(this,"Error","Введите число от 0 до 8!");

//        else
//            QMessageBox::warning(this,"Error"," Нажмите стоп прежде чем ввести!");

//    }catch(...){
//        QMessageBox::warning(this,"Error","Введите корректное значение ячейки!");
//    }

}

void MainWindow::updateStateSlot(){
    game->start(gField, states);
    drawField();
    epoch ++;
//    tablesList[epochSlider->value()]
//    epochSlider->setMaximum(epochSlider->maximum()+1);
//    epochSlider->setValue(epochSlider->maximum());
    epochLabel->setText(QString("Эпоха: ")+QString::number(epoch));
}

void MainWindow::setFreqSlot(){
    try{
        if (!tmr->isActive()){
            tmr->setInterval(freqTimer->text().toInt());
        }
    }catch(...){
        QMessageBox::warning(this,"Error","Введите корректное значение таймера!");
    }
}

void MainWindow::stopGameSlot(){
    tmr->stop();
}

void MainWindow::startGameSlot(){
    tmr->start();

//    fieldTable = new QTableWidget(height,width,this);
//    fieldTable->horizontalHeader()->setVisible(false);
//    fieldTable->horizontalHeader()->setDefaultSectionSize(cellSize);
//    fieldTable->verticalHeader()->setVisible(false);
//    fieldTable->verticalHeader()->setDefaultSectionSize(cellSize);
//    fieldTable->setEditTriggers(0);
//    tablesList << fieldTable;

}

//void MainWindow::epochSlot(int pos)
//{
//    epochLabel->setText(QString("Эпоха: ")+QString::number(pos));

//}


void MainWindow::saveSlot(){
    QString fileName = QFileDialog::getSaveFileName(this,
             tr("Сохранить геном"), "",
             tr("Геном (*.gfld);;All Files (*)"));
    if (fileName.isEmpty())
             return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_3);

        Cell** temp = gField->returnField();
        out << QString::number(gField->iFieldHeight) << "\n" << QString::number(gField->iFieldWidth) << "\n";
        for(int h = 0; h < gField->iFieldHeight; h++){
            for(int w = 0; w < gField->iFieldWidth; w++)
                out << QString::number(temp[h][w].bIsAlive);
            out << "\n";
        }
    }
}

void MainWindow::loadSlot(){

    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Открыть геном"), "",
             tr("Геном (*.gfld);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_3);

        QString pntr;
        int height, width;

        in >> pntr;
        height = pntr.toInt();
        in >> pntr;

        in >> pntr;
        width = pntr.toInt();
        in >> pntr;

        gField = new Field(width, height);

        for(int h = 0; h < height; h++){
            for(int w = 0; w < width; w++){
                if (pntr.toInt() == 1)
                    gField->makeAlive(w,h);
                in >> pntr;
            }
            in >> pntr;
        }
        game = new Game(width, height);
        startNewGame(height, width);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}





