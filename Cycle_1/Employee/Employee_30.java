class Main {
    public static void main(String[] args) {
        Employee e = new Employee();
        // ...
    }
}

class Employee {
    String name;
    int age;
    String address;
    int phone_number;
    float salary;

    void printSalaryOf() {
        System.out.println("" + this.salary);
    }
    void printSalaryOf(Employee e) {
        System.out.println("" + e.salary);
    }
}
