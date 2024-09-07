import java.lang.Math;
import java.util.Scanner;

class Shape {
    static public double area(double r) {
        /* Calculate the area of a circle. */
        return Math.PI * Math.pow(r, 2);
    }
    static public double area(double a, double b, double c) {
        /* Calculate the area of a triangle (Heron's formula). */
        double s = (a + b + c) / 2;
        return Math.sqrt(s * (s - a) * (s - b) * (s - c));
    }
    static public double area(double l, double w) {
        /* Calculate the area of a rectangle. */
        return l * w;
    }
}

class Shape_30 {
    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print(
            "Find area of:\n" +
            "   (1) circle\n" +
            "   (2) rectangle\n" +
            "   (3) triangle\n" +
            "Choice: ");
        int choice = kb.nextInt();

        System.out.print("Dimensions: ");
        double result;
        switch (choice) {
            case 1:
                result = Shape.area(kb.nextDouble());
                break;
            case 2:
                result = Shape.area(kb.nextDouble(), kb.nextDouble());
                break;
            case 3:
                result = Shape.area(kb.nextDouble(), kb.nextDouble(), kb.nextDouble());
                break;
            default:
                System.out.println("error: invalid choice");
                return;
        }
        System.out.println("Area: " + result);
    }
}
