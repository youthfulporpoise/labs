class Area_30 {
    public static void main(String[] args) {
        double radius = Double.valueOf(args[0]);
        System.out.println("Radius: " + radius + " => Area: " +
                           Math.pi * Math.pow(radius, 2));
    }
}
        

class Math {
    public static double pi = 3.14159265;
    public static double pow(double a, int r) {
        double value = 1;
        for (int i = 0; i < r; ++i) value *= a;
        return value;
    }
}
