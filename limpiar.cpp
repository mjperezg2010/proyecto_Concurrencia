#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <functional>
#include <numeric>
#include <algorithm>
using namespace std;
void limpiarVersionDos();


template<class T>
struct DefaultFuncComparar
{
  bool operator()(T const& a, T const& b)
  {
    return a > b;
  }
};


//Funcion del sort
template<class T, class U, class FuncComparar = std::function<bool(T const&, T const&)>>
void OrdenarVectores(
  std::vector<T>& a,
  std::vector<U>& b,
  FuncComparar comparar = DefaultFuncComparar<T>())
{
  std::vector<T> copiaA{a};
  std::vector<U> copiaB{b};

  // Creamos el vector de índices
  std::vector<std::size_t> vector_indices(a.size());
  std::iota(vector_indices.begin(), vector_indices.end(), 0);

  // Ordenamos los índices en base al vector "a"
  std::sort(vector_indices.begin(), vector_indices.end(),
      [&](std::size_t i, std::size_t j){ return comparar(a[i], a[j]); });

  // Ordenamos los vectores "a" y "b" en base al vector de índices
  std::transform(vector_indices.begin(), vector_indices.end(), a.begin(),
      [&](std::size_t i){ return copiaA[i]; });

  std::transform(vector_indices.begin(), vector_indices.end(), b.begin(),
      [&](std::size_t i){ return copiaB[i]; });
}

















int main()
{
    limpiarVersionDos();
  
    return 0;
}


void limpiarPrimeraDataset(){

    string texto;
    ifstream archivo;
    ofstream nuevo;

    vector<string> listaArchivo;
    vector<string> listaFinal;
    vector<string> listaTemp;
    archivo.open("./Dataset.txt",ios::in);
    nuevo.open("nuevo.txt",ios::out);



    //Parte de analizar el archivo
    if(archivo.fail()){
        cout<<"El archivo no se abrio"<<endl;
    }else{
        if(nuevo.fail()){
            cout<<"El archivo no se abrio"<<endl;
        }else{
            while (!archivo.eof()) {
                //archivo >> texto;
                //cout << cadena << endl;
                getline(archivo,texto);
                listaArchivo.push_back(texto);
            // nuevo<<texto<<endl;
            }
        }
    }
    


    
    for (size_t i = 0; i < listaArchivo.size(); i++)
    {
        int cont=0,cont2=0;
        char str[listaArchivo.at(i).size()];
        strcpy(str, listaArchivo.at(i).c_str());
        char * pch;
        pch = strtok (str,":");
        
       // pch= strtok(NULL,":");
        //pch= strtok(NULL,":");
        //cout<<pch<<endl;
        
        while (pch != NULL)
        {
            //listaFinal.push_back(pch);
            //printf ("%s\n",pch);
            pch = strtok (NULL, ":");
            cont++;
        }


        char stre[listaArchivo.at(i).size()];
        strcpy(stre, listaArchivo.at(i).c_str());
        char * pche;
        pche = strtok (stre,":");
        cont--;
        while (pche != NULL)
        {
            //listaFinal.push_back(pch);
            //printf ("%s\n",pch);
            pche = strtok (NULL, ":");
            cont2++;
            //cout<<cont<<" - "<<cont2<<endl;
            if((cont2)==(cont)){
                listaFinal.push_back(pche);
                
            }
        }
        


        if(i==0 || i==3){
            cout<<cont2<<endl;
        }
        
        
        
    }


  for (size_t i = 0; i < listaFinal.size(); i++)
  {
      nuevo<<listaFinal.at(i)<<"\n";
  }

    archivo.close();
    nuevo.close();
    cout<<listaArchivo.at(0)<<endl;



}

void limpiarVersionDos(){
    string texto;
    ifstream archivo;
    ofstream nuevo;

    vector<string> listaArchivo;
    vector<int> listaPos;
    vector<string> listaPalabras;
    archivo.open("contar.txt",ios::in);
    nuevo.open("nuevoDatos.txt",ios::out);



    //Parte de analizar el archivo
    if(archivo.fail()){
        cout<<"El archivo no se abrio"<<endl;
    }else{
        if(nuevo.fail()){
            cout<<"El archivo no se abrio"<<endl;
        }else{
            while (!archivo.eof()) {
                //archivo >> texto;
                //cout << cadena << endl;
                getline(archivo,texto);
                listaArchivo.push_back(texto);
            // nuevo<<texto<<endl;
            }
        }
    }

    


    char r=listaArchivo.at(0)[1];
    //cout<<r<<endl;

/*
     
    char str[listaArchivo.at(0).size()];
    strcpy(str, listaArchivo.at(0).c_str());
    char * pch;
    pch = strtok (str," ";
    cout<<pch<<endl; 
       // pch= strtok(NULL,":");
        //pch= strtok(NULL,":");
        //cout<<pch<<endl;

*/



    

    for (size_t y = 0; y < listaArchivo.size(); y++)
    {
        string final;
        string finalt;
        stringstream concatenar;
        stringstream numeros;
        bool bandera=false;
        for (size_t  i= 0; i < listaArchivo.at(y).size(); i++)
        {
            if(listaArchivo.at(y)[i]!=r && bandera==false){
                concatenar << listaArchivo.at(y)[i];
            }else{
              bandera=true;
            }

            if(bandera && listaArchivo.at(y)[i]!=r){
                numeros << listaArchivo.at(y)[i];
            }
            
            
        }
        
        
        final= concatenar.str();
        finalt = numeros.str();

        

        int number;
        istringstream iss (finalt);
        iss >> number;


        listaPalabras.push_back(final);
        listaPos.push_back(number);
       
        
    }

    
/*
    int tempi,cont=0,size=listaPos.size();
    string temps;

    for (int i=1; i<size; i++){
        for (int j=0 ; j<size - 1; j++){
            if (listaPos[j] < listaPos[j+1]){
                temps = listaPalabras[j];
                listaPalabras[j] = listaPalabras[j+1];
                listaPalabras[j+1] = temps;


                tempi = listaPos[j];
                listaPos[j] = listaPos[j+1];
                listaPos[j+1] = tempi;

               

            }
        }
         cout<<i<<endl;
    }*/


    OrdenarVectores(listaPos,listaPalabras);
    cout<<listaPalabras.at(0) << " - "<<listaPos.at(0)<<endl;
    
    for (size_t i = 0; i < listaPos.size(); i++)
  {
      nuevo<<listaPalabras.at(i)<<" "<<listaPos.at(i)<<"\n";
  }  
               
  
   
    




}