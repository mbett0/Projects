using System.Diagnostics;

namespace JbmfgPartsDB
{
    public partial class Form1 : Form
    {
        BindingSource partsBindingSource = new BindingSource();
        BindingSource quotesBindingSource = new BindingSource();
        BindingSource ordersBindingSource = new BindingSource();
        public Form1()
        {
            InitializeComponent();
            QuoteCheckBox.Checked = true;
            PartsDAO partsDAO = new PartsDAO();

            partsBindingSource.DataSource = partsDAO.getAllParts();
            dataGridView1.DataSource = partsBindingSource;

            quotesBindingSource.DataSource = partsDAO.getAllQuotes();
            dataGridView2.DataSource = quotesBindingSource;

            ordersBindingSource.DataSource = partsDAO.getAllOrders();
            dataGridView3.DataSource = ordersBindingSource;

        }

        private void LoadParts_Click(object sender, EventArgs e)
        {
            PartsDAO partsDAO = new PartsDAO();
            partsBindingSource.DataSource = partsDAO.getAllParts();

            dataGridView1.DataSource = partsBindingSource;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            PartsDAO partsDAO = new PartsDAO();
            partsBindingSource.DataSource = partsDAO.searchPartNumbers(textBox1.Text);
            dataGridView1.DataSource = partsBindingSource;
            textBox1.Text = String.Empty;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void txt_PDF_TextChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            String result = txt_PartNumber.Text;
            PartsDAO partsDAO = new PartsDAO();
            if (partsDAO.verifyPartNumber(result) == 1)
            {
                MessageBox.Show("Please enter a unique value for the part number", "ERROR: Part With Entered Number Already Exists",
MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                Part part = new Part
                {
                    PartID = result,
                    PDF = txt_PDF.Text
                };
                int addOnePartCheck = partsDAO.addOnePart(part);
                MessageBox.Show(addOnePartCheck + " new part added");
                txt_PDF.Text = String.Empty;
                txt_PartNumber.Text = String.Empty;
            }
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void dataGridView2_CellClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            DataGridView dataGridView = (DataGridView)sender;

            int rowClicked = dataGridView.CurrentRow.Index;

            PartsDAO partsDAO = new PartsDAO();

            quotesBindingSource.DataSource = partsDAO.getQuotes(dataGridView.Rows[rowClicked].Cells[0].Value.ToString());
            dataGridView2.DataSource = quotesBindingSource;
            ordersBindingSource.DataSource = partsDAO.getOrders(dataGridView.Rows[rowClicked].Cells[0].Value.ToString());
            dataGridView3.DataSource = ordersBindingSource;
            txt_oPart.Text = dataGridView.Rows[rowClicked].Cells[0].Value.ToString();
            txt_PdfPartNum.Text = dataGridView.Rows[rowClicked].Cells[0].Value.ToString();

            String filePath = dataGridView.Rows[rowClicked].Cells[1].Value.ToString();
            if (e.ColumnIndex == 1)
            {
                if (File.Exists(filePath))
                {
                    Process.Start("explorer.exe", "/select, " + filePath);
                }
            }
        }

        private void dataGridView3_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            PartsDAO partsDAO = new PartsDAO();
            quotesBindingSource.DataSource = partsDAO.getAllQuotes();

            dataGridView2.DataSource = quotesBindingSource;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            PartsDAO partsDAO = new PartsDAO();
            ordersBindingSource.DataSource = partsDAO.getAllOrders();

            dataGridView3.DataSource = ordersBindingSource;
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void QuoteCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            OrderCheckBox.Checked = !QuoteCheckBox.Checked;
        }

        private void OrderCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            QuoteCheckBox.Checked = !OrderCheckBox.Checked;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            String part = txt_oPart.Text;
            DateTime date = Date_Order.Value;
            int quantity = 0;
            String customer = txt_Customer.Text;
            double price = 0;
            int qoro = 0;

            if (OrderCheckBox.Checked)
            {
                qoro = 1;
            }

            if (!Int32.TryParse(txt_Quantity.Text, out quantity))
            {
                MessageBox.Show("Please enter a number value for quanitity", "ERROR: Quantity Must Be a Number",
MessageBoxButtons.OK, MessageBoxIcon.Error);
                txt_Quantity.Text = String.Empty;
                return;
            }

            if (!Double.TryParse(txt_PPU.Text, out price))
            {
                MessageBox.Show("Please enter a number value for price", "ERROR: Price Must Be a Number",
MessageBoxButtons.OK, MessageBoxIcon.Error);
                txt_PPU.Text = String.Empty;
                return;
            }

            PartsDAO partsDAO = new PartsDAO();
            if (partsDAO.verifyPartNumber(part) == 0) //create func
            {
                MessageBox.Show("Please enter an existing part number", "ERROR: Part Number Does Not Exist",
MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                Order order = new Order
                {
                    PartID = part,
                    Date = date,
                    Quantity = quantity,
                    Customer = customer,
                    Price = price
                };
                int addOneOrderCheck = partsDAO.addOneOrder(order, qoro);
                MessageBox.Show(addOneOrderCheck + " new order/quote added");
                txt_oPart.Text = String.Empty;
                txt_Quantity.Text = String.Empty;
                txt_Customer.Text = String.Empty;
                txt_PPU.Text = String.Empty;
            }
        }

        private void textBox2_TextChanged_1(object sender, EventArgs e)
        {

        }

        private void button6_Click(object sender, EventArgs e)
        {
            String part = txt_DeleteQuote.Text;
            PartsDAO partsDAO = new PartsDAO();

            if (partsDAO.verifyOrderNumber(part) == 0) //checks if it exists
            {
                MessageBox.Show("Please enter an existing order ID", "ERROR: Order ID Does Not Exist",
MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                partsDAO.deleteOrder(part);
                MessageBox.Show("Quote/Order with ID " + part + " was deleted");
                txt_DeleteQuote.Text = String.Empty;
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            String part = txt_PdfPartNum.Text;
            String newLocation = txt_pdfUpdate.Text;
            PartsDAO partsDAO = new PartsDAO();

            if (partsDAO.verifyPartNumber(part) == 0) //checks if it exists
            {
                MessageBox.Show("Please enter an existing part number", "ERROR: Part Number Does Not Exist",
MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                partsDAO.editPDFLocation(part, newLocation);
                MessageBox.Show("Part " + part + " PDF location changed to \n" + newLocation);
                txt_pdfUpdate.Text = String.Empty;
            }
        }
    }
}