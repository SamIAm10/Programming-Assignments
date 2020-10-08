public class popGrowth {
	public static void main(String[] args) {
		double start = Double.parseDouble(args[0]);
		double growthRate = Double.parseDouble(args[1]);
		double currentPop = start;
		double newPop = currentPop;
		for (int i = 1; i <= 100; i++) {
			newPop = growthRate * currentPop * (1 - currentPop);
			if (newPop > 1)
				break;
			currentPop = newPop;
			System.out.println(currentPop);
			}
	}
}
