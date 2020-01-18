package com.company;
import	java.util.Scanner;

import java.io.IOException;
import java.util.Scanner;
import com.company.*;

public class Main {

    Goods List0 = new Goods();

    public int Check() {
        return List0.Get_ID();
    }


    public void GetList() {
        System.out.println();
        System.out.println("------------------------------");
        System.out.println("ID: " + List0.Get_ID());
        System.out.println("Category: " + List0.Get_Category());
        System.out.println("Price: " + List0.Get_Price());
        System.out.println("Among: " + List0.Get_Among());
        System.out.println("------------------------------");
    }

    public void AddList_Clothes1() {
        List0.Set_ID(1);
        List0.Set_Category("Clothes");
        List0.Set_Price(1000);
        List0.Set_Among();
    }

    public void AddList_Laptops1() {
        List0.Set_ID(3);
        List0.Set_Category("Laptops");
        List0.Set_Price(3000);
        List0.Set_Among();
    }

    public void AddList_Laptops2() {
        List0.Set_ID(4);
        List0.Set_Category("Laptops");
        List0.Set_Price(4000);
        List0.Set_Among();
    }

    public void DeleteList() {
        List0.Set_ID(0);
        List0.Set_Category(null);
        List0.Set_Price(0);
        List0.Set_Among(0);
    }

    public int CheckList() {
        int x, y, z;
        x = List0.Get_Among();
        y = List0.Get_Price();
        z = x * y;
        return z;
    }


    public static void main(String[] args)  {
        // write your code here
        Scanner scanner = new Scanner(System.in);

        Clothes clothes1 = new Clothes();
        Clothes clothes2 = new Clothes();
        Laptops laptops1 = new Laptops();
        Laptops laptops2 = new Laptops();
        Main List1 = new Main();
        Main List2 = new Main();
        Main List3 = new Main();

        clothes1.Set_ID(1);
        clothes1.Set_Category("Clothes");
        clothes1.Set_Price(1000);
        clothes1.Set_Designer("Jimmy");
        clothes1.Set_Size("S,M,L");

        clothes2.Set_ID(2);
        clothes2.Set_Category("Clothes");
        clothes2.Set_Price(2000);
        clothes2.Set_Designer("Ben");
        clothes2.Set_Size("M,L,XL");

        laptops1.Set_ID(3);
        laptops1.Set_Category("Laptops");
        laptops1.Set_Price(3000);
        laptops1.Set_CPU("Intel");
        laptops1.Set_ScreenSize("13.3");

        laptops2.Set_ID(4);
        laptops2.Set_Category("Laptops");
        laptops2.Set_Price(4000);
        laptops2.Set_CPU("AMD");
        laptops2.Set_ScreenSize("15.6");

        while (true) {
            System.out.println("------------------------------");
            System.out.println("Hello,please imput a digit");
            System.out.println("1-显示购物清单");
            System.out.println("2-显示物品列表");
            System.out.println("3-添加商品");
            System.out.println("4-清空购物车");
            System.out.println("5-结算");

            int Digit = scanner.nextInt();

            if (Digit == 1) {
                if (List1.Check() == 0 || List1.Check() == 1 || List1.Check() == 3 || List1.Check() == 4)
                    if (List2.Check() == 0)
                        List1.GetList();
                    else if (List3.Check() == 0) {
                        List1.GetList();
                        List2.GetList();
                    } else {
                        List1.GetList();
                        List2.GetList();
                        List3.GetList();
                    }
            }

            if (Digit == 2) {
                System.out.println();
                System.out.println("------------------------------");
                System.out.println("ID: " + clothes1.Get_ID());
                System.out.println("Category: " + clothes1.Get_Category());
                System.out.println("Price: " + clothes1.Get_Price());
                System.out.println("Designer: " + clothes1.Get_Designer());
                System.out.println("Size: " + clothes1.Get_Size());

                System.out.println();
                System.out.println("ID: " + laptops1.Get_ID());
                System.out.println("Category: " + laptops1.Get_Category());
                System.out.println("Price: " + laptops1.Get_Price());
                System.out.println("Designer: " + laptops1.Get_CPU());
                System.out.println("Size: " + laptops1.Get_ScreenSize());

                System.out.println();
                System.out.println("ID: " + laptops2.Get_ID());
                System.out.println("Category: " + laptops2.Get_Category());
                System.out.println("Price: " + laptops2.Get_Price());
                System.out.println("Designer: " + laptops2.Get_CPU());
                System.out.println("Size: " + laptops2.Get_ScreenSize());
                System.out.println("------------------------------");
            }

            if (Digit == 3) {
                System.out.println("输入商品ＩＤ");
                int temp8 = scanner.nextInt();
                if (temp8 == clothes1.Get_ID()) {
                    if (List1.Check() == clothes1.Get_ID() || List1.Check() == 0) {
                        List1.AddList_Clothes1();
                        System.out.println("Succeed");
                    } else if (List2.Check() == clothes1.Get_ID() || List2.Check() == 0) {
                        List2.AddList_Clothes1();
                        System.out.println("Succeed");
                    } else {
                        List3.AddList_Clothes1();
                        System.out.println("Succeed");
                    }
                } else if (temp8 == laptops1.Get_ID()) {
                    if (List1.Check() == laptops1.Get_ID() || List1.Check() == 0) {
                        List1.AddList_Laptops1();
                        System.out.println("Succeed");
                    } else if (List2.Check() == laptops1.Get_ID() || List2.Check() == 0) {
                        List2.AddList_Laptops1();
                        System.out.println("Succeed");
                    } else {
                        List3.AddList_Laptops1();
                        System.out.println("Succeed");
                    }
                } else if (temp8 == laptops2.Get_ID()) {
                    if (List1.Check() == laptops2.Get_ID() || List1.Check() == 0) {
                        List1.AddList_Laptops2();
                        System.out.println("Succeed");
                    } else if (List2.Check() == laptops2.Get_ID() || List2.Check() == 0) {
                        List2.AddList_Laptops2();
                        System.out.println("Succeed");
                    } else {
                        List3.AddList_Laptops2();
                        System.out.println("Succeed");
                    }
                } else {
                    System.out.println();
                    System.out.println("ID not found");
                }
            }

            if (Digit == 4) {
                List1.DeleteList();
                List2.DeleteList();
                List3.DeleteList();
                System.out.println("Your shopping list has been empted");
                List1.GetList();
            }

            if (Digit == 5) {
                double money, money1, money2, money3;
                if (List1.Check() == 3) {
                    money1 = 0.8 * List1.CheckList();
                } else {
                    money1 = List1.CheckList();
                }
                if (List2.Check() == 3) {
                    money2 = 0.8 * List2.CheckList();
                } else {
                    money2 = List2.CheckList();
                }
                if (List3.Check() == 3) {
                    money3 = 0.8 * List3.CheckList();
                } else {
                    money3 = List3.CheckList();
                }
                money = money1 + money2 + money3;
                System.out.println();
                System.out.println("You should paid");
                System.out.println(money);
                System.out.println("------------------------------");
            }
        }
    }

}
