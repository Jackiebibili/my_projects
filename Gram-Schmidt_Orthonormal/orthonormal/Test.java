package orthonormal;

import java.util.Scanner;

public class Test {

	public static void main(String[] args) throws CloneNotSupportedException, Exception 
	{
		Scanner in = new Scanner(System.in);
		System.out.println("Enter the # indep. vecs. dimension, followed by the # of vecs");
		int dim = in.nextInt();
		int vecs = in.nextInt();
		Vector<Double>[] block = new Vector[vecs];
		System.out.println("Enter the elements of each (column)vector, separate by a space,");
		System.out.println("press enter when finish entering each vector");
		
		//populate the matrix (column vectors)
		for(int i = 0; i < vecs; i++)
		{
			Double [] arr = new Double[dim];

			for(int j = 0; j < dim; j++)
			{
				arr[j] = in.nextDouble();
			}
			block[i] = new Vector<Double>(arr, dim);
			System.out.println("----------------");
		}
		
		//create an object of type Orthonormals<T>
		Orthonormals<Double> example = new Orthonormals<>(block, vecs);
		
		//if m = n => Q is a square matrix
		if(dim == vecs)
		{
			example.orthoDecompose();
			example.displayDecomposition();
			System.out.println("");

		}
		else
		{
			example.calcOrthonormal();
			example.displayOrthonormal();
			System.out.println("");
		}
		
		//least square solution
		System.out.println("Enter the vector b, separate each element by a space");
		Double [] vec_b = new Double[vecs];

		for(int i = 0; i < vecs; i++)
		{
			vec_b[i] = in.nextDouble();
		}
		Vector<Number> b = new Vector<Number>(vec_b, vecs);
		example.leastSquareSolution(b);
		example.displayLeastSquareSolution();
	}

}
