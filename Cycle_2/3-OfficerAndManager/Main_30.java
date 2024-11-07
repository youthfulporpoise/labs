import java.time.Year;
import java.util.Scanner;

class Main_30 {
    public static void main(String[] args) {
        Employee officer = new Officer("Rahul", 27, 0, "Breach Candy, Mumbai", 20000,
                                       "Advertisement", "Copywriter");
        Employee manager = new Manager("Vidya", 38, 0, "Greater Kailash, Delhi",
                                        56000, "Advertisement", "Art Director");
        System.out.println("MANAGER\n" + manager);
        System.out.println("\nOFFICER\n" + officer);
    }
}

class Employee {
    String name;
    int age;
    int phoneNumber;
    String address;
    double salary;

    Employee(String name, int age, int phoneNumber,
             String address, double salary) {
        this.name = name; this.age = age; this.phoneNumber = phoneNumber;
        this.address = address; this.salary = salary;
    }

    public void printSalary() {
        System.out.println("Salary: ₹" + this.salary);
    }
    
    public String toString() {
        return "\t" + name + " (b. " + (Year.now().getValue() - age) + ") \n\t" +
               (address.isBlank() ? "-/-" : address) + "\n\t" +
               "Phone: " + (phoneNumber == 0 ? "-/-" : phoneNumber) + "\n\t" +
               "Salary: ₹" + salary;
    }
}

final class Officer extends Employee {
    String department;
    String specialization;

    Officer(String name, int age, int phoneNumber,
            String address, double salary,
            String department, String specialization) {
        super(name, age, phoneNumber, address, salary);
        this.department = department; this.specialization = specialization;
    }

    @Override
    public String toString() {
        return super.toString() + "\n\t" +
               "(" + department + ", " + specialization + ")";
    }
}

final class Manager extends Employee {
    String department;
    String specialization;

    Manager(String name, int age, int phoneNumber,
            String address, double salary,
            String department, String specialization) {
        super(name, age, phoneNumber, address, salary);
        this.department = department; this.specialization = specialization;
    }

    @Override
    public String toString() {
        return super.toString() + "\n\t" +
               "(" + department + ", " + specialization + ")";
    }
}
