class II_3 {
    public static void main(String[] args) {
    }
}

class Employee {
    String name;
    int age;
    long phoneNumber;
    String address;
    double salary;

    public void printSalary() {
        System.out.println("Salary: " + this.salary);
    }
}

class Officer extends Employee {
    String specialization;
    String department;
}

class Manager extends Employee {
    String specialization;
    String department;
}
