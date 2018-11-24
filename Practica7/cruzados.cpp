#include <iostream>
#include <stdio.h>     
#include <stdlib.h>    
#include <time.h>   
#include <math.h>

class Cruza{
private:
    int poblacion;
    int genes;
    int **individuosE;
    int **individuosB;
    int **individuosEC; 
public:
    Cruza(int, int);
    void CreaIndividuos();
    bool CheckRep(int, int , int**);
    void ImprimirRes(int **,int**);
    void LiberarMemoria();
    void OX(int);
    void PMX(int,int);
    void PbX();
    void ObX();
};
using namespace std;

Cruza::Cruza(int ipoblacion,int igenes){
    poblacion = ipoblacion;
    genes = igenes;
    individuosE = new int*[poblacion]; 
    individuosB = new int*[poblacion];
    individuosEC = new int*[poblacion];

    for(int i=0;i<poblacion;i++){
        individuosE[i] = new int[genes];
        individuosB[i] = new int[genes];
        individuosEC[i] = new int[genes];
    }
}

void Cruza::CreaIndividuos(){
    int random;
    for(int i=0;i<poblacion;i++){
        for(int j=0;j<genes;j++){
            do
                random =  rand() % genes + 1;
            while(CheckRep(random,i,individuosE));
            individuosE[i][j] = random;
            individuosEC[i][j] = 0;
        }
        
    }
}

void Cruza::OX(int TamSub){
    int subc[poblacion][TamSub],sc,banH1,banH2,paux,inicio=2;
    int padreaux[poblacion][genes-TamSub];
    bool isInH1, isInH2;

    for(int i=0;i<poblacion-1;i++){
        sc=0;
        for(int j=0;j<genes;j++){
            if(j>inicio && j<=inicio+TamSub){ 
                individuosEC[i][j]=individuosE[i][j];
                individuosEC[i+1][j]=individuosE[i+1][j];
                subc[i][sc]=individuosE[i][j];
                subc[i+1][sc++]=individuosE[i+1][j];
            }
            else{
                individuosEC[i][j]=0;
            }
        }
        i++;    
    }
    for (int i=0;i<poblacion-1;i++){
        banH1=0;
        banH2=0;
        isInH1=false;
        isInH2=false;
        for (int j=0;j<genes;j++){
            for (int k=0;k<TamSub;k++){
                if (subc[i][k]==individuosE[i+1][j])
                    isInH1=true;
                if (subc[i+1][k]==individuosE[i][j])
                    isInH2=true;
            }
            if (!isInH1)
                padreaux[i][banH1++]=individuosE[i+1][j];
           
            if (!isInH2) 
                padreaux[i+1][banH2++]=individuosE[i][j];

            isInH1=false;
            isInH2=false;      
       }
       i++;
       
    }
    for (int i=0;i<poblacion-1;i++){
        paux=0;
        for (int j=0;j<genes;j++){
            if (j<=inicio || j>inicio+TamSub){
                individuosEC[i][j]=padreaux[i][paux]; 
                individuosEC[i+1][j]=padreaux[i+1][paux++];     
            }
        }
        i++;
    } 
    ImprimirRes(individuosE,individuosEC);
}


void Cruza::PMX(int pto1,int pto2){
    pto1--;
    pto2--;
    int TamSub=pto2-pto1;
    int subc[poblacion][TamSub],sc;
    bool isInH1, isInH2;

    for(int i=0;i<poblacion-1;i++){
        sc=0;
        
        for(int j=0;j<genes;j++){
            if(j>pto1 && j<=pto2){ 
                individuosEC[i][j]=individuosE[i+1][j];
                individuosEC[i+1][j]=individuosE[i][j];
                subc[i][sc]=individuosE[i+1][j];
                subc[i+1][sc++]=individuosE[i][j];
            }
            else{
                individuosEC[i][j]=0;
            }
        }
        i++;    
    }
    
    for (int i=0;i<poblacion-1;i++){
        isInH1=false;
        isInH2=false;
        for (int j=0;j<genes;j++){
            for(int k=0;k<TamSub;k++){ 
                    if (subc[i][k]==individuosE[i][j])
                        isInH1=true;
                    if (subc[i+1][k]==individuosE[i+1][j])
                        isInH2=true;
            }
            if(j<=pto1 || j>pto2){
                if (!isInH1) 
                    individuosEC[i][j]=individuosE[i][j];
                else
                    individuosEC[i][j]=0;
                 
                if (!isInH2) 
                   individuosEC[i+1][j]=individuosE[i+1][j];
                else
                    individuosEC[i+1][j]=0;   
            }
            isInH1=false;
            isInH2=false;
        } 
        i++;
    }

    for (int i=0;i<poblacion-1;i++){
        for (int j=0;j<genes;j++){
            for(int k=0;k<TamSub;k++){
                for(int l=0;l<genes;l++){
                    
                    if(subc[i+1][k]==individuosEC[i][l]){
                        subc[i+1][k]=-1;
                    }
                    if(subc[i][k]==individuosEC[i+1][l]){
                        subc[i][k]=-1;
                    }
                }
            }
            if(j<=pto1 || j>pto2){ 
                if(individuosEC[i][j]==0){
                    for(int m=0;m<TamSub;m++){
                        if(subc[i+1][m]!=-1){
                            individuosEC[i][j]=subc[i+1][m];
                            subc[i+1][m]=-1;
                            break;
                        }
                    }
                }
                if(individuosEC[i+1][j]==0){
                    for(int m=0;m<TamSub;m++){
                        if(subc[i][m]!=-1){
                            individuosEC[i+1][j]=subc[i][m];
                            subc[i][m]=-1;
                            break;
                        }
                        
                    }
                }
            }
        } 
        i++;
    }

    ImprimirRes(individuosE,individuosEC);
}

void Cruza::PbX(){
    int indices[]={1,4,6,9},iban,banH1,banH2;
    int subc[poblacion][4],padreaux[poblacion][genes-4];
    bool isInH1,isInH2;
    for(int i=0;i<poblacion-1;i++){
        iban=0;
        banH1=0;
        banH2=0;
        isInH1=false;
        isInH2=false; 
        for(int j=0;j<genes;j++){
            if(indices[iban]==j){
                individuosEC[i][j]=individuosE[i][j];
                individuosEC[i+1][j]=individuosE[i+1][j];
                subc[i][iban]=individuosE[i][j];
                subc[i+1][iban++]=individuosE[i+1][j];
            }else{
                individuosEC[i][j]=0;
                individuosEC[i+1][j]=0;
            }
        }
        for(int j=0;j<genes;j++){
             for (int k=0;k<4;k++){
                if (subc[i][k]==individuosE[i+1][j])
                    isInH1=true;
                if (subc[i+1][k]==individuosE[i][j])
                    isInH2=true;
            }
            if (!isInH1)
                padreaux[i][banH1++]=individuosE[i+1][j];
           
            if (!isInH2) 
                padreaux[i+1][banH2++]=individuosE[i][j];

            isInH1=false;
            isInH2=false;      
            
        }

        i++;
    }
    for(int i=0;i<poblacion-1;i++){
        banH1=0;
        banH2=0;
        for(int j=0;j<genes;j++){
            if(individuosEC[i][j]==0){
                individuosEC[i][j]=padreaux[i][banH1++];
            }
            if(individuosEC[i+1][j]==0){
                individuosEC[i+1][j]=padreaux[i+1][banH2++];
            }
        }
        i++;
    }

    ImprimirRes(individuosE,individuosEC);
}

void Cruza::ObX(){
    int indices[]={1,4,6,9},iban,banH1,banH2;
    int subc[poblacion][4],padreaux[poblacion][genes-4];
    bool isInH1,isInH2;
    for(int i=0;i<poblacion-1;i++){
        iban=0;
        banH1=0;
        banH2=0;
        isInH1=false;
        isInH2=false; 
        for(int j=0;j<genes;j++){
            if(indices[iban]==j){
                subc[i][iban]=individuosE[i][j];
                subc[i+1][iban++]=individuosE[i+1][j];
            }
        }
        for(int j=0;j<genes;j++){
             for (int k=0;k<4;k++){
                if (subc[i][k]==individuosE[i+1][j])
                    isInH1=true;
                if (subc[i+1][k]==individuosE[i][j])
                    isInH2=true;
            }
            if (!isInH1){ 
                individuosEC[i][j]=individuosE[i+1][j];
            }else{
                individuosEC[i][j]=0;
            }
           
            if (!isInH2){ 

                 individuosEC[i+1][j]=individuosE[i][j];
            }else{
                individuosEC[i+1][j]=0;
            }

            isInH1=false;
            isInH2=false;      
            
        }

        i++;
    }
    

    for(int i=0;i<poblacion-1;i++){
        banH1=0;
        banH2=0;
        for(int j=0;j<genes;j++){
            if(individuosEC[i][j]==0){
                individuosEC[i][j]=subc[i][banH1++];
            }
            if(individuosEC[i+1][j]==0){
                individuosEC[i+1][j]=subc[i+1][banH2++];
            }
        }
        i++;
    }
    ImprimirRes(individuosE,individuosEC);

    
}




void Cruza::ImprimirRes(int **arr, int **arr2){
    for(int i=0;i<poblacion;i++){
        cout<<i+1<<"   |   ";
        for(int j=0;j<genes;j++)
            cout<<arr[i][j];
        cout<<"   |   ";
        for(int j=0;j<genes;j++)
            cout<<arr2[i][j];
        cout<<endl;
    }
}

void Cruza::LiberarMemoria(){
    for(int i=0;i<poblacion;i++){
        delete []individuosE[i];
        delete []individuosB[i];
        delete []individuosEC[i];
    }
    
    delete []individuosE;
    delete []individuosB;
    delete []individuosEC;
}

bool Cruza::CheckRep(int n, int fila, int **num)
{
    for(int i=0; i<genes; i++){
        if(n == num[fila][i])
                return true;
    }
    return false;
}


int main(int argc, char const *argv[])
{
    char opc = 's';
    
    int indiv, alel,opc1;
    srand(time(NULL));
    while(opc=='s'){
    
        cout<<"Metodos de cruza para permutaciones"<<endl;
        cout<<"1.- Order Crossover"<<endl<<"2.- Partially Mapped Crossover"<<endl<<"3.- Position-based Crossover"<<endl<<"4.- Order-based Crossover"<<endl<<"5.- Salir"<<endl;
        
        cout<<"Escribe el numero de individuos: ";
        cin>>indiv;
        cout<<endl<<"Escribe el numero de genes: ";
        cin>>alel;
        
        Cruza c(indiv, alel);
        c.CreaIndividuos();
        cout<<endl<<"Escribe una opcion de cruza: ";
        cin>>opc1;
		if(opc1 == 1){
			int tamsub;
            cout<<"Order Crossover"<<endl;
            cout<<"Escribe el tamanio de la subcadena: ";
            cin>>tamsub;
            cout<<endl<<"No. |   Individuos   |   Cruza "<<endl;
    		cout<<"____________________________________________"<<endl;
            c.OX(tamsub);
		}else if(opc1 == 2){
			int pto1, pto2;
            cout<<"Partially Mapped Crossover"<<endl;
            cout<<"Escribe el punto de cruza 1: ";
            cin>>pto1;
            cout<<"Escribe el punto de cruza 2: ";
            cin>>pto2;
            cout<<endl<<"No. |   Individuos   |   Cruza "<<endl;
    		cout<<"____________________________________________"<<endl;
            c.PMX(pto1,pto2);
		}else if(opc1 == 3){
			cout<<"Position-based Crossover"<<endl;
            cout<<"Los indices tomados son: 1,4,6,9"<<endl;
            cout<<endl<<"No. |   Individuos   |   Cruza "<<endl;
    		cout<<"____________________________________________"<<endl;
            c.PbX();
		}else if(opc1 == 4){
			cout<<"Order-based Crossover"<<endl;
            cout<<"Los indices tomados son: 1,4,6,9"<<endl;
            cout<<endl<<"No. |   Individuos   |   Cruza "<<endl;
    		cout<<"____________________________________________"<<endl;
            c.ObX();
		}else if(opc1 == 5){
			exit(0);
		}
        c.LiberarMemoria();
        cout<<endl<<"Deseas volver al menu?(s/n): "<<endl;
        cin>>opc;
        
        system("cls");
    }   
    cout<<endl;
   

    
    return 0;
}


