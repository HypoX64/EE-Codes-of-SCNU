package com.company;

import com.company.Goods;

public class Clothes extends Goods {
    private String Designer;
    private String Size;

    public void Set_Designer(String temp4) {
        Designer = temp4;
    }

    public void Set_Size(String temp5) {
        Size = temp5;
    }

    public String Get_Designer() {
        return Designer;
    }

    public String Get_Size() {
        return Size;
    }

    // public void Show() {
    //     System.out.println("ID:" + Clothes.Get_Name());
    //     System.out.println("Name:" + Clothes.Get_Name());
    //     System.out.println("Price:" + Clothes.Get_Price);
    //     System.out.println("Among:" + Clothes.Get_Among);
    //     System.out.println("Designer:" + Clothes.Get_Designer);
    //     System.out.println("Size" + Clothes.Get_Size);
    // }
}
