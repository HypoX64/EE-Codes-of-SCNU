//百度地图地点检索功能
package Map;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;

public class BDSearch {
	public String query;
	public String region;
	public String name0 = null;
	public String address0 = null;
	public String location0 = null;
	public String name1 = "0";
	public String address1 = null;
	public String location1 = null;
	public String message = null;
	
	
	public void search() throws IOException {
		StringBuilder json = new StringBuilder();
		URL URL = new URL("http://api.map.baidu.com/place/v2/search?query=" + query + "&region=" + region 
						+ "&page_size=2&output=json&ak=75EYHRd9dg4ful7Qxwn1wWsMQjA3I0Ep");
		/*URL URL = new URL("http://api.map.baidu.com/place/v2/search?query=ATM机&tag=银行&region=广州" 
						+ "&output=json&ak=75EYHRd9dg4ful7Qxwn1wWsMQjA3I0Ep");		//测试URL*/
		URLConnection connection = URL.openConnection();
		connection.setDoOutput(true);
			BufferedReader in = new BufferedReader(new InputStreamReader(URL.openStream()));
		
		String inputLine;
		while ((inputLine = in.readLine()) != null)
			json.append(inputLine);
		in.close();
		
		JSONObject jsonObject = JSONObject.parseObject(String.valueOf(json));
		if(jsonObject.get("status").toString().equals("0")) {
			message = jsonObject.get("message").toString();
			JSONArray result = jsonObject.getJSONArray("results");
			
			JSONObject info0 = result.getJSONObject(0);
			name0 = info0.get("name").toString();
			address0 = info0.get("address").toString();
			JSONObject locat0 = info0.getJSONObject("location");
			location0 = "经度：" + locat0.get("lng").toString() + "，纬度：" + locat0.get("lat").toString();
			
			JSONObject info1 = result.getJSONObject(1);
			name1 = info1.get("name").toString();
			address1 = info1.get("address").toString();
			JSONObject locat1 = info1.getJSONObject("location");
			location1 = "经度：" + locat1.get("lng").toString() + "，纬度：" + locat1.get("lat").toString();
			
		}
		else {
			message = jsonObject.get("message").toString();
			System.out.println("\n错误信息：" + message + "\n");
		}
	}
}