import java.util.Scanner;
import java.lang.StringBuffer;

class BTD_30 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Binary number: ");
        int b = scanner.nextInt();
        System.out.println("Decimal number: " + binaryToDecimal(b));

        System.out.print("\nDecimal number: ");
        int d = scanner.nextInt();
        System.out.println("Binary number: " + decimalToBinary(d));
    }

    public static String binaryToDecimal(int b) {
        int r = 0;
        int p = 0;
        while (b > 0) {
            r += b % 10 * Math.pow(2, p++);
            b = b / 10;
        }
        return String.valueOf(r);
    }

    public static String decimalToBinary(int d) {
        StringBuffer r = StringBuffer("");
        while (d > 0) {
            r.append(d % 2);
            d /= 2;
        } ;
    }
}
