var nb_dropdown_click = 0;
function show_dropdown_list()
{

  var filter_parameter = document.getElementById("filter_parameter");
  filter_parameter.className = "parameter_content show_parameter_content";
  nb_dropdown_click += 1;

  var dropdown = document.getElementById("dropdownmenu");
  if(dropdown)
    dropdown.style.zIndex = "6";
}

window.onclick = function(event) {

  if (event.target.className != "fas fa-bars" || ( (nb_dropdown_click % 2) == 0) )
  {
    var dropdowns = document.getElementsByClassName("parameter_content");
    var i;
    for (i = 0; i < dropdowns.length; i++) {
      var openDropdown = dropdowns[i];
      if (openDropdown.classList.contains('show_parameter_content')) {
        openDropdown.classList.remove('show_parameter_content');
      }
    }
    nb_dropdown_click = 0;

    var dropdown = document.getElementById("dropdownmenu");
    if(dropdown)
      dropdown.style.zIndex = "4";
  }

}
var target = document.getElementById("target");
var data = target ? JSON.parse(target.getAttribute("data-ad-json")) : "";

function sortbyprice()
{
  // sessionStorage.setItem("needtosort", "byprice");
  // Sort data by price
  data.sort(function(lhs, rhs)
  {
    return lhs.PRICE - rhs.PRICE;
  });
  generate_summary_page(data, empty=true)
}

function sortbysurface()
{
  // sessionStorage.setItem("needtosort", "bysurface");
  // Sort data by surface
  data.sort(function(lhs, rhs)
  {
      return lhs.SURFACE - rhs.SURFACE;
  });
  generate_summary_page(data, empty=true)
}

function sortbydate()
{
  // sessionStorage.setItem("needtosort", "bydate");
  // Sort data by time
  data.sort(ByTimeStamp);
  generate_summary_page(data, empty=true)
}

function sortbypricebym2()
{
  // sessionStorage.setItem("needtosort", "bypricebym2");
  // Sort data by price and surface
  data.sort(function(lhs, rhs)
  {
    return Math.floor( lhs.PRICE / lhs.SURFACE) - Math.floor( rhs.PRICE / rhs.SURFACE);
  });
  generate_summary_page(data, empty=true)
}

