/************************************************************
 *JAVA程序设计-大作业											*
 *作品名称：地图系统											*
 *作者：梁志浩（20172333075）、何尔恒（2017233****）			*
 *该地图系统可选择使用高德地图或百度地图							*
 *为确保程序正常使用，请添加 lib 目录下 fastjson-1.2.62.jar		*
 ************************************************************/
package Map;

import java.io.IOException;
import java.util.Scanner;

public class MapMain {
	
	public static void welcome() {
		
	}
	
	public static void main(String[] args) throws IOException {
		Scanner scanner = new Scanner(System.in);
		while (true) {
			System.out.println("****欢迎使用地图程序，请输入对应数字选择地图****");
			System.out.println("1——高德地图");
			System.out.println("2——百度地图");
			System.out.println("0——退出程序");
			
			int Digit = scanner.nextInt();
            switch(Digit) {
            	case 1:
            		System.out.println("欢迎使用高德地图！");
            		ALiMap.Alimap();
            		continue;
            	case 2:
            		System.out.println("欢迎使用百度地图！");
            		BDMap.BDmap();
            		continue;
            	case 0:
            		System.out.println("程序结束");
                    System.exit(0);
                    scanner.close();//当此后非程序结束，须删除此行
                    continue;
                default:
                    System.out.println("\n输入有误\n");
            }
        }
	}
}