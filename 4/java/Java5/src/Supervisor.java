class Supervisor implements Runnable {
    private final AbstractProgram abstractProgram;
    private final int pollingTimeout;
    private Thread abstractProgramThread;

    public Supervisor(AbstractProgram abstractProgram, int pollingTimeout) {
        this.abstractProgram = abstractProgram;
        this.pollingTimeout = pollingTimeout;
    }
    private void startProgram() {
        abstractProgramThread = new Thread(abstractProgram);
        abstractProgramThread.start();
    }
    @Override
    public void run() {
        System.out.println("Супервизор: run()");
        startProgram();

        while(true) {
            ExecutionState executionState = abstractProgram.waitForStateChange(pollingTimeout);
            System.out.println("Супервизор: получено состояние " + executionState.toString());
            switch (executionState) {
                case FATAL_ERROR -> stopProgram();
                case STOPPING -> runProgram();
                default -> idle();
            }
            if (executionState == ExecutionState.FATAL_ERROR) {
                System.out.println("Супервизор: выход...");
                break;
            }
        }

    }

    private void idle(){
        System.out.println("Супервизор: действий не требуется");
    }
    private void runProgram() {
        System.out.println("Супервизор: перезапуск программы...");
        abstractProgramThread.interrupt();
        startProgram();
    }

    private void stopProgram() {
        System.out.println("Супервизор: остановка программы...");
        abstractProgramThread.interrupt();
    }
}