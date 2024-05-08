import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.PrintStream;

public class Lab2Window extends JFrame {
    private final JTextArea logArea;
    private final JButton runButton;

    public Lab2Window() {
        setTitle("Lab2 - Annotations");
        setSize(400, 500);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setResizable(false);

        JPanel mainPanel = new JPanel(new BorderLayout());

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
                Lab2.Main.main();
                System.setOut(System.out);
            }
        });
        mainPanel.add(runButton, BorderLayout.NORTH);

        add(mainPanel);
    }

    private void redirectSystemOut() {
        PrintStream printStream = new PrintStream(new CustomOutputStream(logArea));
        System.setOut(printStream);
    }
}
