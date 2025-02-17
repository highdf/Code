package src.ui;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

public class GameJFrame extends JFrame {

	public GameJFrame() {
		super();
		this.setSize(600, 700);
		this.setDefaultWindow();
		this.setMenu();
		this.setVisible(true);
	}

	public GameJFrame(int width, int height) {
		super();
		this.setSize(width, height);
		this.setDefaultWindow();
		this.setMenu();
		this.setVisible(true);
	}

	//set
	private void setDefaultWindow() {
		this.setTitle("Puzzl Game");
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(3);
	}

	private void setMenu() {
		JMenuBar jMenuBar = new JMenuBar();
		JMenu jMenu0 = new JMenu("Options");
		JMenu jMenu1 = new JMenu("About Us");

		JMenuItem item0 = new JMenuItem("Restart");
		JMenuItem item1 = new JMenuItem("Log in again");
		JMenuItem item2 = new JMenuItem("Cloase game");

		JMenuItem item3 = new JMenuItem("Official account");

		jMenu0.add(item0);
		jMenu0.add(item1);
		jMenu0.add(item2);

		jMenu1.add(item3);

		jMenuBar.add(jMenu0);
		jMenuBar.add(jMenu1);

		this.setJMenuBar(jMenuBar);
	}

}
