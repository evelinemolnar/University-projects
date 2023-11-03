namespace lab1
{
    partial class FormAdaugare
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
            this.labelId = new System.Windows.Forms.Label();
            this.buttonAdauga = new System.Windows.Forms.Button();
            this.panel = new System.Windows.Forms.FlowLayoutPanel();
            this.SuspendLayout();
            // 
            // labelId
            // 
            this.labelId.AutoSize = true;
            this.labelId.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.125F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelId.Location = new System.Drawing.Point(180, 9);
            this.labelId.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.labelId.Name = "labelId";
            this.labelId.Size = new System.Drawing.Size(446, 31);
            this.labelId.TabIndex = 16;
            this.labelId.Text = "Adaugare entitate cu id-ul parintelui ";
            // 
            // buttonAdauga
            // 
            this.buttonAdauga.BackColor = System.Drawing.Color.MediumOrchid;
            this.buttonAdauga.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonAdauga.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonAdauga.Location = new System.Drawing.Point(247, 794);
            this.buttonAdauga.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.buttonAdauga.Name = "buttonAdauga";
            this.buttonAdauga.Size = new System.Drawing.Size(314, 68);
            this.buttonAdauga.TabIndex = 9;
            this.buttonAdauga.Text = "Adauga";
            this.buttonAdauga.UseVisualStyleBackColor = false;
            this.buttonAdauga.Click += new System.EventHandler(this.ButtonAdauga_Click);
            // 
            // panel
            // 
            this.panel.Location = new System.Drawing.Point(120, 58);
            this.panel.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.panel.Name = "panel";
            this.panel.Size = new System.Drawing.Size(558, 600);
            this.panel.TabIndex = 20;
            // 
            // FormAdaugare
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.OldLace;
            this.ClientSize = new System.Drawing.Size(786, 916);
            this.Controls.Add(this.panel);
            this.Controls.Add(this.buttonAdauga);
            this.Controls.Add(this.labelId);
            this.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.Name = "FormAdaugare";
            this.Text = "FormAdaugare";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label labelId;
        private System.Windows.Forms.Button buttonAdauga;
        private System.Windows.Forms.FlowLayoutPanel panel;
    }
}