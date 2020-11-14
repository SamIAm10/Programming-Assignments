
public class maxwellBoltzmannTest {
	public static void main(String[] args) {
		int N = Integer.parseInt(args[0]);
		double o = Double.parseDouble(args[1]);
		maxwellBoltzmannClass mb = new maxwellBoltzmannClass();
		System.out.println(N + " random Boltzmann numbers with standard deviation " + o + ":");
		for (int i = 0; i < N; i++) {
			System.out.println(mb.maxwellBoltzmann(o));
		}
	}
}
