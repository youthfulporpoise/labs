import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Stack size: "); int n = kb.nextInt();
        Stack<Double> stack = new Stack<Double>(n);

        int choice;
        do {
            System.out.print("\n" +
                    "(1)  Push\n" +
                    "(2)  Pop\n" +
                    "(3)  Display\n" +
                    "(-1) Quit\n" +
                    "Choice:");
            choice = kb.nextInt();
            switch (choice) {
                case 1:
                    System.out.print("Element: ");
                    try { stack.push(kb.nextDouble()); }
                    catch (StackFullException e) {
                        System.out.println("The stack is full.");
                        continue;
                    } break;
                case 2:
                    try { System.out.println("Element: " + stack.pop()); }
                    catch (StackEmptyException e) {
                        System.out.println("The stack is empty.");
                        continue;
                    } break;
                case (3):
                    System.out.println("Stack: " + stack);
                    break;
                case (-1):
                    return;
                default:
                    System.out.println("I don‘t understand.");
                    continue;
            }
        } while (choice != -1);
    }
}

class Stack<T> {
    T[] stack;
    int top;
    int n;

    public Stack(int n) { 
        this.n = n;
        stack = new T[n];
        top = 0;
    }

    @Override
    public String toString() {
        String s = new String("");
        if (top == 0) return "-/-";
        for (int i = top; i >= 0;) s += stack[--i];
        return s;
    }
    public void push(T x) throws StackFullException { 
        if (top <= n) stack[top++] = x;
        else throw new StackFullException();
    }
    public T pop() throws StackEmptyException {
        if (top > 0) return stack[--top];
        else throw new StackEmptyException();
    }
}

class StackEmptyException extends Exception {
    StackEmptyException() { super("the stack is empty"); }
}

class StackFullException extends Exception {
    StackFullException() { super("the stack is full"); }
} 
