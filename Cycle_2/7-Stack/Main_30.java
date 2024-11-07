import java.util.Scanner;

class Main_30 {
    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        Stack<Integer> stack = new Stack<Integer>(5);
        Queue<Integer> queue = new Queue<Integer>(5);

        int x;
        try {
            System.out.println("Stack and queue of size 5.");
            System.out.print("Push elements: ");
            for (x = 0; x < 5; ++x) stack.push(kb.nextInt());
            System.out.print("Stack: " + stack + "\n");
            System.out.print("Pop how many? ");
            x = kb.nextInt();
            for (; x > 0; --x) System.out.println("" + stack.pop());

            System.out.print("\nEnqueue elements: ");
            for (x = 0; x < 5; ++x) queue.enqueue(kb.nextInt());
            System.out.print("Queue: " + queue + "\n");
            System.out.print("Dequeue how many? ");
            x = kb.nextInt();
            for (; x > 0; --x) System.out.println("" + queue.dequeue());
        } catch (OverflowException e) {
            System.out.println("Overflow");
            return;
        } catch (UnderflowException e) {
            System.out.println("Underflow");
            return;
        }
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
    public void push(T x) throws OverflowException { 
        if (top < size) stack[top++] = x;
        else throw new OverflowException();
    }
    public T pop() throws UnderflowException {
        if (top > 0) return stack[--top];
        else throw new UnderflowException();
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
                repr = repr.concat(queue[i] + " ");
                i = (i + 1) % size;
            } while (i != r);
            return repr;
        }
    }

    public void enqueue(T x) throws OverflowException {
        if (qs == QS.FULL) throw new OverflowException();
        queue[r] = x; r = (r + 1) % size;
        if (r == f) qs = QS.FULL;
        else qs = QS.NEUTRAL;
    }

    public T dequeue() throws UnderflowException {
        if (qs == QS.EMPTY) throw new UnderflowException();
        T x = queue[f]; f = (f + 1) % size;
        if (r == f) qs = QS.EMPTY;
        else qs = QS.NEUTRAL;
        return x;
    }

}

class UnderflowException extends Exception {
    UnderflowException() { super("overflow"); }
}

class OverflowException extends Exception {
    OverflowException() { super("underflow"); }
} 
