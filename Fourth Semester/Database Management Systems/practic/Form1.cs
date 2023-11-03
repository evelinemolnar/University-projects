using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace practic
{
    public partial class Form1 : Form
    {
        
        string connectionString = @"Server=eveline\sqlexpress;Database=S12023; 
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
                    //de modificat selecturile
                    parentAdapter.SelectCommand = new SqlCommand("SELECT * FROM Autori", sqlConnection);
                    childAdapter.SelectCommand = new SqlCommand("SELECT * FROM Proiecte", sqlConnection);
                    parentAdapter.Fill(ds, "Autori");
                    childAdapter.Fill(ds, "Proiecte");
                    parentBS.DataSource = ds.Tables["Autori"];
                    dataGridViewParent.DataSource = parentBS;
                    DataColumn parentColumn = ds.Tables["Autori"].Columns["cod_autor"];
                    DataColumn childColumn = ds.Tables["Proiecte"].Columns["cod_autor"];
                    DataRelation relation = new DataRelation("FK_Autori_Proiecte",
                        parentColumn, childColumn);
                    ds.Relations.Add(relation);
                    childBS.DataSource = parentBS;
                    childBS.DataMember = "FK_Autori_Proiecte";
                    dataGridViewChild.DataSource = childBS;
                }
            }
            catch (Exception ex)
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
                childAdapter.SelectCommand = new SqlCommand("SELECT * FROM Proiecte", sqlConnection);
                ds.Tables["Proiecte"].Clear();
                childAdapter.Fill(ds, "Proiecte");
            }
        }

        private void ButtonDelete_Click(object sender, EventArgs e)
        {
            using (var sqlConnection = new SqlConnection(connectionString))
            {
                sqlConnection.Open();
                SqlCommand deleteCommand = new SqlCommand("DELETE FROM Proiecte WHERE cod_proiect = @cod_proiect", sqlConnection);
                deleteCommand.Parameters.Add("@cod_proiect", SqlDbType.Int).Value = dataGridViewChild.CurrentRow.Cells[0].Value;
                deleteCommand.ExecuteNonQuery();
                RefreshChildTable();
            }
        }

        private void ButtonUpdate_Click(object sender, EventArgs e)
        {
            try
            {
                int index = dataGridViewChild.CurrentCell.RowIndex;

                int id = (int)dataGridViewChild.Rows[index].Cells["cod_proiect"].Value;
                int cod_autor = (int)dataGridViewChild.Rows[index].Cells["cod_autor"].Value;
                string titlu = textBoxTitlu.Text;
                string descriere = textBoxDescriere.Text;
                string data_depunerii = textBoxData.Text;
                string buget = textBoxBuget.Text;
                using (var sqlConnection = new SqlConnection(connectionString))
                {
                    sqlConnection.Open();
                    childAdapter.UpdateCommand = new SqlCommand("UPDATE Proiecte SET titlu = @titlu, descriere = @descriere, data_depunerii = @data_depunerii, buget = @buget WHERE cod_proiect = @cod_proiect", sqlConnection);
                    childAdapter.UpdateCommand.Parameters.AddWithValue("@cod_proiect", id);
                    childAdapter.UpdateCommand.Parameters.AddWithValue("@titlu", titlu);
                    childAdapter.UpdateCommand.Parameters.AddWithValue("@descriere", descriere);
                    childAdapter.UpdateCommand.Parameters.AddWithValue("@data_depunerii", data_depunerii);
                    childAdapter.UpdateCommand.Parameters.AddWithValue("@buget", buget);
                    childAdapter.UpdateCommand.Parameters.AddWithValue("@cod_autor", cod_autor);
                    childAdapter.UpdateCommand.ExecuteNonQuery();
                    RefreshChildTable();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        private void ButtonAdd_Click(object sender, EventArgs e)
        {
            try
            {
                int index = dataGridViewParent.CurrentCell.RowIndex;
                int cod_autor = (int)dataGridViewParent.Rows[index].Cells["cod_autor"].Value;
                string titlu = textBoxTitlu.Text;
                string descriere = textBoxDescriere.Text;
                string data_depunerii = textBoxData.Text;
                string buget = textBoxBuget.Text;
                using (var sqlConnection = new SqlConnection(connectionString))
                {
                    sqlConnection.Open();
                    childAdapter.InsertCommand = new SqlCommand("INSERT INTO Proiecte VALUES (@titlu, @descriere, @data_depunerii, @buget, @cod_autor)", sqlConnection);
                    childAdapter.InsertCommand.Parameters.AddWithValue("@titlu", titlu);
                    childAdapter.InsertCommand.Parameters.AddWithValue("@descriere", descriere);
                    childAdapter.InsertCommand.Parameters.AddWithValue("@data_depunerii", data_depunerii);
                    childAdapter.InsertCommand.Parameters.AddWithValue("@buget", buget);
                    childAdapter.InsertCommand.Parameters.AddWithValue("@cod_autor", cod_autor);
                    childAdapter.InsertCommand.ExecuteNonQuery();
                    RefreshChildTable();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }
    }

}
