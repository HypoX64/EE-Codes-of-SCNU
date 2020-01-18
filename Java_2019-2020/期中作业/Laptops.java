package com.company;

import com.company.Goods;

public class Laptops extends Goods {
    private String CPU;
    private String ScreenSize;

    public void Set_CPU(String temp6) {
        CPU = temp6;
    }

    public void Set_ScreenSize(String temp7) {
        ScreenSize = temp7;
    }

    public String Get_CPU() {
        return CPU;
    }

    public String Get_ScreenSize() {
        return ScreenSize;
    }
}
