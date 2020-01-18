//百度地图地理编码功能
package Map;

import com.alibaba.fastjson.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;
import java.text.DecimalFormat;
import java.util.Scanner;

public class BDgeocode {
	public int return0;
	public String address;
	public String location;
	public String formatchange_location;
	
	public void geocode() throws IOException {
		StringBuilder json = new StringBuilder();
		Scanner scanner = new Scanner(System.in);
		address = scanner.nextLine();
		if(address.equals("0")) {
			return0 = 1;
			return;
		}
		URL URL = new URL("http://api.map.baidu.com/geocoding/v3/?address=" + address + "&output=json&ak=75EYHRd9dg4ful7Qxwn1wWsMQjA3I0Ep");
		URLConnection connection = URL.openConnection();
		connection.setDoOutput(true);
			BufferedReader in = new BufferedReader(new InputStreamReader(URL.openStream()));
		
		String inputLine;
		while ((inputLine = in.readLine()) != null)
			json.append(inputLine);
		in.close();
		
		JSONObject jsonObject = JSONObject.parseObject(String.valueOf(json));
		JSONObject result = jsonObject.getJSONObject("result");
		JSONObject location = result.getJSONObject("location");
		this.location = "经度：" + location.get("lng").toString() + "，纬度：" + location.get("lat").toString();
		
		String lng = location.get("lng").toString();
		String lat = location.get("lat").toString();
		this.formatchange_location = FormatChange(lng,lat);
	}
	
	public String FormatChange(String a , String b) throws IOException {	//接收坐标为：“经度，纬度”
		DecimalFormat df = new DecimalFormat("0.000000");
		float f1 = Float.parseFloat(a);
        float f2 = Float.parseFloat(b);
        String s1 = df.format(f1);
        String s2 = df.format(f2);
        String s = s2 + "," + s1;	//此时转换后坐标为：“纬度，经度”
        return s;
	}
}