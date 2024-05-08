import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class Main {
    public static void main(String[] args) {
        MyClass obj = new MyClass();
        Method[] methods = obj.getClass().getDeclaredMethods();
        for (Method method : methods) {
            // Игнорируем метод, если аннотации нет
            if (!method.isAnnotationPresent(CallMultipleTimes.class)) {
                continue;
            }

            // Получаем поле аннотации
            int value = method.getAnnotation(CallMultipleTimes.class).value();
            for (int i = 0; i < value; i++) {
                method.setAccessible(true);
                try {
                    // В зависимости от сигнатуры метода, вызываем
                    if (method.getParameterCount() == 1 && method.getParameterTypes()[0] == String.class) {
                        method.invoke(obj, "Hello world");
                    } else if (method.getParameterCount() == 1 && method.getParameterTypes()[0] == int.class) {
                        method.invoke(obj, 256);
                    } else if (method.getParameterCount() == 1 && method.getParameterTypes()[0] == double.class) {
                        method.invoke(obj, 2.718281828);
                    } else if (method.getParameterCount() == 0) {
                        method.invoke(obj);
                    }
                } catch (InvocationTargetException | IllegalAccessException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
