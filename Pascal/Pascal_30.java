import java.lang.Math;

class Pascal_30 {
    public static void main(String[] args) {
        int n = Integer.valueOf(args[0]);
        int[][] pt = new int[n][n];
        int l = pascal(pt, n);

        for (int i = 0; i < n; ++i) {
            int pad = (int) Math.ceil(l * (n - i) / 2);
            System.out.print(String.format("%" + pad + "c", ' '));
            for (int j = 0; j <= i; ++j) {
                String s = String.format("%" + l + "d", pt[i][j]);
                System.out.print(s + " ");
            } System.out.println("");
        }
    }

    public static int pascal(int[][] pt, int n) {
        int high = 1;
        pt[0][0] = 1;
        int i, j;
        for (i = 1; i < n; ++i) {
            pt[i][0] = 1;
            for (j = 1; j < i; ++j) {
                pt[i][j] = pt[i - 1][j - 1] + pt[i - 1][j];
                high = pt[i][j] > high ? pt[i][j] : high;
            } pt[i][j] = 1;
        }
        return (int) Math.floor(Math.log10(high) + 1);
    }
}
