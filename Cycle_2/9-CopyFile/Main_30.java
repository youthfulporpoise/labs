import java.io.*;

class Main_30 {
    public static void main(String[] args) {
        try {
            FileReader fr = new FileReader(new File(args[0]));
            FileWriter fw = new FileWriter(new File(args[1]));
            int x;
            while ((x = fr.read()) != -1) fw.write(x);
            fr.close();
            fw.close();
        } catch (FileNotFoundException e) {
            System.err.printf("%s: does not exist\n", args[0]);
            return;
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Provide <source file> <destination file>");
            return;
        } catch (IOException e) {
            System.err.printf("%s: cannot be opened\n", args[1]);
            return;
        }
    }
}
