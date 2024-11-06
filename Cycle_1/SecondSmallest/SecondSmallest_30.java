import java.util.Scanner;

class SecondSmallest_30 {
    public static void main (String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Array size: "); int n = kb.nextInt();

        int[] array = new int[n];
        System.out.print("Array: ");
        for (int i = 0; i < n; ++i)
            array[i] = kb.nextInt();

        /* We use a partial selection sort: O(n). */
        int min;
        for (int i = 0; i < 2; ++i) {
            min = i;
            for (int j = i + 1; j < n; ++j)
                if (array[j] < array[min])
                    min = j;
            int tmp = array[i];
            array[i] = array[min];
            array[min] = tmp;
        }
        System.out.println("Second smallest: " + array[1]);
    }
}
