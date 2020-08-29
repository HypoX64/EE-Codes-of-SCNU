package Map;

import java.net.URL;
import java.io.*;
import java.net.URLConnection;

import com.alibaba.fastjson.JSONObject;

public class ALiIP {
    public String ip;
    public String province;
    public String city;

    public void Do_ip() throws IOException {
        StringBuilder json = new StringBuilder();
        URL name = new URL("https://restapi.amap.com/v3/ip?ip=" + this.ip +
                "&output=json&key=b3524cc502a4fc39c0d2a2e5cb97b516");
//        URL name = new URL("https://restapi.amap.com/v3/ip?ip=114.247.50" +
//        ".2&output=json&key=b3524cc502a4fc39c0d2a2e5cb97b516");
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
        this.province=jsonObject.getString("province");
        this.city=jsonObject.getString("city");
    }
}
