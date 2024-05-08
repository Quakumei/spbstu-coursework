import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class MyClass {

    @CallMultipleTimes(1)
    private void privatePrint(String message) {
        System.out.println("privatePrint: " + message);
    }
    @CallMultipleTimes(5)
    protected void protectedTimesTwo(int number) {
        System.out.println("protectedTimesTwo: " + number * 2);
    }

    @CallMultipleTimes(3)
    public void publicDivideByTwo(double decimal) {
        System.out.println("Public method called with decimal: " + decimal / 2);
    }

    @CallMultipleTimes(1)
    private void privateVoid() {
        System.out.println("privateVoid");
    }

    @CallMultipleTimes(5)
    protected void protectedVoid() {
        System.out.println("protectedVoid");
    }

    @CallMultipleTimes(3)
    protected void publicVoid() {
        System.out.println("publicVoid");
    }
}
