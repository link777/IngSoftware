
    /*-----------------------------------------------*
     |     Ingenieria en Software:                   |
     |                                               |
     |     Integrante: Patricio Espinoza Salgado.    |
     |                 Jaime Guarda Muga.            |
     |                 Miguel Maraboli Mendez.       |
     |                 Nicolas Paez Morgado.         |
     |                                               |
     *-----------------------------------------------*/

#include <iostream>
#include <cmath>


using namespace std;


int main(int argc, char** argv)
{
int char_2_int(const char *p);
void ayuda();
void acercaDe();

    if (argc <= 1)//si no tiene parametros imprime la ayuda
    {
      ayuda();
    }
            else
                {

                int i=1;
                char simbolo = argv[1][0];
                //cout<<"\n"<<simbolo;

                // cout<<"\nACA";

                if(simbolo == '-')
                {

                     simbolo = argv[1][1];
                   // cout<<"\nACA2";
                   // cout<<"\n"<<simbolo;
                   switch(simbolo)
                    {
                            case 'i':
                                {       // cout<<"\nACA3";
                                     int id =0,nDeEleVec=0,i=0,cifra;
                                     while(argv[2][i])
                                     {
                                         nDeEleVec++;
                                         i++;
                                     }


                                        for(int j = 0; j <= nDeEleVec; j++)
                                        {
                                                simbolo = argv[2][j];
                                                cifra = char_2_int(&simbolo);
                                                id += cifra * pow(10,argc-j);
                                        }
                                        //consulta sql
                                break;
                                }


                            case 'a':
                                {
                                     cout<<"\n\t Opcion a"<<endl;//procedimiento avg y desv s en un archivo
                                break;
                                }


                            case 's':
                                {
                                     cout<<"\n\t Opcion s"<<endl;//procedimiento mustra la desv y el promedio por asignatura
                                break;
                                }


                            case 'v':
                                {
                                     acercaDe();
                                break;                                    //procedimiento acerca de
                                }

                            case 'h':
                                {
                                     ayuda();
                                break;
                                }

                            default:       //SI LA OPCION INGRESADA NO ESTA EN EL MENU, ENTRA AQUI.
                                {
                                    cout<<endl<<"\n\t        Parametro invalido, ingrese -h para ayuda.\n"<<endl;
                                break;
                                }
                    }

                }
            }

    return 0;
}


int char_2_int(const char *p)
{
    int x = 0;
    bool neg = false;

    if (*p == '-')
    {
        neg = true;
        ++p;
    }

    while (*p >= '0' && *p <= '9')
    {
        x = (x*10) + (*p - '0');
        ++p;
    }

    if (neg)
    {
        x = -x;
    }
    return x;
}

void ayuda()
{

        cout<<"\n\t\t\tLos parametros del programa son:"<<endl<<endl;
        cout<<"\t-i [id]    Estima la nota de calculo IV segun el id del estudiante,\n"
            <<"\t           el id debe ser un nuemro entero, ej -id 5432."<<endl<<endl;
        cout<<"\t-a         Estima la nota de calculo IV para todos los estudiantes,\n"
            <<"\t           creando un archivo de texto (estimaciones.csv)."<<endl<<endl;
        cout<<"\t-s         Muestra el promedio, la desviacion estandar de cada una\n"
            <<"\t           de las asignaturas (Calculo I, II, III y IV)."<<endl<<endl;
        cout<<"\t-v         Muestra la fecha y hora de compilacion, la fecha y hora\n "
            <<"\t           actual, la version del programa y el nombre de los\n"
            <<"\t           integrantes del grupo de trabajo.\n";
}

void acercaDe()
{
	cout<<"\t        Integrantes: Patricio Espinoza.\n"
        <<"\t                     Jaime Guarda Muga.\n"
        <<"\t                     Miguel Maraboli Mendez.\n"
	    <<"\t                     Nicolas Paez Morgado.\n";
}
