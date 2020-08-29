package com.company;

public class Goods {
    private int ID;
    private String Category;
    private int Price;
    private int Among;

    public void Set_ID(int temp0) {
        ID = temp0;
    }

    public void Set_Category(String temp1) {
        Category = temp1;
    }

    public void Set_Price(int temp2) {
        Price = temp2;
    }

    public void Set_Among(int temp3) {
        Among = temp3;
    }

    public void Set_Among() {
        Among = Among+1;
    }

    public int Get_ID() {
        return ID;
    }

    public String Get_Category() {
        return Category;
    }

    public int Get_Price() {
        return Price;
    }

    public int Get_Among() {
        return Among;
    }
}
