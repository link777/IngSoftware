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
int char_2_int(const char *p);
void ayuda();
void acercaDe();
void conexionI(string ID);
void conexionA(const char *sentencia);
void conexionS(const char *sentencia);


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

                            if(simbolo=='i' && argc==3)
                                 {       // cout<<"\nACA3";
                                        int ID =0,nDeEleVec=0,i=0,cifra;
                                        nDeEleVec = strlen((&argv[2][0]));// obtiene el largo del strig id

                                            for(int j = 0; j < nDeEleVec; j++)// convierte el string a entero
                                                {
                                                        simbolo = argv[2][j];
                                                        cifra = char_2_int(&simbolo);
                                                        //cout<<endl<<nDeEleVec-j-1<<" numero"<<cifra;
                                                        ID += cifra * pow(10,nDeEleVec-j-1);
                                                 }
                                                      cout<<"\nEl ID ingresado es: "<<&argv[2][0];
                                            conexionI(&argv[2][0]);

                                }


                            if(simbolo=='a')
                                {
                                     const char *sentencia="SELECT semestre,seccion from cursos";
                                     cout<<"\n\t\t\tParametro -a:"<<endl;
                                     conexionA(sentencia);//procedimiento avg y desv s en un archivo
                                }


                            if(simbolo=='s')
                                {
                                     const char *sentencia="SELECT avg(A.nota) as \"Promedio\", STDDEV(A.nota) as \"Desviacion Estandar\", C.asignatura as \"Asignatura\" FROM asignaturas_cursadas A INNER JOIN cursos C ON A.curso_id=C.curso_id group by C.asignatura";
                                     cout<<"\n\t\t\tParametro -s"<<endl;//procedimiento mustra la desv y el promedio por asignatura
                                     conexionS(sentencia);
                                }


                            if(simbolo=='v')
                                {
                                     acercaDe();                                  //procedimiento acerca de
                                }


                            else       //SI LA OPCION INGRESADA NO ESTA EN EL MENU, ENTRA AQUI.
                                {
                                    cout<<endl<<"\n\t\t\tParametro invalido\n"<<endl;
                                    ayuda();
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
        cout<< "\n\t\tVersion de la aplicacion: BETA"<<endl;
        cout<< "\n\t\tVersion del compilador GCC: " __VERSION__;


        cout<<"\n\n\t\tIntegrantes: Patricio Espinoza.\n"
            <<"\t                     Jaime Guarda Muga.\n"
            <<"\t                     Miguel Maraboli Mendez.\n"
            <<"\t                     Nicolas Paez Morgado.\n";

}

void conexionI(string ID)
{
    PGconn *cnn = NULL;
    PGresult *consulta = NULL;

    char *host = "sebastian.cl";
    char *port = "5432";
    char *dataBase = "iswdb";
    char *user = "isw";
    char *passwd = "isw";

    std::string  cadena= "SELECT (A.nota) as \"Nota Real\" FROM asignaturas_cursadas A INNER JOIN cursos C ON A.curso_id=C.curso_id where A.estudiante_id=";
    cadena.append(ID);
    cadena.append("ctm");

    const char *sentencia= cadena.c_str();

    cout<<sentencia<<endl;

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

                // Aqui se despliegan los nombres de las columnas

                    cout << "Los nombres de las columnas son:" << endl << endl;

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

                // Aqui se despliegan los nombres de las columnas

                   RegistroEstimaciones << "     Los nombres de las columnas son:" << endl << endl;

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

                // Aqui se despliegan los nombres de las columnas

                    cout << "Los nombres de las columnas son:" << endl << endl;

                    for (i=0; i<columnas; i++)
                        {
                            cout << PQfname(consulta,i) << "              ";
                        }

                    cout << endl<<endl;

                // Aqui se despliegan los valores de cada fila

                for (i=0; i<filas; i++)
                    {
                        for (int j=0; j<columnas; j++)
                            {
                            cout  << PQgetvalue(consulta,i,j) << "     ";
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

