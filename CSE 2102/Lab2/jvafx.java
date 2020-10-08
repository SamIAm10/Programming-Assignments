import javafx.application.Application;
import javafx.scene.layout.AnchorPane;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;
import javafx.scene.shape.Line;

public class jvafx extends Application {
    public static void main(String[] args) {
        Application.launch(args);;
    }
    @Override
    public void start(Stage primaryStage) {     
        AnchorPane root = new AnchorPane();
        Scene scene = new Scene(root, 300, 300, Color.WHITE);

        Circle c = new Circle();
        c.setCenterX(150);
        c.setCenterY(150);
        c.setRadius(100);
        c.setStroke(Color.BLACK);
        c.setFill(null);

        root.getChildren().add(c);

        int N = 16;
        for (int i = 0; i < N; i++) {
        	double x = 150 + 100 * Math.cos(Math.PI * 2 * i / N);
        	double y = 150 + 100 * Math.sin(Math.PI * 2 * i / N);
            Circle pt = new Circle(x, y, 2);
            pt.setFill(Color.BLACK);
            root.getChildren().add(pt);
        }
        
        double p = .2;
        for (int i = 0; i < N; i++) {
        	double x1 = 150 + 100 * Math.cos(Math.PI * 2 * i / N);
        	double y1 = 150 + 100 * Math.sin(Math.PI * 2 * i / N);
        	for (int j = 0; j < N; j++) {
        		if (j != i && Math.random() < p) {
        			double x2 = 150 + 100 * Math.cos(Math.PI * 2 * j / N);
                	double y2 = 150 + 100 * Math.sin(Math.PI * 2 * j / N);
        			Line line = new Line(x1, y1, x2, y2);
        			line.setStroke(Color.GREY);
        			root.getChildren().add(line);
        		}
        	}
        }

        primaryStage.setScene(scene);
        primaryStage.show();
    }
}