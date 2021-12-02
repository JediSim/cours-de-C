
function traiteData(json,id) {
    if(id=="test"){
        // Si on a appelé le chemin /q1
        document.getElementById(id).innerText = json;
    }
    else if(id=="q1"){
        // Si on a appelé le chemin /q1
        console.log("RATIO : ",json)
        a=parseInt(json[0].value)
        b=parseInt(json[1].value)
        console.log(a+" - "+b)
        data = {
            labels: [
              'Test on',
              'Test off'
            ],
            datasets: [{
              label: 'Personne ayant activé le mode test',
              data: [a,b],
              backgroundColor: [
                'rgb(255, 99, 132)',
                'rgb(54, 162, 235)'
                ],
              hoverOffset: 4
            }]
          };
        const myChart = new Chart(
            document.getElementById('prctTestOn'),
            {
                type:'pie',
                data:data,
            }
          );
}
}

var request = function(url, id) { 
    console.log("ask for distance")
    var xmlhttp = new XMLHttpRequest(); 
    xmlhttp.onreadystatechange = function() { 
        if (this.readyState == 4 && this.status == 200) { 
            traiteData(this.responseText,id)
        } 
    }; 
    xmlhttp.open("GET", url); 
    xmlhttp.send(); 
} 


request("./distance/chambery", "test"); 
request("./q1", "q1"); 