import java.util.Scanner;
import java.io.*;

public class StandardIn {
    public static void main(String[] args) {
    	try {
    		Scanner sc = new Scanner(System.in);
        	System.out.print("Input file path: "); //must add a space at the beginning of the input string
        	String filepath = sc.nextLine();
    		File file = new File(filepath); 
            FileInputStream fs = new FileInputStream(file); 
            Scanner scanner = new Scanner(fs);
            System.out.println("Number of words: " + wordcountFile(scanner));
    	}
    	catch(Exception e) {
	    	Scanner sc = new Scanner(System.in);
	    	System.out.print("Input string:"); //must add a space at the beginning of the input string
	    	String str = sc.nextLine();
	    	System.out.println("Number of words: " + wordcountString(str));
    	}
    }
    
    public static int wordcountString(String s) {
    	int counter = 0;
    	for (int i = 0; i < s.length() - 1; i++) {
    		if (s.charAt(i) == ' ' && s.charAt(i + 1) != ' ')
    			counter++;
    	}
    	return counter;    		
    }
    
    public static int wordcountFile(Scanner scanner) {
    	int counter = 0;
    	while (scanner.hasNext()) {
    		scanner.next();
    		counter++;
    	}
    	return counter;
    }
}
