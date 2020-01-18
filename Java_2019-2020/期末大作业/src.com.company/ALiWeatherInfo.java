package Map;

import java.net.URL;
import java.io.*;
import java.net.URLConnection;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

public class ALiWeatherInfo {
	public String city;

	public String date00;
	public String dayweather00;
	public String daywind00;
	public String week00;
	public String daypower00;
	public String daytemp00;
	public String nightwind00;
	public String nighttemp00;
	public String nightweather00;
	public String nightpower00;

	public String date01;
	public String dayweather01;
	public String daywind01;
	public String week01;
	public String daypower01;
	public String daytemp01;
	public String nightwind01;
	public String nighttemp01;
	public String nightweather01;
	public String nightpower01;

	public String date02;
	public String dayweather02;
	public String daywind02;
	public String week02;
	public String daypower02;
	public String daytemp02;
	public String nightwind02;
	public String nighttemp02;
	public String nightweather02;
	public String nightpower02;

	public String date03;
	public String dayweather03;
	public String daywind03;
	public String week03;
	public String daypower03;
	public String daytemp03;
	public String nightwind03;
	public String nighttemp03;
	public String nightweather03;
	public String nightpower03;

	public void Do_weatherInfo() throws IOException {
		StringBuilder json = new StringBuilder();
		URL name = new URL("https://restapi.amap" + ".com/v3/weather/weatherInfo?city=" + this.city
				+ "&extensions=all&key=b3524cc502a4fc39c0d2a2e5cb97b516");
//        URL name = new URL("https://restapi.amap.com/v3/ip?ip=114.247.50" +
//        ".2&output=json&key=b3524cc502a4fc39c0d2a2e5cb97b516");
		URLConnection connection = name.openConnection();
		connection.setDoOutput(true);
		BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
		String str;
		while ((str = in.readLine()) != null) {
			// System.out.print(str);
			json.append(str);
		}
		in.close();

		JSONObject jsonObject = JSONObject.parseObject(String.valueOf(json));
		JSONArray forecasts = jsonObject.getJSONArray("forecasts");
		JSONObject temp0 = forecasts.getJSONObject(Integer.parseInt("0"));
		JSONArray casts = temp0.getJSONArray("casts");
		JSONObject temp00 = casts.getJSONObject(Integer.parseInt("0"));
		JSONObject temp01 = casts.getJSONObject(Integer.parseInt("1"));
		JSONObject temp02 = casts.getJSONObject(Integer.parseInt("2"));
		JSONObject temp03 = casts.getJSONObject(Integer.parseInt("3"));

		this.date00 = temp00.get("date").toString();
		this.dayweather00 = temp00.get("dayweather").toString();
		this.daywind00 = temp00.get("daywind").toString();
		this.week00 = temp00.get("week").toString();
		this.daypower00 = temp00.get("daypower").toString();
		this.daytemp00 = temp00.get("daytemp").toString();
		this.nightwind00 = temp00.get("nightwind").toString();
		this.nighttemp00 = temp00.get("nighttemp").toString();
		this.nightweather00 = temp00.get("nightweather").toString();
		this.nightpower00 = temp00.get("nightpower").toString();

		this.date01 = temp01.get("date").toString();
		this.dayweather01 = temp01.get("dayweather").toString();
		this.daywind01 = temp01.get("daywind").toString();
		this.week01 = temp01.get("week").toString();
		this.daypower01 = temp01.get("daypower").toString();
		this.daytemp01 = temp01.get("daytemp").toString();
		this.nightwind01 = temp01.get("nightwind").toString();
		this.nighttemp01 = temp01.get("nighttemp").toString();
		this.nightweather01 = temp01.get("nightweather").toString();
		this.nightpower01 = temp01.get("nightpower").toString();

		this.date02 = temp02.get("date").toString();
		this.dayweather02 = temp02.get("dayweather").toString();
		this.daywind02 = temp02.get("daywind").toString();
		this.week02 = temp02.get("week").toString();
		this.daypower02 = temp02.get("daypower").toString();
		this.daytemp02 = temp02.get("daytemp").toString();
		this.nightwind02 = temp02.get("nightwind").toString();
		this.nighttemp02 = temp02.get("nighttemp").toString();
		this.nightweather02 = temp02.get("nightweather").toString();
		this.nightpower02 = temp02.get("nightpower").toString();

		this.date03 = temp03.get("date").toString();
		this.dayweather03 = temp03.get("dayweather").toString();
		this.daywind03 = temp03.get("daywind").toString();
		this.week03 = temp03.get("week").toString();
		this.daypower03 = temp03.get("daypower").toString();
		this.daytemp03 = temp03.get("daytemp").toString();
		this.nightwind03 = temp03.get("nightwind").toString();
		this.nighttemp03 = temp03.get("nighttemp").toString();
		this.nightweather03 = temp03.get("nightweather").toString();
		this.nightpower03 = temp03.get("nightpower").toString();
	}
}
