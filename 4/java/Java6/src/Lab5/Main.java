package Lab5;

import java.util.*;
import java.util.stream.Collectors;

public class Main {
    public static double getAverage(List<Integer> numbers) {
        // метод, возвращающий среднее значение списка целых чисел;
        return numbers.stream()
                .mapToInt(Integer::intValue)
                .average()
                .orElse(0.0);
    }

    public static List<String> convertToUpperCaseWithPrefix(List<String> strings) {
        // метод, приводящий все строки в списке в верхний регистр и
        // добавляющий к ним префикс «_new_»;
        return strings.stream()
                .map(str -> "_new_" + str.toUpperCase())
                .collect(Collectors.toList());
    }

    public static List<Integer> getUniqueSquares(List<Integer> numbers) {
        // метод, возвращающий список квадратов всех встречающихся
        // только один раз элементов списка;
        return numbers.stream()
                .filter(num -> Collections.frequency(numbers, num) == 1)
                .map(num -> num * num)
                .collect(Collectors.toList());
    }

    public static List<String> filterAndSortStringsStartingWith(
            Collection<String> strings, char letter) {
        // метод, принимающий на вход коллекцию строк и возвращает все
        // строки, начинающиеся с заданной буквы, отсортированные по
        //  алфавиту;
        return strings.stream()
                .filter(str -> str.startsWith(String.valueOf(letter)))
                .sorted()
                .collect(Collectors.toList());
    }

    public static <T> T getLastElement(Collection<T> collection) {
        // метод, принимающий на вход коллекцию и возвращающий ее
        // последний элемент или кидающий исключение, если коллекция
        // пуста;
        return collection.stream()
                .reduce((first, second) -> second)
                .orElseThrow(NoSuchElementException::new);
    }

    public static int sumEvenNumbers(int[] numbers) {
        // метод, принимающий на вход массив целых чисел, возвращающий
        // сумму чётных чисел или 0, если чётных чисел нет;
        return Arrays.stream(numbers)
                .filter(num -> num % 2 == 0)
                .sum();
    }

    public static Map<Character, String> convertToMap(List<String> strings) {
        // метод, преобразовывающий все строки в списке в Map, где первый
        // символ – ключ, оставшиеся – значение;
        return strings.stream()
                .collect(
                        Collectors.toMap(
                                str -> str.charAt(0),
                                str -> str.substring(1),
                                (exist, newcomer) -> newcomer
                        ));
    }

    public static void main(String[] args) {
        // Пример использования методов:

        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 5, 7, 8, 9, 10);
        System.out.println("Среднее: " + getAverage(numbers));

        List<String> strings = Arrays.asList("ОоП", "fooBar", "Java is cool");
        List<String> convertedStrings = convertToUpperCaseWithPrefix(strings);
        System.out.println("Преобразованные строки: " + convertedStrings);

        List<Integer> uniqueSquares = getUniqueSquares(numbers);
        System.out.println("Уникальные квадраты: " + uniqueSquares);

        char c = 'b';
        List<String> filteredAndSortedStrings = filterAndSortStringsStartingWith(strings, c);
        System.out.println("Начинающиеся с '" + c + "' в алфавитном порядке: " + filteredAndSortedStrings);

        List<String> emptyList = new ArrayList<>();
        try {
            String lastElement = getLastElement(emptyList);
            System.out.println("Последний элемент: " + lastElement);
        } catch (NoSuchElementException e) {
            System.out.println("Предоставлен пустой список");
        }

        emptyList.add("1");
        emptyList.add("2");
        emptyList.add("3");
        try {
            String lastElement = getLastElement(emptyList);
            System.out.println("Последний элемент: " + lastElement);
        } catch (NoSuchElementException e) {
            System.out.println(e.getMessage());
        }

        int[] intArray = {1, 2, 3, 4, 5};
        int sumOfEvenNumbers = sumEvenNumbers(intArray);
        System.out.println("Сумма четных: " + sumOfEvenNumbers);

        List<String> stringList = Arrays.asList("aApple", "bBanana", "cCherry");
        Map<Character, String> stringMap = convertToMap(stringList);
        System.out.println("Полученный словарь: " + stringMap);
    }
}