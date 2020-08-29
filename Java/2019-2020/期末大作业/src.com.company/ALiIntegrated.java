package Map;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;

public class ALiIntegrated {
    public String city;
    public String cityd;
    public String origin;
    public String destination;
    public String distance;
    public String taxi_cost;
    public String cost;
    public String duration;

    public void Do_integrated() throws IOException {
        StringBuilder json = new StringBuilder();
        URL name = new URL("https://restapi.amap.com/v3/direction/transit/integrated" +
                "?key=b3524cc502a4fc39c0d2a2e5cb97b516&origin=" + this.origin +
                "&destination" +
                "=" + this.destination + "&city=" + this.city + "&cityd=" + this.cityd + "&strategy=0" +
                "&nightflag=0");
//        URL name = new URL("https://restapi.amap.com/v3/direction/transit/integrated" +
//                "?key=b3524cc502a4fc39c0d2a2e5cb97b516&origin=116.481028,39" +
//                ".989643&destination=116.434446,39" +
//                ".90816&city=北京&cityd=北京&strategy=0&nightflag=0");
        URLConnection connection = name.openConnection();
        connection.setDoOutput(true);
        BufferedReader in =
                new BufferedReader(new InputStreamReader(connection.getInputStream()));
        String str;
        while ((str = in.readLine()) != null) {
            json.append(str);
        }
        in.close();

        JSONObject jsonObject = JSONObject.parseObject(String.valueOf(json));
        JSONObject route = (JSONObject) jsonObject.get("route");
        this.distance = route.get("distance").toString();
        this.taxi_cost = route.get("taxi_cost").toString();
        JSONArray transits=route.getJSONArray("transits");
        JSONObject temp0=transits.getJSONObject(Integer.parseInt("0"));
        this.cost=temp0.get("cost").toString();
        this.duration = temp0.get("duration").toString();
    }
}
