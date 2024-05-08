public class HorseMove implements Move {
    @Override
    public void move(Hero hero) {
        hero.setX(hero.getX()+3);
        hero.setY(hero.getY()+3);
    }
}
