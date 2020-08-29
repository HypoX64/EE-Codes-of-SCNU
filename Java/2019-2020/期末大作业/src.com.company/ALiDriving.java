package Map;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;

public class ALiDriving {
    public String origin;
    public String destination;
    public String distance;
    public String duration;
    public String strategy;
    public String tolls;
    public String traffic_lights;

    public void Do_driving() throws IOException {
        StringBuilder json = new StringBuilder();
        URL name = new URL("https://restapi.amap" +
                ".com/v3/direction/driving?key" +
                "=b3524cc502a4fc39c0d2a2e5cb97b516&origin=" + this.origin +
                "&destination=" + this.destination + "&originid" +
                "=&destinationid" +
                "=&extensions" +
                "=base&strategy=0" +
                "&waypoints=&avoidpolygons=&avoidroad=");
//        URL name = new URL("https://restapi.amap
//        .com/v3/direction/transit/integrated" +
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
        JSONArray paths = route.getJSONArray("paths");
        JSONObject temp0 = paths.getJSONObject(Integer.parseInt("0"));
        this.distance = temp0.get("distance").toString();
        this.duration = temp0.get("duration").toString();
        this.strategy = temp0.get("strategy").toString();
        this.tolls = temp0.get("tolls").toString();
        this.traffic_lights = temp0.get("traffic_lights").toString();
    }
}
