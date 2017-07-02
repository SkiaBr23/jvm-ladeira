/*
 * Compile assim: javac int_logico.java -target 1.2 -source 1.2
 */
public class testarray{
	public static void main(String args[]){

		int array[] = {4,5,6};
		long arraylong[] = {225,255,255};
		short arrayshort[] = {4,5,6};
		boolean arraybool[] = {true,false,true};
		char arraychar[] = {'c','h','a'};
		float arrayfloat[] = {3.4f,3.5f,3.6f};
		double arraydouble[] = {3.4,3.5,3.6};
		byte arraybyte[] = {'b','y','t'};

		System.out.println(array.length);
		System.out.println(arrayshort.length);
		System.out.println(arraybool.length);
		System.out.println(arraychar.length);
		System.out.println(arrayfloat.length);
		System.out.println(arraybyte.length);
		System.out.println(arraydouble.length);
		for(int j = 0; j < array.length; j++){
			System.out.println(array[j]);
		}


	}
}