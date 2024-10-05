class Main_30 {
    public static void main(String[] args) {
        String[] ss = {"Oracle", "Sun Microsystems", null};
        for (int i = 0; i <= 3; ++i) {
            System.out.println(i + "");
            try { System.out.println(ss[1 / i + i].length() + ""); }
            catch (ArithmeticException e) {
                System.out.println("An ArithmeticException was caught.");
                continue;
            } catch (NullPointerException e) {
                System.out.println("A NullpointerException was caught.");
                continue;
            } catch (ArrayIndexOutOfBoundsException e) {
                System.out.println("An ArrayOutOfBoundsException was caught.");
                continue;
            }
        }
    }
}
