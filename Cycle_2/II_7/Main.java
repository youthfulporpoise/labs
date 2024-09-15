import java.util.Scanner;
import java.util.ArrayList;

class Main {
    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Stack size: "); int n = kb.nextInt();
        Stack<Character> stack = new Stack<Character>(n);

        int choice;
        do {
            System.out.print("\n" +
                    "(1)  Push\n" +
                    "(2)  Pop\n" +
                    "(3)  Display\n" +
                    "(-1) Quit\n" +
                    "Choice: ");
            choice = kb.nextInt();
            switch (choice) {
                case 1:
                    System.out.print("Element: ");
                    try { stack.push(kb.next().charAt(0)); }
                    catch (StackFullException e) {
                        System.out.println("\nThe stack is full.");
                        continue;
                    } break;
                case 2:
                    try { System.out.println("\nElement: " + stack.pop()); }
                    catch (StackEmptyException e) {
                        System.out.println("\nThe stack is empty.");
                        continue;
                    } break;
                case (3):
                    System.out.println("Stack: " + stack);
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
    T[] stack;
    int n;
    int top;

    public Stack(int n) { 
        this.n = n;
        stack = (T[]) new Object[n];
        top = 0;
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
    public void push(T x) throws StackFullException { 
        if (top < n) stack[top++] = x;
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
