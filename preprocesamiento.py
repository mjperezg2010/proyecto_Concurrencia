# Clase Preprocesamiento del Dataset Querys wikimedia
"""
Proyecto: Contador de Palabras con Hadoop/MapReduce
Clase: Concurrencia de Sistemas Distribuidos 

Integrantes:
Bryan Manrique Amador Mena
Martín José Pérez Gálvez
Richardson Alejandro Laínez Cárcamo

"""

archivo=open("Dataset.txt","r")
archivo2=open("Dataset_Limpio.txt","w")

listaArchivo=[]
listaGuardar=[]


Diccionario=["about", "above", "across", "after", 
"against", "along", "among", "around", "at",
  "because of", "before", "behind", "below", 
  "beneath", "beside", "besides", "between",
  "beyond", "but", "by", "concerning", "despite", 
  "down", "during", "except", "excepting",
  "for", "from", "in", "in front of", "inside", 
  "in spite of", "instead of", "into",
  "like", "near", "of", "off", "onto", "out", 
  "outside", "over", "past", "regarding",
  "since", "through", "throughout", "to", "toward", 
  "under", "underneath", "until", "up",
  "upon", "up to", "with", "within", "without", 
  "with regard to", "with respect to","and","the",
  "my","how","did","you","nd","th","i","st","de","s"]




for i in range(0,498196):
    listaArchivo.append(archivo.readline())



for i in range(0,len(listaArchivo)):
    linea=listaArchivo[i]
    

    #Caracteres que no son letras
    temporal=""

    for j in linea:
        if(j.isalpha() or j=='\n' or j==' '):
            temporal=temporal+j
        elif (j=='-' or j=='/'):
            temporal=temporal+' '


    #Eliminar preposiciones
    temporal=temporal.lower()
    for j in Diccionario:
        prep1=j+' '
        prep2=' '+j+' '

    
        if(prep1 in temporal):
            if(prep1[0]==temporal[0] and prep1[1]==temporal[1]):
                temporal=temporal.replace(prep1,"")

    
        if(prep2 in temporal):
            temporal=temporal.replace(prep2," ")

    #Guardar valores en la listaGuardar
    
    listaGuardar.append(temporal)
    print(temporal)
for i in listaGuardar:
    archivo2.write(i)



archivo.close()

