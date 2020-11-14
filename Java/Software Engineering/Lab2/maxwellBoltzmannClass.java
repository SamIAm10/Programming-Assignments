import java.util.Random;

public class maxwellBoltzmannClass extends Random {
	public static double maxwellBoltzmann(double o) {
		Random g = new Random();
		double x = g.nextGaussian(), y = g.nextGaussian(), z = g.nextGaussian();
		x *= o;
		y *= o;
		z *= o;
		double avg = (x + y + z)/3;
		x -= avg;
		y -= avg;
		z -= avg;
		return Math.sqrt(Math.pow(x, 2) + Math.pow(y, 2) + Math.pow(z, 2));
	}
}
