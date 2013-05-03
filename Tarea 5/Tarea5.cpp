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
#include <string.h>
#include <ctime>
#include <fstream>
#include <string.h>
#include <libpq-fe.h>


using namespace std;


int main(int argc, char** argv)
{
void ayuda();
void acercaDe();
void conexionI(const char *sentencia);
void conexionA(const char *sentencia);
void conexionS(const char *sentencia);


    if (argc <= 1)  //si no tiene parametros imprime la ayuda
    {
      ayuda();
    }
        else
            {

                int i=1;
                char simbolo = argv[1][0];

                if(simbolo == '-')
                {

                     simbolo = argv[1][1];


                            if(simbolo=='i' && argc==3)
                                 {
                                    std::string  cadena= "SELECT * from estimados where estudiante_id= ";  //concatenar la sentencia con el ID
                                    cadena.append((&argv[2][0]));
                                    const char *sentencia= cadena.c_str();
                                    cout<<"\n\tEl ID ingresado es: "<<&argv[2][0]<<endl;
                                    conexionI(sentencia);

                                 }


                            if(simbolo=='a')
                                {
                                     const char *sentencia="SELECT * FROM estimados";
                                     cout<<"\n\t\t\tParametro -a:"<<endl;
                                     conexionA(sentencia);  //procedimiento avg y desv s en un archivo
                                }


                            if(simbolo=='s')
                                {
                                     const char *sentencia="SELECT avg(A.nota) as \"Promedio\", STDDEV(A.nota) as \"Desviacion Estandar\", C.asignatura as \"Asignatura\" FROM asignaturas_cursadas A INNER JOIN cursos C ON A.curso_id=C.curso_id group by C.asignatura";
                                     cout<<"\n\t\t\tParametro -s"<<endl;
                                     conexionS(sentencia);  //procedimiento mustra la desv y el promedio por asignatura

                                }


                            if(simbolo=='v')
                                {
                                     acercaDe();  //procedimiento acerca de
                                }

                            if(simbolo=='h')
                                {
                                     cout<<endl<<"\n\t\t\tParametro invalido\n"<<endl;
                                     ayuda();
                                }
                }
            }

    return 0;
}


void ayuda()
{

        cout<<"\n\n\t\t\tLos parametros del programa son:"<<endl<<endl;
        cout<<"\t-i [id]    Estima la nota de calculo IV segun el id del estudiante,\n"
            <<"\t           el id debe ser un nuemro entero, ej -id 5432."<<endl<<endl;
        cout<<"\t-a         Estima la nota de calculo IV para todos los estudiantes,\n"
            <<"\t           creando un archivo de texto (estimaciones.csv), ordenado\n"
            <<"\t           por ID de estudiante de manera ascendente."<<endl<<endl;
        cout<<"\t-s         Muestra el promedio y la desviacion estandar de cada una\n"
            <<"\t           de las asignaturas (Calculo I, II, III y IV)."<<endl<<endl;
        cout<<"\t-v         Muestra la fecha y hora de compilacion, la fecha y hora\n "
            <<"\t           actual, la version del programa y el nombre de los\n"
            <<"\t           integrantes del grupo de trabajo.\n\n";
}

void acercaDe()
{
        time_t tSac = time(NULL);  // instante actual

        struct tm* pt1 = localtime(&tSac);
        cout << "\n\n\t\tHora actual = " << pt1->tm_hour << ":" << pt1->tm_min << ":"
                       << pt1->tm_sec << endl;
        cout << "\t\tFecha actual= " << pt1->tm_mday << "-" << pt1->tm_mon+1 << "-"
                       << pt1->tm_year+1900 << endl;

        cout<< "\n\n\t\tHora de compilacion: " __TIME__<<endl;
        cout<< "\n\t\tFecha de compilacion: " __DATE__<<endl;
        cout<< "\n\t\tVersion de la aplicacion: v1.0"<<endl;
        cout<< "\n\t\tVersion del compilador GCC: " __VERSION__;


        cout<<"\n\n\t\tIntegrantes: Patricio Espinoza.\n"
            <<"\t                     Jaime Guarda Muga.\n"
            <<"\t                     Miguel Maraboli Mendez.\n"
            <<"\t                     Nicolas Paez Morgado.\n";

}

void conexionI(const char *sentencia)
{
    PGconn *cnn = NULL;
    PGresult *consulta = NULL;

    char *host = "sebastian.cl";
    char *port = "5432";
    char *dataBase = "iswdb";
    char *user = "isw";
    char *passwd = "isw";

    int i;

   cnn = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);

    if (PQstatus(cnn) != CONNECTION_BAD)
        {
            cout << "\n\t\t--------------------------------------" << endl;
            cout << "\t\t|  Conexion al Servidor Establecida  |" << endl;
            cout << "\t\t--------------------------------------" << endl << endl;

            consulta = PQexec(cnn, sentencia);

            if (consulta != NULL)
                {
                    int filas = PQntuples(consulta);
                    int columnas = PQnfields(consulta);
                    cout << "No. Filas:" << filas << endl;
                    cout << "No. Columnas:" << columnas << endl << endl;


                    for (i=0; i<columnas; i++)
                        {
                            cout << PQfname(consulta,i) << "    |    ";
                        }

                    cout << endl;

                // Aqui se despliegan los valores de cada fila

                for (i=0; i<filas; i++)
                    {
                        for (int j=0; j<columnas; j++)
                            {
                            cout  << PQgetvalue(consulta,i,j) << "           ";
                            }
                    cout << endl;
                    }
                }

        // Ahora nos toca liberar la memoria
        PQclear(consulta);

        }

    else
        {
            cout << "\t\t--------------------------------------" << endl;
            cout << "\t\t|          Error de Conexion         |" << endl;
            cout << "\t\t--------------------------------------" << endl << endl;
            return 0;
        }

    PQfinish(cnn);
}


void conexionA(const char *sentencia)
{
    PGconn *cnn = NULL;
    PGresult *consulta = NULL;

    char *host = "sebastian.cl";
    char *port = "5432";
    char *dataBase = "iswdb";
    char *user = "isw";
    char *passwd = "isw";

    int i;
    ofstream RegistroEstimaciones("estimaciones.csv", ios::app);

   cnn = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);

    if (PQstatus(cnn) != CONNECTION_BAD)
        {
            cout << "\n\t\t--------------------------------------" << endl;
            cout << "\t\t|    Datos guardados exitosamente    |" << endl;
            cout << "\t\t--------------------------------------" << endl << endl;

            consulta = PQexec(cnn, sentencia);

            if (consulta != NULL)
                {
                    int filas = PQntuples(consulta);
                    int columnas = PQnfields(consulta);
                    RegistroEstimaciones << "      No. Filas:" << filas << endl;
                    RegistroEstimaciones << "      No. Columnas:" << columnas << endl << endl;


                    for (i=0; i<columnas; i++)
                        {
                            RegistroEstimaciones <<"     "<<  PQfname(consulta,i) << "         ";
                        }

                    RegistroEstimaciones << endl<<endl;

                // Aqui se despliegan los valores de cada fila

                for (i=0; i<filas; i++)
                    {
                        for (int j=0; j<columnas; j++)
                            {
                            RegistroEstimaciones  <<"     "<< PQgetvalue(consulta,i,j) << "            ";
                            }
                        RegistroEstimaciones << endl;
                    }
                }
        RegistroEstimaciones  << "----------------------------------------------------------"<<endl<<endl;
        RegistroEstimaciones.close();
        // Ahora nos toca liberar la memoria
        PQclear(consulta);

        }

    else
        {
            cout << "\t\t--------------------------------------" << endl;
            cout << "\t\t|          Error de Conexion         |" << endl;
            cout << "\t\t--------------------------------------" << endl << endl;
            return 0;
        }

    PQfinish(cnn);
}



void conexionS(const char *sentencia)
{
    PGconn *cnn = NULL;
    PGresult *consulta = NULL;

    char *host = "sebastian.cl";
    char *port = "5432";
    char *dataBase = "iswdb";
    char *user = "isw";
    char *passwd = "isw";
    int i;

   cnn = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);

    if (PQstatus(cnn) != CONNECTION_BAD)
        {
            cout << "\n\t\t--------------------------------------" << endl;
            cout << "\t\t|  Conexion al Servidor Establecida  |" << endl;
            cout << "\t\t--------------------------------------" << endl << endl;

            consulta = PQexec(cnn, sentencia);

            if (consulta != NULL)
                {
                    int filas = PQntuples(consulta);
                    int columnas = PQnfields(consulta);
                    cout << "No. Filas:" << filas << endl;
                    cout << "No. Columnas:" << columnas << endl << endl;


                    for (i=0; i<columnas; i++)
                        {
                            cout << "      " <<PQfname(consulta,i) << "     ";
                        }

                    cout << endl<<endl;

                // Aqui se despliegan los valores de cada fila

                for (i=0; i<filas; i++)
                    {
                        for (int j=0; j<columnas; j++)
                            {
                            cout  << "  " <<PQgetvalue(consulta,i,j) << "   ";
                            }
                    cout << endl;
                    }
                }

        // Ahora nos toca liberar la memoria
        PQclear(consulta);

    }

    else
        {
            cout << "\t\t--------------------------------------" << endl;
            cout << "\t\t|          Error de Conexion         |" << endl;
            cout << "\t\t--------------------------------------" << endl << endl;
            return 0;
        }

    PQfinish(cnn);
}

