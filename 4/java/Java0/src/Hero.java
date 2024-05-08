public class Hero {
    private int x;
    private int y;
    private Move move;

    public Hero(int x, int y) {
        this.x = x;
        this.y = y;
    }
    public void setMove(Move Move) {
        this.move = Move;
    }
    public Move getMoveName() {
        return move;
    }
    public void printPosition() {
        System.out.printf("Hero (x:%d, y:%d)%n", this.x, this.y);
    }
    public void move() {
        if (move != null) {
            move.move(this);
        }
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }
}