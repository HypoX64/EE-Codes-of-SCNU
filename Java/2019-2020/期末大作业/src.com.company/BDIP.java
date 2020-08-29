//百度地图IP定位功能
package Map;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;

import com.alibaba.fastjson.JSONObject;

public class BDIP {
	public String ip;
	public String address = null;
	public String city_code = null;
	public String message = "0";
	
	public void ip_location() throws IOException {
		StringBuilder json = new StringBuilder();
		URL URL = new URL("https://api.map.baidu.com/location/ip?ip=" + ip 
							+ "&ak=75EYHRd9dg4ful7Qxwn1wWsMQjA3I0Ep&coor=bd09ll");
		/*URL URL = new URL("https://api.map.baidu.com/location/ip?ip=183.63.102.207" 
							+ "&ak=75EYHRd9dg4ful7Qxwn1wWsMQjA3I0Ep&coor=bd09ll");	//测试URL*/
		URLConnection connection = URL.openConnection();
		connection.setDoOutput(true);
			BufferedReader in = new BufferedReader(new InputStreamReader(URL.openStream()));
		
		String inputLine;
		while ((inputLine = in.readLine()) != null) 
			json.append(inputLine);
			
		in.close();
		
		JSONObject jsonObject = JSONObject.parseObject(String.valueOf(json));
		if (jsonObject.get("status").toString().equals("0")) {
			JSONObject content = jsonObject.getJSONObject("content");
			JSONObject address_detail = content.getJSONObject("address_detail");
			String province = address_detail.get("province").toString();
			String city = address_detail.get("city").toString();
			String district = address_detail.get("district").toString();
			String street = address_detail.get("street").toString();
			String street_number = address_detail.get("street_number").toString();
			this.address = province + city + district + street + street_number;
			this.city_code = address_detail.get("city_code").toString();
		}
		else {
			message = jsonObject.get("message").toString();
			System.out.println("\n错误信息：" + message + "\n");
		}
	}
}