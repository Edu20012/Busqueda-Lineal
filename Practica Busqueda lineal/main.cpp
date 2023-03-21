#include <iostream>
#include <string>

#define TAM 100

class Solicitud{
private:
    std::string nombre_alumno;
    std::string carrera;
    int materias_aprobadas;
    float promedio_general;
public:
    Solicitud(){};
    Solicitud(std::string n, std::string c, int m, float p) :
        nombre_alumno(n), carrera(c), materias_aprobadas(m), promedio_general(p) {}

    friend std::ostream & operator<<(std::ostream &O, const Solicitud &x){
            O<<"\n Nombre del alumno: "<<x.nombre_alumno;
            O<<"\n Carrera: "<<x.carrera;
            O<<"\n Materias aprobadas: "<<x.materias_aprobadas;
            O<<"\n Promedio general: "<<x.promedio_general<<std::endl;
            return O;
    }

    friend std::istream & operator>>(std::istream &O, Solicitud &x){
            std::cout<<"\n Nombre del alumno: ";
            O>>x.nombre_alumno;
            std::cout<<"\n Carrera: ";
            O>>x.carrera;
            std::cout<<"\n Materias aprobadas: ";
            O>>x.materias_aprobadas;
            std::cout<<"\n Promedio general: ";
            O>>x.promedio_general;
            return O;
    }
     bool operator==(const Solicitud& s) const {
        return nombre_alumno == s.nombre_alumno && carrera == s.carrera && materias_aprobadas == s.materias_aprobadas && promedio_general == s.promedio_general;
    }
};

template<class T>
class Cola{
private:
    T datos[TAM];
    int ult;
    bool inserta(T , int);
    bool elimina(int);
    T recupera(int)const;
    int primero()const;
    int ultimo()const;
public:
    Cola():ult(-1){}
    bool vacia()const;
    bool llena()const;
    bool Queue(T&);
    bool Dequeue();
    void imprime()const;
    T Front()const;
    int busquedalineal(const Solicitud &elem)const;
};


template<class T>
T Cola<T>::Front()const{
    T x=datos[primero()];
    return x;
}

template<class T>
bool Cola<T>::Dequeue(){
    if(vacia()){
        return false;
    }
    else{
        elimina(primero());
    }
    return true;
}

template<class T>
bool Cola<T>::Queue(T& elem){
    if(llena()){
        return false;
    }
    if(vacia()){
        inserta(elem,0);
    }
    else{
        inserta(elem, ultimo()+1);
    }
    return true;
}

template<class T>
void Cola<T>::imprime()const{
    if(!vacia()){
        for(int i=0; i<=ult; i++){
            T x=datos[i];
            std::cout<<x<<std::endl;
        }
    }
}

template<class T>
bool Cola<T>::vacia()const{
    return ult==-1;
}

template<class T>
bool Cola<T>::llena()const{
    return ult==TAM-1;
}

template<class T>
bool Cola<T>::inserta(T elem, int pos){
    if(llena() || pos<0 || pos>ult+1){
        std::cout<<"\n No se pudo insertar";
        return false;
    }
    int i=ult;
    while(i>=pos){
        datos[i+1]=datos[i];
        i--;
    }
    datos[pos]=elem;
    ult++;
    return true;
}
template<class T>
bool Cola<T>::elimina(int pos){
    if(vacia() || pos<0 || pos>ult){
        return false;
    }
    int i=pos;
    while(i<ult){

        datos[i]=datos[i+1];
        i++;
    }
    ult--;
    return true;
}
template<class T>
int Cola<T>::primero()const{
    return 0;
}
template<class T>
int Cola<T>::ultimo()const{
    return ult;
}
template<class T>
int Cola<T>::busquedalineal(const Solicitud &elem)const{
    Solicitud s;
    for(int i=0; i<=ult; i++){
        s=datos[i];
        if(elem==s)
            return i;
    }
    return -1;
}
int main(){
    Cola<Solicitud> cola_solicitudes;
    int opcion;
    Solicitud solicitud;

    do{
        std::cout << "\n\n *******************************************************";
        std::cout << "\n\t1. Agregar solicitud\n";
        std::cout << "\n\n";
        std::cout << "\n\t2. Atender solicitud\n";
        std::cout << "\n\n";
        std::cout << "\n\t3. Mostrar solicitudes\n";
        std::cout << "\n\n";
        std::cout << "\n\t4. Busqueda lineal (Encontrar Solicitud)\n\n";
        std::cout << "\n\n";
        std::cout << "\n\t5. Salir\n";
        std::cout << "\n\n*********************************************************";
        std::cout << "\n\nSeleccione una opcion: ";
        std::cin >> opcion;

        switch(opcion){
            case 1:
                std::cout << "\nIngresar los datos de la solicitud:\n";
                std::cin >> solicitud;
                if(cola_solicitudes.Queue(solicitud)){
                    std::cout << "\nSolicitud agregada exitosamente.\n";
                }
                else{
                    std::cout << "\nNo se pudo agregar la solicitud.\n";
                }
                break;

            case 2:
                if(cola_solicitudes.vacia()){
                    std::cout << "\nNo hay solicitudes para atender.\n";
                }
                else{
                    solicitud = cola_solicitudes.Front();
                    std::cout << "\nAtendiendo la siguiente solicitud:\n";
                    std::cout << solicitud;
                    cola_solicitudes.Dequeue();
                }
                break;

            case 3:
                std::cout << "\nListado de solicitudes:\n";
                if(cola_solicitudes.vacia()){
                    std::cout << "\nNo hay solicitudes en la cola.\n";
                }
                else{
                    cola_solicitudes.imprime();
                }
                break;

           case 4:
                {
                    std::string nombre_alumno, carrera;
                    int materias_aprobadas;
                    float promedio_general;
                    std::cout << "\nIngrese los datos de la solicitud que desea buscar:\n";
                    std::cout << "Nombre del alumno: ";
                    std::cin >> nombre_alumno;
                    std::cout << "Carrera: ";
                    std::cin >> carrera;
                    std::cout << "Materias aprobadas: ";
                    std::cin >> materias_aprobadas;
                    std::cout << "Promedio general: ";
                    std::cin >> promedio_general;
                    Solicitud solicitud_busqueda(nombre_alumno, carrera, materias_aprobadas, promedio_general);
                    int indice = cola_solicitudes.busquedalineal(solicitud_busqueda);
                    if(indice != -1){
                        std::cout << "\nLa solicitud se encuentra en la posicion " << indice << " de la cola.\n";
                    }
                    else{
                        std::cout << "\nLa solicitud no se encuentra en la cola.\n";
                    }
                }
                break;

            case 5:
                std::cout << "\nSaliendo...\n";
                break;

            default:
                std::cout << "\nOpcion invalida. Por favor seleccione una opcion valida.\n";
                break;
        }
    }while(opcion != 5);

return 0;
}
