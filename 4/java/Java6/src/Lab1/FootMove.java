package Lab1;

public class FootMove implements Move {
    @Override
    public void move(Hero hero) {
        hero.setX(hero.getX() + 2);
        hero.setY(hero.getY() + 2);
    }
}
