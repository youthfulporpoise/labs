import java.io.*;
import java.util.Scanner;

class Main_30 {
    public static void main(String[] args) {
        try {
            Scanner f = new Scanner(new File(args[0]));
            FileWriter fOdd = new FileWriter(new File("odd.txt"));
            FileWriter fEven = new FileWriter(new File("even.txt"));
            int i;
            while (f.hasNextInt()) {
                i = f.nextInt();
                if (i % 2 == 0) fEven.write(i + " "); 
                else fOdd.write(i + " ");
            } fOdd.write('\n'); fEven.write('\n');
            fOdd.close(); fEven.close(); f.close();
        } catch (IOException e) {
            System.err.println("error: cannot write");
            return;
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("argument: provide input file");
            return;
        }
    }
}
