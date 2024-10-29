/*
 * Write a Java program to demonstrate synchornization using synchornized
 * keyword.
 */

class Main {
    public static void main (String[] args) {
        Thread t1 = new Thread(new T1("FATHER"));
        Thread t2 = new Thread(new T1("SON"));
        Thread t3 = new Thread(new T1("HOLY SPIRIT"));
        t1.start(); t2.start(); t3.start();
    }
}

class Action {
    public static synchronized void perform(String name) {
        System.out.print(name + ": ");
        for (int i = 0; i < 10; ++i) System.out.print(i + " ");
        System.out.println("");
    }
}

class T1 implements Runnable {
    String name;
    T1(String name) { this.name = name; }
    public void run() { Action.perform(name); }
}
