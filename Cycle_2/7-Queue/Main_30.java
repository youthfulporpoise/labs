class Main_30 {
    public static void main(String[] args) {
        Queue<Character> queue = new Queue<Character>(5);

        System.out.println("Enqueueing h, e, l, l, and o.");
        char[] letters = {'h', 'e', 'l', 'l', 'o'};
        try {
            for (char c : letters) queue.enqueue(c);
            System.out.println("Queue: " + queue);
            System.out.println("Dequeueing: " + queue.dequeue() + " dequeued.");
        } catch (OverflowException e) {
            System.out.println("Queue: OVERFLOW");
        } catch (UnderflowException e) {
            System.out.println("Queue: UNDERFLOW");
        }

        // int choice;
        // do {
        //     System.out.print("\n" +
        //             "(1) Enqueue  (2) Dequeue (3) Display  (4) Quit\n" +
        //             "Choice: ");
        //     choice = kb.nextInt();
        //     System.out.print("\n");
        //     switch (choice) {
        //         case 1:
        //             System.out.print("Element: ");
        //             try { queue.enqueue(kb.next().charAt(0)); }
        //             catch (OverflowException e) {
        //                 System.out.println("\nThe queue is full.");
        //                 continue;
        //             } break;
        //         case 2:
        //             try { System.out.println("\nElement: " + queue.dequeue()); }
        //             catch (UnderflowException e) {
        //                 System.out.println("\nThe queue is empty.");
        //                 continue;
        //             } break;
        //         case (3):
        //             System.out.println("Queue: " + queue);
        //             break;
        //         case (-1):
        //             return;
        //         default:
        //             System.out.println("\nI don‘t understand.");
        //             continue;
        //     }
        // } while (choice != -1);
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
