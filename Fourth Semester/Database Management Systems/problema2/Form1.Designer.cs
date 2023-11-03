namespace problema2
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
            this.textBoxTitlu = new System.Windows.Forms.TextBox();
            this.textBoxAn = new System.Windows.Forms.TextBox();
            this.textBoxDurata = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.buttonAdd = new System.Windows.Forms.Button();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.buttonUpdate = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewParent)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewChild)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewParent
            // 
            this.dataGridViewParent.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewParent.Location = new System.Drawing.Point(33, 30);
            this.dataGridViewParent.Name = "dataGridViewParent";
            this.dataGridViewParent.RowHeadersWidth = 82;
            this.dataGridViewParent.RowTemplate.Height = 33;
            this.dataGridViewParent.Size = new System.Drawing.Size(978, 535);
            this.dataGridViewParent.TabIndex = 0;
            this.dataGridViewParent.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewParentCellClicked);
            // 
            // dataGridViewChild
            // 
            this.dataGridViewChild.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewChild.Location = new System.Drawing.Point(299, 619);
            this.dataGridViewChild.Name = "dataGridViewChild";
            this.dataGridViewChild.RowHeadersWidth = 82;
            this.dataGridViewChild.RowTemplate.Height = 33;
            this.dataGridViewChild.Size = new System.Drawing.Size(1043, 541);
            this.dataGridViewChild.TabIndex = 1;
            this.dataGridViewChild.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewChildCellClicked);
            // 
            // textBoxTitlu
            // 
            this.textBoxTitlu.Location = new System.Drawing.Point(1330, 147);
            this.textBoxTitlu.Name = "textBoxTitlu";
            this.textBoxTitlu.Size = new System.Drawing.Size(244, 31);
            this.textBoxTitlu.TabIndex = 2;
            // 
            // textBoxAn
            // 
            this.textBoxAn.Location = new System.Drawing.Point(1330, 233);
            this.textBoxAn.Name = "textBoxAn";
            this.textBoxAn.Size = new System.Drawing.Size(244, 31);
            this.textBoxAn.TabIndex = 3;
            // 
            // textBoxDurata
            // 
            this.textBoxDurata.Location = new System.Drawing.Point(1330, 337);
            this.textBoxDurata.Name = "textBoxDurata";
            this.textBoxDurata.Size = new System.Drawing.Size(244, 31);
            this.textBoxDurata.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(1206, 150);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 25);
            this.label1.TabIndex = 5;
            this.label1.Text = "titlu";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(1160, 233);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(113, 25);
            this.label2.TabIndex = 6;
            this.label2.Text = "an lansare";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(1160, 337);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(73, 25);
            this.label3.TabIndex = 7;
            this.label3.Text = "durata";
            // 
            // buttonAdd
            // 
            this.buttonAdd.Location = new System.Drawing.Point(1321, 454);
            this.buttonAdd.Name = "buttonAdd";
            this.buttonAdd.Size = new System.Drawing.Size(149, 54);
            this.buttonAdd.TabIndex = 8;
            this.buttonAdd.Text = "ADD";
            this.buttonAdd.UseVisualStyleBackColor = true;
            this.buttonAdd.Click += new System.EventHandler(this.ButtonAdd_Click);
            // 
            // buttonDelete
            // 
            this.buttonDelete.Location = new System.Drawing.Point(1484, 781);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(122, 44);
            this.buttonDelete.TabIndex = 9;
            this.buttonDelete.Text = "DELETE";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.Click += new System.EventHandler(this.ButtonDelete_Click);
            // 
            // buttonUpdate
            // 
            this.buttonUpdate.Location = new System.Drawing.Point(1484, 934);
            this.buttonUpdate.Name = "buttonUpdate";
            this.buttonUpdate.Size = new System.Drawing.Size(122, 46);
            this.buttonUpdate.TabIndex = 10;
            this.buttonUpdate.Text = "UPDATE";
            this.buttonUpdate.UseVisualStyleBackColor = true;
            this.buttonUpdate.Click += new System.EventHandler(this.ButtonUpdate_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1710, 1216);
            this.Controls.Add(this.buttonUpdate);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.buttonAdd);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxDurata);
            this.Controls.Add(this.textBoxAn);
            this.Controls.Add(this.textBoxTitlu);
            this.Controls.Add(this.dataGridViewChild);
            this.Controls.Add(this.dataGridViewParent);
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
        private System.Windows.Forms.TextBox textBoxTitlu;
        private System.Windows.Forms.TextBox textBoxAn;
        private System.Windows.Forms.TextBox textBoxDurata;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button buttonAdd;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.Button buttonUpdate;
    }
}

