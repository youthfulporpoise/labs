import java.util.Scanner;
import java.util.StringTokenizer;

class Main_30 {
    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Integers (separated by spaces): ");
        String ss = kb.nextLine();

        StringTokenizer st = new StringTokenizer(ss, " ");
        int[] ns = new int[st.countTokens()];
        int i = 0; String t = "";

        while (st.hasMoreTokens()) {
            try { 
                t = st.nextToken();
                ns[i++] = Integer.parseInt(t);
            } catch (NumberFormatException e) {
                System.out.println("\n" + t + " is not a number");
                return;
           }
        }

        int sum = 0;
        System.out.print("Integers read: ");
        for (int n : ns) {
            sum += n;
            System.out.print(n + " ");
        } System.out.println("\nSum: " + sum);
    }
}
