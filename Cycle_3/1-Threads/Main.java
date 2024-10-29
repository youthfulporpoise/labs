/*
 * Write a Java program 3 threads:
 *   - t1 creates positive integers <10;
 *   - t2 prints odd numbers between 1 and 5;
 *   - t3 pritns even numbers between 1 and 5.
 */

class Main {
    public static void main (String[] args) {
        Thread t1 = new Thread(new T1());
        Thread t2 = new Thread(new T2());
        Thread t3 = new Thread(new T3());
        t1.start(); t2.start(); t3.start();
    }
}

class T1 implements Runnable {
    public void run() {
        for (int i = 0; i < 10; ++i) System.out.print(i + " ");
        System.out.println("");
    }
}

class T2 implements Runnable {
    public void run() {
        for (int i = 1; i <= 5; i += 2) System.out.print(i + " ");
        System.out.println("");
    }
}

class T3 implements Runnable {
    public void run() {
        for (int i = 2; i <= 5; i += 2) System.out.print(i + " ");
        System.out.println("");
    }
}
