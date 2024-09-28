import java.util.Scanner;
import java.util.ArrayList;

class Main_30 {
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
    private T[] stack;
    int size;
    private int top;

    public Stack(int n) { 
        this.size = n;
        stack = (T[]) new Object[size];
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
}

class EmptyException extends Exception {
    EmptyException() { super("the structure is empty"); }
}

class FullException extends Exception {
    FullException() { super("the structure is full"); }
} 
