namespace lab1
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.dataGridViewParent = new System.Windows.Forms.DataGridView();
            this.dataGridViewChild = new System.Windows.Forms.DataGridView();
            this.labelParent = new System.Windows.Forms.Label();
            this.labelChild = new System.Windows.Forms.Label();
            this.labelMessageToUser = new System.Windows.Forms.Label();
            this.buttonAdauga = new System.Windows.Forms.Button();
            this.buttonSterge = new System.Windows.Forms.Button();
            this.buttonActualizeaza = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewParent)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewChild)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewParent
            // 
            this.dataGridViewParent.BackgroundColor = System.Drawing.Color.MistyRose;
            this.dataGridViewParent.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            resources.ApplyResources(this.dataGridViewParent, "dataGridViewParent");
            this.dataGridViewParent.Name = "dataGridViewParent";
            this.dataGridViewParent.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewCellClickedParent);
            // 
            // dataGridViewChild
            // 
            this.dataGridViewChild.BackgroundColor = System.Drawing.Color.MistyRose;
            this.dataGridViewChild.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            resources.ApplyResources(this.dataGridViewChild, "dataGridViewChild");
            this.dataGridViewChild.Name = "dataGridViewChild";
            this.dataGridViewChild.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewCellChildrenClicked);
            // 
            // labelParent
            // 
            resources.ApplyResources(this.labelParent, "labelParent");
            this.labelParent.Name = "labelParent";
            // 
            // labelChild
            // 
            resources.ApplyResources(this.labelChild, "labelChild");
            this.labelChild.Name = "labelChild";
            // 
            // labelMessageToUser
            // 
            resources.ApplyResources(this.labelMessageToUser, "labelMessageToUser");
            this.labelMessageToUser.Name = "labelMessageToUser";
            // 
            // buttonAdauga
            // 
            this.buttonAdauga.BackColor = System.Drawing.Color.MediumOrchid;
            resources.ApplyResources(this.buttonAdauga, "buttonAdauga");
            this.buttonAdauga.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonAdauga.Name = "buttonAdauga";
            this.buttonAdauga.UseVisualStyleBackColor = false;
            this.buttonAdauga.Click += new System.EventHandler(this.addbtn_Click);
            // 
            // buttonSterge
            // 
            this.buttonSterge.BackColor = System.Drawing.Color.MediumOrchid;
            resources.ApplyResources(this.buttonSterge, "buttonSterge");
            this.buttonSterge.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonSterge.Name = "buttonSterge";
            this.buttonSterge.UseVisualStyleBackColor = false;
            this.buttonSterge.Click += new System.EventHandler(this.deletebtn_Click);
            // 
            // buttonActualizeaza
            // 
            this.buttonActualizeaza.BackColor = System.Drawing.Color.MediumOrchid;
            resources.ApplyResources(this.buttonActualizeaza, "buttonActualizeaza");
            this.buttonActualizeaza.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonActualizeaza.Name = "buttonActualizeaza";
            this.buttonActualizeaza.UseVisualStyleBackColor = false;
            this.buttonActualizeaza.Click += new System.EventHandler(this.updatebtn_Click);
            // 
            // label1
            // 
            this.label1.AllowDrop = true;
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            this.label1.UseCompatibleTextRendering = true;
            // 
            // label2
            // 
            resources.ApplyResources(this.label2, "label2");
            this.label2.Name = "label2";
            // 
            // Form1
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FloralWhite;
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.buttonActualizeaza);
            this.Controls.Add(this.buttonSterge);
            this.Controls.Add(this.buttonAdauga);
            this.Controls.Add(this.labelMessageToUser);
            this.Controls.Add(this.labelChild);
            this.Controls.Add(this.labelParent);
            this.Controls.Add(this.dataGridViewChild);
            this.Controls.Add(this.dataGridViewParent);
            this.Name = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewParent)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewChild)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewParent;
        private System.Windows.Forms.DataGridView dataGridViewChild;
        private System.Windows.Forms.Label labelParent;
        private System.Windows.Forms.Label labelChild;
        private System.Windows.Forms.Label labelMessageToUser;
        private System.Windows.Forms.Button buttonAdauga;
        private System.Windows.Forms.Button buttonSterge;
        private System.Windows.Forms.Button buttonActualizeaza;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}

