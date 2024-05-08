package Lab4;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashMap;
import java.util.List;
import java.util.Vector;

public class Translator {
    private final HashMap<String, String> dictionary = new HashMap<>();

    public Translator(String filename) throws IOException, InvalidFileFormatException {
        extendDictionaryFromFile(new File(filename));
    }

    public Translator() {
    }

    public void flushDictionary() {
        dictionary.clear();
    }

    public void extendDictionaryFromString(String text) throws InvalidFileFormatException, IOException {
        extendDictionary(new BufferedReader(new StringReader(text)));
    }

    public void extendDictionaryFromFile(File file) throws IOException, InvalidFileFormatException {
        extendDictionary(new BufferedReader(new FileReader(file)));
    }

    private void extendDictionary(BufferedReader bufferedReader) throws IOException, InvalidFileFormatException {
        try (BufferedReader reader = bufferedReader) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.toLowerCase().split("\\s*\\|\\s*");
                if (parts.length == 2) {
                    String key = parts[0];
                    String value = parts[1];
                    dictionary.put(key, value);
                } else {
                    throw new InvalidFileFormatException(line);
                }
            }
        }
    }

    public String translateFile(String filename) throws FileReadException {
        try {
            return Files.readAllLines(Path.of(filename), StandardCharsets.UTF_8)
                    .stream()
                    .map(this::translate)
                    .reduce((l, r) -> l + "\n" + r).orElse("");
        } catch (IOException e) {
            throw new FileReadException("Ошибка чтения файла");
        }
    }

    public boolean isPunctuationToken(String token) {
        return token.length() == 1 && !Character.isLetterOrDigit(token.charAt(0));
    }

    public String translate(String input) {
        List<String> result = new Vector<String>();
        String[] tokens = input.split("\\s+|(?<=\\p{Punct})|(?=\\p{Punct})");

        for (int i = 0; i < tokens.length; i++) {
            String token = tokens[i];
            String tokenKey = token.toLowerCase();

            // Case 0. Punctuation
            if (isPunctuationToken(tokenKey)) {
                result.add(tokenKey);
                continue;
            }

            // Case 1. Not in dictionary
            if (!dictionary.containsKey(tokenKey)) {
                result.add(token);
                continue;
            }

            // Case 2. In dictionary, need to check if longer version is in dictionary
            String longestKey = tokenKey;
            int iAdditional = 0;

            while (
                    i + iAdditional + 1 < tokens.length &&
                            dictionary.containsKey(longestKey + " " + tokens[i + iAdditional + 1].toLowerCase())
            ) {
                longestKey = longestKey + " " + tokens[i + iAdditional + 1].toLowerCase();
                iAdditional += 1;
            }

            // If first letter is capitalized, keep it that way
            String translatedToken = dictionary.get(longestKey);
            if (Character.isUpperCase(token.charAt(0))) {
                translatedToken = translatedToken.substring(0, 1).toUpperCase() + translatedToken.substring(1);
            }

            result.add(translatedToken);
            i += iAdditional;
        }
        return result.stream().reduce((l, r) -> isPunctuationToken(r) ? l + r : l + ' ' + r).orElseThrow();
    }
}