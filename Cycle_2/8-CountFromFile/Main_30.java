import java.io.*;
import java.util.Scanner;

class Main_30 {
    public static void main(String[] args) {
        try {
            Scanner f = new Scanner(new File(args[0]));
            int l = 0, w = 0, c = 0;
            while (f.hasNextLine()) {
                String line = f.nextLine();
                l += 1;
                String[] words = line.strip().split("\\s+").length;
                w += words.length;
                for (String s : words)
                    c += s.length();
            } System.out.printf("Lines: %d\nWords: %d\nCharacters: %d\n", l, w, c);
            f.close();
        } catch (FileNotFoundException e) {
            System.err.printf("%s: does not exist\n", args[0]);
            return;
        } catch (ArrayIndexOutOfBoundsException e) {
            System.err.println("argument: must provide at least and at most one file");
            return;
        }
    }
}
