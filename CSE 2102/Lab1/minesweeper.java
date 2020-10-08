public class minesweeper { 
    public static void main(String[] args) { 
        int M = Integer.parseInt(args[0]);
        int N = Integer.parseInt(args[1]);
        double p = Double.parseDouble(args[2]);
        boolean[][] mines = new boolean[M+2][N+2];
        for (int x = 1; x <= M; x++)
            for (int y = 1; y <= N; y++)
            	mines[x][y] = (Math.random() < p);
        for (int x = 1; x <= M; x++) {
            System.out.print("|");
            for (int y = 1; y <= N; y++)
                if (mines[x][y])
                	System.out.print("* ");
                else
                	System.out.print(". ");
            System.out.println("|");
        }
        int[][] count_mines = new int[M+2][N+2];
        for (int x = 1; x <= M; x++)
            for (int y = 1; y <= N; y++)
                for (int a = x - 1; a <= x + 1; a++)
                    for (int b = y - 1; b <= y + 1; b++)
                        if (mines[a][b])
                        	count_mines[x][y] += 1;
        System.out.println();
        for (int x = 1; x <= M; x++) {
            System.out.print("|");
            for (int y = 1; y <= N; y++) {
                if (mines[x][y])
                	System.out.print("* ");
                else
                	System.out.print(count_mines[x][y] + " ");
            }
            System.out.println("|");
        }

    }
}
