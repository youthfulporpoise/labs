import java.util.Scanner;

class OpsMatrix_30 {
    static class Matrix {
        /* A class representing a matrix object. */
        public int rows;
        public int cols;
        private int[][] matrix;

        Matrix(int rows, int cols, int[][] array) {
            this.rows = rows;
            this.cols = cols;
            this.matrix = new int[rows][cols];
            this.populate(array);
        }

        private void populate(int[][] array) {
            for (int i = 0; i < this.rows; ++i)
                for (int j = 0; j < this.cols; ++j)
                    this.matrix[i][j] = array[i][j];
        }

        public void print(String msg) {
            System.out.println(msg);
            for (int i = 0; i < this.rows; ++i) {
                for (int j = 0; j < this.cols; ++j) 
                    System.out.print(this.matrix[i][j] + " ");
                System.out.println("");
            } System.out.println("");
        }

        public Matrix transpose() {
            Matrix m = new Matrix(this.rows, this.cols, this.matrix);
            for (int i = 0; i < this.rows; ++i)
                for (int j = 0; j < this.cols; ++j)
                    this.matrix[i][j] = m.matrix[j][i];
            return this;
        }
    }

    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Rows: ");
        int rows = kb.nextInt();

        System.out.print("Columns: ");
        int cols = kb.nextInt();

        System.out.println("Matrix: ");
        int[][] array = new int[rows][cols];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                array[i][j] = kb.nextInt();

        Matrix m = new Matrix(rows, cols, array);
        m.transpose().print("\nTranspose:");
    }
}
