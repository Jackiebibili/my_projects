package orthonormal;

public class Vector<T extends Number> implements Cloneable
{
	protected Number [] vector;
	int col;
	public static final int SIZE = 3;
	
	//constructors
	public Vector()
	{
		vector = (T[])new Number[SIZE];
		col = SIZE;
	}
	public Vector(int size)
	{
		vector = (T[])new Number[size];
		col = size;
	}
	public Vector(T [] arr, int size)
	{
		col = size;
		vector = (T[])new Number[size];
		for(int i = 0; i < size; i++)
		{
			vector[i] = arr[i];
		}
	}
	
	public void initVector()
	{
		for(int i = 0; i < col; i++)
		{
			vector[i] = (Double)0.0;
		}
	}
	
	//copy the vector, use clone() under the Cloneable interface
	public Object clone() throws CloneNotSupportedException
	{
		Vector<Number> vec = new Vector(this.col);
		for(int i = 0; i < this.col; i++)
		{
			vec.vector[i] = this.vector[i];
		}
		return vec;
	}
	
	public double innerProduct(Vector<? extends Number>a)throws Exception
	{
		double num = 0.0;
		if(a.col == this.col)
		{
			for(int i = 0; i < this.col; i++)
			{
				num += this.vector[i].doubleValue() * a.vector[i].doubleValue();
			}
			return num;
		}
		else
		{
			throw new Exception("Vectors are not in the same dimension");
		}
	}
	
	public Vector<Number> subtract(Vector<Number>a)throws Exception
	{
		if(a.col != this.col)
		{
			throw new Exception("Vectors are not in the same dimension");
		}
		Vector<Number> temp = (Vector<Number>)clone();
		for(int i = 0;i < col;i++)
		{
			temp.vector[i] = temp.vector[i].doubleValue() - a.vector[i].doubleValue();
		}
		return temp;
	}
	
	public Vector<Number>[] outerProduct(Vector<Number> a)throws Exception
	{
		if(a.col != this.col)
		{
			throw new Exception("Vectors are not in the same dimension");
		}
		else
		{
			Vector<Number>[] temp = new Vector[this.col];
			for(int k = 0; k < this.col; k++)
			{
				temp[k] = new Vector<Number>(this.col);
			}
			for(int i = 0 ;i < this.col; i++)
			{
				for(int j = 0; j < a.col; j++)
				{
					temp[j].vector[i] = this.vector[i].doubleValue()*a.vector[j].doubleValue();
				}
			}
			return temp;
		}
	}
	
	public Vector<Number> matrixVector(Vector<Number> [] a)throws Exception
	{
		if(a.length != this.col)
		{
			throw new Exception("Vectors are not in the same dimension");
		}
		else
		{
			Vector<Number> temp = new Vector<Number>(a[0].col);
			temp.initVector();
			for(int i = 0; i < a[0].col; i++)
			{
				for(int j = 0; j < this.col; j++)
				{
					temp.vector[i] = temp.vector[i].doubleValue() + a[j].vector[i].doubleValue()*this.vector[j].doubleValue();
				}
			}
			return temp;
		}
	}
	
	public Vector<Number> constantVector(double c)
	{
		Vector<Number> temp = new Vector<Number>(this.col);
		for(int i = 0; i < this.col; i++)
		{
			temp.vector[i] = c * this.vector[i].doubleValue();
		}
		return temp;
	}
	
	public double vectorLength() throws Exception
	{
		double inner = this.innerProduct(this);
		return Math.sqrt(inner);
	}
	
	
	
	
}
