import java.util.Arrays;
//import java.util.Random;

public class Sorts {
	public static void main(String[] args) {
		int score[] = new int[1000];
		System.out.println("\n排序前数组内容如下：");
		for (int k = 0; k < score.length; k++) {
			score[k] = (int) (Math.random() * 1001);
			System.out.print(score[k] + "\t");
		}


		int scores1[]= new int[1000];
		int scores2[]= new int[1000];
		int scores3[]= new int[1000];
		int scores4[]= new int[1000];
		
		//scores1 = score;
		//scores2 = score;
		//scores3 = score;
		//scores4 = score;

		for (int k = 0; k < scores4.length; k++) {
			scores4[k] = (int) (Math.random() * 1001);
			//System.out.print(scores4[k] + "\t");
		}

		for (int k = 0; k < scores3.length; k++) {
			scores3[k] = (int) (Math.random() * 1001);
			//System.out.print(scores3[k] + "\t");
		}

		for (int k = 0; k < scores2.length; k++) {
			scores2[k] = (int) (Math.random() * 1001);
			//System.out.print(scores2[k] + "\t");
		}

		for (int k = 0; k < scores1.length; k++) {
			scores1[k] = (int) (Math.random() * 1001);
			//System.out.print(scores1[k] + "\t");
		}
		
		
		//int scores4[] = { 77, 55, 88, 99, 66, 11, 33, 44, 22 }; // 定义含有5个元素的数组
		long start4 = System.currentTimeMillis();
		for (int i = 0; i < scores4.length; i++) { // 插入排序
			for (int j = i; j > 0; j--) {
				if (scores4[j] < scores4[j - 1]) {
					int temp = scores4[j];
					scores4[j] = scores4[j - 1];
					scores4[j - 1] = temp;
				}
				 else {
					break;
				}
			}
		}
		long end4 = System.currentTimeMillis();
		System.out.println("\n插入排序后的数组内容如下:");
		for (int j = 0; j < scores4.length; j++) // 遍历排序后的数组
		{
			System.out.print(scores4[j] + "\t");
		}
		System.out.println("\n插入排序运算时间为");
		System.out.println(end4 - start4);


		//int scores2[] = { 77, 55, 88, 99, 66, 11, 33, 44, 22 }; // 定义含有5个元素的数组
		long start2 = System.currentTimeMillis();
		for (int i = 0; i < scores2.length - 1; i++) { // 选择排序
			for (int j = i + 1; j < scores2.length; j++) {
				if (scores2[i] > scores2[j]) {
					int temp = scores2[i];
					scores2[i] = scores2[j];
					scores2[j] = temp;
				}
			}
		}
		long end2 = System.currentTimeMillis();
		System.out.println("\n选择排序后的数组内容如下:");
		for (int j = 0; j < scores2.length; j++) // 遍历排序后的数组
		{
			System.out.print(scores2[j] + "\t");
		}
		System.out.println("\n选择排序运算时间为");
		System.out.println(end2 - start2);
		

		//int scores3[] = { 77, 55, 88, 99, 66, 11, 33, 44, 22 }; // 定义含有5个元素的数组
		long start3 = System.currentTimeMillis();
		for (int i = 0; i < scores3.length - 1; i++) { // 冒泡排序
			for (int j = 0; j < scores3.length - 1 - i; j++) {
				if (scores3[j] > scores3[j + 1]) {
					int temp = scores3[j];
					scores3[j] = scores3[j + 1];
					scores3[j + 1] = temp;
				}
			}
		}
		long end3 = System.currentTimeMillis();
		System.out.println("\n冒泡排序后的数组内容如下:");
		for (int j = 0; j < scores3.length; j++) // 遍历排序后的数组
		{
			System.out.print(scores3[j] + "\t");
		}
		System.out.println("\n冒泡排序运算时间为");
		System.out.println(end3 - start3);

	
		System.out.println("\nsort排序前数组内容如下:");
		for (int i = 0; i < scores1.length; i++)// 对score数组进行循环遍历
		{
			System.out.print(scores1[i] + "\t");
		}
		System.out.println("\nsort排序后的数组内容如下:");
		long start1 = System.currentTimeMillis();
		Arrays.sort(scores1); // 对数组进行排序
		long end1 = System.currentTimeMillis();
		for (int j = 0; j < scores1.length; j++) // 遍历排序后的数组
		{
			System.out.print(scores1[j] + "\t");
		}
		System.out.println("\nsort运算时间为");
		System.out.println(end1 - start1);


		System.out.println("\nsort运算时间为");
		System.out.println(end1 - start1);
		System.out.println("选择排序运算时间为");
		System.out.println(end2 - start2);
		System.out.println("冒泡排序运算时间为");
		System.out.println(end3 - start3);
		System.out.println("插入排序运算时间为");
		System.out.println(end4 - start4);
	}
}