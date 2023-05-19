#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include "ConexionBD.h"

using namespace std;

class Marca {
    // Atributos
private:
    int idMarca;
    string marca;

public:
    // Constructor
    Marca() {}

    Marca(int id, string m) {
        idMarca = id;
        marca = m;
    }

    // Métodos
    // set (modificar)
    void setIdMarca(int id) { idMarca = id; }
    void setMarca(string m) { marca = m; }

    // get (mostrar)
    int getIdMarca() { return idMarca; }
    string getMarca() { return marca; }

    // Métodos CRUD
    void crear() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConectar()) {
            string insert = "INSERT INTO marcas(marca) VALUES('" + marca + "')";
            const char* i = insert.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                cout << "Ingreso exitoso..." << endl;
            }
            else {
                cout << "Error al ingresar la informacion: " << mysql_error(cn.getConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexion ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void leer() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        if (cn.getConectar()) {
            string consulta = "SELECT * FROM marcas";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                cout << "------------------- Marcas -------------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "ID: " << fila[0] << ", Marca: " << fila[1] << endl;
                }
            }
            else {
                cout << "Error al realizar la consulta: " << mysql_error(cn.getConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexion ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void actualizar(int id) {
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConectar()) {
            string update = "UPDATE marcas SET marca = '" + marca + "' WHERE idmarca = " + to_string(id);
            const char* u = update.c_str();
            q_estado = mysql_query(cn.getConectar(), u);
            if (!q_estado) {
                cout << "Actualizacion exitosa..." << endl;
            }
            else {
                cout << "Error al actualizar la informacion: " << mysql_error(cn.getConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexion ---" << endl;
        }
        cn.cerrar_conexion();
    }

    void eliminar(int id) {
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConectar()) {
            string del = "DELETE FROM marcas WHERE idmarca = " + to_string(id);
            const char* d = del.c_str();
            q_estado = mysql_query(cn.getConectar(), d);
            if (!q_estado) {
                cout << "Eliminacion exitosa..." << endl;
            }
            else {
                cout << "Error al eliminar la informacion: " << mysql_error(cn.getConectar()) << endl;
            }
        }
        else {
            cout << "--- Error en la conexion ---" << endl;
        }
        cn.cerrar_conexion();
    }
};