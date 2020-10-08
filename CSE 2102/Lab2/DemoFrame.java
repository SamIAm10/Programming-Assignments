import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class DemoFrame extends JFrame implements ActionListener {
	private static Color[] colors = {Color.red, Color.blue, Color.green, Color.pink, Color.yellow, Color.orange, 
									Color.DARK_GRAY, Color.magenta, Color.white, Color.cyan, Color.black};
	
	public DemoFrame(int x, int y, int height, int width) {
		this.setBounds(x, y, width, height);
		this.getContentPane().setBackground(Color.PINK);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setResizable(false);
		
		JPanel child = new JPanel();
		child.setBounds(0, 0, width, height);
		child.setOpaque(false);
		this.getContentPane().add(child);
		
		JButton colorButton = new JButton("Random Color");
		colorButton.setBounds(200, 200, 100, 20);
		colorButton.addActionListener(this);
		colorButton.setActionCommand("randomize");
		child.add(colorButton);
		
		JButton lineButton = new JButton("Random line");
		lineButton.addActionListener(this);
		lineButton.setActionCommand("line");
		child.add(lineButton);
		
		JButton circleButton = new JButton("Random circle");
		circleButton.setBounds(200, 400, 100, 20);
		circleButton.addActionListener(this);
		circleButton.setActionCommand("circle");
		child.add(circleButton);
		
//		createButton("Random Color", "randomize", child);
//		createButton("Random Line", "line", child);
//		createButton("Random Circle", "circle", child);
	}
	
	private void createButton(String text, String command, JPanel parent) {
		JButton button = new JButton(text);
		button.addActionListener(this);
		button.setActionCommand(command);
		parent.add(button);
	}
	
	private void randomizeColor() {
		int index = new Random().nextInt(colors.length);
		this.getContentPane().setBackground(colors[index]);
	}
	
	private void drawLine() {
		int x1 = new Random().nextInt(this.getWidth());
		int x2 = new Random().nextInt(this.getWidth());
		int y1 = new Random().nextInt(this.getHeight());
		int y2 = new Random().nextInt(this.getHeight());
		
		this.getGraphics().drawLine(x1, y1, x2, y2);
	}
	
	private void drawCircle() {
		int diameter = new Random().nextInt(75);
		int originX = new Random().nextInt(this.getWidth());
		int originY = new Random().nextInt(this.getHeight());
		
		this.getGraphics().drawOval(originX, originY, diameter, diameter);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		String action = e.getActionCommand();
		if (action.equals("randomize")) {
			randomizeColor();
		} else if (action.equals("line")) {
			drawLine();
		} else if (action.equals("circle")) {
			drawCircle();
		}
	}
}