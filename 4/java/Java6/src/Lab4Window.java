import Lab4.InvalidFileFormatException;
import Lab4.Translator;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;


public class Lab4Window extends JFrame {
    private final Translator translator = new Translator();
    private final JTextArea dictionaryField;
    private final JButton translateButton;
    private final JTextArea inputField;
    private final JTextArea translationField;

    public Lab4Window() {
        setTitle("Lab4 - Translator");
        setSize(600, 600);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setResizable(false);

        JPanel mainPanel = new JPanel(new GridLayout(2, 2));

        // Dictionary Field
        dictionaryField = new JTextArea();
        dictionaryField.setText(readFileToString("src/Lab4/dictionary.txt"));
        JScrollPane dictionaryScrollPane = new JScrollPane(dictionaryField);
        mainPanel.add(createTitledPanel("Dictionary", dictionaryScrollPane));

        // Translate Button
        translateButton = new JButton("TRANSLATE");
        translateButton.addActionListener(getTranslateListener());
        mainPanel.add(createTitledPanel("Translate", translateButton));

        // Input Field
        inputField = new JTextArea();
        inputField.setText(readFileToString("src/Lab4/input.txt"));
        JScrollPane inputScrollPane = new JScrollPane(inputField);
        mainPanel.add(createTitledPanel("Input", inputScrollPane));

        // Translation Field
        translationField = new JTextArea();
        translationField.setEditable(false);
        translationField.setLineWrap(true);
        translationField.setWrapStyleWord(true);
        JScrollPane translationScrollPane = new JScrollPane(translationField);

        mainPanel.add(createTitledPanel("Translation", translationScrollPane));


        add(mainPanel);
    }

    private String readFileToString(String filePath) {
        // Read the file content into a byte array
        byte[] fileBytes;
        try {
            fileBytes = Files.readAllBytes(Paths.get(filePath));
            return new String(fileBytes);
        } catch (IOException e) {
            return "";
        }
    }

    private ActionListener getTranslateListener() {
        return new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                translator.flushDictionary();
                String dictionaryString = dictionaryField.getText();
                String output;
                try {
                    translator.extendDictionaryFromString(dictionaryString);
                } catch (InvalidFileFormatException | IOException ex) {
                    output = "Error on reading dictionary";
                    translationField.setText(output);
                    return;
                }
                output = translator.translate(inputField.getText());
                translationField.setText(output);
            }
        };
    }

    private JPanel createTitledPanel(String title, JComponent component) {
        JPanel panel = new JPanel(new BorderLayout());
        panel.setBorder(BorderFactory.createTitledBorder(title));
        panel.setAlignmentY(Component.TOP_ALIGNMENT);
        panel.add(component);
        return panel;
    }
}
