open System
open System.IO

let lines = File.ReadAllLines("gen.ged")

lines |> Seq.iter (fun item ->
if item.Contains("0 @I")
then item.Substring(3, 7) |> printfn "%A")