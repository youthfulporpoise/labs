import java.time.Year;
import java.util.Scanner;

class II_3 {
    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        kb.useDelimiter("\n");

        System.out.print("Number of managers: ");
        int managerNumber = kb.nextInt();
        Manager[] managers = new Manager[managerNumber];
        for (int i = 0; i < managerNumber; i++) {
            System.out.println("\nManager #" + (i + 1) + ":");
            System.out.print("Name: "); String name = kb.next();
            System.out.print("Age: "); int age = kb.nextInt();
            System.out.print("Phone number: "); int phoneNumber = kb.nextInt();
            System.out.print("Address: "); String address = kb.next();
            System.out.print("Salary: "); double salary = kb.nextDouble();
            System.out.print("Department: "); String dept = kb.next();
            System.out.print("Specialization: "); String spec = kb.next();
            managers[i] = new Manager(name, age, phoneNumber, address, salary,
                                      dept, spec);
        }
        System.out.print("\nNumber of officers: ");
        int officerNumber = kb.nextInt();
        Officer[] officers = new Officer[officerNumber];
        for (int i = 0; i < officerNumber; i++) {
            System.out.println("\nOfficer #" + (i + 1));
            System.out.print("Name: "); String name = kb.next();
            System.out.print("Age: "); int age = kb.nextInt();
            System.out.print("Phone number: "); int phoneNumber = kb.nextInt();
            System.out.print("Address: "); String address = kb.next();
            System.out.print("Salary: "); double salary = kb.nextDouble();
            System.out.print("Department: "); String dept = kb.next();
            System.out.print("Specialization: "); String spec = kb.next();
            officers[i] = new Officer(name, age, phoneNumber, address, salary,
                                      dept, spec);
        }

        if (managerNumber != 0 ) {
            System.out.println("\nMANAGERS: ");
            for (Manager m : managers) System.out.println("" + m + "\n");
        }
        if (officerNumber != 0) {
            System.out.println("\nOFFICERS: ");
            for (Officer o : officers) System.out.println("" + o + "\n");
        }
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

class Officer extends Employee {
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

class Manager extends Employee {
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
