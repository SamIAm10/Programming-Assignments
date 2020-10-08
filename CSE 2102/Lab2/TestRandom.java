import java.util.Random;

public class TestRandom {
	public static void main(String[] args) {
		int N = Integer.parseInt(args[0]);
		double[] randomfl = new double[N];
		double[] randomG = new double[N];
		int[] randomInt = new int[N];
		for (int i = 0; i < N; i++) {
			Random rand1 = new Random();
			Random rand2 = new Random();
			Random rand3 = new Random();
			double x = rand1.nextDouble();
			double y = rand2.nextGaussian();
			int z = rand3.nextInt(1000);
			randomfl[i] = x;
			randomG[i] = y;
			randomInt[i] = z;
		}
		
		System.out.println("Statistics for " + N + " random doubles:");
		System.out.println("Minimum: " + MinDouble(randomfl));
		System.out.println("Standard deviation: " + StDevDouble(randomfl));
		System.out.println();
		System.out.println("Statistics for " + N + " random Guassians:");
		System.out.println("Minimum: " + MinDouble(randomG));
		System.out.println("Standard deviation: " + StDevDouble(randomG));
		System.out.println();
		System.out.println("Statistics for " + N + " random integers (from 0 to 1000):");
		System.out.println("Minimum: " + MinInt(randomInt));
		System.out.print("Standard deviation: " + StDevInt(randomInt));
	}
	
	public static double MinDouble(double[] array) {
	    double min = array[0];
	    for (int i = 1; i < array.length; i++) {
	        if (array[i] < min)
	            min = array[i];
	    }
	    return min;
	}
	
	public static int MinInt(int[] array) {
	    int min = array[0];
	    for (int i = 1; i < array.length; i++) {
	        if (array[i] < min)
	            min = array[i];
	    }
	    return min;
	}
	
	public static double StDevDouble(double array[]) {
        double s = 0;
        double stdev = 0;
        for(double n : array) 
            s += n;
        double avg = s / array.length;
        for(double n : array) 
            stdev += Math.pow(n - avg, 2);
        return Math.sqrt(stdev/array.length);
    }
	
	public static double StDevInt(int array[]) {
        double s = 0;
        double stdev = 0;
        for(double n : array)
            s += n;
        double avg = s / array.length;
        for(double n : array) 
            stdev += Math.pow(n - avg, 2);
        return Math.sqrt(stdev/array.length);
    }

}
