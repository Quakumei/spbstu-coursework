import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.PrintStream;

public class Lab6Window extends JFrame {
    private final JButton runButton;
    private final JTextArea logArea;
    private final JTextField changeStateIntervalField;
    private final JTextField workIntervalField;
    private final JTextField pollingTimeoutField;


    public Lab6Window() {
        setTitle("Lab6 - Threading");
        setSize(400, 600);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setResizable(false);

        JPanel mainPanel = new JPanel(new BorderLayout());

        // Parameter Panel
        JPanel parameterPanel = new JPanel(new GridLayout(3, 2));
        parameterPanel.setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));

        JLabel changeStateIntervalLabel = new JLabel("Change state interval:");
        changeStateIntervalField = new JTextField("3000");
        JLabel workIntervalLabel = new JLabel("Work longevity:");
        workIntervalField = new JTextField("1000");
        JLabel pollingTimeoutLabel = new JLabel("Polling Timeout:");
        pollingTimeoutField = new JTextField("2000");

        parameterPanel.add(changeStateIntervalLabel);
        parameterPanel.add(changeStateIntervalField);
        parameterPanel.add(workIntervalLabel);
        parameterPanel.add(workIntervalField);
        parameterPanel.add(pollingTimeoutLabel);
        parameterPanel.add(pollingTimeoutField);

        mainPanel.add(parameterPanel, BorderLayout.NORTH);

        // Log Area
        logArea = new JTextArea();
        logArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(logArea);
        mainPanel.add(scrollPane, BorderLayout.CENTER);

        // Run Button
        runButton = new JButton("RUN");
        runButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                runButton.setEnabled(false);
                redirectSystemOut();
                System.out.println("================================");
                int randomChangeStateInterval = Integer.parseInt(changeStateIntervalField.getText());
                int workInterval = Integer.parseInt(workIntervalField.getText());
                int pollingTimeout = Integer.parseInt(pollingTimeoutField.getText());
                SwingUtilities.invokeLater(Lab6.Main.startSupervisor(randomChangeStateInterval, workInterval, pollingTimeout));
                System.setOut(System.out);
                runButton.setEnabled(true);
            }
        });
        mainPanel.add(runButton, BorderLayout.SOUTH);

        add(mainPanel);
    }

    private void redirectSystemOut() {
        PrintStream printStream = new PrintStream(new CustomOutputStream(logArea));
        System.setOut(printStream);
    }
}