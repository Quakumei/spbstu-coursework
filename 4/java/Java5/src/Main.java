public class Main {
    public static void main(String[] args) {
        new Thread(
                new Supervisor(
                        new AbstractProgram(1, 1000),
                        1000
                )
        ).start();
    }
}