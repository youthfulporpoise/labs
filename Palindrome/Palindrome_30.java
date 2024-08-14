class Palindrome_30 {
    public static void main(String[] args) {
        String s = args[0];
        if (is_palindrome(s)) System.out.println(s + " is a palindrome.");
        else System.out.println(s + " is not a palindrome.");
    }

    public static boolean is_palindrome(String s) {
        int n = s.length();
        for (int i = 0; i <= n / 2; ++i)
            if (s.charAt(i) != s.charAt(n - i - 1))
                return false;
        return true;
    }
}
