//百度地图
package Map;
import java.io.IOException;
import java.util.Scanner;

public class BDMap {
	public void BDgeocode() throws IOException {
		try {
			BDgeocode geocode0 = new BDgeocode();
			System.out.print("请输入需要查询的地点（输入 0 可返回上一级菜单）：");
			geocode0.geocode();
			if(geocode0.return0 == 1) {
				System.out.println("\n返回上一级菜单\n");
                return;
			}
			System.out.println("\n该地的坐标点为：" + geocode0.location + "\n");
		} catch (Exception e) {
			System.out.println("\n输入有误\n");
        }
	}
	
	public void BDPathPlanning() throws IOException {
		try {
			BDPathPlanning pathplanning = new BDPathPlanning();
			BDgeocode geocode1 = new BDgeocode();
			BDgeocode geocode2 = new BDgeocode();

			System.out.print("请输入出发地（输入 0 可返回上一级菜单）：");
			geocode1.geocode();
			if(geocode1.return0 == 1) {
				System.out.println("\n返回上一级菜单\n");
                return;
			}
			System.out.print("请输入目的地：");
	        geocode2.geocode();
	        System.out.println("处理中...");
	        
	        pathplanning.origin = geocode1.formatchange_location;
	        pathplanning.destination = geocode2.formatchange_location;
	        
	        /*----------------------riding----------------------*/
	        pathplanning.riding();
	        if(pathplanning.taxi_time_h != 0) {
	        	System.out.println("\n起点和终点的骑行距离为：" + pathplanning.riding_distance + "米，预计耗时"
	        			+ pathplanning.riding_time_h + "小时" + pathplanning.riding_time_min + "分钟"
	        			+ pathplanning.riding_time_s + "秒");
	        }
	        else if(pathplanning.riding_time_min != 0) {
	        	System.out.println("\n起点和终点的骑行距离为：" + pathplanning.riding_distance + "米，预计耗时"
	        			+ pathplanning.riding_time_min + "分钟" + pathplanning.riding_time_s + "秒");
	        }
	        else System.out.println("\n起点和终点的骑行距离为："+ pathplanning.riding_distance + "米，预计耗时" 
        			+ pathplanning.riding_time_s + "秒");
	        /*-----------------------walk-----------------------*/
	        pathplanning.walking();
	        if(pathplanning.walk_time_h != 0) {
	        	System.out.println("起点和终点的步行距离为：" + pathplanning.walk_distance + "米，预计耗时" 
	        			+ pathplanning.walk_time_h + "小时" + pathplanning.walk_time_min + "分钟"
	        			+ pathplanning.walk_time_s + "秒");
	        }
	        else if(pathplanning.walk_time_min != 0) {
	        	System.out.println("起点和终点的步行距离为："+ pathplanning.walk_distance + "米，预计耗时" 
	        			+ pathplanning.walk_time_min + "分钟" + pathplanning.walk_time_s + "秒");
	        }
	        else System.out.println("起点和终点的步行距离为："+ pathplanning.walk_distance + "米，预计耗时" 
	        			+ pathplanning.walk_time_s + "秒");
	        /*-----------------------taxi-----------------------*/
	        pathplanning.transit();
	        if(pathplanning.taxi_time_h != 0) {
	        	System.out.println("出租车行驶距离为：" + pathplanning.taxi_distance + "米，预计耗时"
	        			+ pathplanning.taxi_time_h + "小时" + pathplanning.taxi_time_min + "分钟"
	        			+ pathplanning.taxi_time_s + "秒，预计费用为：" + pathplanning.taxi_cost + "元");
	        }
	        else if(pathplanning.taxi_time_min != 0) {
	        	System.out.println("出租车行驶距离为：" + pathplanning.taxi_distance + "米，预计耗时"
	        			+ pathplanning.taxi_time_min + "分钟" + pathplanning.taxi_time_s 
	        			+ "秒，预计费用为：" + pathplanning.taxi_cost + "元");
	        }
	        else System.out.println("出租车行驶距离为：" + pathplanning.taxi_distance + "米，预计耗时"
        			+ pathplanning.taxi_time_s + "秒，预计费用为：" + pathplanning.taxi_cost + "元");
	        /*-----------------------bus------------------------*/
	        if(pathplanning.bus_time_h != 0) {
	        	System.out.println("最快捷公交换乘方案价格为：" + pathplanning.bus_cost + "元，预计时间为" 
	        			+ pathplanning.bus_time_h + "小时" + pathplanning.bus_time_min + "分钟" 
	        			+ pathplanning.bus_time_s + "秒\n");
	        	}
	        else if(pathplanning.bus_time_min != 0) {
	        	System.out.println("最快捷公交换乘方案价格为：" + pathplanning.bus_cost + "元，预计时间为" 
	        			+ pathplanning.bus_time_min + "分钟"+ pathplanning.bus_time_s + "秒\n");
	        	}
	        else System.out.println("最快捷公交换乘方案价格为：" + pathplanning.bus_cost + "元，预计时间为" 
	        			+ pathplanning.bus_time_s + "秒\n");
		} catch (Exception e) {
            System.out.println("\n输入有误\n");
        }
    }
	
	public void BDSearch() throws IOException  {
		try {
			BDSearch search = new BDSearch();
			Scanner scanner = new Scanner(System.in);
			System.out.print("请输入需要检索的关键字（如：美食、银行、XX大厦等。输入 0 可返回上一级菜单）：");
			search.query = scanner.nextLine();
			if(search.query.equals("0")) {
				System.out.println("\n返回上一级菜单\n");
                return;
			}
			System.out.print("请输入需要检索城市（仅限城市名，如：东莞、广州等）：");
			search.region = scanner.nextLine();
			System.out.println("处理中...");
			search.search();
			if(search.message.equals("ok")) {
				System.out.println("\n检索结果 1 ：");
				System.out.println("地点名：" + search.name0);
				System.out.println("地址：" + search.address0);
				System.out.println(search.location0 + "\n");
				if(search.name1.equals(null)) {
					System.out.println("检索结果 2 ：");
					System.out.println("地点名：" + search.name1);
					System.out.println("地址：" + search.address1);
					System.out.println(search.location1 + "\n");
				}
			}
		} catch (Exception e) {
            System.out.println("\n输入有误\n");
        }
	}
	
	public void BDip() throws IOException {
		BDIP ip_location = new BDIP();
		try {
			Scanner scanner = new Scanner(System.in);
			System.out.print("请输入需要查询的IP地址（如果输入为空，默认查询本机；输入 0 可返回上一级菜单）：");
			ip_location.ip = scanner.nextLine();
			if(ip_location.ip.equals("0")) {
				System.out.println("\n返回上一级菜单\n");
                return;
			}
			System.out.println("处理中...");
			ip_location.ip_location();
			if(ip_location.message.equals("0")) {
				System.out.println("\n此IP地址的地址信息为：" + ip_location.address);
				System.out.println("所在城市的百度城市代码为：" + ip_location.city_code + "\n");
			}
		}catch (Exception e) {
			System.out.println("\n输入有误\n");
        }
		
	}
	
	public static void BDmap() throws IOException{
		BDMap BDfunction = new BDMap();
		Scanner scanner = new Scanner(System.in);
		while (true) {
			System.out.println("请输入对应数字选择功能：");
            System.out.println("1——地理编码");
            System.out.println("2——路径规划");
            System.out.println("3——地点检索");
            System.out.println("4——IP定位");
            System.out.println("0——返回主菜单");
            
            int Digit = scanner.nextInt();
            switch(Digit) {
            	case 1:
            		BDfunction.BDgeocode();
            		continue;
            	case 2:
            		BDfunction.BDPathPlanning();
            		continue;
            	case 3:
            		BDfunction.BDSearch();
            		continue;
            	case 4:
            		BDfunction.BDip();
            		continue;
            	case 0:
            		System.out.println("\n返回主菜单\n");
            		return;
                default:
                    System.out.println("\n输入有误\n");
            }
        }
	}
}