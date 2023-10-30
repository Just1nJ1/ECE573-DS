public class BadGrowArray implements Cloneable  {
	private	int[] data;
	public BadGrowArray() {
		data = null;
		len = 0;
	}
	public Object clone() {
    BadGrowArray copy = new BadGrowArray();
		copy.data = new int[this.len];
		System.arraycopy(data, 0, copy.data, 0, len);
		return copy;
	}
	public void addStart(int v) { //O(len)
		int[] temp = data; //O(1)
		data = new int[len+1]; //O(1) in Java this is O(len)
		data[0] = v; //O(1)
		for (int i = 0; i < len; i++)  //O(len)
			data[i+1] = temp[i];
		len++;
	}
	// insert before location i
	public void insert(int v, int i) { //O(len)
		int[] temp = data;
		data = new int[len+1];
		for (int j = 0; j < i; j++)
			data[j] = temp[j];
		data[i] = v;
		for (int j = i; j < len; j++)
			data[j+1] = temp[j];
		len++;
	}
	// remove from end and return the value being removed
	public int removeEnd() {  //O(1)
		int temp = data[len-1];
		len--;
		return temp;
	}

	public int removeStart() { //O(len)
		int temp = data[0];
		--len;
		for (int i = 0; i < len; i++)
      data[i] = data[i+1];			
	}
	int remove(int pos);//O(len)

  int get(int pos) {
		return data[pos];//O(1)
	}
	int size()  {
		return len;
	}
};

void f(BadGrowArray b) {

}


int main() {
	BadGrowArray bga;
	const int n = 1000000; // n=10^6   O(n^2) = 10^12
	for (int i = 0; i < n; i++)
		bga.addEnd(i); // 1 + 2 + 3 + ....  + n = O(n^2)
	BadGrowArray bga2 = bga;
	bga2[0] = 5;
	
	f(bga);;
}

/*
In MATLAB

   x = [];
   x = [x i];

   StringBuilder b = new StringBuilder(10000*5);
   for (int i = 0; i < 10000;i++)
     b.append(i);   //"01234567891011121314....99100101102....999... 9999

		 String s = "abc" + "def" + x + "ghi" + k;
   StringBuilder b = new StringBuilder();
   b.append("abcdef");
   b.append(x);
   b.append("ghi");
   b.append(k);
   s = b.toString();





	
*/
