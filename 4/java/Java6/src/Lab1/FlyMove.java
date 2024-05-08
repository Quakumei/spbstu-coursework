package Lab1;

public class FlyMove implements Move {
    @Override
    public void move(Hero hero) {
        hero.setX(hero.getX() + 5);
        hero.setY(hero.getY() + 5);
    }
}
