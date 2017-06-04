public class Main {
  public static final String stringMax = "Max";
  public static final int intMax = 10;
  public static final char charMax = 'M';
  public static final float floatMax = 3;
  public static final boolean bMax = true;
  public static final short sMax = 20;
  public static final byte byteMax = 2;

  public static void main(String[] args) {
    final int NUM_FACTS = 100;
    for(int i = 0; i < NUM_FACTS; i++)
      System.out.println( i + "! is " + factorial(i));
  }

  public static int factorial(int n) {
    int result = 1;
    for(int i = 2; i <= n; i++)
      result *= i;
      return result;
  }
}
