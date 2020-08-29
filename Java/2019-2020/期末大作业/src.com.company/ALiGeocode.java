package Map;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;
import java.util.Scanner;

public class ALiGeocode {
	public int return0;

	public String address;
	public String formatted_address;
	public String adcode;
	public String citycode;
	public String location;

	public void Do_geocode() throws IOException {
		StringBuilder json = new StringBuilder();
		Scanner scanner = new Scanner(System.in);
		this.address = scanner.nextLine();
		if (this.address.equals("0")) {
			this.return0 = 1;
			return;
		}
		System.out.print("处理中\n");
		URL name = new URL("https://restapi.amap" + ".com/v3/geocode/geo?key=b3524cc502a4fc39c0d2a2e5cb97b516"
				+ "&address=" + this.address + "&city=");
		URLConnection connection = name.openConnection();
		connection.setDoOutput(true);
		BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
		String str;
		while ((str = in.readLine()) != null) {
			json.append(str);
		}
		in.close();

		JSONObject jsonObject = JSONObject.parseObject(String.valueOf(json));
		JSONArray geocodes = jsonObject.getJSONArray("geocodes");
//        System.out.println(geocodes); //用于测试是否接成功转换geocodes
		JSONObject temp0 = (JSONObject) geocodes.get(Integer.parseInt("0"));
		this.formatted_address = temp0.get("formatted_address").toString();
		this.adcode = temp0.get("adcode").toString();
		this.citycode = temp0.get("citycode").toString();
		this.location = temp0.get("location").toString();
	}
}
