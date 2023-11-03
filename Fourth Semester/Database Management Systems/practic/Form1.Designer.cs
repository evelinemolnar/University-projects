namespace practic
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridViewParent = new System.Windows.Forms.DataGridView();
            this.dataGridViewChild = new System.Windows.Forms.DataGridView();
            this.buttonAdd = new System.Windows.Forms.Button();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.buttonUpdate = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxTitlu = new System.Windows.Forms.TextBox();
            this.textBoxDescriere = new System.Windows.Forms.TextBox();
            this.textBoxData = new System.Windows.Forms.TextBox();
            this.textBoxBuget = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewParent)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewChild)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewParent
            // 
            this.dataGridViewParent.BackgroundColor = System.Drawing.Color.Thistle;
            this.dataGridViewParent.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewParent.Location = new System.Drawing.Point(24, 21);
            this.dataGridViewParent.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.dataGridViewParent.Name = "dataGridViewParent";
            this.dataGridViewParent.RowHeadersWidth = 82;
            this.dataGridViewParent.RowTemplate.Height = 33;
            this.dataGridViewParent.Size = new System.Drawing.Size(1344, 530);
            this.dataGridViewParent.TabIndex = 0;
            this.dataGridViewParent.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewParentCellClicked);
            // 
            // dataGridViewChild
            // 
            this.dataGridViewChild.BackgroundColor = System.Drawing.Color.Thistle;
            this.dataGridViewChild.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewChild.Location = new System.Drawing.Point(62, 558);
            this.dataGridViewChild.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.dataGridViewChild.Name = "dataGridViewChild";
            this.dataGridViewChild.RowHeadersWidth = 82;
            this.dataGridViewChild.RowTemplate.Height = 33;
            this.dataGridViewChild.Size = new System.Drawing.Size(1373, 477);
            this.dataGridViewChild.TabIndex = 1;
            this.dataGridViewChild.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewChildCellClicked);
            // 
            // buttonAdd
            // 
            this.buttonAdd.BackColor = System.Drawing.Color.MediumPurple;
            this.buttonAdd.Location = new System.Drawing.Point(1522, 633);
            this.buttonAdd.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.buttonAdd.Name = "buttonAdd";
            this.buttonAdd.Size = new System.Drawing.Size(157, 65);
            this.buttonAdd.TabIndex = 2;
            this.buttonAdd.Text = "ADD";
            this.buttonAdd.UseVisualStyleBackColor = false;
            this.buttonAdd.Click += new System.EventHandler(this.ButtonAdd_Click);
            // 
            // buttonDelete
            // 
            this.buttonDelete.BackColor = System.Drawing.Color.MediumPurple;
            this.buttonDelete.Location = new System.Drawing.Point(1522, 775);
            this.buttonDelete.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(147, 71);
            this.buttonDelete.TabIndex = 3;
            this.buttonDelete.Text = "DELETE";
            this.buttonDelete.UseVisualStyleBackColor = false;
            this.buttonDelete.Click += new System.EventHandler(this.ButtonDelete_Click);
            // 
            // buttonUpdate
            // 
            this.buttonUpdate.BackColor = System.Drawing.Color.MediumPurple;
            this.buttonUpdate.Location = new System.Drawing.Point(1522, 918);
            this.buttonUpdate.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.buttonUpdate.Name = "buttonUpdate";
            this.buttonUpdate.Size = new System.Drawing.Size(147, 58);
            this.buttonUpdate.TabIndex = 4;
            this.buttonUpdate.Text = "UPDATE";
            this.buttonUpdate.UseVisualStyleBackColor = false;
            this.buttonUpdate.Click += new System.EventHandler(this.ButtonUpdate_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(1517, 46);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 25);
            this.label1.TabIndex = 5;
            this.label1.Text = "TITLU";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(1485, 187);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(133, 25);
            this.label2.TabIndex = 6;
            this.label2.Text = "DESCRIERE";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(1466, 300);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(192, 25);
            this.label3.TabIndex = 7;
            this.label3.Text = "DATA_DEPUNERII";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(1503, 412);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(84, 25);
            this.label4.TabIndex = 8;
            this.label4.Text = "BUGET";
            // 
            // textBoxTitlu
            // 
            this.textBoxTitlu.Location = new System.Drawing.Point(1455, 100);
            this.textBoxTitlu.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBoxTitlu.Name = "textBoxTitlu";
            this.textBoxTitlu.Size = new System.Drawing.Size(193, 31);
            this.textBoxTitlu.TabIndex = 9;
            // 
            // textBoxDescriere
            // 
            this.textBoxDescriere.Location = new System.Drawing.Point(1455, 227);
            this.textBoxDescriere.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBoxDescriere.Name = "textBoxDescriere";
            this.textBoxDescriere.Size = new System.Drawing.Size(193, 31);
            this.textBoxDescriere.TabIndex = 10;
            // 
            // textBoxData
            // 
            this.textBoxData.Location = new System.Drawing.Point(1455, 352);
            this.textBoxData.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBoxData.Name = "textBoxData";
            this.textBoxData.Size = new System.Drawing.Size(193, 31);
            this.textBoxData.TabIndex = 11;
            // 
            // textBoxBuget
            // 
            this.textBoxBuget.Location = new System.Drawing.Point(1455, 477);
            this.textBoxBuget.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBoxBuget.Name = "textBoxBuget";
            this.textBoxBuget.Size = new System.Drawing.Size(203, 31);
            this.textBoxBuget.TabIndex = 12;
            this.textBoxBuget.TextChanged += new System.EventHandler(this.textBox4_TextChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.BackColor = System.Drawing.Color.Lavender;
            this.ClientSize = new System.Drawing.Size(1729, 1088);
            this.Controls.Add(this.textBoxBuget);
            this.Controls.Add(this.textBoxData);
            this.Controls.Add(this.textBoxDescriere);
            this.Controls.Add(this.textBoxTitlu);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.buttonUpdate);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.buttonAdd);
            this.Controls.Add(this.dataGridViewChild);
            this.Controls.Add(this.dataGridViewParent);
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewParent)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewChild)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewParent;
        private System.Windows.Forms.DataGridView dataGridViewChild;
        private System.Windows.Forms.Button buttonAdd;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.Button buttonUpdate;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBoxTitlu;
        private System.Windows.Forms.TextBox textBoxDescriere;
        private System.Windows.Forms.TextBox textBoxData;
        private System.Windows.Forms.TextBox textBoxBuget;
    }
}

