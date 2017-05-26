//https://wiki.libsdl.org/SDLScancodeLookup

var rows = document.querySelectorAll("table")[1].querySelectorAll("tr")
var string = "enum Keys\n{\n";

for(let i = 1; i < rows.length; i++)
{
  let value = rows[i].children[0].children[1].innerText;
  let name = rows[i].children[2].children[0].innerText.slice(13);
  let num =  " " + name + " = " + value + ",\n";
  string += num;
}

string += "}";
string