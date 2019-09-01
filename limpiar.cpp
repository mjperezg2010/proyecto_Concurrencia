#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;
int main()
{
  
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
    
}