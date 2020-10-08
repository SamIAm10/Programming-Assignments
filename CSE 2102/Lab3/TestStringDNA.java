import java.io.*;

public class TestStringDNA {
	public static void main(String[] args) {
		try {
	    	System.out.print("Input test file path: " + args[0]);
	    	System.out.println();
	    	System.out.println();
	    	String filepath = args[0];
			File testfile = new File(filepath);
			FileReader fr = new FileReader(testfile);
			BufferedReader br = new BufferedReader(fr);
			String s;
			int line = 1;
			while ((s = br.readLine()) != null) {
				StringDNA dna = new StringDNA();
				System.out.println("Line " + line++ + ":");
				if (dna.isValidDNA(s)) {
					System.out.println("DNA string: " + s);
					System.out.println("Valid DNA?: " + dna.isValidDNA(s));
					System.out.println("Watson-Crick complement: " + dna.complementWC(s));
					System.out.println("Watson-Crick complemented palindrome?: " + dna.palindromeWC(s));
				}
				else {
					System.out.println("DNA string: " + s);
					System.out.println("Invalid DNA string");
				}
				System.out.println();
			}
		}
		catch (FileNotFoundException e) {
			System.out.println("Invalid file path");
		}
		catch (Exception e) {
			System.out.println();
		}
	}
}
