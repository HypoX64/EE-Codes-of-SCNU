package sort20153100073;


import java.util.*;

public class sort20153100073{
	//冒泡排序算法
	public static void bubble_sort(int[] arr){  
        int i, j, temp, len = arr.length;  
        for (i = 0; i < len - 1; i++)  
            for (j = 0; j < len - 1 - i; j++)  
                if (arr[j] > arr[j + 1]) {  
                    temp = arr[j];  
                    arr[j] = arr[j + 1];  
                    arr[j + 1] = temp;  
                }  
	}  
	
	public static void main(String args[]){
		int arr[]=new int[100];
		int arr_hub[]=new int[100];
		int arr_class[]=new int[100];
		
		for(int i=0;i<100;i++){
			arr[i]=(int)(Math.random()*100);//获取随机数
			arr_hub[i]=arr[i];//深复制
			arr_class[i]=arr[i];//深复制
		}
		System.out.println("生成的随机数："+Arrays.toString(arr));
		
		//计算冒泡排序消耗时间
		long startTime=System.nanoTime();   //获取开始时间 
		bubble_sort(arr_hub);
		long endTime=System.nanoTime(); //获取结束时间 
		System.out.println("冒泡排序程序运行时间： "+(endTime-startTime)+"ns"); 
		System.out.println("冒泡排序结果： "+Arrays.toString(arr_hub));
		
		//调用Arrays.sort方法排序
		long startTime1=System.nanoTime();   //获取开始时间 
		Arrays.sort(arr_class);
		long endTime1=System.nanoTime(); //获取结束时间 
		System.out.println("数组类排序方法运行时间： "+(endTime1-startTime1)+"ns"); 
		System.out.println("数组类排序方法结果： "+Arrays.toString(arr_class));

	}
}
