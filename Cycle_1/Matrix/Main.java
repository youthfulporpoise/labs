import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Rows: "); int rows = kb.nextInt();
        System.out.print("Columns: "); int cols = kb.nextInt();

        int[][] array = new int[rows][cols];
        System.out.println("\nMatrix: ");
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                array[i][j] = kb.nextInt();

        Matrix m = new Matrix(rows, cols, array);
        m.transpose();
        System.out.println("\nTranspose:\n" + m);
    }
}

class Matrix {
    int rows, cols;
    private int[][] matrix;

    Matrix(int rows, int cols, int[][] array) {
        this.rows = rows;
        this.cols = cols;
        this.matrix = new int[rows][cols];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                this.matrix[i][j] = array[i][j];
    }

    @Override
    public String toString() {
        String s = "";
        for (int i = 0; i < this.rows; ++i) {
            for (int j = 0; j < this.cols; ++j)
                s += this.matrix[i][j] + " ";
            s += "\n"; s.trim();
        }
        return s;
    }

    void transpose() {
        int[][] tmp = this.matrix.clone();
        int rows = this.rows; this.rows = this.cols; this.cols = rows;
        this.matrix = new int[this.rows][this.cols];

        for (int i = 0; i < this.rows; ++i)
            for (int j = 0; j < this.cols; ++j)
                this.matrix[i][j] = tmp[j][i];
    }
}
