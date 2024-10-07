class Main_30 {
    public static void main(String[] args) {
        Stack<Character> stack = new Stack<Character>(5);

        System.out.println("Pushing o, l, l, e, and h.");
        char[] letters = {'o', 'l', 'l', 'e', 'h'};
        try {
            for (char c : letters) stack.push(c);
            System.out.println("Stack: " + stack);
            System.out.println("Popping: " + stack.pop() + " popped.");
        } catch (OverflowException e) {
            System.out.println("Stack: OVERFLOW");
        } catch (UnderflowException e) {
            System.out.println("Stack: UNDERFLOW");
        }

        // int choice;
        // do {
        //     System.out.print("\n" +
        //             "(1) Push  (2) Pop (3) Display  (4) Quit\n" +
        //             "Choice: ");
        //     choice = kb.nextInt();
        //     System.out.print("\n");
        //     switch (choice) {
        //         case 1:
        //             System.out.print("Element: ");
        //             try { stack.push(kb.next().charAt(0)); }
        //             catch (OverflowException e) {
        //                 System.out.println("\nThe stack is full.");
        //                 continue;
        //             } break;
        //         case 2:
        //             try { System.out.println("\nElement: " + stack.pop()); }
        //             catch (UnderflowException e) {
        //                 System.out.println("\nThe stack is empty.");
        //                 continue;
        //             } break;
        //         case (3):
        //             System.out.println("Stack: " + stack);
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

final class Stack<T> {
    /** The Stack generic */
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

class UnderflowException extends Exception {
    UnderflowException() { super("overflow"); }
}

class OverflowException extends Exception {
    OverflowException() { super("underflow"); }
} 
