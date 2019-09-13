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

public class ContarPalabras2 {

  public static class TokenizerMapper
       extends Mapper<Object, Text, Text, IntWritable>{

    private final static IntWritable two = new IntWritable(1);
    private Text word = new Text();
  
    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
                        
      StringTokenizer itr = new StringTokenizer(value.toString());
      while (itr.hasMoreTokens()) {
          String [] palabras=value.toString().split(" ");
           String []Temp;
           String Palabra=itr.nextToken();
            String Concatenadas="";
            for (String palabraTemp : palabras) {
                if (!(palabraTemp.equalsIgnoreCase(Palabra))&&Palabra.length()>0&&palabraTemp.length()>0) {
                  
                    Concatenadas+=Palabra+" "+palabraTemp+"-";
                }
            }
           Temp=Concatenadas.split("-");
          for(int i=0;i<Temp.length;i++){
              word.set(Temp[i]);
              context.write(word, two);
          }
      }//Fin del while
    }
  }
/*SUMA LAS PALABRAS */
  public static class PalabrasReducir
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
    Job job = Job.getInstance(conf, "word count");
    job.setJarByClass(ContarPalabras2.class);
    job.setMapperClass(TokenizerMapper.class);
    job.setCombinerClass(PalabrasReducir.class);
    job.setReducerClass(PalabrasReducir.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}
