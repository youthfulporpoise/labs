import java.util.Scanner;
import java.util.ArrayList;

class Main_30 {
    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Queue size: "); int n = kb.nextInt();
        Queue<Character> queue = new Queue<Character>(n);

        int choice;
        do {
            System.out.print("\n" +
                    "(1) Enqueue  (2) Dequeue (3) Display  (4) Quit\n" +
                    "Choice: ");
            choice = kb.nextInt();
            System.out.print("\n");
            switch (choice) {
                case 1:
                    System.out.print("Element: ");
                    try { queue.enqueue(kb.next().charAt(0)); }
                    catch (FullException e) {
                        System.out.println("\nThe queue is full.");
                        continue;
                    } break;
                case 2:
                    try { System.out.println("\nElement: " + queue.dequeue()); }
                    catch (EmptyException e) {
                        System.out.println("\nThe queue is empty.");
                        continue;
                    } break;
                case (3):
                    System.out.println("Queue: " + queue);
                    break;
                case (-1):
                    return;
                default:
                    System.out.println("\nI don‘t understand.");
                    continue;
            }
        } while (choice != -1);
    }
}

final class Stack<T> {
    private T[] stack;
    int size;
    private int top = 0;

    public Stack(int n) { 
        this.size = n;
        stack = (T[]) new Object[size];
    }

    @Override
    public String toString() {
        if (top == 0) return "-/-";
        else {
            String s = new String("");
            for (int i = top; i > 0;) s += stack[--i] + " ";
            return s;
        }
    }
    public void push(T x) throws FullException { 
        if (top < size) stack[top++] = x;
        else throw new FullException();
    }
    public T pop() throws EmptyException {
        if (top > 0) return stack[--top];
        else throw new EmptyException();
    }
}

final class Queue<T> {
    private T[] queue;
    int size;
    private int f = 0, r = 0;

    private enum QS { FULL, NEUTRAL, EMPTY };
    private QS qs = QS.EMPTY;

    public Queue(int n) {
        this.size = n;
        queue = (T[]) new Object[size];
    }

    @Override
    public String toString() {
        if (qs == QS.EMPTY) return "-/-";
        else {
            String repr = "";
            int i = f;
            do {
                repr = repr.concat(queue[i] + "");
                i = (i + 1) % size;
            } while (i != r);
            return repr;
        }
    }

    public void enqueue(T x) throws FullException {
        if (qs == QS.FULL) throw new FullException();
        queue[r] = x; r = (r + 1) % size;
        if (r == f) qs = QS.FULL;
        else qs = QS.NEUTRAL;
    }

    public T dequeue() throws EmptyException {
        if (qs == QS.EMPTY) throw new EmptyException();
        T x = queue[f]; f = (f + 1) % size;
        if (r == f) qs = QS.EMPTY;
        else qs = QS.NEUTRAL;
        return x;
    }

}

class EmptyException extends Exception {
    EmptyException() { super("overflow"); }
}

class FullException extends Exception {
    FullException() { super("underflow"); }
} 
