#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum estados {
  q0,q1,q2,q3,q4,q5,q6
};
int leerTamano(int i, char dir_entrada[])
{
    FILE *f;
    f=fopen(dir_entrada,"rt");
    char entrada;
    if(f)
    {
        fseek(f,0,SEEK_END);
        i=ftell(f)/sizeof(char);
        fseek(f,0,SEEK_SET);
    }
    else
    {
        printf("ERROR DE APERTURA DE ARCHIVO");
    }
    fclose(f);
    return i;
}
void escribirArray(char entrada[], char dir_entrada[], int i)
{
    FILE *f;
    int j=0;
    f=fopen(dir_entrada,"rt");
    char leido;
    if(f)
    {
        while(fread(&leido,sizeof(char),1,f))
        {
            entrada[j]=leido;
            j++;        
        }
    }
    else
    {
        printf("ERROR DE APERTURA DE ARCHIVO");
    }
    fclose(f);
    return;
}
int ingresarEnAutomata(int estado, char caracter)
{
    switch (estado)
    {
    case q0:
        if (caracter=='0')
        {
            estado=q1;
        }
        else if (caracter>'0' && caracter<='9')
        {
            estado=q2;
        }   
        else
        {
            estado=q6;
        }      
        break;
    case q1:
         if(caracter>='0' && caracter<'8')
        {
            estado=q5;
        }
        else if(caracter=='X'||caracter=='x')
        {
            estado=q3;
        }
        else
        {
            estado=q6;
        }
        break;
    case q2:
        if(caracter>='0'&&caracter<='9')
        {
            estado=q2;
        }
        else
        {
            estado=q6;
        }
        break;
    case q3:
    case q4:
        if((caracter>='0'&&caracter<='9')||(caracter>='a'&&caracter<='f')||(caracter>='A'&&caracter<='F'))
        {
            estado=q4;
        }
        else
        {
            estado=q6;
        }
        break;
    case q5:
        if(caracter>='0'&&caracter<='7')
        {
            estado=q5;
        }
        else
        {
            estado=q6;
        }
        break;    
    default:
        estado=q6;
        break;
    }
    return estado;
}

void escribirResultado(int estado,char palabra[],char dir_salida[])
{
    char octal[]="Octal";
    char decimal[]="Decimal";
    char hexadecimal[]="Hexadecimal";
    char no_reconocido[]="No reconocido";
    FILE* f;
    f=fopen(dir_salida,"at");
        switch(estado)
        {
            case q1:
                fprintf(f,"%s %s %s \n",palabra,"\t \t",octal);
                break;
            case q2:
                fprintf(f,"%s %s %s \n",palabra,"\t \t",decimal);
                break;
            case q4:
                fprintf(f,"%s %s %s \n",palabra,"\t \t",hexadecimal);
                break;
            case q5:
                fprintf(f,"%s %s %s \n",palabra,"\t \t",octal);
                break;
            case q6:
                fprintf(f,"%s %s %s \n",palabra,"\t \t",no_reconocido);
                break;
        }
        fclose(f);
        return;
}
int crearPalabra(int j,int k,char entrada[],char palabra[])
{
    int f=0;
    while(k<j)
    {   
        if(entrada[k]!=',')
        {
            palabra[f]=entrada[k];
                
        }         
        k++;
        f++;       
    }
    return k;
}
int main()
{
    int estado;
    char dir_entrada[]="entrada.txt";
    char dir_salida[]="salida.txt";
    char* entrada;
    char* palabra;
    int i=0,j=0,t,f;
    int k=0;
    i=leerTamano(i,dir_entrada); 
    entrada=malloc(i*sizeof(entrada)); //equivalente a entrada = new char [i]
    escribirArray(entrada,dir_entrada,i);
    while(j<i)
    {
        estado=q0;
        while (entrada[j]!=','&&j<i)
        {
            estado=ingresarEnAutomata(estado,entrada[j]);
            j++;
        }
        j++;
        t=j-k;
        palabra=malloc(t*sizeof(palabra));
        memset( palabra, 0, t*sizeof(char));
        k=crearPalabra(j,k,entrada,palabra);
        escribirResultado(estado,palabra,dir_salida);
        free(palabra);       
    }
    free(entrada); 
    printf("\n FIN");
    return 0;
}