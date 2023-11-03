using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;

namespace problema2
{
    public partial class Form1 : Form
    {
        string connectionString = @"Server=eveline\sqlexpress;Database=Problema2; 
        Integrated Security=true;TrustServerCertificate=true;";

        DataSet ds = new DataSet();
        SqlDataAdapter parentAdapter = new SqlDataAdapter();
        SqlDataAdapter childAdapter = new SqlDataAdapter();
        BindingSource parentBS = new BindingSource();
        BindingSource childBS = new BindingSource();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (var sqlConnection = new SqlConnection(connectionString))
                {
                    sqlConnection.Open();
                    MessageBox.Show("Conexiunea la baza de date a fost realizata cu succes!");
                    parentAdapter.SelectCommand = new SqlCommand("SELECT * FROM Artisti", sqlConnection);
                    childAdapter.SelectCommand = new SqlCommand("SELECT * FROM Melodii", sqlConnection);
                    parentAdapter.Fill(ds, "Artisti");
                    childAdapter.Fill(ds, "Melodii");
                    parentBS.DataSource = ds.Tables["Artisti"];
                    dataGridViewParent.DataSource = parentBS;
                    DataColumn parentColumn = ds.Tables["Artisti"].Columns["cod_artist"];
                    DataColumn childColumn = ds.Tables["Melodii"].Columns["cod_artist"];
                    DataRelation relation = new DataRelation("FK_Artisti_Melodii",
                        parentColumn, childColumn);
                    ds.Relations.Add(relation);
                    childBS.DataSource = parentBS;
                    childBS.DataMember = "FK_Artisti_Melodii";
                    dataGridViewChild.DataSource = childBS;
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }

        private void DataGridViewChildCellClicked(object sender, DataGridViewCellEventArgs e)
        {
            using (var sqlConnection = new SqlConnection(connectionString))
            {
                sqlConnection.Open();
                if (dataGridViewChild.Rows[e.RowIndex] != null)
                {
                    buttonUpdate.Enabled = true;
                    buttonDelete.Enabled = true;
                    buttonAdd.Enabled = false;
                }
            }
        }

        private void DataGridViewParentCellClicked(object sender, DataGridViewCellEventArgs e)
        {
            using (var sqlConnection = new SqlConnection(connectionString))
            {
                sqlConnection.Open();
                if (dataGridViewChild.Rows[e.RowIndex] != null)
                {
                    buttonUpdate.Enabled = false;
                    buttonDelete.Enabled = false;
                    buttonAdd.Enabled = true;
                }
            }
        }

        private void RefreshChildTable()
        {
            using (var sqlConnection = new SqlConnection(connectionString))
            {
                sqlConnection.Open();
                childAdapter.SelectCommand = new SqlCommand("SELECT * FROM Melodii", sqlConnection);
                ds.Tables["Melodii"].Clear();
                childAdapter.Fill(ds, "Melodii");
            }
        }

        private void ButtonDelete_Click(object sender, EventArgs e)
        {
            using (var sqlConnection = new SqlConnection(connectionString))
            {
                sqlConnection.Open();
                SqlCommand deleteCommand = new SqlCommand("DELETE FROM Melodii WHERE cod_melodie = @cod_melodie", sqlConnection);
                deleteCommand.Parameters.Add("@cod_melodie", SqlDbType.Int).Value = dataGridViewChild.CurrentRow.Cells[0].Value;
                deleteCommand.ExecuteNonQuery();
                RefreshChildTable();
            }
        }

        private void ButtonUpdate_Click(object sender, EventArgs e)
        {
            try
            {
                int index = dataGridViewChild.CurrentCell.RowIndex;

                int id = (int)dataGridViewChild.Rows[index].Cells["cod_melodie"].Value;
                int cod_artist = (int)dataGridViewChild.Rows[index].Cells["cod_artist"].Value;
                string titlu = textBoxTitlu.Text;
                string an_lansare = textBoxAn.Text;
                string durata = textBoxDurata.Text;
                using (var sqlConnection = new SqlConnection(connectionString))
                {
                    sqlConnection.Open();
                    childAdapter.UpdateCommand = new SqlCommand("UPDATE Melodii SET titlu = @titlu, an_lansare = @an_lansare, durata = @durata WHERE cod_melodie = @cod_melodie", sqlConnection);
                    childAdapter.UpdateCommand.Parameters.AddWithValue("@cod_melodie", id);
                    childAdapter.UpdateCommand.Parameters.AddWithValue("@titlu", titlu);
                    childAdapter.UpdateCommand.Parameters.AddWithValue("@an_lansare", an_lansare);
                    childAdapter.UpdateCommand.Parameters.AddWithValue("@durata", durata);
                    childAdapter.UpdateCommand.Parameters.AddWithValue("@cod_artist", cod_artist);
                    childAdapter.UpdateCommand.ExecuteNonQuery();
                    RefreshChildTable();
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }

        private void ButtonAdd_Click(object sender, EventArgs e)
        {
            try
            {
                int index = dataGridViewParent.CurrentCell.RowIndex;
                int cod_artist = (int)dataGridViewParent.Rows[index].Cells["cod_artist"].Value;
                string titlu = textBoxTitlu.Text;
                string an_lansare = textBoxAn.Text;
                string durata = textBoxDurata.Text;
                using (var sqlConnection = new SqlConnection(connectionString))
                {
                    sqlConnection.Open();
                    childAdapter.InsertCommand = new SqlCommand("INSERT INTO Melodii VALUES (@titlu, @an_lansare, @durata, @cod_artist)", sqlConnection);
                    childAdapter.InsertCommand.Parameters.AddWithValue("@titlu", titlu);
                    childAdapter.InsertCommand.Parameters.AddWithValue("@an_lansare", an_lansare);
                    childAdapter.InsertCommand.Parameters.AddWithValue("@durata", durata);
                    childAdapter.InsertCommand.Parameters.AddWithValue("@cod_artist", cod_artist);
                    childAdapter.InsertCommand.ExecuteNonQuery();
                    RefreshChildTable();
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }




    }
}
