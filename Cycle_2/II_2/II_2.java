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
        System.out.println("Salary of an employee: " + 10000);
    }
}

class Engineer extends Employee {
    public void calcSalary() {
        System.out.println("Salary of an engineer: " + 20000);
        super.calcSalary();
    }
}
