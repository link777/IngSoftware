
    /*-----------------------------------------------*
     |     Ingenieria en Software:                   |
     |                                               |
     |     Integrante: Patricio Espinoza Salgado     |
     |                                               |
     *-----------------------------------------------*/

#include <iostream>
#include <libpq-fe.h>

using namespace std;

PGconn *cnn = NULL;
PGresult *result = NULL;

char *host = "sebastian.cl";
char *port = "5432";
char *dataBase = "iswdb";
char *user = "isw";
char *passwd = "isw";

int main(int argc, char * argv[])
{
    int i;

   cnn = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);

    if (PQstatus(cnn) != CONNECTION_BAD) {
        cout << "\t\t--------------------------------------" << endl;
        cout << "\t\t|  Conexion al Servidor Establecida  |" << endl;
        cout << "\t\t--------------------------------------" << endl << endl;

        result = PQexec(cnn, "SELECT C.docente_id as \"ID Profesor\", AVG(A.nota) as \"Promedio Notas\", STDDEV(A.nota) as \"Desviacion Estandar\" FROM cursos C INNER JOIN asignaturas_cursadas A ON A.curso_id = C.curso_id GROUP BY C.docente_id");

        if (result != NULL) {
            int filas = PQntuples(result);
            int columnas = PQnfields(result);
            cout << "No. Filas:" << filas << endl;
            cout << "No. Columnas:" << columnas << endl << endl;

        // Aqui se despliegan los nombres de las columnas

            cout << "Los nombres de las columnas son:" << endl << endl;

            for (i=0; i<columnas; i++) {
                cout << PQfname(result,i) << "    |    ";
            }

            cout << endl;

        // Aqui se despliegan los valores de cada fila

            for (i=0; i<filas; i++) {
                for (int j=0; j<columnas; j++) {
                    cout  << PQgetvalue(result,i,j) << "           ";
                }
                cout << endl;
            }
        }

        // Ahora nos toca liberar la memoria
        PQclear(result);

    } else {
        cout << "Error de conexion" << endl;
        return 0;
    }

    PQfinish(cnn);

    return 0;
}
