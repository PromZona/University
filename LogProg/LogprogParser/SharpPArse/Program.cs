using System;
using System.IO;
using System.Collections.Generic;

namespace SharpPArse
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] file = File.ReadAllLines("gen.ged");
            List<string> keys = new List<string>();
            List<string> givn = new List<string>();
            List<string> surn = new List<string>();
            List<string> sex = new List<string>();
            List<string> husb = new List<string>();
            List<string> wife = new List<string>();
            List<string> chil = new List<string>();

            foreach (string a in file)
            {
                if (a.Contains("0 @I")) keys.Add(a[2..11]);
                if (a.Contains("GIVN")) givn.Add(a[7..]);
                if (a.Contains("SURN")) surn.Add(a[7..]);
                if (a.Contains("SEX")) sex.Add(a[6..]);
                if (a.Contains("HUSB")) husb.Add(a[7..]);
                if (a.Contains("WIFE")) wife.Add(a[7..]);
                if (a.Contains("CHIL")) chil.Add(a[7..]);
            }
            List<string> sexToFile = new List<string>();
            List<string> parentToFile = new List<string>();
            for (int i = 0; i < givn.Count; i++)
            {
                if (sex[i] == "M") sexToFile.Add("male('" + givn[i] + "', '" + surn[i] + "').");
                if (sex[i] == "F") sexToFile.Add("female('" + givn[i] + "', '" + surn[i] + "').");
            }
            sexToFile.Sort();
            File.WriteAllLines("main.pl", sexToFile.ToArray());
            for (int i = 0; i < husb.Count; i++)
            {
                string childName = givn[keys.IndexOf(chil[i])];
                string husbandName = givn[keys.IndexOf(husb[i])];
                string wifeName = givn[keys.IndexOf(wife[i])];
                parentToFile.Add("parent('" + childName + "', '" + husbandName + "').");
                parentToFile.Add("parent('" + childName + "', '" + wifeName + "').");
            }
            File.AppendAllLines("main.pl", parentToFile.ToArray());
        }
    }
}
