class LargestOfTwo {
    public static void main(String[] args) {
        int x = Integer.valueOf(args[0]), y = Integer.valueOf(args[1]);
        if (x > y) System.out.println(x + "is the Largest.");
        else System.out.println(y + "is the Largest.");
    }
}
