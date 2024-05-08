package Lab1;

public class ExitMove implements Move {
    @Override
    public void move(Hero hero) {
        System.exit(0);
    }
}
