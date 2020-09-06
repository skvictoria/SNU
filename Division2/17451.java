import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {
	public static void main (String[] args) throws IOException {

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int num = Integer.parseInt(br.readLine());
		if(num>=1){
			double[] arr;
			String[] tmparr = br.readLine().split(" ");
			arr = Arrays.stream(tmparr).mapToDouble(Double::parseDouble).toArray();

			double tmp = arr[num-1];
			for (int i=num-1;i>0;i--){
				tmp = Math.ceil(tmp/arr[i-1])*arr[i-1];
			}
			System.out.print((long)tmp);
		}
		br.close();


	}

}
