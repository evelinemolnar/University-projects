using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab1
{
    public partial class FormAdaugare : Form
    {
        private readonly string idParent;
        SqlConnection connection = new SqlConnection(@"Server=eveline\sqlexpress;Database=Hotels; 
        Integrated Security=true;TrustServerCertificate=true;");
        private int nr = Convert.ToInt32(ConfigurationManager.AppSettings["ChildNumberOfColumns"]);
        private System.Windows.Forms.TextBox[] textBoxes;
        private System.Windows.Forms.Label[] labels;
        private List<string> columnNames = new List<string>(ConfigurationManager.AppSettings["ChildLabelNames"].Split(','));
        private string childTableName = ConfigurationManager.AppSettings["ChildTableName"];
        private string parentTableName = ConfigurationManager.AppSettings["ParentTableName"];
        private string columnNamesInsertParameters = ConfigurationManager.AppSettings["ColumnNamesInsertParameters"];
        private List<string> paramsNames = new List<string>(ConfigurationManager.AppSettings["ColumnNamesInsertParameters"].Split(','));
        public FormAdaugare(string idParent)
        {
            this.idParent = idParent;
            InitializeComponent();
            InitializePanel();
            labelId.Text += this.idParent;
        }
        private void InitializePanel()
        {

            textBoxes = new System.Windows.Forms.TextBox[nr];
            labels = new System.Windows.Forms.Label[nr];

            for (int i = 0; i < nr; i++)
            {
                textBoxes[i] = new System.Windows.Forms.TextBox();
                labels[i] = new System.Windows.Forms.Label();
                labels[i].Text = columnNames[i];
            }
            for (int i = 0; i < nr; i++)
            {
                panel.Controls.Add(labels[i]);
                panel.Controls.Add(textBoxes[i]);
            }
        }

        private void ButtonAdauga_Click(object sender, EventArgs e)
        {
            try
            {
                string confirmare = "Doriti sa adaugati entitatea cu id-ul parinte : " + idParent + ":\n";
                for (int i = 0; i < nr; i++)
                {
                    confirmare = confirmare + paramsNames[i] + ": " + textBoxes[i].Text + "\n";
                }


                DialogResult dialogResult = MessageBox.Show(confirmare, "Confirmare ", MessageBoxButtons.OKCancel);
                if (dialogResult == DialogResult.OK)
                {
                    SqlCommand cmd = new SqlCommand("insert into " + childTableName + " ( " + ConfigurationManager.AppSettings["ChildLabelNames"] + " ) values ( " + columnNamesInsertParameters + " )", connection);
                    
                    for (int i = 0; i < nr; i++)
                    {
                        cmd.Parameters.AddWithValue(paramsNames[i], textBoxes[i].Text);
                    }
                    SqlDataAdapter daChild = new SqlDataAdapter(cmd);
                    DataSet dataSet = new DataSet();
                    daChild.Fill(dataSet);

                    MessageBox.Show("Succes!", "Notificare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Notificare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }
    }
}
