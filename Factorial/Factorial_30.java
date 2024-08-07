class Factorial_30 {
    public static void main(String[] args) {
        int i = 14;
        System.out.println(i + "! = " + factorial(i));
    }

    public static long factorial(long n) {
        if (n == 0) return 1;
        else return (n * factorial(n - 1));
    }
}
