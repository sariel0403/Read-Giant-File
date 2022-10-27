using System.Text;

namespace ReadGiantTextFile
{
    public partial class Form1 : Form
    {
        List<string> chunkList;
        public Form1()
        {
            chunkList = new List<string>();
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "All Files (*.*)|*.*";
            openFileDialog.FilterIndex = 1;
            if(openFileDialog.ShowDialog() != DialogResult.OK) return;
            string strDataLine;
            chunkList.Clear();
            using (StreamReader srStreamRdr = new StreamReader(openFileDialog.FileName))
            {
                int count = 0;
                string chunk = "";
                while ((strDataLine = srStreamRdr.ReadLine()) != null)
                {
                    count++;
                    chunk += strDataLine + "\r\n";
                    if(count == 9216)
                    {
                        count = 0;
                        chunkList.Add(chunk);
                        chunk = "";
                    }
                }
            }
            MessageBox.Show("Read Success!");
        }
        private void ChunkFunction(string str, int index)
        {
            string fileName = @"D:\Chunk" + index + ".txt";

            try
            {
                // Check if file already exists. If yes, delete it.     
                if (File.Exists(fileName))
                {
                    File.Delete(fileName);
                }

                // Create a new file     
                using (FileStream fs = File.Create(fileName))
                {
                    // Add some text to file    
                    Byte[] data = new UTF8Encoding(true).GetBytes(str);
                    fs.Write(data, 0, data.Length);
                }

            }
            catch (Exception Ex)
            {
                MessageBox.Show(Ex.ToString());
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            for(int i = 0; i < chunkList.Count; i++)
            {
                ChunkFunction(chunkList[i], i);
            }
            MessageBox.Show("Run Success! Please Check Disk D.");
        }
    }
}