import java.util.Scanner;

class CharFrequency_30 {
    public static void main (String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("String: ");
        String s = scanner.nextLine();
        System.out.print("Key: ");
        char k = scanner.next().charAt(0);

        int f = frequency(s, k);
        System.out.println(k + " occurs " + f + " time(s).");
    }

    public static int frequency(String s, char k) {
        int f = 0;
        for (int i = 0; i < s.length(); ++i)
            if (k == s.charAt(i)) f++;
        return f;
    }
}
