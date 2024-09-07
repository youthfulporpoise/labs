class Prime_30 {
    public static void main(String[] args) {
        int p = Integer.valueOf(args[0]);
        if (p < 0) p = -p;

        if (is_prime(p)) System.out.println(p + " is prime.");
        else System.out.println(p + " is not a prime.");
    }

    public static boolean is_prime(int x) {
        if (x < 2) return false;
        for (int i = 2; i < (x >> 1); ++i)
            if (x % i == 0) return false;
        return true;
    }
}
