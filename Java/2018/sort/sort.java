package sort20153100073;


import java.util.*;

public class sort20153100073{
	//ð�������㷨
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
			arr[i]=(int)(Math.random()*100);//��ȡ�����
			arr_hub[i]=arr[i];//���
			arr_class[i]=arr[i];//���
		}
		System.out.println("���ɵ��������"+Arrays.toString(arr));
		
		//����ð����������ʱ��
		long startTime=System.nanoTime();   //��ȡ��ʼʱ�� 
		bubble_sort(arr_hub);
		long endTime=System.nanoTime(); //��ȡ����ʱ�� 
		System.out.println("ð�������������ʱ�䣺 "+(endTime-startTime)+"ns"); 
		System.out.println("ð���������� "+Arrays.toString(arr_hub));
		
		//����Arrays.sort��������
		long startTime1=System.nanoTime();   //��ȡ��ʼʱ�� 
		Arrays.sort(arr_class);
		long endTime1=System.nanoTime(); //��ȡ����ʱ�� 
		System.out.println("���������򷽷�����ʱ�䣺 "+(endTime1-startTime1)+"ns"); 
		System.out.println("���������򷽷������ "+Arrays.toString(arr_class));

	}
}
