package Lab4;

import java.io.IOException;

public class Main {

    public static void main(String[] args) {
        final String DICTIONARY_FILENAME = "src/dictionary.txt";
        final String INPUT_FILENAME = "src/input.txt";
        try {
            Translator translator = new Translator(DICTIONARY_FILENAME);
            System.out.println(translator.translateFile(INPUT_FILENAME));
        } catch (IOException | InvalidFileFormatException | FileReadException e) {
            e.printStackTrace();
        }
    }
}