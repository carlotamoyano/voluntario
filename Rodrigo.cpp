#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include "gsl_rng.h"
#include <iostream>
#define N 16 

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

            E=E+(-1/2)*mtrz[i][j]*(mtrz[i][aux3]+mtrz[i][aux4]+mtrz[aux1][j]+mtrz[aux2][j]);   
        }
    } 
    return E;
}

double corr(int mtrz[N][N],int g)
{
    double snm;
    for (int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(i<N-g)
            {
                snm=snm+mtrz[i][j]*mtrz[i+g][j];
            }
            else
            {
                snm=snm+mtrz[i][j]*mtrz[i+g-N][j];
            }
        }

    }
    return snm/(N*N);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


int main()
{  
    FILE* fichero= fopen("ising_data.dat","a");
    FILE* magnitudes= fopen("magnitudes.dat","a");
for (int k=0;k<10;k++){
    int matriz[N][N];
    double mg;   //variable donde se va a sumar la magnetizacion para cada 100 pmc
    double E;
    double E2;
    double snm;
    //double snmt;
    //double snmn;
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
    for (int a=0; a<1000000*N*N;a++)
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
            matriz[n][m]=-matriz[n][m];
        }


        //calculo de magnitudes:
        if(d==100*pow(N,2))
        {
            mg=magnetizacion(matriz)+mg;

            E=energia(matriz)+E;
            E2=energia(matriz)*energia(matriz)+E2;
            
            int g=1;
            snm=corr(matriz,g)+snm;
            //snmt=corr(matriz,T)+snmt;
            //snmn=corr(matriz,N)+snmn;

            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    if (j<N-1)
                    {
                        //fichero << matriz[i][j]<<", ";
                        fprintf(fichero,"%d," , matriz[i][j]);
                    }

                    else
                    {
                        //fichero<<matriz[i][j+1]<<endl;
                        fprintf(fichero,"%d \n" , matriz[i][j]);
                    }    
            
                }
                
            }
            fprintf(fichero,"\n");

            d=0;
        }
        else
        {
            d=d+1;
        }


    }

    double promediomg=mg/10000;

    double promedioE=E/10000;
    double promedioE2=E2/10000;

    double promedioen=promedioE/(2*N);
    double promediocn=(1/(N*N*T))*(promedioE2-promedioE*promedioE);
    
    double promediosnm=snm/10000;
    //double promediosnmt=snmt/10000;
    //double promediosnmn=snmn/10000;

    double promediof=(1/(N*N))*promediosnm;
    //double promedioft=(1/(N*N))*promediosnmt;
    //double promediofn=(1/(N*N))*promediosnmn;
    fprintf(magnitudes,"T: %f \n",T);
    fprintf(magnitudes,"Magnetización promedio: %f \n Energía media: %f \n Calor específico: %f \n Función de correlación: %f \n",promediomg,promedioen,promediocn,promediof);

T=T+0.2;
}
    fclose(fichero);
    fclose(magnitudes);
    return 0;
}


