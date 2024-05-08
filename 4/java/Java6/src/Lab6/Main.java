package Lab6;

public class Main {
    public static void main() {
        startSupervisor(3000, 1000, 2000);
    }

    public static Thread startSupervisor(int randomChangeStateInterval, int workInterval, int pollingTimeout) {
        AbstractProgram program = new AbstractProgram(randomChangeStateInterval, workInterval);
        return new Thread(new Supervisor(program, pollingTimeout));
    }
}