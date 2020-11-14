import javafx.application.Application;
import javafx.scene.layout.AnchorPane;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;
import java.util.*;

public class RandomSquaresAndRectangles extends Application {
	public static void main(String[] args) {
        Application.launch(args);
    }

	@Override
    public void start(Stage stage) {
		int N = Integer.parseInt(getParameters().getRaw().get(0));
    	double p = Double.parseDouble(getParameters().getRaw().get(1));
        AnchorPane anchor = new AnchorPane();
        Scene scene = new Scene(anchor, 700, 700, Color.WHITE);
        ArrayList<Rectangle> arr = new ArrayList<Rectangle>();
        Random rng = new Random(); 
        
        for (int i = 0; i < N; i++) {
        	if (Math.random() < p) {
        		Square sq = new Square();
        		sq.setCenterX(rng.nextInt(500));
        		sq.setCenterY(rng.nextInt(500));
        		sq.setWidth(100);
        		Rectangle r = new Rectangle();
        		r.setX(sq.getCenterX());
        		r.setY(sq.getCenterY());
        		r.setWidth(sq.getWidth());
        		r.setHeight(sq.getHeight());
        		r.setFill(null);
        		r.setStroke(Color.BLUE);
        		arr.add(r);
        	}
        	else {
        		TwiceRectangle tr = new TwiceRectangle();
        		tr.setCenterX(rng.nextInt(500));
        		tr.setCenterY(rng.nextInt(500));
        		tr.setWidth(200);
        		Rectangle r = new Rectangle();
        		r.setX(tr.getCenterX());
        		r.setY(tr.getCenterY());
        		r.setWidth(tr.getWidth());
        		r.setHeight(tr.getHeight());
        		r.setFill(null);
        		r.setStroke(Color.RED);
        		arr.add(r);        		
        	}
        }
        anchor.getChildren().addAll(arr);
        stage.setScene(scene);
        stage.show();
	}
}
