using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;
using System.Configuration;
using System.Collections.Generic;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Reflection.Emit;

namespace lab1

{
    /*
    <appSettings>
		<add key = "ParentTableName" value="Clienti"/>
		<add key = "ChildTableName" value="Facturi"/>
		<add key = "ChildNumberOfColumns" value="3"/>
		<add key = "ChildLabelNames" value="rez_id,client_id,valoare"/>
		<add key = "ColumnNamesInsertParameters" value="@rez_id,@client_id,@valoare"/>
		<add key = "UpdateQuery" value="update Facturi set @rez_id=rez_id, client_id=@client_id, valoare=@valoare where id=@id"/>
		<add key = "SelectQuery" value="select * from Facturi"/>
		<add key = "SelectParent" value="select * from Clienti"/>
		<add key = "SelectChild" value="select * from Facturi where client_id=@id"/>
		<add key = "DeleteChild" value="delete from Facturi where id=@id"/>
	</appSettings>
    
     <appSettings>
		<add key ="ParentTableName" value="Clienti"/>
		<add key ="ChildTableName" value="Rezervari"/>
		<add key ="ChildNumberOfColumns" value="5"/>
		<add key ="ChildLabelNames" value="client_id,admin_id,check_in,check_out,status_id"/>
		<add key="ColumnNamesInsertParameters" value="@client_id,@admin_id,@check_in,@check_out,@status_id"/>
		<add key="UpdateQuery" value="update Rezervari set client_id=@client_id, admin_id=@admin_id, check_in=@check_in, check_out=@check_out, status_id=@status_id where id=@id"/>
		<add key="SelectQuery" value="select * from Rezervari"/>
		<add key="SelectParent" value="select * from Clienti"/>
		<add key="SelectChild" value="select * from Rezervari where client_id=@id"/>
		<add key="DeleteChild" value="delete from Rezervari where id=@id"/>
	</appSettings>
    */
    public partial class Form1 : Form
    {
        SqlConnection connection = new SqlConnection(@"Server=eveline\sqlexpress;Database=Hotels; 
        Integrated Security=true;TrustServerCertificate=true;");
        private string childTableName = ConfigurationManager.AppSettings["ChildTableName"];
        private string parentTableName = ConfigurationManager.AppSettings["ParentTableName"];
        private SqlDataAdapter sqlDataAdapter = new SqlDataAdapter();
        private System.Windows.Forms.TextBox[] textBoxes;
        private System.Windows.Forms.Label[] labels;
        private List<string> columnNames = new List<string>(ConfigurationManager.AppSettings["ChildLabelNames"].Split(','));
        private List<string> paramsNames = new List<string>(ConfigurationManager.AppSettings["ColumnNamesInsertParameters"].Split(','));
        private string columnNamesInsertParameters = ConfigurationManager.AppSettings["ColumnNamesInsertParameters"];
        private int nr = Convert.ToInt32(ConfigurationManager.AppSettings["ChildNumberOfColumns"]);

        public Form1()
        {
            InitializeComponent();
            InitializeGridViews();
            
        }

        

        private void InitializeGridViews()
        {
            dataGridViewParent.SelectionChanged += new EventHandler(LoadChildren);
            string select = ConfigurationManager.AppSettings["SelectParent"];
            sqlDataAdapter.SelectCommand = new SqlCommand(select, connection);
            DataSet dataSet = new DataSet();
            sqlDataAdapter.Fill(dataSet);
            dataGridViewParent.DataSource = dataSet.Tables[0];

            buttonSterge.Enabled = false;
            buttonActualizeaza.Enabled = false;
        }

        private void LoadChildren(object sender, EventArgs e)
        {
            try
            {
                int parentId = (int)dataGridViewParent.CurrentRow.Cells[0].Value;
                string select = ConfigurationManager.AppSettings["SelectChild"];
                SqlCommand cmd = new SqlCommand(select, connection);
                cmd.Parameters.AddWithValue("@id", parentId);
                SqlDataAdapter daChild = new SqlDataAdapter(cmd);
                DataSet dataSet = new DataSet();
                daChild.Fill(dataSet);
                dataGridViewChild.DataSource = dataSet.Tables[0];
            }
            catch (Exception ex)
            {
                DataSet dataSet = new DataSet();
                dataGridViewChild.DataSource = dataSet;
            }
        }

        private void DataGridViewCellChildrenClicked(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                if (dataGridViewChild.Rows[e.RowIndex] != null)
                {
                    buttonActualizeaza.Enabled = true;
                    buttonSterge.Enabled = true;
                    buttonAdauga.Enabled = false;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                connection.Close();
            }
        }

        private void addbtn_Click(object sender, EventArgs e)
        {
            try
            {
                if (dataGridViewParent.CurrentCell != null)
                {
                    int index = dataGridViewParent.CurrentCell.RowIndex;
                    string idSelectedParent = dataGridViewParent.Rows[index].Cells["id"].FormattedValue.ToString();
                    Form formAdaugare = new FormAdaugare(idSelectedParent);
                    formAdaugare.ShowDialog();
                    LoadChildren(null, null);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                connection.Close();
            }

        }

        private void deletebtn_Click(object sender, EventArgs e)
        {
            try
            {
                int index = dataGridViewChild.CurrentCell.RowIndex;
                string childId = dataGridViewChild.Rows[index].Cells[0].FormattedValue.ToString();
                DialogResult dialogResult = MessageBox.Show("Cofirmati stergerea inregistrarii cu id " + childId + "?", "Confirmare stergere", MessageBoxButtons.OKCancel);
                if (dialogResult == DialogResult.OK)
                {
                    string delete = ConfigurationManager.AppSettings["DeleteChild"];
                    SqlCommand cmd = new SqlCommand(delete, connection);
                    cmd.Parameters.AddWithValue("@id", childId);
                    SqlDataAdapter daChild = new SqlDataAdapter(cmd);
                    DataSet dataSet = new DataSet();
                    connection.Open();
                    cmd.ExecuteNonQuery();
                    LoadChildren(null, null);
                    connection.Close();
                    MessageBox.Show("Succes!", "Notificare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void updatebtn_Click(object sender, EventArgs e)
        {
            try
            {
                if (dataGridViewChild.CurrentCell != null)
                {
                    int childIndex = dataGridViewChild.CurrentCell.RowIndex;
                    string confirmare = "Doriti sa schimbati linia selectata in:\n";
                    for (int i = 0; i < nr; i++)
                    {
                        confirmare = confirmare + paramsNames[i] + ": " + dataGridViewChild.Rows[childIndex].Cells[i + 1].Value + "\n";
                    }
                    DialogResult dialogResult = MessageBox.Show(confirmare, "Confirmare actualizare", MessageBoxButtons.OKCancel);
                    if (dialogResult == DialogResult.OK)
                    {

                        string update = ConfigurationManager.AppSettings["UpdateQuery"];
                        SqlCommand cmd = new SqlCommand(update, connection);
                        for (int i = 0; i < nr; i++)
                        {
                            cmd.Parameters.AddWithValue(paramsNames[i], dataGridViewChild.Rows[childIndex].Cells[i + 1].Value);
                        }
                        cmd.Parameters.AddWithValue("@id", (int)dataGridViewChild.Rows[childIndex].Cells[0].Value);
                        connection.Open();
                        cmd.ExecuteNonQuery();
                        connection.Close();

                        MessageBox.Show("Succes!", "Notificare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        LoadChildren(null, null);
                    }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                connection.Close();
            }
        }

        private void DataGridViewCellClickedParent(object sender, DataGridViewCellEventArgs e)
        {
            buttonAdauga.Enabled = true;
            buttonActualizeaza.Enabled = false;
            buttonSterge.Enabled = false;
        }


    }
}
