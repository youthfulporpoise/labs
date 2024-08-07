class LargestOfThree_30 {
    public static void main(String[] args) {
        int x = Integer.valueOf(args[0]),
            y = Integer.valueOf(args[1]),
            z = Integer.valueOf(args[2]),
            k;

        if (x > y) k = x;
        else k = y;
        if (z > k) k = z;

        System.out.println("Input: " + x + " " + y + " " + z);
        System.out.println(k + " is the largest.");

    }
}
