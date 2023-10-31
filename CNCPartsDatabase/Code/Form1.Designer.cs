namespace JbmfgPartsDB
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            LoadParts = new Button();
            dataGridView1 = new DataGridView();
            button1 = new Button();
            textBox1 = new TextBox();
            groupBox1 = new GroupBox();
            button2 = new Button();
            txt_PDF = new TextBox();
            txt_PartNumber = new TextBox();
            label1 = new Label();
            label2 = new Label();
            dataGridView2 = new DataGridView();
            button3 = new Button();
            button4 = new Button();
            dataGridView3 = new DataGridView();
            groupBox2 = new GroupBox();
            txt_PPU = new TextBox();
            label7 = new Label();
            OrderCheckBox = new CheckBox();
            QuoteCheckBox = new CheckBox();
            Date_Order = new DateTimePicker();
            button5 = new Button();
            txt_Customer = new TextBox();
            txt_Quantity = new TextBox();
            txt_oPart = new TextBox();
            label6 = new Label();
            label5 = new Label();
            label4 = new Label();
            label3 = new Label();
            groupBox3 = new GroupBox();
            button6 = new Button();
            txt_DeleteQuote = new TextBox();
            label8 = new Label();
            groupBox4 = new GroupBox();
            txt_PdfPartNum = new TextBox();
            label10 = new Label();
            button7 = new Button();
            txt_pdfUpdate = new TextBox();
            label9 = new Label();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)dataGridView2).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView3).BeginInit();
            groupBox2.SuspendLayout();
            groupBox3.SuspendLayout();
            groupBox4.SuspendLayout();
            SuspendLayout();
            // 
            // LoadParts
            // 
            LoadParts.Location = new Point(13, 14);
            LoadParts.Margin = new Padding(4, 5, 4, 5);
            LoadParts.Name = "LoadParts";
            LoadParts.Size = new Size(163, 38);
            LoadParts.TabIndex = 0;
            LoadParts.Text = "Display All Parts";
            LoadParts.UseVisualStyleBackColor = true;
            LoadParts.Click += LoadParts_Click;
            // 
            // dataGridView1
            // 
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Location = new Point(13, 62);
            dataGridView1.Margin = new Padding(4, 5, 4, 5);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.RowHeadersWidth = 62;
            dataGridView1.RowTemplate.Height = 25;
            dataGridView1.Size = new Size(360, 896);
            dataGridView1.TabIndex = 1;
            dataGridView1.CellClick += dataGridView1_CellClick;
            // 
            // button1
            // 
            button1.BackColor = SystemColors.ControlLightLight;
            button1.Location = new Point(202, 966);
            button1.Name = "button1";
            button1.Size = new Size(171, 38);
            button1.TabIndex = 2;
            button1.Text = "Search By Part#";
            button1.UseVisualStyleBackColor = false;
            button1.Click += button1_Click;
            // 
            // textBox1
            // 
            textBox1.Location = new Point(13, 970);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(183, 31);
            textBox1.TabIndex = 1;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(button2);
            groupBox1.Controls.Add(txt_PDF);
            groupBox1.Controls.Add(txt_PartNumber);
            groupBox1.Controls.Add(label1);
            groupBox1.Controls.Add(label2);
            groupBox1.Location = new Point(13, 1007);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(360, 169);
            groupBox1.TabIndex = 4;
            groupBox1.TabStop = false;
            groupBox1.Text = "Add New Part";
            // 
            // button2
            // 
            button2.Location = new Point(242, 122);
            button2.Name = "button2";
            button2.Size = new Size(105, 34);
            button2.TabIndex = 9;
            button2.Text = "Add";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // txt_PDF
            // 
            txt_PDF.Location = new Point(197, 85);
            txt_PDF.Name = "txt_PDF";
            txt_PDF.Size = new Size(150, 31);
            txt_PDF.TabIndex = 3;
            txt_PDF.TextChanged += txt_PDF_TextChanged;
            // 
            // txt_PartNumber
            // 
            txt_PartNumber.Location = new Point(197, 38);
            txt_PartNumber.Name = "txt_PartNumber";
            txt_PartNumber.Size = new Size(150, 31);
            txt_PartNumber.TabIndex = 2;
            txt_PartNumber.TextChanged += textBox2_TextChanged;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(6, 38);
            label1.Name = "label1";
            label1.Size = new Size(58, 25);
            label1.TabIndex = 5;
            label1.Text = "Part #";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(6, 85);
            label2.Name = "label2";
            label2.Size = new Size(189, 25);
            label2.TabIndex = 6;
            label2.Text = "PDF Link/File Location:";
            // 
            // dataGridView2
            // 
            dataGridView2.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView2.Location = new Point(426, 53);
            dataGridView2.Name = "dataGridView2";
            dataGridView2.RowHeadersWidth = 62;
            dataGridView2.RowTemplate.Height = 33;
            dataGridView2.Size = new Size(923, 536);
            dataGridView2.TabIndex = 5;
            dataGridView2.CellClick += dataGridView2_CellClick;
            // 
            // button3
            // 
            button3.Location = new Point(426, 12);
            button3.Name = "button3";
            button3.Size = new Size(207, 34);
            button3.TabIndex = 6;
            button3.Text = "Display Recent Quotes";
            button3.UseVisualStyleBackColor = true;
            button3.Click += button3_Click;
            // 
            // button4
            // 
            button4.Location = new Point(426, 595);
            button4.Name = "button4";
            button4.Size = new Size(207, 34);
            button4.TabIndex = 8;
            button4.Text = "Display Recent Orders";
            button4.UseVisualStyleBackColor = true;
            button4.Click += button4_Click;
            // 
            // dataGridView3
            // 
            dataGridView3.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView3.Location = new Point(426, 635);
            dataGridView3.Name = "dataGridView3";
            dataGridView3.RowHeadersWidth = 62;
            dataGridView3.RowTemplate.Height = 33;
            dataGridView3.Size = new Size(923, 230);
            dataGridView3.TabIndex = 7;
            dataGridView3.CellContentClick += dataGridView3_CellContentClick;
            // 
            // groupBox2
            // 
            groupBox2.Controls.Add(txt_PPU);
            groupBox2.Controls.Add(label7);
            groupBox2.Controls.Add(OrderCheckBox);
            groupBox2.Controls.Add(QuoteCheckBox);
            groupBox2.Controls.Add(Date_Order);
            groupBox2.Controls.Add(button5);
            groupBox2.Controls.Add(txt_Customer);
            groupBox2.Controls.Add(txt_Quantity);
            groupBox2.Controls.Add(txt_oPart);
            groupBox2.Controls.Add(label6);
            groupBox2.Controls.Add(label5);
            groupBox2.Controls.Add(label4);
            groupBox2.Controls.Add(label3);
            groupBox2.Location = new Point(426, 871);
            groupBox2.Name = "groupBox2";
            groupBox2.Size = new Size(411, 307);
            groupBox2.TabIndex = 9;
            groupBox2.TabStop = false;
            groupBox2.Text = "Add Orders and Quotes";
            // 
            // txt_PPU
            // 
            txt_PPU.Location = new Point(121, 181);
            txt_PPU.Name = "txt_PPU";
            txt_PPU.Size = new Size(282, 31);
            txt_PPU.TabIndex = 8;
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Location = new Point(6, 182);
            label7.Name = "label7";
            label7.Size = new Size(119, 25);
            label7.TabIndex = 13;
            label7.Text = "Price Per Unit:";
            // 
            // OrderCheckBox
            // 
            OrderCheckBox.AutoSize = true;
            OrderCheckBox.Location = new Point(306, 219);
            OrderCheckBox.Name = "OrderCheckBox";
            OrderCheckBox.Size = new Size(84, 29);
            OrderCheckBox.TabIndex = 10;
            OrderCheckBox.Text = "Order";
            OrderCheckBox.UseVisualStyleBackColor = true;
            OrderCheckBox.CheckedChanged += OrderCheckBox_CheckedChanged;
            // 
            // QuoteCheckBox
            // 
            QuoteCheckBox.AutoSize = true;
            QuoteCheckBox.Location = new Point(212, 219);
            QuoteCheckBox.Name = "QuoteCheckBox";
            QuoteCheckBox.Size = new Size(88, 29);
            QuoteCheckBox.TabIndex = 9;
            QuoteCheckBox.Text = "Quote";
            QuoteCheckBox.UseVisualStyleBackColor = true;
            QuoteCheckBox.CheckedChanged += QuoteCheckBox_CheckedChanged;
            // 
            // Date_Order
            // 
            Date_Order.Location = new Point(103, 68);
            Date_Order.Name = "Date_Order";
            Date_Order.Size = new Size(300, 31);
            Date_Order.TabIndex = 5;
            // 
            // button5
            // 
            button5.Location = new Point(289, 260);
            button5.Name = "button5";
            button5.Size = new Size(112, 34);
            button5.TabIndex = 11;
            button5.Text = "Add";
            button5.UseVisualStyleBackColor = true;
            button5.Click += button5_Click;
            // 
            // txt_Customer
            // 
            txt_Customer.Location = new Point(121, 144);
            txt_Customer.Name = "txt_Customer";
            txt_Customer.Size = new Size(282, 31);
            txt_Customer.TabIndex = 7;
            // 
            // txt_Quantity
            // 
            txt_Quantity.Location = new Point(121, 105);
            txt_Quantity.Name = "txt_Quantity";
            txt_Quantity.Size = new Size(281, 31);
            txt_Quantity.TabIndex = 6;
            // 
            // txt_oPart
            // 
            txt_oPart.Location = new Point(121, 30);
            txt_oPart.Name = "txt_oPart";
            txt_oPart.Size = new Size(281, 31);
            txt_oPart.TabIndex = 4;
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(6, 144);
            label6.Name = "label6";
            label6.Size = new Size(93, 25);
            label6.TabIndex = 3;
            label6.Text = "Customer:";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(6, 105);
            label5.Name = "label5";
            label5.Size = new Size(84, 25);
            label5.TabIndex = 2;
            label5.Text = "Quantity:";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(6, 68);
            label4.Name = "label4";
            label4.Size = new Size(49, 25);
            label4.TabIndex = 1;
            label4.Text = "Date";
            label4.Click += label4_Click;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(6, 33);
            label3.Name = "label3";
            label3.Size = new Size(58, 25);
            label3.TabIndex = 0;
            label3.Text = "Part #";
            // 
            // groupBox3
            // 
            groupBox3.Controls.Add(button6);
            groupBox3.Controls.Add(txt_DeleteQuote);
            groupBox3.Controls.Add(label8);
            groupBox3.Location = new Point(843, 871);
            groupBox3.Name = "groupBox3";
            groupBox3.Size = new Size(240, 120);
            groupBox3.TabIndex = 10;
            groupBox3.TabStop = false;
            groupBox3.Text = "Delete Quotes/Orders";
            // 
            // button6
            // 
            button6.Location = new Point(122, 68);
            button6.Name = "button6";
            button6.Size = new Size(112, 34);
            button6.TabIndex = 14;
            button6.Text = "Delete";
            button6.UseVisualStyleBackColor = true;
            button6.Click += button6_Click;
            // 
            // txt_DeleteQuote
            // 
            txt_DeleteQuote.Location = new Point(144, 24);
            txt_DeleteQuote.Name = "txt_DeleteQuote";
            txt_DeleteQuote.Size = new Size(90, 31);
            txt_DeleteQuote.TabIndex = 13;
            txt_DeleteQuote.TextChanged += textBox2_TextChanged_1;
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Location = new Point(6, 27);
            label8.Name = "label8";
            label8.Size = new Size(142, 25);
            label8.TabIndex = 12;
            label8.Text = "Quote/Order ID:";
            // 
            // groupBox4
            // 
            groupBox4.Controls.Add(txt_PdfPartNum);
            groupBox4.Controls.Add(label10);
            groupBox4.Controls.Add(button7);
            groupBox4.Controls.Add(txt_pdfUpdate);
            groupBox4.Controls.Add(label9);
            groupBox4.Location = new Point(1089, 871);
            groupBox4.Name = "groupBox4";
            groupBox4.Size = new Size(270, 175);
            groupBox4.TabIndex = 11;
            groupBox4.TabStop = false;
            groupBox4.Text = "Change Part PDF Location";
            // 
            // txt_PdfPartNum
            // 
            txt_PdfPartNum.Location = new Point(70, 24);
            txt_PdfPartNum.Name = "txt_PdfPartNum";
            txt_PdfPartNum.Size = new Size(194, 31);
            txt_PdfPartNum.TabIndex = 17;
            // 
            // label10
            // 
            label10.AutoSize = true;
            label10.Location = new Point(6, 30);
            label10.Name = "label10";
            label10.Size = new Size(58, 25);
            label10.TabIndex = 16;
            label10.Text = "Part #";
            // 
            // button7
            // 
            button7.Location = new Point(148, 126);
            button7.Name = "button7";
            button7.Size = new Size(112, 34);
            button7.TabIndex = 15;
            button7.Text = "Update";
            button7.UseVisualStyleBackColor = true;
            button7.Click += button7_Click;
            // 
            // txt_pdfUpdate
            // 
            txt_pdfUpdate.Location = new Point(6, 89);
            txt_pdfUpdate.Name = "txt_pdfUpdate";
            txt_pdfUpdate.Size = new Size(258, 31);
            txt_pdfUpdate.TabIndex = 18;
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Location = new Point(6, 61);
            label9.Name = "label9";
            label9.Size = new Size(160, 25);
            label9.TabIndex = 13;
            label9.Text = "New PDF Location:";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = SystemColors.Control;
            BackgroundImageLayout = ImageLayout.Center;
            ClientSize = new Size(1371, 1190);
            Controls.Add(groupBox4);
            Controls.Add(groupBox3);
            Controls.Add(groupBox2);
            Controls.Add(button4);
            Controls.Add(dataGridView3);
            Controls.Add(button3);
            Controls.Add(dataGridView2);
            Controls.Add(groupBox1);
            Controls.Add(textBox1);
            Controls.Add(button1);
            Controls.Add(dataGridView1);
            Controls.Add(LoadParts);
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            Margin = new Padding(4, 5, 4, 5);
            Name = "Form1";
            Text = "Load All Parts";
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)dataGridView2).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView3).EndInit();
            groupBox2.ResumeLayout(false);
            groupBox2.PerformLayout();
            groupBox3.ResumeLayout(false);
            groupBox3.PerformLayout();
            groupBox4.ResumeLayout(false);
            groupBox4.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button LoadParts;
        private DataGridView dataGridView1;
        private Button button1;
        private TextBox textBox1;
        private GroupBox groupBox1;
        private TextBox txt_PDF;
        private TextBox txt_PartNumber;
        private Label label1;
        private Label label2;
        private Button button2;
        private DataGridView dataGridView2;
        private Button button3;
        private Button button4;
        private DataGridView dataGridView3;
        private GroupBox groupBox2;
        private Label label4;
        private Label label3;
        private Button button5;
        private TextBox txt_Customer;
        private TextBox txt_Quantity;
        private TextBox txt_oPart;
        private Label label6;
        private Label label5;
        private CheckBox OrderCheckBox;
        private CheckBox QuoteCheckBox;
        private DateTimePicker Date_Order;
        private TextBox txt_PPU;
        private Label label7;
        private GroupBox groupBox3;
        private GroupBox groupBox4;
        private Label label8;
        private Button button6;
        private TextBox txt_DeleteQuote;
        private Label label10;
        private Button button7;
        private TextBox txt_pdfUpdate;
        private Label label9;
        private TextBox txt_PdfPartNum;
    }
}