import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class MainApp {
    private final JFrame mainFrame;
    private final JButton lab1Button;
    private final JButton lab2Button;
    private final JButton lab3Button;
    private final JButton lab4Button;
    private final JButton lab5Button;
    private final JButton lab6Button;

    public MainApp() {
        mainFrame = new JFrame("Main Window");
        lab1Button = createButton("Lab1", Lab1Window.class);
        lab2Button = createButton("Lab2", Lab2Window.class);
        lab3Button = createButton("Lab3", Lab3Window.class);
        lab4Button = createButton("Lab4", Lab4Window.class);
        lab5Button = createButton("Lab5", Lab5Window.class);
        lab6Button = createButton("Lab6", Lab6Window.class);

        mainFrame.setLayout(new GridLayout(6, 1));
        mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        mainFrame.setSize(200, 300);
        mainFrame.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new MainApp();
            }
        });
    }

    private JButton createButton(String buttonText, Class<? extends JFrame> windowClass) {
        JButton button = new JButton(buttonText);
        mainFrame.add(button);
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                lockButtons();
                openNewWindow(windowClass);
            }
        });
        return button;
    }

    private void lockButtons() {
        lab1Button.setEnabled(false);
        lab2Button.setEnabled(false);
        lab3Button.setEnabled(false);
        lab4Button.setEnabled(false);
        lab5Button.setEnabled(false);
        lab6Button.setEnabled(false);
    }

    private void unlockButtons() {
        lab1Button.setEnabled(true);
        lab2Button.setEnabled(true);
        lab3Button.setEnabled(true);
        lab4Button.setEnabled(true);
        lab5Button.setEnabled(true);
        lab6Button.setEnabled(true);
    }

    private void openNewWindow(Class<? extends JFrame> windowClass) {
        try {
            JFrame newFrame = windowClass.getDeclaredConstructor().newInstance();
            newFrame.addWindowListener(new WindowAdapter() {
                @Override
                public void windowClosing(WindowEvent e) {
                    unlockButtons();
                }
            });
            newFrame.setVisible(true);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}

