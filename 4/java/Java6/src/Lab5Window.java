import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

import static Lab5.Main.*;

public class Lab5Window extends JFrame {
    private final JTextField integerInputField;
    private final JTextField stringInputField;
    private final JTextArea integerOutputArea;
    private final JTextArea stringOutputArea;

    public Lab5Window() {
        setTitle("Lab5 - Stream API");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setResizable(false);

        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));

        // Integer input section
        JPanel integerInputPanel = createInputPanel("Input Integer List (comma-separated):");
        integerInputField = createTextField();
        integerInputField.setText("1, 2, 3");
        integerInputPanel.add(integerInputField);
        mainPanel.add(integerInputPanel);

        // Integer output section
        JPanel integerOutputPanel = createOutputPanel("Integer Output:");
        integerOutputArea = createTextArea();
        integerOutputPanel.add(new JScrollPane(integerOutputArea));
        mainPanel.add(integerOutputPanel);

        // String input section
        JPanel stringInputPanel = createInputPanel("Input String List (comma-separated):");
        stringInputField = createTextField();
        stringInputField.setText("Школа, Работа, торт, терпение");
        stringInputPanel.add(stringInputField);
        mainPanel.add(stringInputPanel);

        // String output section
        JPanel stringOutputPanel = createOutputPanel("String Output:");
        stringOutputArea = createTextArea();
        stringOutputPanel.add(new JScrollPane(stringOutputArea));
        mainPanel.add(stringOutputPanel);

        // Process buttons section
        JPanel buttonPanel = new JPanel(new FlowLayout());
        JButton processIntegersButton = new JButton("Process Integers");
        processIntegersButton.addActionListener(getProcessIntegersListener());
        buttonPanel.add(processIntegersButton);

        JButton processStringsButton = new JButton("Process Strings");
        processStringsButton.addActionListener(getProcessStringsListener());
        buttonPanel.add(processStringsButton);

        mainPanel.add(buttonPanel);

        add(mainPanel);
    }

    private ActionListener getProcessIntegersListener() {
        return new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                processIntegers();
            }
        };
    }

    private ActionListener getProcessStringsListener() {
        return new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                processStrings();
            }
        };
    }

    private JPanel createInputPanel(String title) {
        JPanel panel = new JPanel();
        panel.setBorder(BorderFactory.createTitledBorder(title));
        panel.setLayout(new FlowLayout(FlowLayout.LEFT));
        return panel;
    }

    private JPanel createOutputPanel(String title) {
        JPanel panel = new JPanel();
        panel.setBorder(BorderFactory.createTitledBorder(title));
        panel.setLayout(new BorderLayout());
        return panel;
    }

    private JTextField createTextField() {
        return new JTextField(20);
    }

    private JTextArea createTextArea() {
        JTextArea textArea = new JTextArea(5, 30);
        textArea.setEditable(false);
        return textArea;
    }

    private void processIntegers() {
        String input = integerInputField.getText();
        List<Integer> integerList = parseIntegerList(input);

        String result = "Последний элемент коллекции: " + getLastElement(integerList) + "\n"
                + "Среднее: " + getAverage(integerList) + "\n"
                + "Уникальные квадраты: " + getUniqueSquares(integerList) + "\n";

        integerOutputArea.setText(result);

    }

    private void processStrings() {
        String input = stringInputField.getText();
        List<String> stringList = parseStringList(input);
        String result = "Последний элемент коллекции: " +
                getLastElement(stringList) + "\n"
                + "Отсортированные по алфавиту и начинающиеся на \"т\": " +
                filterAndSortStringsStartingWith(stringList, 'т') + "\n"
                + "Верхний регистр с префиксом _new_: " +
                convertToUpperCaseWithPrefix(stringList) + "\n";

        stringOutputArea.setText(result);
    }

    private List<Integer> parseIntegerList(String input) {
        List<Integer> integerList = new ArrayList<>();
        String[] integerStrings = input.split(",\\s*");
        for (String integerString : integerStrings) {
            if (integerString.length() == 0 || !Character.isDigit(integerString.charAt(0))) {
                continue;
            }
            int value = Integer.parseInt(integerString);
            integerList.add(value);
        }
        return integerList;
    }

    private List<String> parseStringList(String input) {
        if (Objects.equals(input, "")) {
            return new ArrayList<>();
        }
        String[] stringArray = input.split(",\\s*");
        return new ArrayList<>(Arrays.asList(stringArray));
    }
}
