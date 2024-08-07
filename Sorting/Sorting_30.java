class Sorting_30 {
    public static void main(String[] args) {
        int[] array = {89, 72, 23, 92, 74, 51, 32};

        System.out.print("Array: ");
        for (int x : array)
            System.out.print(x + " ");
        System.out.println("");


        System.out.print("Sorted array: ");
        for (int x : sort(array))
            System.out.print(x + " ");
        System.out.println("");
    }

    public static int[] sort(int[] array) {
        /* We sort the array using selection sort. */
        int k;
        for (int i = 0; i < array.length - 1; ++i) {
            for (int j = i + 1; j < array.length; ++j)
                if (array[j] < array[i]) {
                    int tmp = array[i];
                    array[i] = array[j];
                    array[j] = tmp;
                }
        }
        return array;
    }
}
