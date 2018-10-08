#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //MainWindow::makePlot();
    //familia(32,5,5,3,3);
    //familia(32,5,10,3,3);
    familia(32,5,15,3,3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::familia(int imiembros,int igenes,int igeneraciones,int ipcruza,int imutar){
    miembros = imiembros;
        genes = igenes;
        generaciones = igeneraciones;
        pcruza = ipcruza;
        mutar = imutar;
        contador=0;
        for(int i=0;i<generaciones;i++){
            //-------------------------------------------------------------------------------------------------
            //esta parte habra que meterla en un form de tamaño de generaciones en void familia
            llenaindividuos();//crea individuosE e individuosB
            captitud();
            cprobabilidad();
            if(i==0 || i==(generaciones-1))
                TablasA(i+1);
            ruleta();
            cruza();
            if(i==0 || i==(generaciones-1))
                TablasB(i+1);
            TablasC(i+1);
            maxmin();

            reasignar();
            //-------------------------------------------------------------------------------------------------
        }
        graficar();
}

void MainWindow::captitud(){
    suma = 0;
    for(int i=0;i<miembros;i++){
        aptitud[i] = pow(individuosE[i],2);
        suma += aptitud[i];
        //cout << "x i aptitud" <<" "<<individuosE[i]<<" " <<i << " " << aptitud[i] << endl;
    }
}

void MainWindow::cprobabilidad(){
    for(int i=0;i<miembros;i++){
        probabilidad[i] = aptitud[i]/(float)suma;
        //cout <<"aptitud: "<<aptitud[i]<< " Probabilidad: "<<probabilidad[i]<<endl;
    }
    //cout << suma<< endl;
}

void MainWindow::llenaindividuos(){
    int limite=0,random;
    //int individuos[32];
    for(int i=0;i<genes;i++){
        limite += pow(2,i);
    }
    for(int i=0;i<miembros;i++){
        random =  rand() % limite + 1;//numero para el individuo
        individuosE[i]= random; //Individuos enteros es el "x"

        //cout <<"i: "<<i<<" entero: "<< individuosE[i] << " Binario: ";
        toBinary(random,i);
        //cout << endl;
    }
}

void MainWindow::toBinary(int numero,int valori){
    int dividendo, resto, divisor = 2,cont = 1,j=genes-1;
    for(int i=0;i<genes;i++){
        individuosB[valori][i] = 0; //Binario de los enteros
    }
    dividendo = numero;
    while(dividendo >= divisor){
    resto = dividendo % 2;
    if(resto == 1)
        individuosB[valori][j] = 1;
    else
       individuosB[valori][j] = 0;
       dividendo = dividendo/divisor;
       cont++;
       j--;
    }
    if(dividendo == 1)
       individuosB[valori][j] = 1;
    else
       individuosB[valori][j] = 0;
    /*for(int i=0;i<5;i++){
        cout << individuosB[valori][i] ;
    }*/
    //cout << endl;
}

void MainWindow::TablasA(int generacion){
    ofstream archivo;  // objeto de la clase ofstream
    archivo.open("tablasA.txt",ios::app);
    archivo << generacion << "a generacion | Tabla 1" << endl;
    archivo << "No. | Poblacion Inicial | Valor x | Aptitud |Probabilidad"<<endl;
    string binario[miembros];
    for(int i=0;i<miembros;i++){
        for(int j=0;j<genes;j++){
            if(individuosB[i][j]==0)
                binario[i]+='0';
            else
                binario[i]+='1';
        }
    }
    for(int i = 0; i < miembros;i++){
        archivo<<(i+1)<<setw(4)<< "|"<<setw(12)<< binario[i]<< setw(8)<<"|"<< setw(5)<<individuosE[i]<<setw(5)<<"|"<<setw(7)<<aptitud[i]<<setw(3) <<"|"<< setw(5)<<probabilidad[i]<<endl;
    }
    float promedio= 1/ (float)miembros;
    archivo<<"Suma"<<setw(32)<<"|"<<setw(8)<<suma<<setw(2)<<"|"<<"1"<<endl;
    archivo<<"Promedio"<<setw(28)<<"|"<<setw(8)<<(suma/miembros)<<setw(2)<<"|"<<promedio<<endl;
    archivo<<"Max"<<setw(33)<<"|"<<setw(8)<<getMaxI(aptitud)<<setw(2)<<"|"<<getMaxF(probabilidad)<<endl;
    archivo<<"Min"<<setw(33)<<"|"<<setw(8)<<getMinI(aptitud)<<setw(2)<<"|"<<getMinF(probabilidad)<<endl;
    archivo<<endl<<endl;
    archivo.close();
}

int MainWindow::getMaxI(int *aux){
    int max=aux[0];
    for(int i=0;i<miembros;i++)
        if(aux[i] > max)
            max = aux[i];
    return max;
}

int MainWindow::getMinI(int *aux){
    int min=aux[0];
    for(int i=0;i<miembros;i++)
        if(aux[i] < min)
            min = aux[i];
    return min;
}

float MainWindow::getMaxF(float *aux){
    float max=aux[0];
    for(int i=0;i<miembros;i++)
        if(aux[i] > max)
            max = aux[i];
    return max;
}

float MainWindow::getMinF(float *aux){
    float min=aux[0];
    for(int i=0;i<miembros;i++)
        if(aux[i] < min)
            min = aux[i];
    return min;
}

void MainWindow::ruleta(){
    int sum,flecha;
    int limites[33];
    limites[0] = 0;
    for(int i=1;i<miembros;i++){
        sum += individuosE[i];
        limites[i] = sum;
    }
    //cout << "suma: " << sum<< endl;
    for(int j=0;j<miembros;j++){
        flecha = rand() % sum + 1;
        //cout << "flecha: " << flecha << " j: "<< j << " padres: ";
        for(int i=0;i<miembros;i++){
            if(limites[i]<flecha && flecha<=limites[i+1]){
                padres[j] = i;
                //cout << padres[j] << endl;
            }
        }
    }
}

void MainWindow::cruza(){
    //int individuosBC[32][5];
    //int individuosBD[32][5];
    //int pcruza;
    for(int i=0;i<miembros;i++){
        for(int j=0;j<genes;j++){
            individuosBC[i][j] = individuosB[padres[i]][j];
        }
    }
    for(int i=0;i<miembros-1;i++){
        for(int k=0;k<pcruza;k++){
            individuosBD[i][k] = individuosBC[i][k];
            individuosBD[i+1][k] = individuosBC[i+1][k]; //Individuos binarios descendencia
        }
        for(int j=pcruza;j<genes;j++){
            individuosBD[i][j] = individuosBC[i+1][j];
            individuosBD[i+1][j] = individuosBC[i][j];
        }
        /*for(int j=0;j<genes;j++){
            cout << individuosBD[i][j];
        }
        cout << endl;
        for(int j=0;j<genes;j++){
            cout << individuosBD[i+1][j];
        }
        cout << endl;
        cout << "i: " << i << endl;
        cout << "i+1: "<< i+1 << endl;*/
        i++;
    }
}

void MainWindow::TablasB(int generacion){
    //individuosBC[32][5];
    //int individuosBD[32][5];

    ofstream archivo;  // objeto de la clase ofstream
    archivo.open("tablasB.txt",ios::app);
    archivo << generacion << "a generacion | Tabla 2" << endl;
    archivo << "No. |    Cruza    |Pto. de cruza| Descendencia | Valor x | Aptitud "<<endl;
    string binarioC[miembros], binarioD[miembros];
    for(int i=0;i<miembros;i++){
        for(int j=0;j<genes;j++){
            if(individuosBC[i][j]==0)
                binarioC[i]+='0';
            else
                binarioC[i]+='1';

            if(individuosBD[i][j]==0)
                binarioD[i]+='0';
            else
                binarioD[i]+='1';

        }
    }
    int binD[miembros];
    for(int i = 0; i < miembros;i++){
        archivo<<(i+1)<<setw(4)<< "|"<<setw(10)<< binarioC[i]<< setw(4)<<"|"<<setw(6) <<pcruza<<setw(7)<<" |"<<setw(10)<<binarioD[i]<<setw(6)<<"|"<<setw(5)<<toint(i)<<setw(5)<<"|"<<setw(5)<<(toint(i)*toint(i))<<endl; //SE TIENE QUE OBTENER EL VALOR
        binD[i]=toint(i)*toint(i);
    }
    float promedio= getSuma(binD)/ (float)miembros;
    archivo<<"Suma"<<setw(55)<<"|"<<setw(8)<<getSuma(binD)<<endl;
    archivo<<"Promedio"<<setw(51)<<"|"<<setw(8)<<promedio<<endl;
    archivo<<"Max"<<setw(56)<<"|"<<setw(8)<<getMaxI(binD)<<endl;
    archivo<<"Min"<<setw(56)<<"|"<<setw(8)<<getMinI(binD)<<endl;
    archivo<<endl<<endl;
    archivo.close();
}

int MainWindow::toint(int conv){
    int regresa = 0,exponente=0;
    for(int i=genes-1;i>=0;i--){
        //cout << individuosBD[conv][exponente];
        if(individuosBD[conv][i] == 1){
            regresa += pow(2,exponente);
        }
        exponente++;
    }
    //cout <<" " <<regresa << endl;
    return regresa;
}

int MainWindow::getSuma(int *aux){
    int suma=0;
    for(int i=0;i<miembros;i++)
        suma+=aux[i];
    return suma;
}

void MainWindow::TablasC(int generacion){ //Se tiene que mutar aqui porque el arreglo individuosBD se modifica
    //individuosBC[32][5];
    //int individuosBD[32][5];
    if(generacion==1 || generacion==generaciones){
        ofstream archivo;  // objeto de la clase ofstream
        archivo.open("tablasC.txt",ios::app);
        archivo << generacion << "a generacion | Tabla 3" << endl;
        archivo << "No. | Descendencia | Mutacion | Valor x | Aptitud "<<endl;
        string binarioD[miembros], binarioDM[miembros];
        for(int i=0;i<miembros;i++){
            for(int j=0;j<genes;j++){
                if(individuosBD[i][j]==0)
                    binarioD[i]+='0';
                else
                    binarioD[i]+='1';

            }
        }
        mutacion();
        for(int i=0;i<miembros;i++){
            for(int j=0;j<genes;j++){
                if(individuosBD[i][j]==0)
                    binarioDM[i]+='0';
                else
                    binarioDM[i]+='1';

            }
        }

        int binD[miembros];
        for(int i = 0; i < miembros;i++){
            archivo<<(i+1)<<setw(4)<< "|"<<setw(10)<< binarioD[i]<< setw(4)<<"|"<<setw(6)<<binarioDM[i]<<setw(6)<<"|"<<setw(5)<<toint(i)<<setw(5)<<"|"<<setw(5)<<(toint(i)*toint(i))<<endl; //SE TIENE QUE OBTENER EL VALOR
            binD[i]=toint(i)*toint(i);
        }


        float promedio= getSuma(binD)/ (float)miembros;
        archivo<<"Suma"<<setw(38)<<"|"<<setw(8)<<getSuma(binD)<<endl;
        archivo<<"Promedio"<<setw(34)<<"|"<<setw(8)<<promedio<<endl;
        archivo<<"Max"<<setw(39)<<"|"<<setw(8)<<getMaxI(binD)<<endl;
        archivo<<"Min"<<setw(39)<<"|"<<setw(8)<<getMinI(binD)<<endl;
        archivo<<endl<<endl;
        archivo.close();
    }else{
        mutacion();
    }
}

void MainWindow::mutacion(){
    int imutar;
    //srand (time(NULL));
    for(int i=0;i<mutar;i++){
        imutar = rand() % (miembros-1);
        //cout << "imutar: " << imutar<<endl;
        //gmutar = rand() % (genes-1) + 1;
        for(int j=0;j<genes;j++){
            //cout << individuosBD[imutar][j] << endl;
            if(individuosBD[imutar][j] == 0){

                individuosBD[imutar][j] = 1;

                break;
            }
        }

    }
}

void MainWindow::maxmin(){
    int tmax,tmin,temp;
    tmax = toint(0);
    tmin = toint(0);
    for(int i=1;i<miembros;i++){
        temp = toint(i);
        if(temp > tmax){
            tmax = 	temp;
        }
        if(temp < tmin){
            tmin = temp;
        }
        //cout <<"max "<<tmax<<endl;
        //cout <<"min "<<tmin<<endl;
    }
    mayores[contador] = cprobabilidadD(tmax);
    menores[contador] = cprobabilidadD(tmin);
    contador++;
}

float MainWindow::cprobabilidadD(int num){
    int sum=0;
    for(int i=0;i<miembros;i++){
        sum += toint(i);
    }
    return num/(float)sum;
}

void MainWindow::reasignar(){
    //individuosB,individuosE,individuosBD
    //individuosBD -> individuosB;
    //individuosBD -> toint ->individuosE;
    for(int i=0;i<miembros;i++){
        for(int j=0;j<genes;j++){
            individuosB[i][j] = individuosBD[i][j];
        }
        individuosE[i] = toint(i);
    }
}

void MainWindow::graficar(){
    cout << "entro a graficar"<<endl;
    QVector<double> x(generaciones), y(generaciones), y2(generaciones); // initialize with entries 0..100
    for (int i=0; i<generaciones; ++i)
    {
      x[i] = i; // x va de 0 a 31
      y[i] = (double)mayores[i];
      //cout << y[i] << endl;
      y2[i] = (double)menores[i];
    }
    QString str(QVariant(generaciones).toString()+" Generaciones");//genero el titulo
    ui->custom->plotLayout()->insertRow(0);
    ui->custom->plotLayout()->addElement(0, 0, new QCPTextElement(ui->custom, str, QFont("sans", 12, QFont::Bold)));
    // create graph and assign data to it:
    ui->custom->addGraph();
    ui->custom->graph(0)->setPen(QPen(Qt::red));
    ui->custom->graph(0)->setData(x, y);
    ui->custom->addGraph();
    ui->custom->graph(1)->setPen(QPen(Qt::blue));
    ui->custom->graph(1)->setData(x, y2);
    // give the axes some labels:

    ui->custom->xAxis->setLabel("x");
    ui->custom->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->custom->xAxis->setRange(0, generaciones-1);
    double maxy = getmaxy();
    ui->custom->yAxis->setRange(0, maxy);
    ui->custom->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->custom->replot();
}

double MainWindow::getmaxy(){
    float regresa =0;
    for(int i=0;i<generaciones;i++){
        if(regresa < mayores[i]){
            regresa = mayores[i];
        }
    }
    return (double)regresa;
}

void MainWindow::makePlot(){

    //familia(32,5,5,3,3);
    //familia(32,5,10,3,3);
    //familia(32,5,15,3,3);
}
