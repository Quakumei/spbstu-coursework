import java.util.ArrayList;
import java.util.List;

public class Main {
    private static void segregate(List<? extends Chordates> unsortedCollection,
                                  List<? super HedgehogOrdinary> hedgehogCollection,
                                  List<? super Manul> manulCollection,
                                  List<? super Lynx> lynxCollection) {
        for (Chordates in : unsortedCollection) {
            if (in instanceof HedgehogOrdinary) {
                hedgehogCollection.add((HedgehogOrdinary) in);
            } else if (in instanceof Manul) {
                manulCollection.add((Manul) in);
            } else if (in instanceof Lynx) {
                lynxCollection.add((Lynx) in);
            }
        }
    }

    private static void printCollections(List<? extends Chordates> hedgehogCollection,
                                         List<? extends Chordates> manulCollection,
                                         List<? extends Chordates> lynxCollection) {
        System.out.println("Ежи:");
        for (Chordates hedgehog : hedgehogCollection) {
            hedgehog.info();
        }
        System.out.println("\nМанулы:");
        for (Chordates manul : manulCollection) {
            manul.info();
        }
        System.out.println("\nРыси:");
        for (Chordates lynx : lynxCollection) {
            lynx.info();
        }

    }


    public static void main(String[] args) {
        List<Chordates> chordatesList = new ArrayList<>();

        chordatesList.add(new Manul());
        chordatesList.add(new Manul());
        chordatesList.add(new Manul());
        chordatesList.add(new Manul());
        chordatesList.add(new HedgehogOrdinary());
        chordatesList.add(new HedgehogOrdinary());
        chordatesList.add(new HedgehogOrdinary());
        chordatesList.add(new Lynx());
        chordatesList.add(new Lynx());
        chordatesList.add(new Lynx());
        chordatesList.add(new Lynx());
        chordatesList.add(new Lynx());

        // 1
        List<Chordates> chordatesList1 = new ArrayList<>();
        List<Manul> manulList1 = new ArrayList<>();
        List<Feline> felineList1 = new ArrayList<>();

        segregate(chordatesList, chordatesList1, manulList1, felineList1);
        System.out.println("--- 1 ---");
        printCollections(chordatesList1, manulList1, felineList1);

        // 2
        List<Hedgehogs> hedgehogList2 = new ArrayList<>();
        List<Feline> felineList2 = new ArrayList<>();
        List<Predatory> predatoryList2 = new ArrayList<>();

        segregate(chordatesList, hedgehogList2, felineList2, predatoryList2);
        System.out.println("\n--- 2 ---");
        printCollections(hedgehogList2, felineList2, predatoryList2);


        // 3
        List<Insectivora> insectivoraList3 = new ArrayList<>();
        List<Predatory> predatoryList31 = new ArrayList<>();
        List<Predatory> predatoryList32 = new ArrayList<>();

        segregate(chordatesList, insectivoraList3, predatoryList31, predatoryList32);
        System.out.println("\n--- 3 ---");
        printCollections(insectivoraList3, predatoryList31, predatoryList32);


        // 4 - показываем, что также работает, если srcCollection - наследник Chordates
        List<Hedgehogs> hedgehogsList4 = new ArrayList<>();
        List<Predatory> predatoryList41 = new ArrayList<>();
        List<Predatory> predatoryList42 = new ArrayList<>();

        // ! manulList1
        segregate(manulList1, hedgehogsList4, predatoryList41, predatoryList42);
        System.out.println("\n--- 4 ---");
        printCollections(hedgehogsList4, predatoryList41, predatoryList42);
    }
}
