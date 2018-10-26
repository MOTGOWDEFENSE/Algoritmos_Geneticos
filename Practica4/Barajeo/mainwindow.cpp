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
     //familia(16,5,10,3,3);
     //familia(16,5,30,3,3);
     //familia(16,5,50,3,3);
     familia(16,5,100,3,3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::graficar(){
    //cout << "entro a graficar"<<endl;
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

void MainWindow::familia(int imiembros,int igenes,int igeneraciones,int ipcruza,int imutar){
    miembros = imiembros;
    genes = igenes;
    generaciones = igeneraciones;
    pcruza = ipcruza;
    mutar = imutar;
    contador=0;
    for(int i=0;i<generaciones;i++){
        //esta parte habra que meterla en un form de tamaño de generaciones en void familia
        llenaindividuos();
        captitud();
        cprobabilidad();
        if(i==0 || i==(generaciones-1))
            TablasA(i+1);
        barajeo();
        if(i==0 || i==(generaciones-1))
            TablasA1(i+1);
        cruza();
        if(i==0 || i==(generaciones-1))
            TablasB(i+1);
        TablasC(i+1);
        maxmin();
        reasignar();
    }
    graficar();
}

void MainWindow::llenaindividuos(){
    int limite=0,random;
    for(int i=0;i<genes;i++){
        limite += pow(2,i);
    }
    for(int i=0;i<miembros;i++){
        random =  rand() % limite + 1;//numero para el individuo
        individuosE[i]= random;
        //cout <<"i: "<<i<<" entero: "<< individuosE[i] << " Binario: ";
        toBinary(random,i);
        //cout << endl;
    }
}

void MainWindow::toBinary(int numero,int valori){
    int dividendo, resto, divisor = 2,cont = 1,j=genes-1;
    for(int i=0;i<genes;i++){
        individuosB[valori][i] = 0;
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
    cout << endl;
}

void MainWindow::captitud(){
    suma = 0;
    for(int i=0;i<miembros;i++){
        //aptitud[i] = pow(individuosE[i],2);
        aptitud[i] = (individuosE[i]-5)/(float)(2+sin(individuosE[i]));
        if(aptitud[i] < 0){
            aptitud[i] *= -1;
        }
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

void MainWindow::barajeo(){

    barajeo1[0] = -1;
    barajeo2[0] = -1;
    int comodin,contador1=0,ban=0,contador2=0;
    while(contador1<miembros){
        comodin = rand() % miembros;
        for(int j=0;j<contador1;j++){
            if(barajeo1[j] == comodin){
                ban=1;
                break;
            }
        }
        if(ban==0){
            //cout << "Barajeo: " << comodin << " Contador1: "<<contador1<< endl;
            barajeo1[contador1] = comodin;
            contador1++;
        }
        ban=0;
    }
    /*cout << endl;
    cout << "salio del primer while"<<endl;
    cout << endl;*/

    contador1 = 0,contador2=0;
    float p=0;
    while(contador1<miembros){
        comodin = rand() % miembros;
        for(int j=0;j<contador1;j++){
            if(barajeo2[j] == comodin){
                ban=1;
                break;
            }
        }
        if(ban==0){
            //cout << "Barajeo: " << comodin << " Contador1: "<<contador1<< endl;
            barajeo2[contador1] = comodin;
            contador1++;
        }
        ban=0;
    }
    /* << endl;
    cout << "salio del primer while"<<endl;
    cout << endl;*/
    for(int i=0;i<(miembros-1);i++){
            p = (float) rand()/RAND_MAX; //el valor de 0.7<=p<=1

            if(flip(p)){//flip sale TRUE
                if(barajeo1[i]>barajeo1[i+1]) //Asiganmos el que tenga mayor jerarquía
                    padres[contador2] = barajeo1[i];
                else
                    padres[contador2] = barajeo1[i+1];

            }else if(!flip(p)){//flip sale FALSE
                if(barajeo1[i]<barajeo1[i+1]) //Asiganmos el que tenga menor jerarquía
                    padres[contador2] = barajeo1[i];
                else
                    padres[contador2] = barajeo1[i+1];

            }
            contador2++;
            i++;
        }
        for(int i=0;i<(miembros-1);i++){
            p = (float) rand()/RAND_MAX; //el valor de 0.7<=p<=1

            if(flip(p)){//flip sale TRUE
                if(barajeo2[i]>barajeo2[i+1]) //Asiganmos el que tenga mayor jerarquía
                    padres[contador2] = barajeo2[i];
                else
                    padres[contador2] = barajeo2[i+1];

            }else if(!flip(p)){//flip sale FALSE
                if(barajeo2[i]<barajeo2[i+1]) //Asiganmos el que tenga menor jerarquía
                    padres[contador2] = barajeo2[i];
                else
                    padres[contador2] = barajeo2[i+1];

            }
            contador2++;
            i++;
        }
    /*for(int i=0;i<miembros;i++){
        cout << "valor: "<<padres[i]<<endl;
    }*/
}

bool MainWindow::flip(float p){
    if(p<0.7)
        return false;
    else
        return true;
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
            individuosBD[i+1][k] = individuosBC[i+1][k];
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

void MainWindow::mutacion(){
    int imutar;
    for(int i=0;i<mutar;i++){
        imutar = rand() % (miembros-1) + 1;
        //gmutar = rand() % (genes-1) + 1;
        for(int j=0;j<genes;j++){
            if(individuosBD[imutar][j] == 0){
                individuosBD[imutar][j] = 1;
                break;
            }
        }
        /*for(int j=0;j<genes;j++){
            cout << individuosBD[imutar][j];
        }
        cout << endl;*/
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

void MainWindow::TablasA1(int generacion){
    ofstream archivo;  // objeto de la clase ofstream
    archivo.open("tablasA1.txt",ios::app);
    archivo << generacion << "a generacion | Tabla de seleccion de padres" << endl;
    archivo << "No. | Poblacion Inicial | Aptitud |Barajeo 1| Barajeo 2"<<endl;
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
        archivo<<(i+1)<<setw(4)<< "|"<<setw(12)<< binario[i]<<setw(8)<<"|"<<setw(7)<<aptitud[i]<<setw(3) <<"|"<< setw(5)<<(barajeo1[i]+1)<<setw(5)<<"|" <<setw(5)<<(barajeo2[i]+1)<<endl;
    }
    archivo<<endl<<endl;
    archivo.close();
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
    float binD[miembros];
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

        float binD[miembros];
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

float MainWindow::getSuma(float *aux){
    int suma=0;
    for(int i=0;i<miembros;i++)
        suma+=aux[i];
    return suma;
}

float MainWindow::getMaxI(float *aux){
    int max=aux[0];
    for(int i=0;i<miembros;i++)
        if(aux[i] > max)
            max = aux[i];
    return max;
}

float MainWindow::getMinI(float *aux){
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



double MainWindow::getmaxy(){
    float regresa =0;
    for(int i=0;i<generaciones;i++){
        if(regresa < mayores[i]){
            regresa = mayores[i];
        }
    }
    return (double)regresa;
}

