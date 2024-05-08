import java.util.Random;

class AbstractProgram implements Runnable {
    private static ExecutionState state = ExecutionState.UNKNOWN;
    private int randomChangeStateInterval = 1000;
    private int workInterval = 1000;
    private final ExecutionState[] possibleNewStates = {
            ExecutionState.FATAL_ERROR,
            ExecutionState.RUNNING,
            ExecutionState.RUNNING,
            ExecutionState.RUNNING,
            ExecutionState.STOPPING
    };

    public AbstractProgram(int randomChangeStateInterval, int workInterval){
        this.randomChangeStateInterval = randomChangeStateInterval;
        this.workInterval = workInterval;
    }

    synchronized public ExecutionState waitForStateChange(int pollingTimeout) {
        try {
            wait(pollingTimeout);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return state;
    }


    private void randomChangeState() {
        Random random = new Random();
        while (true) {
            System.out.println("Программа.Демон: Начало цикла");
            try {
                Thread.sleep(1);
            } catch (InterruptedException e) {
                // Theoretically unreachable
                e.printStackTrace();
                throw new RuntimeException();
            }

            // Изменение состояния
            synchronized (this) {
                System.out.println("Программа.Демон: Смена состояния");
                System.out.println("Программа.Демон: ExecutionState =  " + state.toString());
                state = possibleNewStates[random.nextInt(possibleNewStates.length)];
                System.out.println("Программа.Демон: ExecutionState --> " + state.toString());
                this.notify();
                if (state == ExecutionState.FATAL_ERROR ||
                        state == ExecutionState.STOPPING) {
                    break;
                }
            }
        }
    }

    private Thread startDaemonRandomChangeState() {
        Thread daemonRandomChangeState = new Thread(this::randomChangeState);
        daemonRandomChangeState.setDaemon(true);
        daemonRandomChangeState.setName("daemonRandomChangeState");
        daemonRandomChangeState.start();
        System.out.println("Программа: Демон успешно запущен");
        return daemonRandomChangeState;
    }

    @Override
    public void run() {
        state = ExecutionState.RUNNING;
        Thread daemonRandomChangeState = startDaemonRandomChangeState();
        while (state == ExecutionState.RUNNING) {
            try {
                // Некоторая работа
                double workSeconds = workInterval / 1000.0;
                System.out.println("Программа: выполняю работу на " + workSeconds + " секунд");
                Thread.sleep(workInterval);
            } catch (InterruptedException e) {
                daemonRandomChangeState.interrupt();
                Thread.currentThread().interrupt();
                System.out.println("Программа: interrupted");
            }
        }
    }
}