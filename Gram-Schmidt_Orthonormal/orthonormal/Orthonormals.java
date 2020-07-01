package orthonormal;

public class Orthonormals<T extends Number>
{
	//the 2d array of independent vecs(input)
	private Vector<Number>[] vecMatrix;
	private Vector<Number>[] orthoMatrix;
	private Vector<Number>[] decompR;	//matrix R in A = QR
	private int numVecs;
	private int row;
	public static final int SIZE = 3;
	public static final int DECIMAL_PLACES = 3;
	public Orthonormals()
	{
		vecMatrix = new Vector[SIZE];
		orthoMatrix = new Vector[SIZE];
		decompR = new Vector[SIZE];
		numVecs = SIZE;
		row = Vector.SIZE;
		initMatrix();
	}
	public Orthonormals(Vector<? extends T>[] arr, int num)
	throws CloneNotSupportedException
	{
		vecMatrix = new Vector[num];
		orthoMatrix = new Vector[num];
		decompR = new Vector[num];
		numVecs = num;
		row = arr[0].col;
		for(int i = 0; i < num; i++)
		{
			//init each vector in the 2d array
			vecMatrix[i] = (Vector<Number>) arr[i].clone();
		}
		initMatrix();
	}
	private void initMatrix()
	{
		orthoMatrix = new Vector[numVecs];
		decompR = new Vector[numVecs];
		for(int i = 0; i < numVecs; i++)
		{
			//init each vector in the 2d array
			orthoMatrix[i] = new Vector<Number>(row);
			orthoMatrix[i].initVector();
			decompR[i] = new Vector<Number>(row);
			decompR[i].initVector();
		}
	}
	
	
	
	public void calcOrthonormal()throws Exception	//helper function
	{
		parseOrtho(numVecs);
	}
	
	private void parseOrtho(int col)throws Exception
	{
		//calc the q1 = a;
		for(int i = 0; i < row; i++)
		{
			orthoMatrix[0].vector[i] = vecMatrix[0].vector[i].doubleValue();
		}
		//get the unit vector
		//orthoMatrix[0] = orthoMatrix[0].constantVector(1.0/orthoMatrix[0].vectorLength());

		//for loop and calc each orthogonal vector
		int i;
		for(i = 1; i < col; i++)
		{
			orthoMatrix[i] = vecMatrix[i].subtract(orthoMatrix[0].matrixVector
					(orthoMatrix[0].outerProduct(vecMatrix[i])).constantVector
					(1.0/(orthoMatrix[0].innerProduct(orthoMatrix[0]))));
			for(int k = 1; k < i; k++)
			{
				orthoMatrix[i] = orthoMatrix[i].subtract(orthoMatrix[k].matrixVector
						(orthoMatrix[k].outerProduct(vecMatrix[i])).constantVector
						(1.0/(orthoMatrix[k].innerProduct(orthoMatrix[k]))));
			}
		}
		
		
		//unit vectors
		for(int j =0; j <col; j++)
		{
			//calc the orthonormal vector
			orthoMatrix[j] = orthoMatrix[j].constantVector(1.0/orthoMatrix[j].vectorLength());
		}
		
	}
	
	public void orthoDecompose() throws Exception
	{
		calcOrthonormal();
		for(int i = 0; i < numVecs; i++)
		{
			for(int j = 0; j <= i; j++)
			{
				decompR[i].vector[j] = orthoMatrix[j].innerProduct(vecMatrix[i]);
			}
		}
	}
	
	public void displayDecomposition()
	{
		System.out.println("The matrix decompositino A = QR is:");
		for(int i = 0; i < row; i++)
		{
			for(int j = 0; j < numVecs; j++)
			{
				System.out.printf("%7.2f ", vecMatrix[j].vector[i]);
			}
			if(i == row/2)
				System.out.print("   =   ");
			else
				System.out.print("       ");
			
			for(int j = 0; j < numVecs; j++)
			{
				System.out.printf("%7.2f ", orthoMatrix[j].vector[i]);
			}
			System.out.print(" | ");

			for(int j = 0; j < numVecs; j++)
			{
				System.out.printf("%7.2f ", decompR[j].vector[i]);
			}
			if(i < row-1)
			{
				//implement visual of the block of the matrix
				hyphenDivider(3, 8*numVecs, "   ");
			}
			
		}
	}
	
	public void hyphenDivider(int f, int n, String dilimeter)
	{
		System.out.println("");
		for(int k = 0; k < f; k++)
		{
			for(int i = 0;i < n; i++)
			{
				System.out.print("-");
			}
			if(k == 0)
				System.out.print("       ");
			else
				System.out.print(dilimeter);
		}
		System.out.println("");
		
	}
	
	public void displayOrthonormal()
	{
		System.out.println("\nThe matrix Q is:");
		for(int i = 0; i < row; i++)
		{
			for(int j = 0; j < numVecs; j++)
			{
				System.out.printf("%3.3f  ", orthoMatrix[j].vector[i]);
			}
			System.out.println("");
		}
	}
}
