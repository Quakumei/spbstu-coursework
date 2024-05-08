import Lab3.Chordates;
import Lab3.HedgehogOrdinary;
import Lab3.Lynx;
import Lab3.Manul;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static Lab3.Main.segregate;

public class Lab3Window extends JFrame {
    private final JButton sortButton;
    private final JComboBox<String> animalComboBox;
    private final JButton addAnimalButton;
    private final Map<String, Class<? extends Chordates>> classMap = new HashMap<>();

    private final JList<String> unsortedChordatesList;
    private final JList<String> manulList;
    private final JList<String> ordinaryHedghogsList;


    private final JList<String> lynxesList;
    private final DefaultListModel<String> unsortedListModel;
    private final DefaultListModel<String> manulListModel;
    private final DefaultListModel<String> hedghogsListModel;
    private final DefaultListModel<String> lynxesListModel;


    private final List<Chordates> unsortedCollection = new ArrayList<>();
    private final List<? super HedgehogOrdinary> hedgehogCollection = new ArrayList<>();
    private final List<? super Manul> manulCollection = new ArrayList<>();
    private final List<? super Lynx> lynxCollection = new ArrayList<>();


    public Lab3Window() {
        setTitle("Lab3 - Animal sorting");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setResizable(false);

        JPanel mainPanel = new JPanel(new GridBagLayout());

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.BOTH;
        gbc.insets = new Insets(5, 5, 5, 5);

        // Sort button
        sortButton = createButton("SORT", Color.WHITE, Color.BLACK, new Dimension(100, 100), getSortListsListener());
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridheight = 1;
        mainPanel.add(sortButton, gbc);

        // Unsorted Chordates list
        unsortedListModel = new DefaultListModel<>();
        unsortedChordatesList = new JList<>(unsortedListModel);
        JScrollPane unsortedScrollPane = new JScrollPane(unsortedChordatesList);
        unsortedScrollPane.setPreferredSize(new Dimension(200, 150));
        gbc.gridx = 1;
        gbc.gridy = 0;
        gbc.gridheight = 1;
        mainPanel.add(createTitledPanel("Unsorted Chordates", unsortedScrollPane), gbc);

        // Subgrid for rightmost tile
        JPanel subgridPanel = new JPanel(new GridBagLayout());
        GridBagConstraints subgridGbc = new GridBagConstraints();
        subgridGbc.fill = GridBagConstraints.VERTICAL;
        subgridGbc.insets = new Insets(5, 5, 5, 5);

        // Animal ComboBox
        animalComboBox = new JComboBox<>();
        animalComboBox.addItem(Manul.class.getSimpleName());
        animalComboBox.addItem(HedgehogOrdinary.class.getSimpleName());
        animalComboBox.addItem(Lynx.class.getSimpleName());
        classMap.put(Manul.class.getSimpleName(), Manul.class);
        classMap.put(HedgehogOrdinary.class.getSimpleName(), HedgehogOrdinary.class);
        classMap.put(Lynx.class.getSimpleName(), Lynx.class);

        subgridGbc.gridx = 0;
        subgridGbc.gridy = 0;
        subgridGbc.weightx = 1.0;
        subgridPanel.add(animalComboBox, subgridGbc);

        // Add Animal button
        addAnimalButton = createButton("Add animal", Color.BLACK, Color.WHITE, new Dimension(150, 50), getAddAnimalListener());
        subgridGbc.gridy = 1;
        subgridGbc.weightx = 1.0;
        subgridPanel.add(addAnimalButton, subgridGbc);

        gbc.gridx = 2;
        gbc.gridy = 0;
        gbc.gridheight = 1;
        mainPanel.add(createTitledPanel("Animal Selection", subgridPanel), gbc);

        // Manul list
        manulListModel = new DefaultListModel<>();
        manulList = new JList<>(manulListModel);
        JScrollPane felinesScrollPane = new JScrollPane(manulList);
        felinesScrollPane.setPreferredSize(new Dimension(150, 100));
        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridheight = 1;
        mainPanel.add(createTitledPanel("Felines", felinesScrollPane), gbc);

        // Ordinary Hedgehogs list
        hedghogsListModel = new DefaultListModel<>();
        ordinaryHedghogsList = new JList<>(hedghogsListModel);
        JScrollPane hedghogsScrollPane = new JScrollPane(ordinaryHedghogsList);
        hedghogsScrollPane.setPreferredSize(new Dimension(150, 100));
        gbc.gridx = 1;
        mainPanel.add(createTitledPanel("Hedgehogs", hedghogsScrollPane), gbc);

        // Lynxes list
        lynxesListModel = new DefaultListModel<>();
        lynxesList = new JList<>(lynxesListModel);
        JScrollPane lynxesScrollPane = new JScrollPane(lynxesList);
        lynxesScrollPane.setPreferredSize(new Dimension(150, 100));
        gbc.gridx = 2;
        mainPanel.add(createTitledPanel("Lynxes", lynxesScrollPane), gbc);

        updateLists();

        add(mainPanel);
    }

    private void listToJList(List<?> objectList, DefaultListModel<String> defaultListModel) {
        defaultListModel.removeAllElements();
        for (Object obj : objectList) {
            defaultListModel.addElement(obj.getClass().getSimpleName());
        }
    }

    private void updateLists() {
        listToJList(unsortedCollection, unsortedListModel);
        listToJList(hedgehogCollection, hedghogsListModel);
        listToJList(manulCollection, manulListModel);
        listToJList(lynxCollection, lynxesListModel);
    }

    private ActionListener getAddAnimalListener() {
        return new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String animalClassKey = String.valueOf(animalComboBox.getSelectedItem());
                Class<? extends Chordates> animalClass = classMap.get(animalClassKey);
                try {
                    Chordates chord = animalClass.getDeclaredConstructor().newInstance();
                    unsortedCollection.add(chord);
                    updateLists();
                } catch (InstantiationException | IllegalAccessException | InvocationTargetException |
                         NoSuchMethodException ex) {
                    throw new RuntimeException(ex);
                }
            }
        };
    }

    private ActionListener getSortListsListener() {
        return new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                segregate(
                        unsortedCollection,
                        hedgehogCollection,
                        manulCollection,
                        lynxCollection
                );
                unsortedCollection.clear();
                unsortedListModel.clear();
                updateLists();
            }
        };
    }

    private JButton createButton(String text, Color background, Color foreground, Dimension size, ActionListener callback) {
        JButton button = new JButton(text);
        button.addActionListener(callback);
        button.setBackground(background);
        button.setForeground(foreground);
        button.setPreferredSize(size);
        return button;
    }

    private JPanel createTitledPanel(String title, JComponent component) {
        JPanel panel = new JPanel(new BorderLayout());
        panel.setBorder(BorderFactory.createTitledBorder(title));
        panel.add(component);
        return panel;
    }
}
