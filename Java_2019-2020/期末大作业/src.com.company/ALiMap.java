//高德地图
package Map;

import java.io.IOException;
import java.util.Scanner;

public class ALiMap {

    public void Geocode() throws IOException {
        try {
            ALiGeocode geocode0 = new ALiGeocode();
            System.out.println("请输入地址（输入0可返回上一级菜单）");
            geocode0.Do_geocode();
            if (geocode0.return0==1){
                System.out.println("\n返回上一级菜单\n");
                return;
            }
            System.out.println("\n地址的结构化地址信息为：" + geocode0.formatted_address);
            System.out.println("地址的区域编码为：" + geocode0.adcode);
            System.out.println("地址的坐标点为：" + geocode0.location + "\n");
        } catch (Exception e) {
            System.out.println("\n输入有误\n");
        }
    }

    public void Direction() throws IOException {
        try {
            ALiGeocode geocode1 = new ALiGeocode();
            ALiGeocode geocode2 = new ALiGeocode();

            ALiIntegrated integrated0 = new ALiIntegrated();
            ALiDriving driving0 = new ALiDriving();
            ALiBicycling bicycling0 = new ALiBicycling();

            System.out.println("请输入出发点（输入0可返回上一级主菜单）");
            geocode1.Do_geocode();
            if (geocode1.return0==1){
                System.out.println("\n返回上一级菜单\n");
                return;
            }
            integrated0.origin = geocode1.location;
            integrated0.city = geocode1.address;
            driving0.origin = geocode1.location;
            bicycling0.origin = geocode1.location;

            System.out.println("请输入目的地（输入0可返回上一级菜单）");
            geocode2.Do_geocode();
            if (geocode2.return0==1){
                System.out.println("\n返回上一级菜单\n");
                return;
            }

            integrated0.destination = geocode2.location;
            integrated0.cityd = geocode2.address;
            driving0.destination = geocode2.location;
            bicycling0.destination = geocode2.location;

            integrated0.Do_integrated();
            driving0.Do_driving();
            bicycling0.Do_bicycling();

            System.out.println("\n起点和终点的步行距离：" + integrated0.distance + "米");
            System.out.println("出租车费用：" + integrated0.taxi_cost + "元");
            System.out.println("最快捷公交换乘方案价格：" + integrated0.cost + "元");
            System.out.println("最快捷公交换乘方案预计时间：" + integrated0.duration + "秒");
            System.out.println("行驶距离：" + driving0.distance + "米");
            System.out.println("预计行驶时间：" + driving0.duration + "秒");
            System.out.println("导航策略：" + driving0.strategy);
            System.out.println("此导航方案道路收费：" + driving0.tolls + "元");
            System.out.println("此导航方案红绿灯个数：" + driving0.traffic_lights + "个");
            System.out.println("起终点的骑行距离：" + bicycling0.distance + "米");
            System.out.println("起终点的骑行时间：" + bicycling0.duration + "秒\n");
        } catch (Exception e) {
            System.out.println("\n输入有误\n");
        }
    }

    public void Text() throws IOException {
        try {
            ALiText text0 = new ALiText();
            Scanner scanner = new Scanner(System.in);
            System.out.print("请输入查询关键词（如：美食、学校）（输入0可返回上一级菜单）\n");
            text0.keywords = scanner.nextLine();
            if (text0.keywords.equals("0")){
                System.out.println("\n返回上一级菜单\n");
                return;
            }
            System.out.print("处理中");
//        System.out.print("请输入查询类型");
//        this.types=scanner.nextLine();
            System.out.print("请输入查询城市（仅限城市名，如：东莞、广州）（输入0可返回上一级菜单）\n");
            text0.city = scanner.nextLine();
            if (text0.city.equals("0")){
                System.out.println("\n返回上一级菜单\n");
                return;
            }
            System.out.print("处理中");
            text0.Do_text();
            System.out.println("\n\n名称：" + text0.name);
            System.out.println("类型：" + text0.type);
            System.out.println("地址：" + text0.pname + text0.cityname + text0.adname + text0.address + "\n");
        } catch (Exception e) {
            System.out.println("\n输入有误\n");
        }
    }

    public void Around() throws IOException {
        try {
            ALiAround around0 = new ALiAround();
            ALiGeocode geocode0 = new ALiGeocode();
            System.out.println("请输入地点（输入0可返回上一级菜单）");
            if (geocode0.return0==1){
                System.out.println("\n返回上一级菜单\n");
                return;
            }
            geocode0.Do_geocode();
            around0.location = geocode0.location;
            Scanner scanner = new Scanner(System.in);
            System.out.print("请输入查询关键词（如：美食、学校）（输入0可返回上一级菜单）\n");
            around0.keywords = scanner.nextLine();
            if (around0.keywords.equals("0")){
                System.out.println("\n返回上一级菜单\n");
                return;
            }
            System.out.print("处理中");
            around0.Do_around();
            System.out.println("\n\n名称：" + around0.name);
            System.out.println("类型：" + around0.type);
            System.out.println("地址：" + around0.pname + around0.cityname + around0.adname + around0.address + "\n");
        } catch (Exception e) {
            System.out.println("\n输入有误\n");
        }
    }

    public void Ip() throws IOException {
        try {
            ALiIP ip0 = new ALiIP();
            System.out.println("请输入需要搜索的IP地址（仅支持国内）（输入0可返回上一级菜单）");
            Scanner scanner = new Scanner(System.in);
            ip0.ip = scanner.nextLine();
            if (ip0.ip.equals("0")){
                System.out.println("\n返回上一级菜单\n");
                return;
            }
            System.out.print("处理中");
            ip0.Do_ip();

            System.out.println("\n\nIP地址：" + ip0.province + ip0.city + "\n");
        } catch (Exception e) {
            System.out.println("\n输入有误\n");
        }
    }

    public void WeatherInfo() throws IOException {
        try {
            ALiGeocode geocode0 = new ALiGeocode();
            ALiWeatherInfo weatherInfo0 = new ALiWeatherInfo();

            System.out.println("请输入地点（输入0可返回上一级菜单）");
            geocode0.Do_geocode();
            if (geocode0.return0==1){
                System.out.println("\n返回上一级菜单\n");
                return;
            }
            weatherInfo0.city = geocode0.adcode;
            weatherInfo0.Do_weatherInfo();

            System.out.println("\n" + geocode0.formatted_address + "今日的天气：");
            System.out.println("日期：\t\t\t\t\t" + weatherInfo0.date00);
            System.out.println("星期：\t\t\t\t\t" + weatherInfo0.week00);
            System.out.println("白天天气现象：\t\t\t" + weatherInfo0.dayweather00);
            System.out.println("晚上天气现象：\t\t\t" + weatherInfo0.nightweather00);
            System.out.println("白天温度（摄氏度）：\t\t" + weatherInfo0.daytemp00);
            System.out.println("晚上温度（摄氏度）：\t\t" + weatherInfo0.nighttemp00);
            System.out.println("白天风向：\t\t\t\t" + weatherInfo0.daywind00);
            System.out.println("晚上风向：\t\t\t\t" + weatherInfo0.nightwind00);
            System.out.println("白天风力（级）：\t\t\t" + weatherInfo0.daypower00);
            System.out.println("晚上风力（级）：\t\t\t" + weatherInfo0.nightpower00);

            System.out.println("\n" + geocode0.formatted_address + "未来三日的天气：");
            System.out.println("\n" + geocode0.formatted_address + "明日的天气：");
            System.out.println("日期：\t\t\t\t\t" + weatherInfo0.date01);
            System.out.println("星期：\t\t\t\t\t" + weatherInfo0.week01);
            System.out.println("白天天气现象：\t\t\t" + weatherInfo0.dayweather01);
            System.out.println("晚上天气现象：\t\t\t" + weatherInfo0.nightweather01);
            System.out.println("白天温度（摄氏度）：\t\t" + weatherInfo0.daytemp01);
            System.out.println("晚上温度（摄氏度）：\t\t" + weatherInfo0.nighttemp01);
            System.out.println("白天风向：\t\t\t\t" + weatherInfo0.daywind01);
            System.out.println("晚上风向：\t\t\t\t" + weatherInfo0.nightwind01);
            System.out.println("白天风力（级）：\t\t\t" + weatherInfo0.daypower01);
            System.out.println("晚上风力（级）：\t\t\t" + weatherInfo0.nightpower01);

            System.out.println("\n" + geocode0.formatted_address + "后天的天气：");
            System.out.println("日期：\t\t\t\t\t" + weatherInfo0.date02);
            System.out.println("星期：\t\t\t\t\t" + weatherInfo0.week02);
            System.out.println("白天天气现象：\t\t\t" + weatherInfo0.dayweather02);
            System.out.println("晚上天气现象：\t\t\t" + weatherInfo0.nightweather02);
            System.out.println("白天温度（摄氏度）：\t\t" + weatherInfo0.daytemp02);
            System.out.println("晚上温度（摄氏度）：\t\t" + weatherInfo0.nighttemp02);
            System.out.println("白天风向：\t\t\t\t" + weatherInfo0.daywind02);
            System.out.println("晚上风向：\t\t\t\t" + weatherInfo0.nightwind02);
            System.out.println("白天风力（级）：\t\t\t" + weatherInfo0.daypower02);
            System.out.println("晚上风力（级）：\t\t\t" + weatherInfo0.nightpower02);

            System.out.println("\n" + geocode0.formatted_address + "大后天的天气：");
            System.out.println("日期：\t\t\t\t\t" + weatherInfo0.date03);
            System.out.println("星期：\t\t\t\t\t" + weatherInfo0.week03);
            System.out.println("白天天气现象：\t\t\t" + weatherInfo0.dayweather03);
            System.out.println("晚上天气现象：\t\t\t" + weatherInfo0.nightweather03);
            System.out.println("白天温度（摄氏度）：\t\t" + weatherInfo0.daytemp03);
            System.out.println("晚上温度（摄氏度）：\t\t" + weatherInfo0.nighttemp03);
            System.out.println("白天风向：\t\t\t\t" + weatherInfo0.daywind03);
            System.out.println("晚上风向：\t\t\t\t" + weatherInfo0.nightwind03);
            System.out.println("白天风力（级）：\t\t\t" + weatherInfo0.daypower03);
            System.out.println("晚上风力（级）：\t\t\t" + weatherInfo0.nightpower03 + "\n");
        } catch (Exception e) {
            System.out.println("\n输入有误\n");
        }
    }

    public static void Alimap() throws IOException {
        // write your code here
    	ALiMap function = new ALiMap();
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.print("选择功能\n");
            System.out.print("输入1——地理编码\n");
            System.out.print("输入2——路径规划\n");
            System.out.print("输入3——关键字搜索\n");
            System.out.print("输入4——周边搜索\n");
            System.out.print("输入5——IP定位\n");
            System.out.print("输入6——天气查询\n");
            System.out.print("输入0——返回主菜单\n");

            String Digit = scanner.nextLine();
            switch (Digit) {
                case "1":
                    function.Geocode();
                    continue;
                case "2":
                    function.Direction();
                    continue;
                case "3":
                    function.Text();
                    continue;
                case "4":
                    function.Around();
                    continue;
                case "5":
                    function.Ip();
                    continue;
                case "6":
                    function.WeatherInfo();
                    continue;
                case "0":
                    System.out.println("\n返回主菜单\n");
                    return;
                default:
                    System.out.println("输入有误\n");
            }
        }
    }
}
