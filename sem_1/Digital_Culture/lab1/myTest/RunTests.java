package myTest;

public class RunTests {
    public static void main(String[] args) {
        try {
            TestClass.test_number_0();
            TestClass.test_number_1();

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
