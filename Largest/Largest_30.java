class Largest_30 {
    public static void main(String[] args) {
        int[] numbers = {8, 9, 2, 9, 23, 90, 43, 17};

        System.out.print("Array: ");
        for (int x : numbers) System.out.print(x + " ");
        System.out.println("");

        System.out.println("Largest: " + max(numbers));
    }

    public static int max(int[] a) {
        int largest = a[0];
        for (int i = 1; i < a.length; ++i)
            if (largest < a[i]) largest = a[i];
        return largest;
    }
}
