import javax.swing.*;
import java.awt.GridLayout;
import java.awt.BorderLayout;
import java.awt.event.*;
import java.util.Stack;
import java.util.Vector;

class Main {
    public static void main(String[] args) {
        Calculator calculator = new Calculator();
        calculator.execute();
    }
}

class Calculator implements ActionListener {
    JFrame frame;
    JTextField  display;
    JPanel buttonPanel, operatorPanel;
    JButton[] buttons, operators;

    public void execute() {
        frame = new JFrame("Calculator");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 400);
        frame.setLayout(new BorderLayout());

        display = new JTextField("");
        display.setEditable(false);
        frame.add(display, BorderLayout.PAGE_START);

        /* The panel to group button with GridLayout. */
        buttonPanel = new JPanel();
        buttonPanel.setLayout(new GridLayout(4, 4));

        buttons = new JButton[16];
        String[] buttonSymbols = { "1", "2", "3", "+",
                                   "4", "5", "6", "-",
                                   "7", "8", "9", "*",
                                   "C", "0", "=", "/" };
        for (int i = 0; i < buttons.length; ++i) {
            buttons[i] = new JButton(buttonSymbols[i]);
            buttons[i].setName(buttonSymbols[i]);
            buttons[i].addActionListener(this);
            buttonPanel.add(buttons[i]);
        } 
        frame.add(buttonPanel, BorderLayout.CENTER);
        /* The buttons panel is added to the main frame. */

        JButton backspace = new JButton("Backspace");
        backspace.setName("backspace");
        backspace.addActionListener(this);
        frame.add(backspace, BorderLayout.PAGE_END);

        frame.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        JButton b = (JButton) e.getSource();
        String text = this.display.getText();
        int textL = text.length();
        String button = b.getName();
        switch (button) {
            case "=":
                Expression ex = new Expression(text);
                this.display.setText(ex.evaluate());
                break;
            case "C":
                this.display.setText("");
                break;
            case "backspace":
                if (!text.isEmpty())
                    this.display.setText(
                        text.substring(0, textL - 1).trim());
                break;
            default:
                if (button.matches("[0-9]+")) 
                  this.display.setText(text + button);
                else this.display.setText(
                        text + " " + button + " ");
        }
    }
}

class Expression {
    String[] expression;
    Vector<String> postfix;
    Stack<String> stack;

    Expression(String expr) {
        this.expression = expr.split(" "); 
        this.postfix = new Vector<String>();
        this.stack = new Stack<String>();
        infixToPostfix();
    }

    private void infixToPostfix() {
        for (String s : expression) {
            if (s.matches("[0-9]+")) postfix.add(s);
            else {
                if (!stack.empty()) {
                    if (priority(s) > priority(stack.peek()))
                        stack.push(s);
                    else {
                        while (!stack.empty()) postfix.add(stack.pop());
                        stack.push(s);
                    }
            } else stack.push(s);
            }
        } while(!stack.empty()) postfix.add(stack.pop());
    }

    public String evaluate() {
        for (String s : postfix) {
            if (s.matches("[0-9]+")) stack.push(s);
            else  {
                int y = Integer.valueOf(stack.pop()),
                    x = Integer.valueOf(stack.pop());
                switch (s) {
                    case "+":
                        stack.push(x + y + ""); 
                        break;
                    case "-":
                        stack.push(x - y + ""); 
                        break;
                    case "*":
                        stack.push(x * y + ""); 
                        break;
                    case "/":
                        stack.push(x / y + ""); 
                        break;
                }
            }
        } return stack.pop();
    }

    private int priority(String operator) {
        if (operator.matches("[+-]")) return 1;
        else return 2;
    }
}
