class SumOfDigits {
    public static void main(String[] args) {
        int x = Integer.valueOf(args[0]);
        int sum = 0;

        System.out.print("Sum of the digits of " + x + " is ");
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        System.out.println(sum + ".");
    }
}
