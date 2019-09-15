//Clase Post Procesamiento de Dataset Querys Wikimedia
/*

Proyecto: Contador de Palabras Dos Frecuente con Hadoop/MapReduce
Clase: Concurrencia de Sistemas Distribuidos 

Integrantes:
Bryan Manrique Amador Mena
Martín José Pérez Gálvez
Richardson Alejandro Laínez Cárcamo

*/

//Importar las clases de hadoop Map/Reduce
import java.io.IOException;
import java.util.StringTokenizer;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
//Inicio de la clase 
public class ContarPalabras2 {
   //Seccion de separacion de las palabras, MAP
 //Utilizacion de las librerias Mapper, InWritable,Text
  public static class TokenizerMapper extends Mapper<Object, Text, Text, IntWritable>{
    private final static IntWritable two = new IntWritable(1);
    private Text word = new Text();
    public void map(Object key, Text value, Context context) throws IOException, InterruptedException {                  
      StringTokenizer itr = new StringTokenizer(value.toString());
         int cont=1;
             //Tomar las palabras una por una
        while (itr.hasMoreTokens()) {
            String[] tokenspalabras = value.toString().split(" "),Temp;
            String Palabra = itr.nextToken(),acum="";
            if(tokenspalabras.length>1){
            for (int i = cont; i < tokenspalabras.length; i++) {
                if (!(tokenspalabras[i].equalsIgnoreCase(Palabra)) && Palabra.length() > 0 && tokenspalabras[i].length() > 0) {
                    acum += Palabra + " " + tokenspalabras[i] + "-";
                }
            }
            Temp = acum.split("-");
            for (int i = 0; i < Temp.length; i++) {
                word.set(Temp[i]);
                context.write(word, two);
            }
            cont=cont+1;
            }
        }
    }
  }

//Seccion de separacion de las palabras, Reduce  
  public static class ReduceClase
       extends Reducer<Text,IntWritable,Text,IntWritable> {
    private IntWritable result = new IntWritable();

    public void reduce(Text key, Iterable<IntWritable> values,
                       Context context
                       ) throws IOException, InterruptedException {
      int sum = 0;
      for (IntWritable val : values) {
        sum += val.get();
      }
      result.set(sum);
      context.write(key, result);
    }
  }

  public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();
    Job job = Job.getInstance(conf, "ontador de Palabras Dos");
    job.setJarByClass(ContarPalabras2.class);
    job.setMapperClass(TokenizerMapper.class);
    job.setCombinerClass(ReduceClase.class);
    job.setReducerClass(ReduceClase.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}

