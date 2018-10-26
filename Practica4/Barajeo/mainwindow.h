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
        void TablasA1(int);
        void barajeo();
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
        float getMaxI(float*);
        float getMinI(float*);
        float getMaxF(float*);
        float getMinF(float*);
        //----------------------------------------//
        //funcion a llamar en tablasB
        int toint(int);
        float getSuma(float*);
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
        bool flip(float p);
        ~MainWindow();

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
        float aptitud[32];
        //----------------------------------------//
        //variables para cprobabilidad()
        float probabilidad[32];
        //----------------------------------------//
        //variables para barajeo()
        int padres[32];
        int barajeo1[32];
        int barajeo2[32];
        //----------------------------------------//
        //variables para cruza()
        int individuosBC[32][5];
        int individuosBD[32][5];
        //----------------------------------------//
        //variables para maxmin()
        float mayores[200];
        float menores[200];
        //----------------------------------------//
        //----------------------------------------//
        //----------------------------------------//
};

#endif // MAINWINDOW_H
