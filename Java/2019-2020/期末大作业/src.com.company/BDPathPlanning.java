//百度地图路径规划功能
package Map;

import com.alibaba.fastjson.JSONObject;
import com.alibaba.fastjson.JSONArray;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;

public class BDPathPlanning {
	public String origin;
	public String destination;
	public String riding_distance;
	public int riding_time_h;
	public int riding_time_min;
	public int riding_time_s;
	public String walk_distance;
	public int walk_time_h;
	public int walk_time_min;
	public int walk_time_s;
	public String taxi_distance;
	public int taxi_time_h;
	public int taxi_time_min;
	public int taxi_time_s;
	public String taxi_cost;
	public String bus_cost;
	public int bus_time_h;
	public int bus_time_min;
	public int bus_time_s;
	
	public void riding() throws IOException {
		StringBuilder json1 = new StringBuilder();
		URL URL1 = new URL("http://api.map.baidu.com/directionlite/v1/riding?origin=" + 
				origin + "&destination=" + destination + "&ak=75EYHRd9dg4ful7Qxwn1wWsMQjA3I0Ep");
		/*URL URL1 = new URL("http://api.map.baidu.com/directionlite/v1/riding?" + 
				"origin=40.01116,116.339303&destination=39.936404,116.452562" + 
				"&ak=75EYHRd9dg4ful7Qxwn1wWsMQjA3I0Ep");	//测试URL */
		//此处坐标格式为“纬度（double），经度（double）”，（小数点后不超过6位）
		URLConnection connection1 =URL1.openConnection();
		connection1.setDoOutput(true);
		BufferedReader in1 = new BufferedReader(new InputStreamReader(URL1.openStream()));
		
		String inputLine1;
		while ((inputLine1 = in1.readLine()) != null)
			json1.append(inputLine1);
		in1.close();
		
		JSONObject r_jsonObject = JSONObject.parseObject(String.valueOf(json1));
		JSONObject result1 = r_jsonObject.getJSONObject("result");
		JSONArray Array_r_route = result1.getJSONArray("routes"); //获取数组
		JSONObject r_route = Array_r_route.getJSONObject(0);
		riding_distance = r_route.get("distance").toString();
		String riding_duration = r_route.get("duration").toString();
		//时间由“秒”换算为“时分秒”
		int riding_duration_h = 0;
		int riding_duration_min = 0;
		int riding_duration_s = 0;
		if(Integer.parseInt(riding_duration) > 59) {
			riding_duration_min = Integer.parseInt(riding_duration) / 60;
			riding_duration_s = Integer.parseInt(riding_duration) % 60;
			if(riding_duration_min > 59) {
				riding_duration_h = riding_duration_min / 60;
				riding_duration_min = riding_duration_min % 60;
				}
			}
		else riding_time_s = Integer.parseInt(riding_duration);
		riding_time_h = riding_duration_h;
		riding_time_min = riding_duration_min;
		riding_time_s = riding_duration_s;
	}
	
	public void walking() throws IOException {
		StringBuilder json2 = new StringBuilder();
		URL URL2 = new URL("http://api.map.baidu.com/directionlite/v1/walking?origin=" + 
				origin + "&destination=" + destination + "&ak=75EYHRd9dg4ful7Qxwn1wWsMQjA3I0Ep");
		/*URL URL2 = new URL("http://api.map.baidu.com/directionlite/v1/walking?" + 
				"origin=40.01116,116.339303&destination=39.936404,116.452562" + 
				"&ak=75EYHRd9dg4ful7Qxwn1wWsMQjA3I0Ep");	//测试URL */
		//此处坐标格式为“纬度（double），经度（double）”，（小数点后不超过6位）
		URLConnection connection2 =URL2.openConnection();
		connection2.setDoOutput(true);
		BufferedReader in2 = new BufferedReader(new InputStreamReader(URL2.openStream()));
		
		String inputLine2;
		while ((inputLine2 = in2.readLine()) != null)
			json2.append(inputLine2);
		in2.close();
		
		JSONObject w_jsonObject = JSONObject.parseObject(String.valueOf(json2));
		JSONObject result2 = w_jsonObject.getJSONObject("result");
		JSONArray Array_w_route = result2.getJSONArray("routes"); //获取数组
		JSONObject w_route = Array_w_route.getJSONObject(0);
		walk_distance = w_route.get("distance").toString();
		String walk_duration = w_route.get("duration").toString();
		//时间由“秒”换算为“时分秒”
		int walk_duration_h = 0;
		int walk_duration_min = 0;
		int walk_duration_s = 0;
		if(Integer.parseInt(walk_duration) > 59) {
			walk_duration_min = Integer.parseInt(walk_duration) / 60;
			walk_duration_s = Integer.parseInt(walk_duration) % 60;
			if(walk_duration_min > 59) {
				walk_duration_h = walk_duration_min / 60;
				walk_duration_min = walk_duration_min % 60;
				}
			}
		else walk_time_s = Integer.parseInt(walk_duration);
		walk_time_h = walk_duration_h;
		walk_time_min = walk_duration_min;
		walk_time_s = walk_duration_s;
	}
	
	public void transit() throws IOException {
		StringBuilder json3 = new StringBuilder();
		URL URL3 = new URL("http://api.map.baidu.com/directionlite/v1/transit?origin=" + 
				origin + "&destination=" + destination + "&ak=75EYHRd9dg4ful7Qxwn1wWsMQjA3I0Ep");
		//URL URL3 = new URL("http://api.map.baidu.com/directionlite/v1/transit?origin=40.01116,116.339303&destination=39.936404,116.452562&ak=75EYHRd9dg4ful7Qxwn1wWsMQjA3I0Ep");//����URL
		//此处坐标格式为“纬度（double），经度（double）”，（小数点后不超过6位）
		URLConnection connection1 =URL3.openConnection();
		connection1.setDoOutput(true);
		BufferedReader in3 = new BufferedReader(new InputStreamReader(URL3.openStream()));
		
		String inputLine3;
		while ((inputLine3 = in3.readLine()) != null)
			json3.append(inputLine3);
		in3.close();
		
		JSONObject t_jsonObject = JSONObject.parseObject(String.valueOf(json3));
		JSONObject result3 = t_jsonObject.getJSONObject("result");
		
		/*----------------taxi----------------*/
		JSONObject taxi = result3.getJSONObject("taxi");
		taxi_distance = taxi.getString("distance").toString();
		String taxi_duration = taxi.getString("duration").toString();
		int taxi_duration_h = 0;
		int taxi_duration_min = 0;
		int taxi_duration_s = 0;
		if(Integer.parseInt(taxi_duration) > 59) {
			taxi_duration_min = Integer.parseInt(taxi_duration) / 60;
        	taxi_duration_s = Integer.parseInt(taxi_duration) % 60;
        	if(taxi_duration_min > 59) {
        		taxi_duration_h = taxi_duration_min / 60;
        		taxi_duration_min = taxi_duration_min % 60;
        	}
		}
		else taxi_duration_s = Integer.parseInt(taxi_duration);
    	taxi_time_h = taxi_duration_h;
		taxi_time_min = taxi_duration_min;
		taxi_time_s = taxi_duration_s;
		JSONArray taxi_detail = taxi.getJSONArray("detail"); //获取数组
		JSONObject t_cost = taxi_detail.getJSONObject(0);
		taxi_cost = t_cost.get("total_price").toString();
		
		/*----------------bus----------------*/
		JSONArray b_route = result3.getJSONArray("routes"); //获取数组
		JSONObject best_bus_route = b_route.getJSONObject(0);
		bus_cost = best_bus_route.getJSONArray("line_price").getJSONObject(0).get("line_price").toString();
		String bus_duration = best_bus_route.get("duration").toString();
		//时间由“秒”换算为“时分秒”
		int bus_duration_h = 0;
		int bus_duration_min = 0;
		int bus_duration_s = 0;
		if(Integer.parseInt(bus_duration) > 59) {
			bus_duration_min = Integer.parseInt(bus_duration) / 60;
        	bus_duration_s = Integer.parseInt(bus_duration) % 60;
        	if(bus_duration_min > 59) {
        		bus_duration_h = bus_duration_min / 60;
        		bus_duration_min = bus_duration_min % 60;
        	}
		}
		else bus_duration_s = Integer.parseInt(bus_duration);
    	bus_time_h = bus_duration_h;
		bus_time_min = bus_duration_min;
		bus_time_s = bus_duration_s;
	}
}