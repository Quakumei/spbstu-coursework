import Lab1.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Lab1Window extends JFrame {
    private final JTextField movePatternTextField;
    private final JButton changeToFlyButton;
    private final JButton changeToFootButton;
    private final JButton changeToHorseButton;
    private final JButton changeToStandStillButton;
    private final JTextField currentXTextField;
    private final JTextField currentYTextField;
    private final JButton makeStepButton;

    private final Hero hero = new Hero(0, 0);

    public Lab1Window() {
        setTitle("Lab1 - Hero");
        setSize(300, 500);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setResizable(false);

        JPanel mainPanel = new JPanel(new GridBagLayout());

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.insets = new Insets(5, 5, 5, 5);

        // Image on top
        ImageIcon imageIcon = new ImageIcon(new ImageIcon("src/Lab1/LePetitPrince.jpg").getImage()
                .getScaledInstance(200, 100, Image.SCALE_SMOOTH));
        JLabel imageLabel = new JLabel(imageIcon);

        // Move Pattern
        JLabel movePatternLabel = new JLabel("Current move pattern:");
        movePatternTextField = new JTextField("Move Pattern Name", 100);
        movePatternTextField.setEditable(false);
        movePatternTextField.setText(hero.getMoveName().getClass().getSimpleName());

        // Change strategy buttons
        changeToFlyButton = createButton("Change to Fly",
                getChangeHeroMoveStrategyListener(new FlyMove()));
        changeToFootButton = createButton("Change to Foot",
                getChangeHeroMoveStrategyListener(new FootMove()));
        changeToHorseButton = createButton("Change to Horse",
                getChangeHeroMoveStrategyListener(new HorseMove()));
        changeToStandStillButton = createButton("Change to Stand Still",
                getChangeHeroMoveStrategyListener(new StandStillMove()));

        // X and Y positions
        JLabel currentXLabel = new JLabel("Current X:");
        currentXTextField = new JTextField(30);
        currentXTextField.setEditable(false);
        currentXTextField.setText(String.valueOf(hero.getX()));
        JLabel currentYLabel = new JLabel("Current Y:");
        currentYTextField = new JTextField(30);
        currentYTextField.setEditable(false);
        currentYTextField.setText(String.valueOf(hero.getY()));

        makeStepButton = createButton("Make a Step", getHeroMakMoveListener());

        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridwidth = 2;
        mainPanel.add(imageLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridwidth = 2;
        mainPanel.add(movePatternLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy = 2;
        mainPanel.add(movePatternTextField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.gridwidth = 2;
        mainPanel.add(changeToFlyButton, gbc);

        gbc.gridy = 4;
        mainPanel.add(changeToFootButton, gbc);

        gbc.gridy = 5;
        mainPanel.add(changeToHorseButton, gbc);

        gbc.gridy = 6;
        mainPanel.add(changeToStandStillButton, gbc);

        gbc.gridx = 0;
        gbc.gridy = 7;
        gbc.gridwidth = 1;
        mainPanel.add(currentXLabel, gbc);

        gbc.gridx = 1;
        mainPanel.add(currentXTextField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 8;
        mainPanel.add(currentYLabel, gbc);

        gbc.gridx = 1;
        mainPanel.add(currentYTextField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 9;
        gbc.gridwidth = 2;
        mainPanel.add(makeStepButton, gbc);

        add(mainPanel);
    }


    private ActionListener getHeroMakMoveListener() {
        return new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                hero.move();
                currentXTextField.setText(String.valueOf(hero.getX()));
                currentYTextField.setText(String.valueOf(hero.getY()));
            }
        };
    }

    private ActionListener getChangeHeroMoveStrategyListener(Move strategy) {
        return new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                hero.setMove(strategy);
                movePatternTextField.setText(hero.getMoveName().getClass().getSimpleName());
            }
        };
    }

    private JButton createButton(String buttonText, ActionListener actionListener) {
        JButton button = new JButton(buttonText);
        button.addActionListener(actionListener);
        return button;
    }
}
