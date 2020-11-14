import javafx.application.Application;
import javafx.scene.layout.AnchorPane;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.stage.Stage;

public class PointsCircle extends Application {
    public static void main(String[] args) {
        Application.launch(args);
    }
    
    @Override
    public void start(Stage stage) {
    	int N = Integer.parseInt(getParameters().getRaw().get(0));
    	double p = Double.parseDouble(getParameters().getRaw().get(1));
        AnchorPane anchor = new AnchorPane();
        Scene scene = new Scene(anchor, 600, 600, Color.WHITE);
        Circle circ = new Circle(300, 300, 200);
        circ.setStroke(Color.BLACK);
        circ.setFill(null);
        anchor.getChildren().add(circ);
        for (int i = 0; i < N; i++) {
        	double x = 300 + 200 * Math.cos(Math.PI * 2 * i / N);
        	double y = 300 + 200 * Math.sin(Math.PI * 2 * i / N);
            Circle point = new Circle(x, y, 2);
            point.setFill(Color.BLACK);
            anchor.getChildren().add(point);
        }
        
        for (int i = 0; i < N; i++) {
        	double x1 = 300 + 200 * Math.cos(Math.PI * 2 * i / N);
        	double y1 = 300 + 200 * Math.sin(Math.PI * 2 * i / N);
        	for (int j = 0; j < N; j++) {
        		if (j != i && Math.random() < p) {
        			double x2 = 300 + 200 * Math.cos(Math.PI * 2 * j / N);
                	double y2 = 300 + 200 * Math.sin(Math.PI * 2 * j / N);
        			Line line = new Line(x1, y1, x2, y2);
        			line.setStroke(Color.GREY);
        			anchor.getChildren().add(line);
        		}
        	}
        }

        stage.setScene(scene);
        stage.show();
    }
}