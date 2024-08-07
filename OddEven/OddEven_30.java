class OddEven_30 {
    public static void main(String[] args) {
        int x = Integer.valueOf(args[0]);

        if (x % 2 == 0) System.out.println(x + " is even.");
        else System.out.println(x + " is odd.");
    }
}
