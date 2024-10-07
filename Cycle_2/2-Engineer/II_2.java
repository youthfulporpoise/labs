class II_2 {
    public static void main(String[] args) {
        Engineer x = new Engineer();
        x.calcSalary();
    }
}

class Employee {
    public void display() {
        System.out.println("Class: Employee");
    }
    public void calcSalary() {
        System.out.println("Salary of an employee: INR " + 10000);
    }
}

final class Engineer extends Employee {
    public void calcSalary() {
        System.out.println("Salary of an engineer: INR " + 20000);
        super.calcSalary();
    }
}
