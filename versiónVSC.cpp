#include <stdio.h>
#include <cmath>
#include <time.h>
#define N 32

//N=16,32,64,128.

double Magnetizacion(int matriz[N][N]){
    double suma=0.0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            suma=suma+matriz[i][j];
      
        }
        
    }
    //valor absoluto
    if (suma<0){
      suma=-suma;
    }
    else{
      suma=suma;
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
                suma=suma+(matriz[i][j]*matriz[i+a][j]);
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
int a;
a=1;
double f1;
srand(time(NULL));
int f=0;
int r=0;
double T;
T=1.5;
//T=1.5; debemos probar con 10 T distintas entre 1.5 y 3.5.
 //N=16,32,64,128.
for (int ll = 0; ll < 11; ll++) {

int nrandom;
int matriz[N][N];
for(int i=0; i<N; i++) {
      for(int j=0; j<N; j++) {
         nrandom = rand() % 2; // generar número aleatorio entre 0 y 1
         if (nrandom==0)
         {
            nrandom=-1;
         }
      //matriz[i][j] = nrandom;
      matriz[i][j]=1;
         //printf("%d\t",matriz[i][j]);
      }
        printf("\n"); 
   }
double mn = 0;
double sumE;
double E;
double E2;
int d=0;
int media, aux1,aux2,aux3,aux4;
double p;
double varE;
printf("%lf\t", correlacion(matriz,2));

while(r< (double) pow(10,6)*N*N){//10^6 pasos de Montecarlo


int f = rand() % N; // Generar un núm aleatorio entre 0 y N-1 para la fila de la matriz
int c = rand() % N; // Generar un núm aleatorio entre 0 y N-1 para la columna de la matriz
int elemento = matriz[f][c]; // Obtener el elemento aleatorio de la matriz 

if (f==N-1 and c!=N-1 and c!=0){
   varE=2* matriz[f][c]*(matriz[0][c]+matriz[f-1][c]+matriz[f][c+1]+matriz[f][c-1]); //definimos la variación de energía 
}
if(f==N-1 and c==0){
   varE=2* matriz[f][c]*(matriz[0][c]+matriz[f-1][c]+matriz[f][c+1]+matriz[f][N-1]);}

if(c==N-1 and f!=N-1 and f!=0){
   varE=2* matriz[f][c]*(matriz[f+1][c]+matriz[f-1][c]+matriz[f][0]+matriz[f][c-1]);  
}
if(c==N-1 and f==0){
   varE=2* matriz[f][c]*(matriz[f+1][c]+matriz[N-1][c]+matriz[f][0]+matriz[f][c-1]);
}

if(c==N-1 and f==N-1){
   varE=2* matriz[f][c]*(matriz[0][c]+matriz[f-1][c]+matriz[f][0]+matriz[f][c-1]);
}
if(c!=N-1 and f!=N-1 and f!=0 and c!=0){
   varE=2* matriz[f][c]*(matriz[f+1][c]+matriz[f-1][c]+matriz[f][c+1]+matriz[f][c-1]);
}
if(f==0 and c==0){
   varE=2* matriz[f][c]*(matriz[f+1][c]+matriz[N-1][c]+matriz[f][c+1]+matriz[f][N-1]);
}
if(c!=N-1 and f==0 and c!=0){
   varE=2* matriz[f][c]*(matriz[f+1][c]+matriz[N-1][c]+matriz[f][c+1]+matriz[f][c-1]);
}
if(f!=N-1 and f!=0 and c==0){
   varE=2.0* matriz[f][c]*(matriz[f+1][c]+matriz[f-1][c]+matriz[f][c+1]+matriz[f][N-1]);
}
//printf("%d\t",varE);
if (1<exp(-varE*1.0/T)){
   p=1.0;
} 
   else{
      p=exp(-varE*1.0/T);
   }

double epsilon = (double) rand() / RAND_MAX;
if (epsilon<p){
   matriz[f][c]=-matriz[f][c];
}
//printf("%d\t",p);
//printf("%d\t", epsilon);


if (d==100*N*N){
    
   mn=mn+Magnetizacion(matriz); 
   E=Energia(matriz);
   sumE=sumE+E;
   E2=E2+pow(E,2);
   f1=f1+ correlacion(matriz,a);
   media=media+1;
   d=0;
}
else {
   d=d+1;
   }
r=r+1;
}

//magnetización promedio

double mNp;
mNp=mn/pow(10,4   );
double en;
en=(sumE/pow(10,4))/(2*N);
double cn;
cn=(1/(pow(N,2)*T))*(E2/pow(10,4)-pow(E/pow(10,4),2));
double fz;
fz=(1/pow(N,2))*f1/pow(10,4);

FILE* archivo = fopen("datosvoluntario.txt", "a");
fprintf(archivo, "T=%lf,",T );
fprintf(archivo, "N=%d,",N );
fprintf(archivo,"mN= %lf,", mNp);
fprintf(archivo, "en= %lf," ,en);
fprintf(archivo,"cn=%lf,",cn);
fprintf(archivo, "fz=%lf\n", fz);
fclose(archivo); 

printf("en= %lf\t",en);
printf("cn= %lf\t",cn);
printf("mN= %lf\t",mNp);
printf("fz= %lf\t",fz);
printf("media= %d\t",media); 
T += 0.2;
}
    return 0;
    
}