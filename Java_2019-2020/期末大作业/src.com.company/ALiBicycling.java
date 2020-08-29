package Map;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;

public class ALiBicycling {
    public String origin;
    public String destination;
    public String distance;
    public String duration;

    public void Do_bicycling() throws IOException {
        StringBuilder json = new StringBuilder();
        URL name = new URL("https://restapi.amap" +
                ".com/v4/direction/bicycling?origin="+this.origin+
                "&destination="
                +this.destination+"&key=b3524cc502a4fc39c0d2a2e5cb97b516");
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
        JSONObject data = (JSONObject) jsonObject.get("data");
        JSONArray paths = data.getJSONArray("paths");
        JSONObject temp0 = paths.getJSONObject(Integer.parseInt("0"));
        this.distance = temp0.get("distance").toString();
        this.duration = temp0.get("duration").toString();
    }
}
