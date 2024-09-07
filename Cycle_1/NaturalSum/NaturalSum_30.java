/* Program: NATURAL SUM
 * Aim: Find the partial number sum upto n;
 */

import java.util.Scanner;

class NaturalSum_30 {
    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("n: ");
        long n = kb.nextLong();
        System.out.println("Sum upto n: " + naturalSum(n));
    }

    public static long naturalSum(long n) {
        return n * (n - 1) / 2;
    }
}
