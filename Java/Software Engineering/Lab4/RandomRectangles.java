import javafx.application.Application;
import javafx.scene.layout.AnchorPane;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;
import java.util.*;

public class RandomRectangles extends Application {
	public static void main(String[] args) {
        Application.launch(args);
    }
	
	@Override
    public void start(Stage stage) {
		int N = Integer.parseInt(getParameters().getRaw().get(0));
    	int min = Integer.parseInt(getParameters().getRaw().get(1));
    	int max = Integer.parseInt(getParameters().getRaw().get(2));
    	AnchorPane anchor = new AnchorPane();
        Scene scene = new Scene(anchor, 700, 700, Color.WHITE);
    	Random rng = new Random();
    	int[] arrAreas = new int[N];
    	int[] arrPerimeters = new int[N];
    	
    	for (int i = 0; i < N; i++) {
    		Rectangle r = new Rectangle();
    		int W = uniform(min, max);
    		int H = uniform(min, max);
    		arrAreas[i] = W * H;
    		arrPerimeters[i] = 2 * (W + H);
    		r.setX(rng.nextInt(500));
    		r.setY(rng.nextInt(500));
    		r.setWidth(W * (int)(100/max));
    		r.setHeight(H * (int)(100/max));
    		r.setFill(null);
    		r.setStroke(Color.BLACK);
    		anchor.getChildren().add(r);    		
    	}
		System.out.println("Average area: " + Arrays.stream(arrAreas).average().getAsDouble());
		System.out.println("Average perimeter: " + Arrays.stream(arrPerimeters).average().getAsDouble());
        stage.setScene(scene);
        stage.show();
	}
	
	public int uniform(int min, int max) {
		int diff = max - min;
		Random rand = new Random();
		return rand.nextInt(diff) + min;
	}
}
