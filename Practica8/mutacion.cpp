#include <iostream>
#include <stdio.h>     
#include <stdlib.h>    
#include <time.h>   
#include <math.h>
#include <algorithm>

class Mutacion{
private:
    int poblacion;
    int genes;
    int **individuosE;
    int **individuosEM; 
public:
    Mutacion(int, int);
    void CreaIndividuos();
    bool CheckRep(int, int , int**);
    bool CheckRepCA(int,int*,int*,int,int);
    void ImprimirRes(int **,int**);
    void LiberarMemoria();
    void Desplazamiento(int);
    void IntercambioRec();
    void Heuristica(int);
};
using namespace std;

Mutacion::Mutacion(int ipoblacion,int igenes){
    poblacion = ipoblacion;
    genes = igenes;
    individuosE = new int*[poblacion]; 
    individuosEM = new int*[poblacion];

    for(int i=0;i<poblacion;i++){
        individuosE[i] = new int[genes];
        individuosEM[i] = new int[genes];
    }
}

void Mutacion::CreaIndividuos(){
    int random;
    for(int i=0;i<poblacion;i++){
        for(int j=0;j<genes;j++){
            do
                random =  rand() % genes + 1;
            while(CheckRep(random,i,individuosE));
            individuosE[i][j] = random;
            individuosEM[i][j] = 0;
        }
    }
}

void Mutacion::Desplazamiento(int valores_mov){
    int aux[poblacion][genes-valores_mov], mt,ax,mutado[poblacion][valores_mov],pos[valores_mov],posmov[valores_mov];
    bool isInPos,isInPosmov;
    int posrand;
    for(int i=0;i<valores_mov;i++){
        do
            posrand =  rand() % genes + 1;
        while(CheckRepCA(posrand,pos,posmov,valores_mov,valores_mov));

        pos[i]=posrand;    
        
    }

    for(int i=0;i<valores_mov;i++){
        do
            posrand =  rand() % genes + 1;
        while(CheckRepCA(posrand,pos,posmov,valores_mov,valores_mov));

        posmov[i]=posrand;    
        
    }

    for(int i=0;i<valores_mov;i++){
        cout<<"Posicion inicial: "<<pos[i]<<" Posicion a moverse: "<<posmov[i]<<endl;
    }

    for (int i=0;i<poblacion;i++){
        ax=0;
        mt=0;
        isInPos=false;
        for (int j=0;j<genes;j++){
            for(int k=0;k<valores_mov;k++){
                if(j==pos[k]-1)
                    isInPos=true;
                   
            }

            if(!isInPos) //Copiamos la cadena sin los valores que se van a desplazar
                aux[i][ax++]=individuosE[i][j];
            //if (j!=pos-1)
              //  aux[i][ax++]=individuosE[i][j];
            else{ //Se copian los valores mutados
                mutado[i][mt]=individuosE[i][pos[mt]-1];
                mt++;
            }
            isInPos=false;
        }
        
        ax=0;
        mt=0;
        isInPosmov=false;
        for (int j=0;j <genes;j++){
        
            for(int k=0;k<valores_mov;k++){
                if(j==posmov[k]-1)
                    isInPosmov=true;
                   
            }
            if (!isInPosmov)
               individuosEM[i][j]=aux[i][ax++];
            else{
                individuosEM[i][posmov[mt]-1]=mutado[i][mt];
                mt++;
            }
            
            isInPosmov=false;  
        }
      
    }
    cout<<endl<<"No. |   Individuos   |   Mutacion "<<endl;
    cout<<"____________________________________________"<<endl;
    ImprimirRes(individuosE,individuosEM);
}
void Mutacion::IntercambioRec(){
    int pos1,pos2,aux;
    pos1=rand()% genes +1;
    do
        aux=rand ()%genes+1;
    while(pos1==aux);
    pos2=aux;  
    cout<<"Las posiciones de los valores cambiados son "<<pos1<<" por "<<pos2<<endl;
    for (int i=0;i<poblacion;i++){
        for (int j=0;j <genes;j++){ 
            if (j==pos1-1)
                individuosEM[i][pos2-1]=individuosE[i][pos1-1];
            else{ 
                if (j==pos2-1)
                    individuosEM[i][pos1-1]=individuosE[i][pos2-1];
                else
                individuosEM[i][j]=individuosE[i][j];
            }
        }
    }
    cout<<endl<<"No. |   Individuos   |   Mutacion "<<endl;
    cout<<"____________________________________________"<<endl;
    ImprimirRes(individuosE,individuosEM);
}

void Mutacion::Heuristica(int num_genes){
    int pos[num_genes],posrand,aux[poblacion][genes-num_genes],mutado[poblacion][num_genes],ax,mt;
    bool isInPos=false,isInPosmov=false;
    for(int i=0;i<num_genes;i++){
        do
            posrand =  rand() % genes + 1;
        while(CheckRepCA(posrand,pos,pos,num_genes,num_genes));
        pos[i]=posrand;    
    }

    for (int i=0;i<poblacion;i++){
        ax=0;
        mt=0;
        isInPos=false;
        for (int j=0;j<genes;j++){
            for(int k=0;k<num_genes;k++){
                if(j==pos[k]-1)
                    isInPos=true;
                   
            }
            if(!isInPos) 
                aux[i][ax++]=individuosE[i][j];
            else{ 
                mutado[i][mt]=individuosE[i][pos[mt]-1];
                mt++;
            }
            isInPos=false;
        }
        
    }
    cout<<"_________________________________"<<endl;
 
    for(int i=0;i<poblacion;i++){
    	cout<<"Permutaciones del individuo: "<<i+1<<endl;
    	cout<<"P= ";
    	for(int j=0;j<genes;j++)
    		cout<<individuosE[i][j];
    	cout<<endl;
		sort(mutado[i], mutado[i] + num_genes);
    	do{
        	
            for(int k=0;k<num_genes;k++){
                cout<<mutado[i][k]<< " ";
            }
            cout<<endl;
        
    	}while(next_permutation( mutado[i], mutado[i] + num_genes));


        
        isInPosmov=false;
        int prm=1;
        cout<<endl<<"Individuos generados"<<endl;
        do{
            ax=0;
            mt=0;
            isInPosmov=false;
            cout<<"P"<<prm++<<"=";
            for (int l=0;l<genes;l++){            
                for(int m=0;m<num_genes;m++){
                    if(l==pos[m]-1)
                        isInPosmov=true;    
                }
                if (!isInPosmov)
                    cout<<aux[i][ax++];
                else{
                    cout<<mutado[i][mt++];
                }
                    
                isInPosmov=false;  
            }            
            cout<<endl;
        
        }while(next_permutation( mutado[i], mutado[i] + num_genes));
		cout<<"_________________________________"<<endl;
	}
}


void Mutacion::ImprimirRes(int **arr, int **arr2){
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

void Mutacion::LiberarMemoria(){
    for(int i=0;i<poblacion;i++){
        delete []individuosE[i];
        delete []individuosEM[i];
    }
    delete []individuosE;
    delete []individuosEM;
}

bool Mutacion::CheckRep(int n, int fila, int **num)
{
    for(int i=0; i<genes; i++){
        if(n == num[fila][i])
                return true;
    }
    return false;
}

bool Mutacion::CheckRepCA(int n, int num1[], int num2[],int indice1,int indice2){
    bool aux=false;
    for(int i=0; i<indice1; i++)
        if(n == num1[i])
            aux=true;
    for(int i=0; i<indice2; i++)
        if(n == num2[i])
            aux=true;
    return aux;
}

int main(int argc, char const *argv[])
{
    char opc = 's';
    
    int indiv=0, alel=0,opc1=0;
    srand(time(NULL));
	
    while(opc=='s'){
    
        cout<<"Metodos de mutacion por permutaciones"<<endl;
        cout<<"1.- Mutacion por insercion"<<endl<<"2.- Mutacion por desplazamiento"<<endl<<"3.- Mutacion por intercambio reciproco"<<endl<<"4.- Mutacion Heuristico"<<endl<<"5.- Salir"<<endl;
        
        cout<<"Escribe el numero de individuos: ";
        cin>>indiv;
        cout<<endl<<"Escribe el numero de genes: ";
        cin>>alel;
        
        Mutacion m(indiv, alel);
        m.CreaIndividuos();
        cout<<endl<<"Escribe una opcion de mutacion: ";
        cin>>opc1;
		if(opc1 == 1){
            cout<<"Mutacion por insercion"<<endl;
            m.Desplazamiento(1);
		}else if(opc1 == 2){
			cout<<"Mutacion por desplazamiento"<<endl;
            int dpz;
            dpz =  rand() % (alel-5) + 2;
            cout<<"Se hicieron "<<dpz<<" desplazamientos"<<endl;
            m.Desplazamiento(dpz);
		}else if(opc1 == 3){
			cout<<"Mutacion por intercambio reciproco"<<endl;
            m.IntercambioRec();
		}else if(opc1 == 4){
			cout<<"Mutacion Heuristica"<<endl;
            int num_genes;
            cout<<"Escribe el numero de genes: ";
            cin>>num_genes;
			m.Heuristica(num_genes);
		}else if(opc1 == 5){
			exit(0);
		}
		
        m.LiberarMemoria();
        cout<<endl<<"Deseas volver al menu?(s/n): "<<endl;
        cin>>opc;
        
        system("cls");
    }  
	
    cout<<endl;
   

    
    return 0;
}


