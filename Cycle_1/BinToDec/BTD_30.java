import java.util.Scanner;
import java.lang.Math;

class BTD_30 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Binary number: ");
        int b = scanner.nextInt();
        System.out.println("Decimal number: " + binaryToDecimal(b));
    }

    public static int binaryToDecimal(int b) {
        int r = 0;
        int p = 0;
        while (b > 0) {
            r += b % 10 * Math.pow(2, p++);
            b = b / 10;
        }
        return r;
    }
}
