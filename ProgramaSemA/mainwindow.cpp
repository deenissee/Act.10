#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Neurona::Neurona(int id, float voltaje, int posicion_x, int posicion_y, int red, int green, int blue, Neurona *sig)
{
    this->id=id;
    this->voltaje=voltaje;
    this->posicion_x=posicion_x;
    this->posicion_y=posicion_y;
    this->red=red;
    this->blue=blue;
    this->green=green;
    this->sig=sig;
}

void Administrar::agregrarInicio(int id, float voltaje, int posicion_x, int posicion_y, int red, int green, int blue)
{
    Neurona *tmp=new Neurona(id, voltaje, posicion_x, posicion_y, red, green, blue, nullptr);
    if(!h)
    {
        h=tmp;
    }
    else
    {
        tmp->sig=h;
        h=tmp;
    }
}

void Administrar::agregarFinal(int id, float voltaje, int posicion_x, int posicion_y, int red, int green, int blue)
{
    Neurona *tmp=new Neurona(id, voltaje, posicion_x, posicion_y, red, green, blue, nullptr);
    if(!h)
    {
        h=tmp;
    }
    else
    {
        Neurona *aux=h;

        while(aux->sig!=nullptr)
        {
            aux=aux->sig;
        }
        aux->sig=tmp;
    }
}

void Administrar::mostrar()
{
}

Administrar *lis= new Administrar();
int id, posicion_x, posicion_y, red, green, blue, buscar;
float voltaje;

void MainWindow::on_insertarID_textChanged(const QString &arg1)
{
    std::string idStd = arg1.toStdString();
    bool band =! idStd.empty() && std::all_of(idStd.begin(), idStd.end(), [](char cad){
        return std::isdigit(static_cast<unsigned char>(cad));
    });

    if (band)
    {
        id= std::stoi(idStd);
    }
}


void MainWindow::on_insertarVOLT_valueChanged(int arg1)
{
    voltaje = arg1;
}


void MainWindow::on_insertPX_valueChanged(int arg1)
{
    posicion_x = arg1;
}


void MainWindow::on_insertPY_valueChanged(int arg1)
{
    posicion_y = arg1;
}


void MainWindow::on_insertRED_valueChanged(int value)
{
    red = value;
}


void MainWindow::on_insertBLUE_valueChanged(int value)
{
    blue = value;
}


void MainWindow::on_insertGREEN_valueChanged(int value)
{
    green = value;
}


void MainWindow::on_agregarINICIO_clicked()
{
    lis->agregrarInicio(id, voltaje, posicion_x, posicion_y, red, green, blue);
    vaciar();
}


void MainWindow::on_insertarFINAL_clicked()
{
    lis->agregarFinal(id, voltaje, posicion_x, posicion_y, red, green, blue);
    vaciar();
}


void MainWindow::on_plainTextEdit_textChanged()
{

}


void MainWindow::on_pushButton_3_clicked()
{
    QString lista;
    Neurona *aux=lis->h;

    if(aux)
    {
        while(aux)
        {
            QString nstr = "Neurona: " + QString::number(aux->id) + "\n";
            nstr += "Voltaje: " + QString::number(aux->voltaje) + "\n";
            nstr += "Posicion X: " + QString::number(aux->posicion_x) + "\n";
            nstr += "Posicion Y: " + QString::number(aux->posicion_y) + "\n";
            nstr += "Rojo: " + QString::number(aux->red) + "\n";
            nstr += "Verde: " + QString::number(aux->green) + "\n";
            nstr += "Azul: " + QString::number(aux->blue) + "\n\n";

            lista += nstr;
            aux=aux->sig;
        }
    }
    else
    {
        lista = "No hay elementos en la lista...";
    }

    ui->plainTextEdit->setPlainText(lista);
}

void MainWindow::vaciar()
{
    id=0;
    voltaje=0.0;
    posicion_x=0;
    posicion_y=0;
    red=0;
    green=0;
    blue=0;

    ui->insertarID->clear();
    ui->insertarVOLT->setValue(0);
    ui->insertPX->setValue(0);
    ui->insertPY->setValue(0);
    ui->insertRED->setValue(0);
    ui->insertBLUE->setValue(0);
    ui->insertGREEN->setValue(0);
}



void MainWindow::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/home", tr("Text files (*.txt)"));

    if(!fileName.isNull())
    {
        QFile file(fileName);

        if(file.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&file);
            Neurona *actual= lis->h;
            while(actual)
            {
                out<<actual->id<<'*'<<actual->voltaje<<'*'<<actual->posicion_x<<'*'<<actual->posicion_y<<'*'<<actual->red
                    <<'*'<<actual->green<<'*'<<actual->blue<<'*'<< '\n';
                actual=actual->sig;
            }
            file.close();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Error al abrir el archivo");
            msgBox.exec();
        }
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Text files (*.txt)"));

    if(!fileName.isNull())
    {
        QFile file(fileName);

        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&file);
            while(!in.atEnd())
            {
                QString QLine = in.readLine();
                QStringList div = QLine.split('*');
                if(div.size()==7)
                {
                    bool convert = false;
                    int id=div[0].toInt(&convert);
                    if (!convert)
                    {
                        continue;
                    }

                    float voltaje = div[1].toFloat(&convert);
                    if (!convert)
                    {
                        continue;
                    }

                    int posicion_x = div[2].toInt(&convert);
                    if (!convert)
                    {
                        continue;

                        int posicion_y = div[3].toInt(&convert);
                        if (!convert)
                        {
                            continue;
                        }

                        int red = div[4].toInt(&convert);
                        if (!convert)
                        {
                            continue;
                        }

                        int green = div[5].toInt(&convert);
                        if (!convert)
                        {
                            continue;
                        }

                        int blue = div[6].toInt(&convert);
                        if (!convert)
                        {
                            continue;
                        }
                        if (lis != nullptr)
                        {
                            lis->agregrarInicio(id, voltaje, posicion_x, posicion_y, red, green, blue);
                        }
                        else
                        {
                            //'lis' no está inicializado
                        }
                    }
                }
            }
        } file.close();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Error al abrir el archivo");
        msgBox.exec();
    }
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    buscar = arg1;
}


void MainWindow::on_search_clicked()
{
    Neurona* neuronaa = lis->buscar(buscar);
    if (neuronaa != nullptr)
    {
        QStringList labels;
        labels << "ID" << "Voltaje" << "Posición X" << "Posición Y" << "Rojo" << "Azul" << "Verde";

        ui->tableWidget->setColumnCount(7);
        ui->tableWidget->setHorizontalHeaderLabels(labels);

        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        QVariantList valor =
            {
                neuronaa->id,
                neuronaa->voltaje,
                neuronaa->posicion_x,
                neuronaa->posicion_y,
                neuronaa->red,
                neuronaa->blue,
                neuronaa->green
        };
        for (int i = 0; i < 7; ++i)
        {
            QTableWidgetItem* item = new QTableWidgetItem(valor[i].toString());
            ui->tableWidget->setItem(rowCount, i, item);
        }
        ui->tableWidget->resizeColumnsToContents();
        ui->tableWidget->resizeRowsToContents();
    }
    else
    {
        QMessageBox msgBox;
            msgBox.setText("No existen elementos");
            msgBox.exec();
    }
}

void MainWindow::on_dibujar_clicked()
{
    quint32 v;
    QPen pen;
    QBrush Brush;
    int ancho, alto, x, y;

    Neurona* aux = lis->h;

    if(aux!=nullptr)
    {

    while (aux != nullptr)
    {
            for (int i = 0; i <= 10; i++)
            {
            QColor color(aux->red, aux->green, aux->blue);
            color.setRed(QRandomGenerator::global()->bounded(256));
            color.setGreen(QRandomGenerator::global()->bounded(256));
            color.setBlue(QRandomGenerator::global()->bounded(256));
            pen.setColor(color);
            Brush.setColor(color);
            Brush.setStyle(Qt::SolidPattern);
            x=aux->posicion_x;
            y=aux->posicion_y;
            ancho= 40;
            alto = 40;
            QGraphicsEllipseItem* ellipse = scene->addEllipse(x, y, alto, ancho, pen, Brush);
            }
            aux =aux->sig;
    }
    ui->graphicsView;
    }
    else
    {
    QMessageBox msgBox;
    msgBox.setText("No existen neuronas");
    msgBox.exec();
    }
}

void Administrar::ordenarId()
{
    if (!h)
    {
            QMessageBox msgBox;
            msgBox.setText("No existen neuronas");
            msgBox.exec();
    }

    Neurona *aux = h;
    Neurona *tmp = nullptr;
    bool band = true;
    int tid, tposx, tposy, tred, tgreen, tblue;
    float tvolt;

    while (band)
    {
            band= false;
            aux = h;

            while (aux->sig != tmp)
            {
            if (aux->id > aux->sig->id)
            {
                tid = aux->id;
                tvolt = aux->voltaje;
                tposx = aux->posicion_x;
                tposy = aux->posicion_y;
                tred = aux->red;
                tgreen = aux->green;
                tblue = aux->blue;

                aux->id = aux->sig->id;
                aux->voltaje = aux->sig->voltaje;
                aux->posicion_x = aux->sig->posicion_x;
                aux->posicion_y = aux->sig->posicion_y;
                aux->red = aux->sig->red;
                aux->green = aux->sig->green;
                aux->blue = aux->sig->blue;

                aux->sig->id = tid;
                aux->sig->voltaje = tvolt;
                aux->sig->posicion_x = tposx;
                aux->sig->posicion_y = tposy;
                aux->sig->red = tred;
                aux->sig->green = tgreen;
                aux->sig->blue = tblue;

                band = true;
            }
            aux = aux->sig;
            }
            tmp = aux;
    }
}

void MainWindow::on_plainTextEdit_2_blockCountChanged(int newBlockCount)
{

}


void MainWindow::on_pushButton_clicked()
{
    lis->ordenarId();
    ui->plainTextEdit->clear();
    on_pushButton_3_clicked();
}
void Administrar::ordenarVoltaje()
{
    if (!h)
    {
            QMessageBox msgBox;
            msgBox.setText("No existen neurona");
            msgBox.exec();
    }

    Neurona *aux = h;
    Neurona *tmp = nullptr;
    bool band = true;
    int tid, tposx, tposy, tred, tgreen, tblue;
    float tvolt;

    while (band)
    {
            band= false;
            aux = h;

            while (aux->sig != tmp)
            {
            if (aux->voltaje > aux->sig->voltaje)
            {
                tid = aux->id;
                tvolt = aux->voltaje;
                tposx = aux->posicion_x;
                tposy = aux->posicion_y;
                tred = aux->red;
                tgreen = aux->green;
                tblue = aux->blue;

                aux->id = aux->sig->id;
                aux->voltaje = aux->sig->voltaje;
                aux->posicion_x = aux->sig->posicion_x;
                aux->posicion_y = aux->sig->posicion_y;
                aux->red = aux->sig->red;
                aux->green = aux->sig->green;
                aux->blue = aux->sig->blue;

                aux->sig->id = tid;
                aux->sig->voltaje = tvolt;
                aux->sig->posicion_x = tposx;
                aux->sig->posicion_y = tposy;
                aux->sig->red = tred;
                aux->sig->green = tgreen;
                aux->sig->blue = tblue;

                band = true;
            }
            aux = aux->sig;
            }
            tmp = aux;
    }
}

void MainWindow::on_ordenarVolt_clicked()
{
    lis->ordenarVoltaje();
    ui->plainTextEdit->clear();
    on_pushButton_3_clicked();
}

