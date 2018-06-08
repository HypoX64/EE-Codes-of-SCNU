using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace calculator
{
    public partial class Form1 : Form
    {

        int flag_sym = 0;
        int flag_equ = 0;
        int flag_err = 0;
        int flag_dot = 0;
        public Form1()
        {
            this.BackColor = Color.White;
            this.TransparencyKey = Color.White;
            this.Opacity = 0.9;//窗体透明度调整

            InitializeComponent();
        }

        private void shownum(String str)//输入栏显示方法
        {
            if (lab1.Text.Length>10)//不能输入超过10个数
            {
            }
            else
            {
                if (flag_equ == 1)//如果一直按等于号，防止程序卡死
                {
                    lab1.Text = lab1.Text+str;
                    flag_equ = 0;
                }
                else
                {
                    if ((lab1.Text) != "0"||str==".")  //如果输入栏为零进行处理的判断
                    {
                        lab1.Text = lab1.Text + str;
                    }
                    else    
                    {
                        lab1.Text = str;
                    }
                }
            }
 
        }

        private void showsymbol(String str)//符号栏显示方法
        {
            if (flag_sym == 0)
            {
                lab2.Text = str;
                lab3.Text = lab1.Text;
                lab1.Text = "0";
            }
            else
            {
                lab2.Text = str;
            }
            flag_sym++;
            flag_dot = 0;
            flag_equ = 0;
        }

        private void button0_Click(object sender, EventArgs e)
        {
            shownum("0");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            shownum("1");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            shownum("2");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            shownum("3");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            shownum("4");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            shownum("5");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            shownum("6");
        }

        private void button7_Click(object sender, EventArgs e)
        {
            shownum("7");
        }

        private void button8_Click(object sender, EventArgs e)
        {
            shownum("8");
        }

        private void button9_Click(object sender, EventArgs e)
        {
            shownum("9");
        }

        private void button_add_Click(object sender, EventArgs e)
        {
            showsymbol("+");
        }

        private void button_sub_Click(object sender, EventArgs e)
        {
            showsymbol("-");
        }

        private void button_mul_Click(object sender, EventArgs e)
        {
            showsymbol("×");
        }

        private void button_div_Click(object sender, EventArgs e)
        {
            showsymbol("÷");
        }

        private void button_equal_Click(object sender, EventArgs e)
        {
            flag_sym = 0;
            if (lab3.Text == "")
            {
                flag_equ = 1;
            }
            else
            {
                double input1 = Convert.ToDouble(lab3.Text.Trim());
                double input2 = Convert.ToDouble(lab1.Text.Trim());
                double output = 0.0;
                switch (lab2.Text)
                {
                    case "+":
                        output = input1 + input2;
                        break;
                    case "-":                       
                        output = input1 - input2;
                        break;
                    case "×":
                        output = input1 * input2;
                        break;
                    case "÷":
                        output = input1 / input2;
                        if (input2==0)
                        {
                            flag_err = 1;
                        }
                        break;
                    default:

                        break;
                }
                if (flag_err==0)
                {
                    lab_history1.Text = lab3.Text + " " + lab2.Text + " " + lab1.Text + " " + "=";
                    lab_history2.Text = output.ToString();
                    lab1.Text = output.ToString();
                    lab2.Text = "";
                    lab3.Text = "";
                }
                else
                {
                    MessageBox.Show("这怎么可能有结果？！");
                    lab1.Text = "";
                    lab2.Text = "";
                    lab3.Text = "";
                    flag_err = 0;
                }
                flag_equ = 1;
                flag_dot = 0;
                
            }

        }

        private void button_dot_Click(object sender, EventArgs e)
        {
            if (flag_dot==0)
            {
                shownum(".");
                flag_dot = 1;
            }
            
        }

        private void button_pm_Click(object sender, EventArgs e)
        {
            double input1 = Convert.ToDouble(lab1.Text);
            input1 = 0 - input1;
            lab1.Text = input1.ToString();
        }

        private void button_del_Click(object sender, EventArgs e)
        {
            if (lab1.Text.Length==1)
            {
                lab1.Text = "0";
            }
            else
            {
                lab1.Text = lab1.Text.Remove(lab1.Text.Length - 1);
            }
        }

        private void button_c_Click(object sender, EventArgs e)
        {
            lab1.Text = "0";
            lab2.Text = "";
            lab3.Text = "";
            flag_sym = 0;
            flag_equ = 0;
            flag_err = 0;
            flag_dot = 0;
        }

        private void button_ce_Click(object sender, EventArgs e)
        {
            lab1.Text = "0";
            lab2.Text = "";
            lab3.Text = "";
            flag_sym = 0;
            flag_equ = 0;
            flag_err = 0;
            flag_dot = 0;
        }

        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {
            switch (e.KeyChar)
            {
                case '0':
                    button0.PerformClick();
                    e.Handled = true;
                    break;
                case '1':
                    button1.PerformClick();
                    e.Handled = true;
                    break;
                case '2':
                    button2.PerformClick();
                    e.Handled = true;
                    break;
                case '3':
                    button3.PerformClick();
                    e.Handled = true;
                    break;
                case '4':
                    button4.PerformClick();
                    e.Handled = true;
                    break;
                case '5':
                    button5.PerformClick();
                    e.Handled = true;
                    break;
                case '6':
                    button6.PerformClick();
                    e.Handled = true;
                    break;
                case '7':
                    button7.PerformClick();
                    e.Handled = true;
                    break;
                case '8':
                    button8.PerformClick();
                    e.Handled = true;
                    break;
                case '9':
                    button9.PerformClick();
                    e.Handled = true;
                    break;
                case '+':
                    button_add.PerformClick();
                    e.Handled = true;
                    break;
                case '-':
                    button_sub.PerformClick();
                    e.Handled = true;
                    break;
                case '*':
                    button_mul.PerformClick();
                    e.Handled = true;
                    break;
                case '/':
                    button_div.PerformClick();
                    e.Handled = true;
                    break;
                case '\b':
                    button_del.PerformClick();
                    e.Handled = true;
                    break;
                case '.':
                    button_dot.PerformClick();
                    e.Handled = true;
                    break;
                case 'c':
                    button_c.PerformClick();
                    e.Handled = true;
                    break;
                case (char)10:
                    button_equal.PerformClick();
                    e.Handled = true;
                    break;

                default:
                    break;
            }
        }

        private void lab_history2_Click(object sender, EventArgs e)
        {
            lab1.Text = lab_history2.Text;
        }
    }
}
