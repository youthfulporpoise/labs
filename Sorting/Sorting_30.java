import java.util.Scanner;

class Sorting_30 {
    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Size: ");
        int n = kb.nextInt();
        System.out.print("Array: ");
        int[] array = new int[n];
        for (int i = 0; i < n; ++i) array[i] = kb.nextInt();

        System.out.print("Sorted array: ");
        for (int x : sort(array))
            System.out.print(x + " ");
        System.out.println("");
    }

    public static int[] sort(int[] array) {
        /* We sort the array using selection sort. */
        int min;
        for (int i = 0; i < array.length - 1; ++i) {
            min = i;
            for (int j = i + 1; j < array.length; ++j)
                if (array[j] < array[min]) min = j;
            int tmp = array[i];
            array[i] = array[min];
            array[min] = tmp;
        }
        return array;
    }
}
