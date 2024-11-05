import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class Main {
    public static void main(String[] args) {
        TrafficLights tl = new TrafficLights();
        tl.execute();
    }
}

class TrafficLights implements ActionListener {
    JFrame frame;
    JPanel controlPanel, light;
    ButtonGroup signals;
    JRadioButton red, orange, green;

    public void execute() {
        frame = new JFrame("Traffic Lights");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 400);
        frame.setLayout(new BorderLayout());

        light = new JPanel();
        light.setBackground(Color.RED);
        frame.add(light, BorderLayout.CENTER);

        controlPanel = new JPanel();
        signals = new ButtonGroup();

        /* Add radio buttons for red, orange, and green lights. */
        red = new JRadioButton("Stop", true);
        red.addActionListener(this);
        signals.add(red);
        controlPanel.add(red);

        orange = new JRadioButton("Slow down");
        orange.addActionListener(this);
        signals.add(orange);
        controlPanel.add(orange);

        green = new JRadioButton("Go");
        green.addActionListener(this);
        signals.add(green);
        controlPanel.add(green);

        frame.add(controlPanel, BorderLayout.PAGE_END);

        frame.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        JRadioButton source = (JRadioButton) e.getSource();
        if (source == green) light.setBackground(Color.GREEN);
        else if (source == orange) light.setBackground(Color.ORANGE);
        else light.setBackground(Color.RED);
    }
}
