#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void familia(int,int,int,int,int);//recibe (int imiembros,int igenes,int igeneraciones,int ipcruza,int imutar)
    //----------------------------------------//
    //funciones a llamar en familia(int,int,int,int,int);
    void llenaindividuos();
    void captitud();
    void cprobabilidad();
    void TablasA(int);
    void ruleta();
    void cruza();
    void TablasB(int);
    void TablasC(int);
    void maxmin();
    void reasignar();
    void graficar();
    //----------------------------------------//
    //----------------------------------------//
    //funcion a llamar en llenaindividuos()
    void toBinary(int,int);
    //----------------------------------------//
    //funcion a llamar en tablasA
    int getMaxI(int*);
    int getMinI(int*);
    float getMaxF(float*);
    float getMinF(float*);
    //----------------------------------------//
    //funcion a llamar en tablasB
    int toint(int);
    int getSuma(int*);
    //----------------------------------------//
    //funcion a llamar en tablasC
    void mutacion();
    //----------------------------------------//
    //funciones a llamar en maxmin()
    float cprobabilidadD(int);
    //----------------------------------------//
    //funciones para graficar()
    double getmaxy();
    //----------------------------------------//
    ~MainWindow();
private slots:
    void makePlot();
private:
    Ui::MainWindow *ui;
    //----------------------------------------//
    //variables para familia()
    int miembros;
    int genes;
    int generaciones;
    int pcruza;
    int mutar;
    int contador;
    //----------------------------------------//
    //----------------------------------------//
    //variables para llenaindividuos()
    int individuosE[32];//
    //----------------------------------------//
    //variables para toBinary(int,int)
    int individuosB[32][5];
    //----------------------------------------//
    //variables para captitud()
    float suma;
    int aptitud[32];
    //----------------------------------------//
    //variables para cprobabilidad()
    float probabilidad[32];
    //----------------------------------------//
    //variables para ruleta()
    int padres[32];
    //----------------------------------------//
    //variables para cruza()
    int individuosBC[32][5];
    int individuosBD[32][5];
    //----------------------------------------//
    //variables para maxmin()
    float mayores[15];
    float menores[15];
    //----------------------------------------//
    //----------------------------------------//
    //----------------------------------------//
};
/*class familia{
    private:
        int individuosB[32][5];
        int individuosE[32];
        int aptitud[32];
        float probabilidad[32];
        int padres[32];
        float suma;
        //float promedio;
        float max;
        float mayores[10];
        float menores[10];
        int contador;
        int miembros;
        int genes;
        int generaciones;
        int individuosBC[32][5];
        int individuosBD[32][5];
        int pcruza;
        int mutar;
    public:
        familia(int,int,int,int,int);
        void llenaindividuos();
        void toBinary(int,int);
        void captitud();
        void cprobabilidad();
        void ruleta();
        void cruza();
        void mutacion();
        void maxmin();
        int toint(int);
        float cprobabilidadD(int);
        void reasignar();
        void getmaxmin();
        void TablasA(int);
        void TablasB(int);
        void TablasC(int);
        int getSuma(int*);
        int getMaxI(int*);
        int getMinI(int*);
        float getMaxF(float*);
        float getMinF(float*);
        void graficar();
};*/
#endif // MAINWINDOW_H
