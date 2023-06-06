#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include "gsl_rng.h"
#include <iostream>
#define N 128

gsl_rng *tau;

double T=1.5;

//~~~~~~~~~~~~~~~~~~~~~~~~DEFINIMOS FUNCIONES~~~~~~~~~~~~~~~~~~~~~~~~~~



double magnetizacion(int mtrz[N][N])
{
    double mn;
    double suma;
    for (int i=0;i<N;i++)
    {
        for(int j=0; j<N;j++)
        {
            suma=suma+mtrz[i][j];
        }
       
    }
    mn=abs(suma)/(N*N);

    return mn;
}


double energia(int mtrz[N][N])
{
    double E;

    for (int i=0; i<N;i++)
    {
        for(int j=0;j<N;j++)
        {   
            int aux1=i+1;
            int aux2=i-1;
            int aux3=j+1;
            int aux4=j-1;

            if (aux1==N)
            {
                aux1=0;
            }
            if (aux2==-1)
            {
                aux2=N-1;
            }
            if (aux3==N)
            {
                aux3=0;
            }
            if (aux4==-1)
            {
                aux4=N-1;
            }

            E=E+(-0.5)*mtrz[i][j]*(mtrz[i][aux3]+mtrz[i][aux4]+mtrz[aux1][j]+mtrz[aux2][j]);   
        }
    } 
    return E;
}

double corr(int mtrz[N][N],int g)
{
    double snm=0.0;
    for (int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(i<N-g)
            {
                snm=snm+(mtrz[i][j]*mtrz[i+g][j]);
            }
            else
            {
                snm=snm+(mtrz[i][j]*mtrz[i+g-N][j]);
            }
        }

    }
    return snm/(N*N);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


int main()
{  
    //FILE* fichero= fopen("ising_data.dat","a");
    FILE* magnitudes= fopen("magnitudes.dat","a");
    
for (int k=0;k<10;k++){
    int w=0;
    int matriz[N][N];
    double mg=0;   //variable donde se va a sumar la magnetizacion para cada 100 pmc
    long double E=0;
    long double E2=0;
    long double sumE=0;
    double snm=0;
    double magne[10000];
    double ener[10000];
    double ener2[10000];
    double corre[10000];
    
    extern gsl_rng *tau; //Puntero al estado del número aleatorio
    int semilla=177013; //Semilla del generador de números aleatorios

    int d=0;

    tau=gsl_rng_alloc(gsl_rng_taus); //Inicializamos el puntero
    gsl_rng_set(tau,semilla); //Inicializamos la semilla


    //generamos matriz N*N toda de 1s
    for (int i=0;i<N;i++)       
    {
        for(int j=0;j<N;j++)
        {
            matriz[i][j]=1;
        }
    }


    //evolucion de la matriz
    double a;
    for (a=0; a< (double) 1000000*(N*N);a++)
    {
        int n=gsl_rng_uniform_int(tau,N);
        int m=gsl_rng_uniform_int(tau,N);

        int aux1=n+1;
        int aux2=n-1;
        int aux3=m+1;
        int aux4=m-1;

        if (aux1==N)
        {
            aux1=0;
        }
        if (aux2==-1)
        {
            aux2=N-1;
        }
        if (aux3==N)
        {
            aux3=0;
        }
        if (aux4==-1)
        {
            aux4=N-1;
        }

        double de=2*matriz[n][m]*(matriz[aux1][m]+matriz[aux2][m]+matriz[n][aux3]+matriz[n][aux4]);
        double p;

        if(1<exp(-de/T))
        {
            p=1;
        }
         if(1>exp(-de/T))
        {
            p=exp(-de/T);
        }

        double x=gsl_rng_uniform(tau);

        if(x<p)
        {
            matriz[n][m]=-1*matriz[n][m];
        }


        //calculo de magnitudes:
        if(d==100*pow(N,2))
        {   
            
            mg=magnetizacion(matriz)+mg;
            
            
            magne[w]=magnetizacion(matriz);

            E=energia(matriz);
            
            ener[w]=E;
            sumE=sumE+E;

            E2=E*E+E2;
            
            ener2[w]=E*E;
            
            int g=1;
            snm=corr(matriz,g)+snm;
            
            corre[w]=corr(matriz,g);

            w=w+1;
            d=0;
            
        }
        else
        {
            d=d+1;
        }


    }

    double promediomg=mg/10000;

    double promedioE=sumE/10000;
    
    double promedioE2=E2/10000;

    double promedioen=promedioE/(2*N);
    
    double promediocn=(promedioE2-(promedioE*promedioE))/(N*N*T);
    
    double promediosnm=snm/10000;

    double promediof=promediosnm;
    
    double incermg;
    double incerE;
    double incerE2;
    double inceren;
    double incercn;
    double incerf;
    for (int i=0;i<10000;i++)
    {
        incermg=(magne[i]-promediomg)*(magne[i]-promediomg)+incermg;
        incerE=(ener[i]-promedioE)*(ener[i]-promedioE)+incerE;
        incerE2=(ener2[i]-promedioE2)*(ener2[i]-promedioE2)+incerE2;
        incerf=(corre[i]-promediosnm)*(corre[i]-promediosnm)+incerf;
        incercn=incercn+((ener2[i]-ener[i]*ener[i])/(N*N*T)-(promedioE2-(promedioE*promedioE))/(N*N*T))*((ener2[i]-ener[i]*ener[i])/(N*N*T)-(promedioE2-(promedioE*promedioE))/(N*N*T));
    }

    incermg=incermg/10000;
    incerE=incerE/10000;
    incerE2=incerE2/10000;
    incerf=incerf/10000;

    inceren=incerE/(2*N);
    incercn=incercn/10000;
    



    fprintf(magnitudes,"T: %f \n",T);
    fprintf(magnitudes,"Magnetización promedio: %f// %f \n Energia: %f// %f \n Energia^2: %f// %f \n  Energía media: %f// %f \n Calor específico: %f// %f \n Función de correlación: %f// %f \n",promediomg,incermg,promedioE,incerE,promedioE2,incerE2,promedioen,inceren,promediocn,incercn,promediof,incerf);

T=T+0.2;
}
    //fclose(fichero);
    fclose(magnitudes);
    return 0;
}


