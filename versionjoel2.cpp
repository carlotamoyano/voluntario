#include <stdio.h>
#include <cmath>
#include <time.h>
# include "gsl_rng.h" //Libreria para generación de números aleatorios

#define N 128

gsl_rng *tau;

double Magnetización(int matriz[N][N]){
    double suma=0.0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            suma=suma+matriz[i][j];
        }
        
    }
    return suma/(N*N);
}


double Energia(int matriz[N][N])
{
    double E;
    E=0;
    int aux1, aux2, aux3, aux4;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            aux1=j+1;
            aux2=j-1;
            aux3=i+1;
            aux4=i-1;
            if (j==N-1)
            {
                aux1=0;
            }
            if (i==N-1)
            {
                aux3=0;
            }
            if (i==0)
            {
                aux4=N-1;
            }
            if (j==0)
            {
                aux2=N-1;
            }
            
            E = E + matriz[i][j] * (matriz[i][aux1] + matriz[i][aux2] + matriz[aux3][j] + matriz[aux4][j]);



        }
        
    }
    return -0.5*E;
}

double correlacion(int matriz[N][N], int a){
    double suma=0.0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
             if(i<N-a)
             {
                suma=suma+matriz[i][j]*matriz[i+a][j];
             }
            else
            {
                suma=suma+matriz[i][j]*matriz[i+a-N][j];
            }
            
        }
        
    }
    return suma/(N*N);   
}


int main(){
    
    double T;
    double rep=(double)N*N*1000000;
    T=1.5;
    int matriz[N][N];
    int random;
    long h;
    int f, c, media, aux1,aux2,aux3,aux4;
    double VEnergia, sumaE, E2,Cn, correl, difE, E;
    double exponencial, p, epsilon;
    double mn=0.0;
    double snm=0.0;
    double smn;
    double sE;
    double sE2;
    double scn;
    double scorrel;
    double w, sen;
    double mag[10000];
    double ener[10000];
    double ener2[10000];
    double fi[10000];
     
    extern gsl_rng *tau; //Puntero al estado del número aleatorio
    int semilla=135254; //Semilla del generador de números aleatorios
    
    
    tau=gsl_rng_alloc(gsl_rng_taus); //Inicializamos el puntero
    gsl_rng_set(tau,semilla); //Inicializamos la semilla

    sumaE=0.0;
    E=0.0;
    h=0;
    E2=0.0;
    media=0.0;
    correl=0.0;
    int a=5;
    //escribir la matriz
    //diferencia de energia
    for (int z = 0; z < 11; z++)
    {
        
    
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j< N; j++)
        {
            matriz[i][j]=1;
            
            
        }
        //
    }

printf("%lf\t", Energia(matriz));

FILE* Magnet;
FILE* es;
FILE* Capcal;
FILE* Correlac;




//empezamos el bucle paso montecarlo
    for (double k = 0; k < rep ; k++)
    {
    f=gsl_rng_uniform_int(tau,N); //posicion aleatoria de la matriz
    c=gsl_rng_uniform_int(tau,N);
    // printf("%d\t,%d\t", f,c);
    //calculamos la energia 

   aux1=f+1;
   aux2=f-1;
   aux3=c+1;
   aux4=c-1;
   if (f==N-1)
   {
        aux1=0;
   }
    if (f==0)
    {
        aux2=N-1;
    }
    if (c==N-1)
    {
        aux3=0;
    }
    if (c==0)
    {
        aux4=N-1;
    }
    
    VEnergia=2.0 * matriz[f][c] * (matriz[aux1][c]+matriz[aux2][c]+matriz[f][aux3]+matriz[f][aux4]);




    //printf("%lf\t", Energia);

    exponencial=exp(-VEnergia*1.0/T);

    //tenemos el minimo entre 1 y exponencial

   p=1.0;
   if (exponencial <1)
   {
        p=exponencial;
   }
   //printf("%lf\n", p);
   epsilon=gsl_rng_uniform(tau);
   //printf("%lf\n", epsilon);

   //si es menor lo cambiamos
   if (epsilon<p)
   {
    matriz[f][c]=-1*matriz[f][c];
   }
   
   //hace lo que debas
    
    if (h==100*N*N)
    {
        
        mn=mn+Magnetización(matriz); 
        E=Energia(matriz);
        sumaE=sumaE+E;
        E2=E2+E*E;
        correl=correl+correlacion(matriz, a);
        media=media+1;
       
        mag[w]=Magnetización(matriz);
        ener[w]=Energia(matriz);
        fi[w]=correlacion(matriz,a);
        ener2[w]=Magnetización(matriz)*Magnetización(matriz);
        snm=correlacion(matriz,a)+snm; 
        w=w+1;
        h=0;
    }
     else
    {
        h=h+1;
    }

}
mn=mn/media;



//printf("Mag=%lf\t", magn);


sumaE=sumaE/media;
//printf("E=%lf\t", sumaE/(2*N));


E2=E2/media;
//printf("Ec=%lf\t", E2);

difE=E2-pow(sumaE,2);

Cn=difE/(N*N*T);
//printf("Cn=%lf\t", Cn);

double mediasnm=snm/10000;
correl=correl/(media);
//printf("F=%lf\t", correl);

FILE* archivo = fopen("datosvoluntario.txt", "a");
fprintf(archivo, "T=%lf,",T );
fprintf(archivo, "N=%d,",N );
fprintf(archivo,"mN= %lf,", mn);
fprintf(archivo, "en= %lf," ,sumaE/(2*N));
fprintf(archivo,"cn=%lf,",Cn);
fprintf(archivo, "correl=%lf\n", correl);


    for (int i=0;i<pow(10,4);i++)
    {
        smn=(mag[i]-mn)*(mag[i]-mn)+smn;
        sE=(ener[i]-sumaE)*(ener[i]-sumaE)+sE;
        sE2=(ener2[i]-E2)*(ener2[i]-E2)+sE2;
        scorrel=(fi[i]-mediasnm)*(f[i]-mediasnm)+scorrel;
        scn=scn+((ener2[i]-ener[i]*ener[i])/(N*N*T)-(E2-(sumaE*sumaE))/(N*N*T))*((ener2[i]-ener[i]*ener[i])/(N*N*T)-(E2-(sumaE*sumaE))/(N*N*T));
    }

    smn=smn/10000;
    sE=sE/10000;
    sE2=sE2/10000;
    scorrel=scorrel/10000;

    sen=sE/(2*N);
    scn=scn/10000;
fprintf(archivo, "smn= %lf,", smn);
fprintf(archivo, "sen= %lf,", sen);
fprintf(archivo, "scn= %lf,", scn);
fprintf(archivo, "scorrel= %lf,", scorrel);


fclose(archivo); 

T=T+0.2;
    }

    return 0;
}