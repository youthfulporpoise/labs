class LargestN_30 {
    public static void main(String[] args) {
        int max = Integer.valueOf(args[0]);
        for (String s : args) {
            int x = Integer.valueOf(s);
            if (x > max) max = x;
        }

        System.out.print("Input: ");
        for (String s : args) System.out.print(s + " ");
        System.out.println("  (" + args.length + ")");
        System.out.println(max + " is the largest.");
    }
}
