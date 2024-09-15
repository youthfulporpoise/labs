public class Main_30 {
    public static void main(String[] args) {
        Shape a = new Triangle();
        System.out.printf("Sides for %s: %d\n", a.name, a.numberOfSides());
        a = new Rectangle();
        System.out.printf("Sides for %s: %d\n", a.name, a.numberOfSides());
        a = new Hexagon();
        System.out.printf("Sides for %s: %d\n", a.name, a.numberOfSides());
    }
}

abstract class Shape {
    String name = "shape";
    abstract int numberOfSides();
}

final class Triangle extends Shape {
    Triangle() { this.name = "triangle"; }
    @Override
    int numberOfSides() { return 3; }
}

final class Rectangle extends Shape {
    Rectangle() { this.name = "rectangle"; }
    @Override
    int numberOfSides() { return 4; }
}

final class Hexagon extends Shape {
    Hexagon() { this.name = "hexagon"; }
    @Override
    int numberOfSides() { return 6; }
}
