package Lab1;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Game {

    public static Move readMove() {
        Map<Integer, Move> moveStrategies = new HashMap<>();
        moveStrategies.put(0, new StandStillMove());
        moveStrategies.put(1, new FlyMove());
        moveStrategies.put(2, new FootMove());
        moveStrategies.put(3, new HorseMove());
        moveStrategies.put(4, new ExitMove());

        System.out.println("Select Move:");
        for (Map.Entry<Integer, Move> entry : moveStrategies.entrySet()) {
            System.out.println(entry.getKey() + "\t:\t" + entry.getValue().getClass().getSimpleName());
        }

        Scanner scn = new Scanner(System.in);
        int choice;

        try {
            choice = Integer.parseInt(scn.nextLine());
        } catch (NumberFormatException e) {
            System.err.println("Invalid input, standing still");
            return moveStrategies.get(0);
        }

        if (moveStrategies.containsKey(choice)) {
            return moveStrategies.get(choice);
        } else {
            System.err.println("No such move, standing still");
            return moveStrategies.get(0);
        }
    }

    public static void main(String[] args) {
        Hero hero = new Hero(0, 0);
        while (true) {
            hero.printPosition();
            Move newMove = readMove();
            hero.setMove(newMove);

            System.out.printf("Move using: %s%n", hero.getMoveName().getClass().getSimpleName());
            hero.move();
        }
    }
}
