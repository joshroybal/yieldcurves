function AddStyle()
{  
   var stylesheet = document.getElementById("stylesheet");
   stylesheet.innerHTML = "<link rel='stylesheet' media='all' type='text/css' href='/includes/gradienttable.css'/>";

   var yieldTable = document.getElementById("yieldTable");
   yieldTable.classList.add("gradienttable");
   var headers = document.getElementsByTagName("th");
   var data_cells = document.getElementsByTagName("td");

   yieldTable.classList.add("gradienttable");
}

window.onload = AddStyle;
